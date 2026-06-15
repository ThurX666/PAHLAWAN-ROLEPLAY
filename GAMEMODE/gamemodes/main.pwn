#define CGEN_MEMORY 40000
#define YSI_NO_HEAP_MALLOC

/* Includes */

#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS	500

#include <strlib>
#include <crashdetect>
#include <a_mysql>
#include <streamer>
#include <sscanf2>
#include <TimestampToDate>
#include <garageblock>
#include <samp_bcrypt>

#include <YSI_Coding\y_malloc>
#include <YSI_Coding\y_va>
#include <YSI_Server\y_colours>
#include <YSI_Visual\y_commands>
#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_timers>
#include <YSI_Extra\y_inline_mysql>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>
#include <YSI_Server\y_flooding>
#include <YSI_Coding\y_hooks>

#include <textdraw-streamer>
#include <mSelection>
#include <progress2>
#include <geoiplite>
#include <dini>
#include <EVF2>

#include <easyDialog>
#include <screen-colour-fader>

new bool:FactionVehHasCallsign[MAX_VEHICLES];

HOOKED_DestroyVehicle(&vehicleid)
{
    if(Iter_Contains(Vehicle, vehicleid))
    {
        CallLocalFunction("OnVehicleDestroyed", "i", vehicleid);

		FactionVehHasCallsign[vehicleid] = false;
		DestroyFactVehToys(vehicleid);

		DisableVehicleSpeedCap(vehicleid);

		new tersi = Vehicle_GetIterID(vehicleid);
		if(tersi != -1)
		{
			DestroyVehicleToys(tersi);
		}
        DestroyVehicle(vehicleid);
    }
	
    vehicleid = INVALID_VEHICLE_ID;
}

#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle HOOKED_DestroyVehicle

//files modular
#include "utils/utils"

//kendaraan admin
enum __serverInfo
{
	adminV[MAX_ADMIN_VEHICLES],
	bool:pNameTagShown,
	bool:Maintenance,
	MTTime,
	g_AdvertSentPublic,
	g_TotalAdverts,
	g_ComponentPrice,
	g_ComponentStock,

	bool:HalloweenEvent,
	bool:WinterEvent,

	bool:ShopRobberyOngoing,
	ShopRobberyCooldown,

	GInsuTime,

	bool:KonserStarted,
	KonserMusicLink[144],

	PDBCDJLink[144]
};
new GM[__serverInfo];

/* Enums */
enum e_player_data
{
	pID,
	pUCP[22],
	pRegisterDate[50],
	pLastLogin[50],
	pSSN,
	pName[MAX_PLAYER_NAME + 1],

	pBodyHeight,
	pBodyWeight,

	pAdminname[MAX_PLAYER_NAME + 1],
	pIP[16 + 1],
	pAdmin,
	bool:pApprentice,
	bool:pSteward,
	pStewardTime,
	pLevel,
	Float:pPos[4],
	Float:pHealth,
	Float:pArmor,
	pDirtyMoney,
	pMoney,
	pBankMoney,
	pBankNumber,
	pCasinoChip,
	pWorld,
	pInterior,
	pSkin,
	pUniform,
	pUsingClothes,
	pAge,
	pOrigin[64],
	pGender,
	pJob,
	pFightingStyle,
	
	bool:pGVL1Lic,
	pGVL1LicTime,

	bool:pGVL2Lic,
	pGVL2LicTime,

	bool:pMBLic,
	pMBLicTime,

	bool:pBLic,
	pBLicTime,

	bool:pAir1Lic,
	pAir1LicTime,

	bool:pAir2Lic,
	pAir2LicTime,

	bool:pFirearmLic,
	pFirearmLicTime,

	bool:pHuntingLic,
	pHuntingLicTime,

	//warn
	pWarn,

	//faction
	pFaction,
	pFactionRank,
	pBadge,

	bool:pOnDuty,

	//family
	pFamily,
	pFamilyRank,

	//arrest IC
	bool:pArrested,
	pArrestTime,

	//law community service
    pGivenComServBy,
    pGiveComServTo,
    pTotalComServed,
    pHowMuchComServing,
    bool:pCommunityService,

	//VIP
	pVIP,
	pVIPTime,

	//knock
	bool:pKnockdown,
	pKnockdownTime,
	bool:pComma,

	//check sedang di dalam sesuatu
	pInDoor,
	pInHouse,
	pInBiz,
	pInGas,
	pInStone,
	pInTree,

	//lapar haus
	pHunger,
	pThirst,
	pStress,

	pXmasGiftTime,

	//map setting
    Float:pRenderSetting,

	bool:pHasKTP,
	pKTPTime,
	bool:pEarphone,
	bool:pBoombox,
	bool:pHasHuntingRifle,

	pHasGudangID,
	pGudangRentTime,

	//delays
	pMowingSidejobDelay,
	pSweeperSidejobDelay,
	pForkliftSidejobDelay,
	pTrashCollectorDelay,
	pPizzaSidejobDelay,
	pTaxMinute,

	//shared key
	pHouseSharedID,

	bool:pTutorialPassed,

	pHours,
	pMinutes,
	pSeconds,
	pLoginTime,

	pPaycheckIndex,
	
	pSlipSalary,

	pWaterInBucket,
	
	//NOT SAVE
	pTempChip,

	bool:pBuckledOn,

	bool:pBlindfolded,

	bool:pIsFallFromInterior,
	pEditModshopStatus,
	
	bool:pLivestreamMode,
	pLivestreamTitle[144],

	pHoldingCrateType,
	bool:pHoldingSledge,
	pHoldingOreType,

	bool:pFlareUsed,
	STREAMER_TAG_OBJECT:pFlareObjid,
	STREAMER_TAG_MAP_ICON:pFlareIcon[MAX_PLAYERS],

	STREAMER_TAG_MAP_ICON:pSignalIcon,
	
	bool:pUsingJoint,

	pESharedType,
	pESharedOfferer,
	
	bool:pDuringUseLocalMedic,

	pDelayKnockdownSignalSent,

	bool:pToggleNameID,
	STREAMER_TAG_3D_TEXT_LABEL:pNameIDLabel[MAX_PLAYERS],

	pRaceEventStep,

	bool:pHoldingSkate,
	bool:pSkating,

	bool:pHoldFlashlight,
	bool:pFlashlightOn,

	pCountry[MAX_COUNTRY_LENGTH],
	pCity[MAX_CITY_LENGTH],

	pTypeDisphone,
	bool:pUsedDisphone,
	pWaitingDisphone,
	STREAMER_TAG_OBJECT:pDTOObject,
	STREAMER_TAG_3D_TEXT_LABEL:pDTOLabel,

	STREAMER_TAG_RACE_CP:UberRCP,

	pAppearance[144],

	pEatingIndexID,
	pEatingStep,
	pDrinkingStep,

	bool:pTortured,
	bool:pTeleported,
	
	pAdvertDelay,
	
	//AFK check
    bool:pIsAFK,
    pAFKCount,
    pAFKTime,
    pAFKNumb,
    Float:afkx,
    Float:afky,
    Float:afkz,

	bool:pEatingDrinking,
	STREAMER_TAG_OBJECT:PoliceConeObjid,

    STREAMER_TAG_OBJECT:PoliceSpikeObjid,
    STREAMER_TAG_AREA:PoliceSpikeArea,

    STREAMER_TAG_OBJECT:PoliceRoadblockObjid,
	bool:LSFDDuringReviving,

	pAccDeathTime,
	pStuckRequest,
	pStuckWaiting,

	pVersion[24],

	bool:pVoted,
	
	bool:pInEvent,
	bool:pShowFooter,
	pFooterTimer,

	bool:pKillEffectTDShown,
	pKillEffectTimer,

	bool:pShowWarnTD,
	pWarnTDTimer,

	pQBRobbery,
	pABRobbery[128],

	pACWarns,

	bool:pHasArmor,
	bool:pArmorEmpty,

	pDragOffer,
	
	bool:pMenuShowed,
	bool:pTurningEngine,

	pIdlingTime,
	Float:idlex,
	Float:idley,
	Float:idlez,

	bool:pHiddenAdmin,

	pDuringConsficatingMeat,
	
	pSideJob,

	pMechTempComp1,
	pMechTempComp2,

	bool:pIsSmoking,
	bool:pIsSmokeBlowing,
	pSmokedTimes,

	p911Hotline,
	pMekHotline,
	pPdgHotline,
	pDinarHotline,
	pPemdaHotline,

	bool:pTaser,
	pTazedTime,
	bool:pUseBeanbag,
	pBeanbagTime,
	bool:pTackleEnable,
	pTackleTime,

	pStressedTime,

	LoginAttempts,
	
	bool:IsLoggedIn,

	bool:pHasSharedGPS,
	STREAMER_TAG_MAP_ICON:pSharedGPSIcon,

	STREAMER_TAG_MAP_ICON:g_CarstealIcon[MAX_PLAYERS],

	//report ask
	pAskTime,
	pReportTime,

	DraggingID,
	pGetDraggedBy,
	bool:pDetained,

	//hbe
	pHungerTime,
	pThirstTime,
	pStressTime,

	bool: pCuffed,
	bool: pTied,
	
	STREAMER_TAG_3D_TEXT_LABEL:pAdoTag,
	bool: pAdoActive,

	bool:pSpawned,
	pChar,

	//animchat
    bool:pChatAnim,

	//freeze
	bool:pFreeze,

	bool:pShowNotifBox,

	//activity
	Float:pActivityTime,
	Float:pInfoTimeTD,
	Float:pSuccessTimeTD,
	Float:pErrorTimeTD,
	Float:pSyntaxTimeTD,
	Float:pWarningTimeTD,

	//robbery
	bool:pDuringRobbery,
	pInRobberyID,
	STREAMER_TAG_MAP_ICON:pSignalRobberyIcon[MAX_PLAYERS],

	bool:pDuringBRobbery,

	//carsteal
	bool:pDuringCarsteal,
	STREAMER_TAG_3D_TEXT_LABEL:pCarstealLabel,
	STREAMER_TAG_3D_TEXT_LABEL:pCarstealLabelPart,
	bool:pCarstealHoldingPart,
	STREAMER_TAG_CP:pCarstealStoringCP,

	//toys
	pToySelected,
	bool:pIsToyInsertedOnMysql,

	//modshop slot id
	EditingModshopSlotID,

	//blackjack id
	EditingTableBJID,
	
	//newspaper stand
	EditingNewsStandID,
	
	//vending
	EditingVendingID,

	//craft table
	EditingCraftTableID,

	//graffitti
	EditingGraffitiID,
	
	//tree
	EditingTreeID,
	
	//ore
	EditingOreID,
	
	//xmas
	EditingXmasTreeID,

	//rsign
	EditingRSignID,

	//speed cam
	EditingSCamID,

	//garbage
	EditingGarbageID,

	//fivem label
	EditingFLabelID,

	//weed editing
	EditingKanabisID,

	//robbery editing
	EditingRobberyID,

	//button
	EditingButton,
	EditingButtonID,

	//atm
	EditingAtmID,

	//deer
	EditingDeerID,

	pSpec,
	bool:pSPY,

	//admin
	bool: pAdminDuty,

	bool: pIsUsingUniform,

	//counting item
	pCountingValue,
	
	//garkot check
	pInGarkot,

	//bike rent check
	pInRent,

	//rusun check
	pInRusun,

	//gudang check
	pInGudang,

	//weed check
	pInCannabis,

	//plant check
	pInPlant,

	//inventory system
	pSelectItem,
	pInventTargetID,
	pItemQuantity,

	//gps
	bool:pUsingGPS,
	
	//refuel
	bool:pDuringRefueling,
	bool:pHoldingFuelCan,
	pRefuelingPrice,

	//playertimer

	AntiBHOP,

	//atm temp
	pTempTransferID,
	pTempSellerID,
	pTempSellPrice,
	pTempSellIterID,

	//sql db temp
	pTempSQLFactMemberID,
	pTempSQLFactRank,
	pTempSQLImpoundID,
	pTempSQLImpoundVID,

	pTempValue,
	pTempValue2,

	//temp veh
	pTempVehID,
	pTempVehIterID,
	STREAMER_TAG_RACE_CP:pGPSCP,
	STREAMER_TAG_RACE_CP:pCarstealRCP,

	bool:pCharSelected,

	pPumpkins,

	pDevice,
	bool:pInLoginBox,
	bool:pInVerifyCode,
	bool:pInResetPassword,
	pTempPassword[64]
};

new AccountData[MAX_PLAYERS][e_player_data];

new gpsZone;

//Files Modular setelah yang atas
#include "core/gmcore"

main()
{
	print("|----------------------------------|");
	print("| Pahlawan Roleplay | NEW GAMEMODE |");
	print("|----------------------------------|");
}

public OnGameModeInit()
{
	Database_Connect();

	SetWorldTime(WorldTime);
	SetWeather(WorldWeather);

	mysql_tquery(g_SQL, "SELECT * FROM `doors`", "LoadDoors");
	mysql_tquery(g_SQL, "SELECT * FROM `garbages`", "LoadGarbages");
	mysql_tquery(g_SQL, "SELECT * FROM `shops`", "LoadShops");
	mysql_tquery(g_SQL, "SELECT * FROM `biz`", "LoadBizes");
	mysql_tquery(g_SQL, "SELECT * FROM `fivem_labels`", "LoadFivemLabelText");
	mysql_tquery(g_SQL, "SELECT * FROM `public_garages`", "LoadPublicGarages");
	mysql_tquery(g_SQL, "SELECT * FROM `rentals`", "LoadRentals");
	mysql_tquery(g_SQL, "SELECT * FROM `actors`", "LoadActors");
	mysql_tquery(g_SQL, "SELECT * FROM `atms`", "LoadAtms");
	mysql_tquery(g_SQL, "SELECT * FROM `bankpoints`", "LoadBankPoints");
	mysql_tquery(g_SQL, "SELECT * FROM `vendings`", "LoadVendings");
	mysql_tquery(g_SQL, "SELECT * FROM `robberies`", "LoadRobberies");
	mysql_tquery(g_SQL, "SELECT * FROM `mapicons`", "LoadMapIcons");
	mysql_tquery(g_SQL, "SELECT * FROM `houses`", "LoadHouses");
	mysql_tquery(g_SQL, "SELECT * FROM `rusun`", "LoadRusun");
	mysql_tquery(g_SQL, "SELECT * FROM `gudang`", "LoadGudang");
	mysql_tquery(g_SQL, "SELECT * FROM `basement`", "LoadBasement");
	mysql_tquery(g_SQL, "SELECT * FROM `buttons`", "LoadButtons");
	mysql_tquery(g_SQL, "SELECT * FROM `kanabis`", "LoadKanabis");
	mysql_tquery(g_SQL, "SELECT * FROM `dynamic_deer`", "LoadDeers");
	mysql_tquery(g_SQL, "SELECT * FROM `xmas_trees`", "LoadXmasTrees");
	mysql_tquery(g_SQL, "SELECT * FROM `families`", "LoadFamilies");
	mysql_tquery(g_SQL, "SELECT * FROM `dropped_items`", "LoadDropped");
	mysql_tquery(g_SQL, "SELECT * FROM `lockers`", "LoadLockers");
	mysql_tquery(g_SQL, "SELECT * FROM `fcrafts`", "LoadFCrafts");
	mysql_tquery(g_SQL, "SELECT * FROM `armouries`", "LoadArmouries");
	mysql_tquery(g_SQL, "SELECT * FROM `vaults`", "LoadVaults");
	mysql_tquery(g_SQL, "SELECT * FROM `faction_garages`", "LoadFGarages");
	mysql_tquery(g_SQL, "SELECT * FROM `roadsigns`", "LoadRSign");
	mysql_tquery(g_SQL, "SELECT * FROM `speedcam`", "LoadSpeedCam");
	mysql_tquery(g_SQL, "SELECT * FROM `server_tags`", "LoadGraffities");
	//mysql_tquery(g_SQL, "SELECT * FROM `crafttables`", "LoadCraftTables");
	mysql_tquery(g_SQL, "SELECT * FROM `faction_brankas`", "LoadFactionBrankas");
	mysql_tquery(g_SQL, "SELECT * FROM `badside_brankas`", "LoadBadsideBrankas");
	mysql_tquery(g_SQL, "SELECT * FROM `bj_tables`", "LoadBJTables");
	mysql_tquery(g_SQL, "SELECT * FROM `stuffs`", "LoadServerStuffs");
	mysql_tquery(g_SQL, "SELECT * FROM `farmplants`", "LoadFarmPlants");

	new gmtxt[128];
	format(gmtxt, sizeof(gmtxt), "hostname %s", TEXT_HOSTNAME);
	SendRconCommand(gmtxt);
	format(gmtxt, sizeof(gmtxt), "%s", TEXT_GAMEMODE);
	SetGameModeText(gmtxt);
	format(gmtxt, sizeof(gmtxt), "weburl %s", TEXT_WEBURL);
	SendRconCommand(gmtxt);
	format(gmtxt, sizeof(gmtxt), "language %s", TEXT_LANGUAGE);
	SendRconCommand(gmtxt);
	SendRconCommand("mapname San Andreas");
	ManualVehicleEngineAndLights();
	EnableStuntBonusForAll(false);
	AllowInteriorWeapons(true);
	DisableInteriorEnterExits();
	LimitPlayerMarkerRadius(15.0);
	ShowNameTags(false);
	//SetNameTagDrawDistance(10.0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	SetMaxConnections(3, e_FLOOD_ACTION_FBAN);

	BlockGarages();

	CreateHBETextdraw();
	CreateInfoTextdraw();

	CreateKnockTextdraw();
	
	CreateAnnounceTD();

	CreateLockerRoomTD();

	//inventory
	CreateInventTD();
	CreateInventLine();

	CreateIDCTD();
	CreateLCTD();
	CreateKTATD();
	CreateBPJSTD();
	
	CreateProgbarTD();

	//CreateGYMTD();

	CreateClothesShopTD();
	CreateServerNameTD();
	CreateRadioVoiceTD();
	CreatePhoneLockScreenTD();
	CreatePhoneRebootTD();
	CreateUberPhoneTD();
	CreatePhoneMainMenuTD();
	CreatePhoneAppStoreTD();
	CreatePhoneContactTD();
	//CreateSpeedoTD();
	CreatePhoneSettingsTD();
	CreatePhoneSpotifyTD();
	CreateTwitterLoginTD();
	CreateTwitterMainTD();

	CreateCardealerTD();

	CreateStressTD();

	CreateATMTD();

	CreateRadialTD();
	CreateRadialFashionTD();
	CreateRadialVehTD();
	CreateRadialCardTD();

	CreateWarningTD();

	CreateModshopTD();

	CreateBlackjackTD();

	CreateTollTD();

	CreateEmotesTD();

	CreateJobCenterTD();
	
	CreateJobMixTD();

	CreateThurXProjectTD();
	CreateLoginBoxTD();
	CreateLoginScreenTD();
	CreateVerifyCodeTD();
	CreatePhoneHBE();
	//CreateNYCounterTD();

	Event_SGTD = TextDrawCreate(319.000000, 44.000000, "GREEN LIGHT");
	TextDrawFont(Event_SGTD, 1);
	TextDrawLetterSize(Event_SGTD, 0.400000, 2.000000);
	TextDrawTextSize(Event_SGTD, 400.000000, 108.000000);
	TextDrawSetOutline(Event_SGTD, 1);
	TextDrawSetShadow(Event_SGTD, 0);
	TextDrawAlignment(Event_SGTD, 2);
	TextDrawColor(Event_SGTD, -1);
	TextDrawBackgroundColor(Event_SGTD, 255);
	TextDrawBoxColor(Event_SGTD, 0x00FF00FF);
	TextDrawUseBox(Event_SGTD, 1);
	TextDrawSetProportional(Event_SGTD, 1);
	TextDrawSetSelectable(Event_SGTD, 0);
	
	BlindfoldTD = TextDrawCreate(-40.000000, 9.000000, "ld_dual:black");
	TextDrawFont(BlindfoldTD, 4);
	TextDrawLetterSize(BlindfoldTD, 0.600000, 2.000000);
	TextDrawTextSize(BlindfoldTD, 782.000000, 432.000000);
	TextDrawSetOutline(BlindfoldTD, 1);
	TextDrawSetShadow(BlindfoldTD, 0);
	TextDrawAlignment(BlindfoldTD, 1);
	TextDrawColor(BlindfoldTD, -1);
	TextDrawBackgroundColor(BlindfoldTD, 255);
	TextDrawBoxColor(BlindfoldTD, 50);
	TextDrawUseBox(BlindfoldTD, 1);
	TextDrawSetProportional(BlindfoldTD, 1);
	TextDrawSetSelectable(BlindfoldTD, 0);

	KillEffectTD = TextDrawCreate(-111.000000, -147.000000, "ld_dual:light");
	TextDrawFont(KillEffectTD, 4);
	TextDrawLetterSize(KillEffectTD, 0.600000, 2.000000);
	TextDrawTextSize(KillEffectTD, 855.000000, 775.500000);
	TextDrawSetOutline(KillEffectTD, 1);
	TextDrawSetShadow(KillEffectTD, 0);
	TextDrawAlignment(KillEffectTD, 1);
	TextDrawColor(KillEffectTD, -1105687914);
	TextDrawBackgroundColor(KillEffectTD, 255);
	TextDrawBoxColor(KillEffectTD, 50);
	TextDrawUseBox(KillEffectTD, 1);
	TextDrawSetProportional(KillEffectTD, 1);
	TextDrawSetSelectable(KillEffectTD, 0);

	GarbageHideTD[0] = TextDrawCreate(-3.000000, -5.000000, "ld_dual:black");
	TextDrawFont(GarbageHideTD[0], 4);
	TextDrawLetterSize(GarbageHideTD[0], 0.600000, 2.000000);
	TextDrawTextSize(GarbageHideTD[0], 662.000000, 197.000000);
	TextDrawSetOutline(GarbageHideTD[0], 1);
	TextDrawSetShadow(GarbageHideTD[0], 0);
	TextDrawAlignment(GarbageHideTD[0], 1);
	TextDrawColor(GarbageHideTD[0], -1);
	TextDrawBackgroundColor(GarbageHideTD[0], 255);
	TextDrawBoxColor(GarbageHideTD[0], 50);
	TextDrawUseBox(GarbageHideTD[0], 1);
	TextDrawSetProportional(GarbageHideTD[0], 1);
	TextDrawSetSelectable(GarbageHideTD[0], 0);

	GarbageHideTD[1] = TextDrawCreate(-3.000000, 393.000000, "ld_dual:black");
	TextDrawFont(GarbageHideTD[1], 4);
	TextDrawLetterSize(GarbageHideTD[1], 0.600000, 2.000000);
	TextDrawTextSize(GarbageHideTD[1], 662.000000, 197.000000);
	TextDrawSetOutline(GarbageHideTD[1], 1);
	TextDrawSetShadow(GarbageHideTD[1], 0);
	TextDrawAlignment(GarbageHideTD[1], 1);
	TextDrawColor(GarbageHideTD[1], -1);
	TextDrawBackgroundColor(GarbageHideTD[1], 255);
	TextDrawBoxColor(GarbageHideTD[1], 50);
	TextDrawUseBox(GarbageHideTD[1], 1);
	TextDrawSetProportional(GarbageHideTD[1], 1);
	TextDrawSetSelectable(GarbageHideTD[1], 0);

	for(new i; i < MAX_ADMIN_VEHICLES; i++)
	{
		DestroyVehicle(GM[adminV][i]);
		GM[adminV][i] = INVALID_VEHICLE_ID;
	}
	
	GM[Maintenance] = false;
	GM[MTTime] = 0;
	GM[HalloweenEvent] = false;
	GM[WinterEvent] = false;
	
	GM[ShopRobberyOngoing] = false;
	GM[ShopRobberyCooldown] = 0;
	ResetEvent();

	ObjRSign = LoadModelSelectionMenu("objrsign.txt");
	ModshopModel = LoadModelSelectionMenu("vtoylist.txt");

	if(gpsZone != INVALID_GANG_ZONE)
    {
        GangZoneDestroy(gpsZone);
        gpsZone = INVALID_GANG_ZONE;
    }

    gpsZone = GangZoneCreate(-20000.0000, -20000.0000, 20000.0000, 20000.0000);
	return 1;
}

public OnGameModeExit()
{
	//OnServerOffline();
	foreach(new id : FarmPlants) if(id != INVALID_ITERATOR_SLOT)
	{
		FarmPlant_Save(id);
	}
	
	foreach(new plyid : Player)
	{
		if(!IsPlayerConnected(plyid))
		{
			OnPlayerDisconnect(plyid, 1);
		}
	}
	mysql_close(g_SQL);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	if(!AccountData[killerid][IsLoggedIn] || !AccountData[killerid][pSpawned]) return Kick(killerid);
	foreach(new i : Player)
	{
		if(vehicleid == EventVehicle[i])
		{
			DestroyVehicle(EventVehicle[i]);
			
			ResetPlayerWeapons(i);

			if(Iter_Contains(EvBlueTeam, i))
				Iter_Remove(EvBlueTeam, i);
			
			if(Iter_Contains(EvRedTeam, i))
				Iter_Remove(EvRedTeam, i);

			if(Iter_Contains(EvHumanTeam, i))
				Iter_Remove(EvHumanTeam, i);
			
			if(Iter_Contains(EvZombieTeam, i))
				Iter_Remove(EvZombieTeam, i);
			
			if(Iter_Contains(InEvent, i))
				Iter_Remove(InEvent, i);

			LeaveEvent(i);

			SendClientMessage(i, -1, "[OOC Event] Anda dieleminasi dari event karena merusakkan kendaraan.");

			foreach(new a : InEvent)
			{
				SendClientMessageEx(a, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"got wrecked.", AccountData[i][pName]);
			}
		}
	}
	
	foreach(new vid : PvtVehicles)
	{
		if(vehicleid == PlayerVehicle[vid][pVehPhysic])
		{
			SendClientMessageEx(GetVehicleOwnerID(vid), -1, "Kendaraan "CYAN"%s "WHITE"milikmu dihancurkan oleh "YELLOW"%s(%d).", GetVehicleModelName(GetVehicleModel(PlayerVehicle[vid][pVehPhysic])), AccountData[killerid][pName], killerid);
			
			if(IsVehicleInWater(PlayerVehicle[vid][pVehPhysic]))
            {
                PlayerVehicle[vid][pVehInsuranced] = true;
            }
            else 
            {
				PlayerVehicle[vid][pVehInsuranced] = false;
            }
		}
	}
	
	if(IsVehicleInWater(vehicleid))
	{
		// kasih variable masukin insu
		VehicleCore[vehicleid][vIsDeath] = true;
	}
	else
	{
		// gausah kasih variable masukin insu
		VehicleCore[vehicleid][vIsDeath] = false;
	}
	return 1;
}

public OnVehicleDestroyed(vehicleid)
{
	return 1;
}

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success)
{
	if (GetTickCount() - AC_CMDSpamTime[playerid] < 777)
    {
		ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon tunggu, jangan spam command!");
		Command_SetDeniedReturn(true);
		return COMMAND_DENIED;
	}

	AC_CMDSpamTime[playerid] = GetTickCount();

	if(strfind(cmdtext, "tb.", true) != -1)
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion TrollBoss!");
        KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	if(!strcmp(cmdtext, "/tr", true))
    {
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Cheat Slap!");
        KickEx(playerid);
        Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
    }

	else if(!strcmp(cmdtext, "/menu", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Cleo Menu!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/invisible", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Invisible!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/invis", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Invisible!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/marker", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Marker Teleport!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/rem", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion REM.cs!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/fcrash", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Crasher.luac!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/fspawn", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion FSpawn.cs!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/be", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion FSpawn.cs!");
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/xray", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Wallhack!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/kill", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Kill.cs!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/gunspawn", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Gun Spawn!");
		SetWeapons(playerid);
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/whack", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Gun Spawn!");
		SetWeapons(playerid);
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/dgun", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Gun Spawn!");
		SetWeapons(playerid);
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/pgun", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Gun Spawn!");
		SetWeapons(playerid);
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/xgun", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Gun Spawn!");
		SetWeapons(playerid);
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/skema", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Skema!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/sekema", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Skema!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/cboom", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion CBoom!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/fdeath", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Fake Death/Fake Kill!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/fkill", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Fake Death/Fake Kill!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/intoarce", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Cheat Troll!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/co", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Cheat Troll!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/zboara", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Cheat Troll!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/bubule", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Cheat Troll!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/reconnect", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Fake Client!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/recon", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Fake Client!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/name", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Fake Client!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/connect", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Fake Client!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/disconnect", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Fake Client!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/massban", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Massive Ban!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/massiveban", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Massive Ban!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/maprecord", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Map Stealer!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	else if(!strcmp(cmdtext, "/mapinfo", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Map Stealer!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}
	
	else if(!strcmp(cmdtext, "/mapsave", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Map Stealer!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/mapstealer", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Map Stealer!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	else if(!strcmp(cmdtext, "/mapsteal", true))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Map Stealer!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

	if(success != COMMAND_OK)
    {
		ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Perintah tidak diketahui '%s' gunakan '/help' untuk info lanjut!", cmdtext));
		Command_SetDeniedReturn(true);
        return COMMAND_OK;
    }

	if(!AVC_PConnected[playerid])
	{
        SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server due to access CMD without logged in!");
		KickEx(playerid);
		Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
	}

    if(!AccountData[playerid][IsLoggedIn])
    {
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus login atau spawn sebelum menggunakan CMD!");
        Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
    }
	
    if(!AccountData[playerid][pSpawned])
    {
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus login atau spawn sebelum menggunakan CMD!");
        Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
    }

    if(AccountData[playerid][pActivityTime] != 0)
    {
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang melakukan sesuatu, mohon tunggu!");
        Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
    }
    return COMMAND_OK;
}

public OnIncomingConnection(playerid, ip_address[], port)
{
	if(IsPlayerNPC(playerid)) 
	{
        Ban(playerid);
    }
	return 1;
}

public OnPlayerConnect(playerid)
{
	OnLoadSelectCharTD(playerid);
	OnLoadSelectSpawnTD(playerid);
	ShowLoginScreenTD(playerid);
	HideThurXProjectTD(playerid);
	CreatePlayerLoginBoxTD(playerid);
	CreatePlayerVerifyCodeTD(playerid);
	PlayAudioStreamForPlayer(playerid, "http://127.0.0.1/pahlawan_roleplay/music/Epic_Nuswantoro_(Medley).mp3");
	AccountData[playerid][pTempPassword] = EOS;

	g_MysqlRaceCheck[playerid]++;

	if(IsPlayerNPC(playerid)) 
	{
        Ban(playerid);
        return 0;
    }

	ResetVariables(playerid);
	
	//PlayAudioStreamForPlayer(playerid, "http://103.178.153.173/mbsai.mp3");

	CreateHBEProgressBarTD(playerid);
	CreateInfoTextDrawPlayer(playerid);

	CreateInventWeightTD(playerid);
	CreateInventBoxItemTD(playerid);
	CreateInventNameItemTD(playerid);
	CreateInventPrevModTD(playerid);
	CreateInventQuantTD(playerid);

	CreateKnockPlayerTD(playerid);
	CreatePlayerIDCTD(playerid);
	CreatePlayerLCTD(playerid);
	CreatePlayerKTATD(playerid);
	CreatePBPJSTD(playerid);
	
	CreateProgressBarTD(playerid);

	CreateClothesShopIndexTD(playerid);
	CreateRobberyTD(playerid);
	//CreateRadioVoiceInfoTD(playerid);
	CreateRadioVoiceFreqTD(playerid);
	CreatePhoneIncomingTD(playerid);
	CreatePhoneBankingTD(playerid);
	//CreatePlayerSpeedoTD(playerid);
	CreatePlayerTwitterTD(playerid);
	CreatePlayerUberTD(playerid);
	CreatePlayerRebootTD(playerid);

	CreateCarDealerPTD(playerid);

	CreateATMPTD(playerid);

	CreateFooterTD(playerid);

	CreateWarningPlayerTD(playerid);

	CreateEmotesPTD(playerid);

	CreatePlayerJMixTD(playerid);

	SetPlayerColor(playerid, 0x7F7F83FF);

	AccountData[playerid][pCarstealLabel] = CreateDynamic3DTextLabel(""LIGHTGREEN"Gangster: "WHITE"Apa kau ingin melakukan tugas dariku?\n\
    Jika kau berani melakukannya maka akan kuberi bayaran yang setimpal.\n"YELLOW"CMD: "WHITE"/carsteal", Y_WHITE, 930.9570,2065.1104,10.8203+1.5, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, playerid, 5.0, -1, 0);

	for(new gp; gp < sizeof(__g_GasPumpLoc); gp++)
	{
		g_GasPumpLabel[playerid][gp] = CreateDynamic3DTextLabel("Tekan "GREEN"Y "WHITE"untuk membeli jerigen\nHarga: "GREEN"$1,200", Y_WHITE, __g_GasPumpLoc[gp][0], __g_GasPumpLoc[gp][1], __g_GasPumpLoc[gp][2], 1.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, playerid, 1.5, -1, 0);
	}

	GetPlayerIp(playerid, AccountData[playerid][pIP], 17);
	GetPlayerName(playerid, AccountData[playerid][pUCP], MAX_PLAYER_NAME); //udah dapat nama UCP nya

	if(isnull(AccountData[playerid][pUCP]))
	{
		Kick(playerid);
		return 0;
	}

	GetPlayerVersion(playerid, AccountData[playerid][pVersion], 24);
	if(strcmp(AccountData[playerid][pVersion], "0.3.7") != 0 && strcmp(AccountData[playerid][pVersion], "0.3.7-R3") != 0)
    {
        SendClientMessage(playerid, Y_RED, "[WARNING] CLIENT SA-MP ANDA TIDAK COCOK DENGAN SERVER KAMI! (GUNAKAN 0.3.7 ATAU 0.3.7-R3).");
        SendClientMessage(playerid, Y_RED, "[WARNING] GANTI CLIENT JIKA TERJADI MASALAH DAN GUNAKAN 0.3.7 atau 0.3.7-R3.");
    }
	
	AVC_PConnected[playerid] = false;

	for (new i = 0; i < 20; i++) SendClientMessage(playerid, -1, " ");
	SetTimerEx("SaveFirstSpawn", 1000, false, "i", playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	g_MysqlRaceCheck[playerid]++;

	if(IsPlayerInAnyVehicle(playerid))
        RemovePlayerFromVehicle(playerid);

	if(AccountData[playerid][IsLoggedIn])
	{
		if(AVC_PConnected[playerid])
		{
			UpdateAccountData(playerid);
			RemovePlayerVehicle(playerid);
			RemovePlayerFactionVehicle(playerid);
			RemovePlayerWeapons(playerid);

			if(PlayerPhoneData[playerid][phoneCallingWithPlayerID] != INVALID_PLAYER_ID)
			{
				CutCallingLine(playerid);
			}

			new g = Iter_Free(PeLabelExit), Float:x, Float:y, Float:z, lexst[200], reastr[54];
			switch(reason)
			{
				case 0: { strcopy(reastr, "Crash/Timeout"); }
				case 1: { strcopy(reastr, "Quit/Exit"); }
				case 2: { strcopy(reastr, "Kick/Banned"); }
			}

			GetPlayerPos(playerid, x, y, z);
			format(lexst, sizeof(lexst), "[%s | %s (%d)] has left the server.\nReason: [%s]", AccountData[playerid][pName], AccountData[playerid][pUCP], playerid, reastr);
			PlayerLabelExit[g] = CreateDynamic3DTextLabel(lexst, 0x89CFF0FF, x, y, z-0.3, 30, _, _, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
			Iter_Add(PeLabelExit, g);
			SetTimerEx("ResetLabelExit", 25000, false, "i", g);

			if(AccountData[playerid][pInEvent])
			{
				foreach(new i : InEvent)
				{
					SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"has left the event (%s).", AccountData[playerid][pName], reastr);
				}
			}
		}
	}
	ResetVariables(playerid);

	new repid = GetPlayerReportID(playerid);
	if(repid != INVALID_ITERATOR_SLOT)
		Report_Remove(repid);

	new askid = GetPlayerAskID(playerid);
	if(askid != INVALID_ITERATOR_SLOT)
		Ask_Remove(askid);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	if(IsPlayerNPC(playerid))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena tidak terdeteksi login. "YELLOW"(NPC OPRC)");
		return Kick(playerid);
	}

	//SetPlayerTime(playerid, WorldTime, 0);
	//SetPlayerWeather(playerid, WorldWeather);

	SetPlayerTime(playerid, 6, 0);
	SetPlayerWeather(playerid, 5);

	StartLoginTimeout(playerid);

	if(!pLoginSpawnLoaded[playerid] && !AccountData[playerid][IsLoggedIn])
	{
		pAllowSpawn[playerid] = true;
		pLoginSpawnLoaded[playerid] = true;

		SetSpawnInfo(playerid, NO_TEAM, 1, 1855.000000, -1590.000000, 31.000000, 0.0, 0, 0, 0, 0, 0, 0);
		SpawnPlayer(playerid);
	}

	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	if(!IsPlayerAdmin(playerid))
    {
       	ShowTDN(playerid, NOTIFICATION_ERROR, "Tombol ini telah dinonaktifkan!");
        return KickEx(playerid);
    }

	if(!AVC_PConnected[playerid])
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena tidak terdeteksi login. "YELLOW"[OPRS]");
		return KickEx(playerid);
	}
	return 1;
}

public OnPlayerSpawn(playerid)
{
	if(IsPlayerNPC(playerid))
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena tidak terdeteksi login. "YELLOW"(NPC OPS)");
		return KickEx(playerid);
	}

	// JIKA PLAYER TERDETEKSI BARU MASUK LOBBY SELEKSI KARAKTER
    if (InCharSelection[playerid] == true)
    {
		if(!pAllowSpawn[playerid] && !pLoginSpawnLoaded[playerid])
		{
			SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena terdeteksi Fake Spawn. "YELLOW"[OPS-LCS]");
			return KickEx(playerid);
		}

		if(pAllowSpawn[playerid])
			pAllowSpawn[playerid] = false;

        new vw = playerid + 1000;
        LobbyVirtualWorld[playerid] = vw;
        
        SetPlayerVirtualWorld(playerid, vw);
        SetPlayerInterior(playerid, 2); // Pindah ke interior lobby lu
        SetPlayerPos(playerid, 1855.000000, -1590.000000, 31.000000); // Taruh fisiknya di tengah ruangan
        
        TogglePlayerControllable(playerid, false); // BEKUKAN! Biar gak bisa jalan/jatuh dari map
		CancelSelectTextDraw(playerid); // Batalin textdraw select karakter yang muncul otomatis saat spawn
		
        if(pLoginTransitionTimer[playerid] == -1)
            HideThurXProjectTD(playerid);
        
        LastCharCam[playerid] = PlayerSelectCharTD[playerid];
        SetLobbySelectCharCamera(playerid, PlayerSelectCharTD[playerid]);
        
        CreateLobbyActor(playerid); // Pastikan fungsi ini membuat actor di interior 2 & VW khusus tadi
        Streamer_Update(playerid, -1);
        RefreshLobbyActorAnimations(playerid);

        if(pLoginTransitionTimer[playerid] == -1)
		    OnLoadLobbyRoom(playerid, vw);
        return 1; // RETURN 1 agar kode spawn game normal di bawahnya TIDAK IKUT BERJALAN!
    }

	if(pLoginSpawnLoaded[playerid] && !AccountData[playerid][IsLoggedIn])
	{
		if(!pAllowSpawn[playerid])
		{
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 2);
			SetPlayerPos(playerid, 1855.000000, -1590.000000, 31.000000);
			SetPlayerFacingAngle(playerid, 0.0);
			TogglePlayerControllable(playerid, false);
			CancelSelectTextDraw(playerid);
			return 1;
		}

		pAllowSpawn[playerid] = false;
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 2);
		SetPlayerPos(playerid, 1855.000000, -1590.000000, 31.000000);
		SetPlayerFacingAngle(playerid, 0.0);
		TogglePlayerControllable(playerid, false);
		CancelSelectTextDraw(playerid);
		return 1;
	}

	if(!AccountData[playerid][IsLoggedIn])
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena tidak terdeteksi login. "YELLOW"[OPS]");
		return KickEx(playerid);
	}

	if(GetPlayerSkin(playerid) == 0)
	{
		AccountData[playerid][pSkin] = 1;
		SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena menggunakan skin CJ "YELLOW"[OPS].");
		return KickEx(playerid);
	}

	if(!AVC_PConnected[playerid])
	{
		return Kick(playerid);
	}

	pAllowSpawn[playerid] = false;
	pLoginSpawnLoaded[playerid] = false;

	if(AccountData[playerid][pInEvent])
	{
		Anticheat[playerid][acImmunity] = gettime() + 5;

		ResetPlayerWeapons(playerid);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
			RemovePlayerAttachedObject(playerid, 0);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
			RemovePlayerAttachedObject(playerid, 1);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 2))
			RemovePlayerAttachedObject(playerid, 2);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 3))
			RemovePlayerAttachedObject(playerid, 3);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 4))
			RemovePlayerAttachedObject(playerid, 4);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 5))
			RemovePlayerAttachedObject(playerid, 5);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 6))
			RemovePlayerAttachedObject(playerid, 6);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 7))
			RemovePlayerAttachedObject(playerid, 7);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 8))
			RemovePlayerAttachedObject(playerid, 8);

		if(IsPlayerAttachedObjectSlotUsed(playerid, 9))
			RemovePlayerAttachedObject(playerid, 9);

		if(EventInfo[eventType] == 1)
		{
			//event tdm
			if(Iter_Contains(EvRedTeam, playerid))
			{
				SetPlayerVirtualWorld(playerid, playerid+1);
				SetPlayerInterior(playerid, EventInfo[arenaIntid]);

				TogglePlayerControllable(playerid, false);

				SetTimerEx("UnfreezeEvent", 5000, false, "i", playerid);
			}

			if(Iter_Contains(EvBlueTeam, playerid))
			{
				SetPlayerVirtualWorld(playerid, playerid+1);
				SetPlayerInterior(playerid, EventInfo[arenaIntid]);

				TogglePlayerControllable(playerid, false);

				SetTimerEx("UnfreezeEvent", 5000, false, "i", playerid);
			}
		}
		else if(EventInfo[eventType] == 3)
		{
			SetPlayerVirtualWorld(playerid, playerid+1);
			SetPlayerInterior(playerid, 0);

			SetTimerEx("UnfreezeEvent", 5000, false, "i", playerid);
		}
		else if(EventInfo[eventType] == 5)
		{
			SetTimerEx("LeaveEvent", 5000, false, "i", playerid);
		}
	}
	else
	{
		SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);
		SetPlayerInterior(playerid, AccountData[playerid][pInterior]);
		SetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
		SetPlayerFacingAngle(playerid, AccountData[playerid][pPos][3]);
		SetCameraBehindPlayer(playerid);
		TogglePlayerControllable(playerid, false);
		SetPlayerSpawn(playerid);
		LoadAnims(playerid);

		SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 1);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 1);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 1);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 301);

		Anticheat[playerid][acImmunity] = gettime() + 5;
	}
	return 1;
}

SetPlayerSpawn(playerid)
{
	if(!AccountData[playerid][pSpawned])
	{
		SetPlayerColor(playerid, 0xFFFFFFFF);
		//PlayerTextDrawShow(playerid, RadioVoiceInfoTD[playerid]);

		SetPlayerTime(playerid, WorldTime, 0);
		SetPlayerWeather(playerid, WorldWeather);

		if(AccountData[playerid][pBankNumber] == 0)
		{
			new query[228], rand = RandomEx(111111, 999999);
			new rek = rand+AccountData[playerid][pID];
			mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_BankNumber` FROM `player_characters` WHERE `Char_BankNumber`='%d'", rek);
			mysql_pquery(g_SQL, query, "BankNewRek", "id", playerid, rek);
		}

		if(AccountData[playerid][pSSN] == 0)
		{
			new query[128], rand = RandomEx(111111111, 999999999);
			new ssn = rand+AccountData[playerid][pID];
			mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_SSN` FROM `player_characters` WHERE `Char_SSN`='%d'", ssn);
			mysql_pquery(g_SQL, query, "CharNewSSN", "id", playerid, ssn);
		}
		AddJobIterator(playerid);
		
		AccountData[playerid][pSpawned] = true;

		PlayerPlaySound(playerid, 1188, 0.0, 0.0, 0.0);
		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
		StopAudioStreamForPlayer(playerid);

		SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Halo "RED"%s!, "WHITE"Selamat datang di "CYAN"Pahlawan Roleplay!", AccountData[playerid][pUCP]);
		SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda login sebagai "YELLOW"%s "WHITE"dengan peringkat "CYAN"%s.", AccountData[playerid][pName], GetPlayerLevelName(playerid));
		SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Hari ini: "YELLOW"%s", GetAdvTime());

		if(AccountData[playerid][pLoginTime] > 0)
		{
			new currentTime = gettime();
			new lastLoginTime = AccountData[playerid][pLoginTime];
			new timeDiff = currentTime - lastLoginTime;

			new timestamp = AccountData[playerid][pLoginTime], year, month, day, hour, minute, second;
			TimestampToDate(timestamp, year, month, day, hour, minute, second, 7);
			printf("%d-%d-%d %d:%d:%d", day, month, year, hour, minute, second);

			new format_string[144];
			if(timeDiff >= 86400)
			{
				format(format_string, sizeof(format_string), "<!> "WHITE"Anda terakhir kali login "YELLOW"%02d/%02d/%d, %02d:%02d:%02d", day, month, year, hour, minute, second);
				SendClientMessage(playerid, Y_PAHLAWAN, format_string);
			}
			else
			{
				format(format_string, sizeof(format_string), "<!> "WHITE"Anda terakhir kali login "YELLOW"%s "WHITE"yang lalu.", FormatTime(timeDiff));
				SendClientMessage(playerid, Y_PAHLAWAN, format_string);
			}
		}

		SendClientMessage(playerid, Y_PURPLE, "<!> Server ini bersifat voice-only, RP tanpa suara (bisu/tuli) tidak diperbolehkan.");
		//SendClientMessage(playerid, 0xFF0000FF, "(Peringatan) Dilarang keras meniup-niup mic!");

		if(!AccountData[playerid][pTutorialPassed])
			SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda belum menyelesaikan tutorial server, gunakan CMD "CMDEA"'/tutorial' "WHITE"untuk memulainya!");

		HideRadarMapForPlayer(playerid);
		
		HideThurXProjectTD(playerid);
		ShowHBETD(playerid);
		ShowServerNameTD(playerid);
		//ShowClockTD(playerid);
	}

	if(AccountData[playerid][pKnockdown] && OJailData[playerid][jailTime] < 1)
	{
		SetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
		ApplyAnimation(playerid, "WUZI", "CS_DEAD_GUY", 4.1, false, false, false, true, 0, true);
		
		AccountData[playerid][pKnockdown] = true;
		AccountData[playerid][pAccDeathTime] = gettime() + 480;

		new frmtsql[215];
		mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `player_characters` SET `Char_Knockdown` = 1 WHERE `pID` = %d", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, frmtsql);

		SetPlayerHealth(playerid, 100);

		PlayerTextDrawSetString(playerid, HABISDARAHTD[playerid], sprintf("%02d menit %02d detik", AccountData[playerid][pKnockdownTime] / 60 % 60, AccountData[playerid][pKnockdownTime] % 3600 % 60));
		ShowKnockTD(playerid);
	}

	if(AccountData[playerid][pComma] && OJailData[playerid][jailTime] < 1)
	{
		AssignPlayerComma(playerid);
	}

	if(AccountData[playerid][pGender] != 0)
	{
		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, AccountData[playerid][pMoney]);
		SetPlayerHealth(playerid, AccountData[playerid][pHealth]);
		SetPlayerScore(playerid, AccountData[playerid][pLevel]);
		TogglePlayerControllable(playerid, false);
		SetTimerEx("UnfreezeSpawn", 8500, false, "i", playerid);
	}
	return 1;
}

forward UnfreezeEvent(playerid);
public UnfreezeEvent(playerid)
{
	if(!IsPlayerConnected(playerid)) 
	{
		TogglePlayerControllable(playerid, true);
		return 0;
	}

	if(!AccountData[playerid][pInEvent] && !EventInfo[eventStarted]) //jika tidak di event dan event tidak dimulai maka dikembalikan
	{
		ResetPlayerWeapons(playerid);

		SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);
		SetPlayerInterior(playerid, AccountData[playerid][pInterior]);
		SetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
		SetPlayerFacingAngle(playerid, AccountData[playerid][pPos][3]);
		SetCameraBehindPlayer(playerid);
		TogglePlayerControllable(playerid, false);
		SetPlayerSpawn(playerid);
		LoadAnims(playerid);

		SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 1);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 1);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 1);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 1000);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 301);

		Anticheat[playerid][acImmunity] = gettime() + 5;
		return 0;
	}

	if(EventInfo[eventType] == 1) //jika TDM
	{
		if(Iter_Contains(EvRedTeam, playerid))
		{
			SetPlayerHealth(playerid, EventInfo[redHealth]);
			Anticheat[playerid][acArmorTime] = gettime() + 11;
			SetPlayerArmour(playerid, EventInfo[redArmour]);

			GivePlayerWeapon(playerid, EventInfo[redWeapon][0], 700);
			GivePlayerWeapon(playerid, EventInfo[redWeapon][1], 700);
			GivePlayerWeapon(playerid, EventInfo[redWeapon][2], 700);
		}

		if(Iter_Contains(EvBlueTeam, playerid))
		{
			SetPlayerHealth(playerid, EventInfo[blueHealth]);
			Anticheat[playerid][acArmorTime] = gettime() + 11;
			SetPlayerArmour(playerid, EventInfo[blueArmour]);

			GivePlayerWeapon(playerid, EventInfo[blueWeapon][0], 700);
			GivePlayerWeapon(playerid, EventInfo[blueWeapon][1], 700);
			GivePlayerWeapon(playerid, EventInfo[blueWeapon][2], 700);
		}
	}
	else if(EventInfo[eventType] == 3) //jika event zombie
	{
		if(Iter_Contains(EvZombieTeam, playerid))
		{
			SetPlayerColor(playerid, 0xFF0000FF);
			SetPlayerSkin(playerid, 162);
			SetPlayerHealth(playerid, 105.00);
			Anticheat[playerid][acArmorTime] = gettime() + 11;

			GivePlayerWeapon(playerid, 9, 1);

			Anticheat[playerid][acImmunity] = gettime() + 5;
			SetPlayerTeam(playerid, 2);
			SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda adalah "RED"Zombie, "YELLOW"habisi semua manusia yang tersisa!");

			pZombieClass[playerid] = 0;
			new rand1 = random(101);
			switch(rand1)
			{
				case 80..100:
				{
					new rand2 = random(3);
					switch(rand2)
					{
						case 0: //badak
						{
							SetPlayerSkin(playerid, 5);
							Anticheat[playerid][acArmorTime] = gettime() + 11;
							SetPlayerArmour(playerid, 254.00);
							pZombieClass[playerid] = 1;

							SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda sekarang menjadi "RED"Zombie Badak, "YELLOW"darah sangat tebal!");
							GameTextForPlayer(playerid, "~r~Zombie Badak~n~~b~darah tebal!", 6555, 3);
						}
						case 1: //cungkring
						{
							SetPlayerSkin(playerid, 230);
							pZombieClass[playerid] = 2;

							SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda sekarang menjadi "RED"Zombie Cungkring, "YELLOW"lompat sangat tinggi!");
							GameTextForPlayer(playerid, "~r~Zombie Cungkring~n~~b~lompat tinggi!", 6555, 3);
						}
						case 2: //jihad
						{
							SetPlayerSkin(playerid, 264);
							pZombieClass[playerid] = 3;

							SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda sekarang menjadi "RED"Zombie Jihadis, "YELLOW"meledak ketika mati!");
							GameTextForPlayer(playerid, "~r~Zombie Jihadis~n~~b~meledak ketika mati!", 6555, 3);
						}
					}
				}
			}
		}

		if(Iter_Contains(EvHumanTeam, playerid))
		{
			Iter_Remove(EvHumanTeam, playerid);
            Iter_Add(EvZombieTeam, playerid);

			static string[144];
			foreach(new i : InEvent)
			{
				format(string, sizeof(string), "{009dc4}%s(%i) "YELLOW"telah terinfeksi dan berubah menjadi "RED"Zombie.", GetName(playerid), playerid);
				SendClientMessage(i, Y_WHITE, string);
			}

			SetPlayerColor(playerid, 0xFF0000FF);
			SetPlayerSkin(playerid, 162);
			SetPlayerHealth(playerid, 105.00);
			Anticheat[playerid][acArmorTime] = gettime() + 11;

			GivePlayerWeapon(playerid, 9, 1);

			Anticheat[playerid][acImmunity] = gettime() + 5;
			SetPlayerTeam(playerid, 2);
			SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda telah terinfeksi dan menjadi "RED"Zombie!");

			pZombieClass[playerid] = 0;
			new rand1 = random(101);
			switch(rand1)
			{
				case 80..100:
				{
					new rand2 = random(3);
					switch(rand2)
					{
						case 0: //badak
						{
							SetPlayerSkin(playerid, 5);
							Anticheat[playerid][acArmorTime] = gettime() + 11;
							SetPlayerArmour(playerid, 254.00);
							pZombieClass[playerid] = 1;

							SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda sekarang menjadi "RED"Zombie Badak, "YELLOW"darah sangat tebal!");
							GameTextForPlayer(playerid, "~r~Zombie Badak~n~~b~darah tebal!", 6555, 3);
						}
						case 1: //cungkring
						{
							SetPlayerSkin(playerid, 230);
							pZombieClass[playerid] = 2;

							SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda sekarang menjadi "RED"Zombie Cungkring, "YELLOW"lompat sangat tinggi!");
							GameTextForPlayer(playerid, "~r~Zombie Cungkring~n~~b~lompat tinggi!", 6555, 3);
						}
						case 2: //jihad
						{
							SetPlayerSkin(playerid, 264);
							pZombieClass[playerid] = 3;

							SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda sekarang menjadi "RED"Zombie Jihadis, "YELLOW"meledak ketika mati!");
							GameTextForPlayer(playerid, "~r~Zombie Jihadis~n~~b~meledak ketika mati!", 6555, 3);
						}
					}
				}
			}
		}
	}

	SetPlayerVirtualWorld(playerid, EventInfo[arenaVWID]);
	TogglePlayerControllable(playerid, true);
	return 1;
}

forward UnfreezeSpawn(playerid);
public UnfreezeSpawn(playerid)
{
	if(!IsPlayerConnected(playerid)) 
	{
		TogglePlayerControllable(playerid, true);
		return 0;
	}

	TogglePlayerControllable(playerid, true);

	if(AccountData[playerid][pArmor] > 0.0)
	{
		AccountData[playerid][pHasArmor] = true;
		SetPlayerArmour(playerid, AccountData[playerid][pArmor]);
		AccountData[playerid][pArmorEmpty] = false;
	}
	else
	{
		SetPlayerArmour(playerid, 0.0);
		AccountData[playerid][pHasArmor] = false;
		AccountData[playerid][pArmorEmpty] = true;
	}
	AttachPlayerToys(playerid);
	SetWeapons(playerid);
	
	SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
	TogglePlayerControllable(playerid, true);
	SetCameraBehindPlayer(playerid);

	if(AccountData[playerid][pIsUsingUniform])
	{
		SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
	}
	
	if(AccountData[playerid][pFaction] != FACTION_NONE)
	{
		AssignFactionStuff(playerid);
	}

	if(OJailData[playerid][jailed])
	{
		SendPlayerToJailAdmin(playerid);
	}

	if(AccountData[playerid][pArrested])
	{
		SendPlayerToFederal(playerid);
	}
	return 1;
}

forward AssignFactionStuff(playerid);
public AssignFactionStuff(playerid)
{	
	if(AccountData[playerid][pFaction] == FACTION_LSPD && AccountData[playerid][pOnDuty])
	{	
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_LSFD && AccountData[playerid][pOnDuty])
	{
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_PUTRIDELI && AccountData[playerid][pOnDuty])
	{
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_SAGOV && AccountData[playerid][pOnDuty])
	{
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_BENNYS && AccountData[playerid][pOnDuty])
	{
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}
	
	if(AccountData[playerid][pFaction] == FACTION_UBER && AccountData[playerid][pOnDuty])
	{
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_DINARBUCKS && AccountData[playerid][pOnDuty])
	{
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_FOX11 && AccountData[playerid][pOnDuty])
	{
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_AUTOMAX && AccountData[playerid][pOnDuty])
	{
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_HANDOVER && AccountData[playerid][pOnDuty])
	{
		if(AccountData[playerid][pIsUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
	}
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);
	if(killerid != INVALID_PLAYER_ID)
	{
		if(!AccountData[killerid][IsLoggedIn] || !AccountData[killerid][pSpawned]) return Kick(killerid);

		ShowKillEffectTD(killerid);

		if(AccountData[killerid][pInEvent] && AccountData[playerid][pInEvent])
		{
			static string[144];
			if(EventInfo[eventType] == 1)
			{
				//event TDM
				if(Iter_Contains(EvRedTeam, killerid)) //red tim bunuh blue tim
				{
					EventInfo[redTeamScore]++;
					
					foreach(new i : InEvent)
					{
						format(string, sizeof(string), ""RED"%s(%i) "YELLOW"killed {009dc4}%s(%i) "YELLOW"(%s), Red Team Score: "RED"%d.", GetName(killerid), killerid, GetName(playerid), playerid,ReturnWeaponName(GetPlayerWeapon(killerid)), EventInfo[redTeamScore]);
						SendClientMessage(i, Y_WHITE, string);
					}
				}

				else if(Iter_Contains(EvBlueTeam, killerid)) //sebaliknya
				{
					EventInfo[blueTeamScore]++;
					
					foreach(new i : InEvent)
					{
						format(string, sizeof(string), "{009dc4}%s(%i) "YELLOW"killed "RED"%s(%i) "YELLOW"(%s), Blue Team Score: {009dc4}%d.", GetName(killerid), killerid, GetName(playerid), playerid,ReturnWeaponName(GetPlayerWeapon(killerid)), EventInfo[blueTeamScore]);
						SendClientMessage(i, Y_WHITE, string);
					}
				}
			}

			//event zombie
			else if(EventInfo[eventType] == 3)
			{
				if(Iter_Contains(EvHumanTeam, killerid)) //jika manusia membunuh zombie
				{
					if(pZombieClass[playerid] == 3) //jihad zombie
					{
						new Float:POS[3];
						GetPlayerPos(playerid, POS[0], POS[1], POS[2]);
    					CreateExplosion(POS[0], POS[1], POS[2], 10, 3.0);
					}

					foreach(new i : InEvent)
					{
						format(string, sizeof(string), "{009dc4}%s(%i) "YELLOW"telah membunuh zombie "RED"%s(%i) "YELLOW"(%s).", GetName(killerid), killerid, GetName(playerid), playerid, ReturnWeaponName(GetPlayerWeapon(killerid)));
						SendClientMessage(i, Y_WHITE, string);
					}
				}
				else if(Iter_Contains(EvZombieTeam, killerid)) //jika zombie menginfeksi manusia
				{
					Iter_Remove(EvHumanTeam, playerid);
                    Iter_Add(EvZombieTeam, playerid);

					foreach(new i : InEvent)
					{
						format(string, sizeof(string), ""RED"%s(%i) "YELLOW"telah menginfeksi {009dc4}%s(%i).", GetName(killerid), killerid, GetName(playerid), playerid);
						SendClientMessage(i, Y_WHITE, string);
					}
				}
			}
		}
		else
		{
			if(AccountData[playerid][pSpawned])
			{
				switch(reason)
				{
					case 0..15:
					{
						DeathCause[playerid][Bruised] = true;
					}
					case 22..34:
					{
						DeathCause[playerid][Shoted] = true;
					}
					case 16, 18, 35..37, 39, 51:
					{
						DeathCause[playerid][Burns] = true;
					}
					case 53:
					{
						DeathCause[playerid][Drown] = true;
					}
					case 54:
					{
						DeathCause[playerid][Fallen] = true;
					}
				}
			}
		}
	}

	foreach(new ii : Player)
    {
        if(AccountData[ii][pAdmin] > 0)
        {
            SendDeathMessageToPlayer(ii, killerid, playerid, reason);
        }
    }

	SetPlayerHealth(playerid, 26);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(!AVC_PConnected[playerid])
	{
		SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena terdeteksi tidak login. "YELLOW"[OPT]");
		Kick(playerid);
        return 0;
	}

	if(!AccountData[playerid][pSpawned] || !AccountData[playerid][IsLoggedIn])
	{
		Kick(playerid);
		return 0;
	}
	/*
    if(strlen(text) > 64)
	{
        format(lstr, sizeof(lstr), "%s says: %.64s", GetPlayerRoleplayName(playerid), text);
        ProxDetector(10, playerid, lstr, 0xE6E6E6E6, 0xC8C8C8C8, 0xAAAAAAAA, 0x8C8C8C8C, 0x6E6E6E6E);

        format(lstr, sizeof(lstr), "...%s", text[64]);
        ProxDetector(10, playerid, lstr, 0xE6E6E6E6, 0xC8C8C8C8, 0xAAAAAAAA, 0x8C8C8C8C, 0x6E6E6E6E);
        SetPlayerChatBubble(playerid, text, X11_WHITE, 10.0, 5000);
	}
	else
    {
        format(lstr, sizeof(lstr), "%s says: %s", GetPlayerRoleplayName(playerid), text);
        ProxDetector(10, playerid, lstr, 0xE6E6E6E6, 0xC8C8C8C8, 0xAAAAAAAA, 0x8C8C8C8C, 0x6E6E6E6E);
        SetPlayerChatBubble(playerid, text, X11_WHITE, 10.0, 5000);
    }
    if(gPlayerUsingLoopingAnim[playerid] != 1 && !AccountData[playerid][pKnockdown] && AccountData[playerid][pChatAnim])
    {
        OnePlayAnim(playerid,"PED","IDLE_CHAT",4.0,0,0,0,1,1);
        SetTimerEx("StopLoopingAnim", strlen(text)*80, false, "i", playerid);
    }*/

	if(strfind(text, "Project SobFoX", true) != -1)
	{
		Kick(playerid);
		return 0;
	}

	if (GetTickCount() - AC_ChatSpamTime[playerid] < 3555)
    {
		Kick(playerid);
		return 0;
	}

	AC_ChatSpamTime[playerid] = GetTickCount();

	return 0;
}

public OnPlayerEnterCheckpoint(playerid)
{
	if(AccountData[playerid][pCommunityService])
	{
		static string[144];
		if(AccountData[playerid][pTotalComServed] >= AccountData[playerid][pHowMuchComServing])
		{
			TogglePlayerControllable(playerid, false);

			PlayComServiceAnim(playerid, 19622, "BD_FIRE","wash_up", 4.1, false, false, false, false, false);

			DisablePlayerCheckpoint(playerid);
			
			format(string, sizeof(string), "SERVICE: "WHITE"Anda telah selesai menjalani "CYAN"Community Service "WHITE"untuk "YELLOW"%dx pembersihan taman.", AccountData[playerid][pTotalComServed], AccountData[playerid][pHowMuchComServing]);
			SendClientMessage(playerid, X11_LIGHTBLUE, string);
			
			AccountData[playerid][pCommunityService] = false;
			AccountData[playerid][pTotalComServed] = -1;
			AccountData[playerid][pHowMuchComServing] = 0;

			AccountData[playerid][pGivenComServBy] = INVALID_PLAYER_ID;
			AccountData[playerid][pGiveComServTo] = INVALID_PLAYER_ID;

			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_ComServing`='%d' WHERE `pID`=%d", AccountData[playerid][pHowMuchComServing], AccountData[playerid][pID]);
			mysql_pquery(g_SQL, query);
			return 1;
		}
		TogglePlayerControllable(playerid, false);
		
		PlayComServiceAnim(playerid, 19622, "BD_FIRE","wash_up", 4.1, false, false, false, true, true);

		AccountData[playerid][pTotalComServed]++;
		new rand = random(sizeof(g_ComServicePoint));
		SetPlayerCheckpoint(playerid, g_ComServicePoint[rand][0], g_ComServicePoint[rand][1], g_ComServicePoint[rand][2], 1.5);

		format(string, sizeof(string), "SERVICE: "WHITE"Anda telah membersihkan taman sebanyak "YELLOW"%dx/%dx.", AccountData[playerid][pTotalComServed], AccountData[playerid][pHowMuchComServing]);
		SendClientMessage(playerid, X11_LIGHTBLUE, string);
	}
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
	return 1;
}

public OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
	return 1;
}

public OnPlayerEnterDynamicRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
	if(checkpointid == AccountData[playerid][pGPSCP] && IsPlayerInDynamicRaceCP(playerid, AccountData[playerid][pGPSCP]))
	{
		if(DestroyDynamicRaceCP(AccountData[playerid][pGPSCP]))
			AccountData[playerid][pGPSCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
	}
	else if(checkpointid == pTutorialRCP[playerid] && IsPlayerInDynamicRaceCP(playerid, pTutorialRCP[playerid]))
	{
		switch(pTutorialStep[playerid])
		{
			case 0:
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Balai Kota"YELLOW", tempat kamu bisa melamar pekerjaan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] KTP sudah otomatis aktif permanen sejak awal pembuatan karakter.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Info jadwal layanan pemerintah bisa dicek lewat Discord atau in-game.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu juga bisa mengambil slip gaji (paycheck) di dalam gedung ini.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 1:
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Saat login, kamu bisa memilih lokasi spawn. Salah satu lokasi utamanya adalah "CYAN"Bandara.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu juga bisa spawn di properti milikmu (seperti rumah atau rusun).");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] "RED"PENTING: "YELLOW"Dilarang keras membuat kerusuhan dalam bentuk apapun di semua lokasi spawn.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 2:
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"IKEA"YELLOW", tempat menjual hasil pekerjaanmu.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Barang olahan hasil kerja bisa kamu jual di sini.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Masuk ke dalam untuk menukarkannya dengan uang.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 3:
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Karaktermu bisa stres. Perhatikan bar merah di pojok kiri bawah layar.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Untuk menurunkannya, kamu bisa berolahraga di "CYAN"GYM "YELLOW"ini.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Dekati alatnya dan tekan tombol "RED"Y "YELLOW"untuk mulai berolahraga.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 4: //garasi kota
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini adalah "CYAN"garkot (garasi kota)"YELLOW", tempat kamu harus menyimpan kendaraan sebelum logout.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu juga bisa menyimpannya di garasi rumah pribadimu jika punya.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kendaraan yang ditinggal di luar akan ditarik ke asuransi (berbayar) saat kamu login kembali.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu dapat melihat status kendaraanmu dengan "RED"CMD '/myv'.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 5: //pembuatan sim
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini tempat pembuatan SIM dan Plat nomor kendaraan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu bisa masuk ke dalam untuk mengurus dokumen kendaraan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Jangan berkendara tanpa SIM dan Plat agar tidak ditilang polisi.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 6: //cardealer
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini adalah "CYAN"Cardealer/Showroom"YELLOW", tempat untuk membeli kendaraan pribadi.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Jika uangmu sudah cukup, kamu bisa membeli mobil atau motor di sini.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kendaraan pribadi bisa menyimpan "RED"senjata & item"YELLOW", dan juga bisa dikunci.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ingat, hanya kendaraan pribadi yang bisa disimpan di garasi kota (garkot).");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 7: //warung
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini adalah salah satu "CYAN"Warung, "YELLOW"kamu dapat membeli beberapa barang di dalamnya.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kami sarankan jika ingin membeli makanan, beli kepada faction restoran agar lebih menguntungkan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu juga dapat membeli alat-alat lainnya di tempat ini.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Setiap "CYAN"Warung "YELLOW"dapat dirampok (pastikan ikuti rules).");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 8: //casino
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini adalah "CYAN"Casino"YELLOW", tempat kamu bisa berjudi.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu harus mencapai level 5 untuk bisa bermain di sini.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");
			
				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 9: //samsat
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini kantor "CYAN"SAMSAT"YELLOW", pusat administrasi kendaraan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu bisa mengurus SIM, dokumen, atau menebus kendaraan sitaan di sini.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Pastikan datang saat jam kerja (cek jadwal di Discord atau in-game).");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");
				
				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 10: //asuransi
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Asuransi"YELLOW", tempat mengambil kendaraanmu yang ditarik (dikenakan biaya).");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kendaraan yang tidak disimpan di garasi (garkot/rumah) saat logout akan berakhir di sini.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Gunakan "RED"CMD '/myv' "YELLOW"untuk mengecek status dan lokasi kendaraanmu.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");
				
				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 11: //bengkel
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Bengkel"YELLOW", tempat servis dan modifikasi kendaraan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu juga bisa melamar kerja di sini jika ada lowongan.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 12: //carnival
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Carnaval"YELLOW", tempat untuk hobi seperti memancing.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu juga bisa berburu rusa, tapi beli dulu peralatannya di "CYAN"Warung"YELLOW".");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Lokasi lainnya bisa kamu cek di "RED"HP > GPS > Lokasi Hobi"YELLOW".");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 13: //mega mall
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Mega Mall"YELLOW", tempat membeli barang-barang yang tidak ada di warung biasa.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Beberapa item di sini hanya bisa dibeli jika sudah mencapai level 5.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 14: //gudang
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Gudang"YELLOW", tempat untuk menyewa penyimpanan tambahan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Masa sewa berlaku 30 hari. Barangmu akan tetap aman meski sewa berakhir.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu hanya perlu memperpanjang sewa untuk bisa mengaksesnya kembali.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 15: //rusun
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Rusun"YELLOW", tempat yang bisa kamu sewa untuk spawn dan menyimpan barang.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kapasitasnya lebih besar dari gudang dan punya fitur tambahan, seperti menyimpan kendaraan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] "RED"PENTING: "YELLOW"Sewa rusun direset serentak. Cek jadwalnya agar sewamu tidak hangus.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 16: //modshop
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Modshop"YELLOW", tempat modifikasi custom kendaraan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Hanya bisa diakses jika kamu sudah mencapai level 5.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 17: //kantor uber
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Kantor Uber"YELLOW", penyedia jasa transportasi online.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu bisa memesan layanan mereka lewat aplikasi di HP.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Jika ada lowongan, kamu juga bisa melamar kerja di sini.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 18: //rumah sakit
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Rumah Sakit"YELLOW", tempat faksi EMS/Paramedis bekerja.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu bisa melamar kerja di sini jika mereka membuka lowongan.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Jika karaktermu pingsan, kamu akan dibawa ke sini untuk mendapat perawatan.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 19: //kantor pewarta
			{
				pTutorialStep[playerid]++;
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Kantor Pewarta Berita"YELLOW", sumber informasi dan berita kota.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu bisa mendengarkan berita terbaru saat mereka sedang "RED"on-air broadcast"YELLOW".");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Jika ada lowongan, kamu juga bisa melamar menjadi jurnalis di sini.");
				SendClientMessage(playerid, X11_YELLOW, "------ # Akhir Informasi ------");

				ResetAllRaceCP(playerid);
	
				pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
			}
			case 20: //penjara
			{
				pTutorialStep[playerid] = -1;
				ResetAllRaceCP(playerid);
	
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Ini "CYAN"Penjara"YELLOW", tempatmu jika ditangkap oleh polisi.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Info lengkap tentang pasal dan hukuman bisa kamu baca di Discord.");
				SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Kamu juga bisa melamar jadi polisi jika ada lowongan dan memenuhi syarat.");

				AccountData[playerid][pTutorialPassed] = true;
				SendClientMessage(playerid, X11_GREEN, "[Tutorial] Kamu telah selesai melaksanakan tutorial, selamat! Kamu diberi $1,500 sebagai hadiah.");
				GivePlayerMoneyEx(playerid, 1500);
				ShowItemBox(playerid, "Cash", "Received $1,500x", 1212, 5);
			}
		}
	}
	return 1;
}

public OnPlayerLeaveDynamicRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid)
{
	if(areaid == AreaSantaiZone)
	{
		ShowAreaSantaiTD(playerid);
	}

	if(areaid == DisnakerDoorSensor)
	{
		if(!g_DisnakerDoorOpened)
		{
			g_DisnakerDoorOpened = true;
			MoveDynamicObject(DisnakerDoor[0], 1616.865966, -1269.938110, 16.479890, 0.6, -0.000007, -0.000000, -89.999977);
			MoveDynamicObject(DisnakerDoor[1], 1616.865966, -1275.880249, 16.479890, 0.6, 0.000007, 0.000000, 89.999977);
		}
	}

	if(areaid == PutriDeliDoorSensor)
	{
		if(!g_PutriDeliDoorOpened)
		{
			g_PutriDeliDoorOpened = true;
			MoveDynamicObject(PutriDeliDoor[0], 662.661315, -1863.011108, 5.489810, 0.6, 0.000000, 0.000000, 180.000000);
			MoveDynamicObject(PutriDeliDoor[1], 656.860473, -1863.011108, 5.490809, 0.6, 0.000000, 0.000000, 720.000000);
		}
	}
	
	if(areaid == SriMersingFDoorSensor)
	{
		if(!g_SriMersingFDoorOpened)
		{
			g_SriMersingFDoorOpened = true;
			MoveDynamicObject(SriMersingDoor[0], -313.817260, 1302.924804, 53.688583, 0.6, 0.000000, 0.000082, 0.000000);
			MoveDynamicObject(SriMersingDoor[1], -307.887115, 1302.944824, 53.688583, 0.6, 0.000000, -0.000082, 179.999496);
		}
	}

	if(areaid == SriMersingBDoorSensor)
	{
		if(!g_SriMersingBDoorOpened)
		{
			g_SriMersingBDoorOpened = true;
			MoveDynamicObject(SriMersingDoor[2], -308.702056, 1285.447509, 53.548583, 0.6, 0.000000, 0.000000, 0.000000);
			MoveDynamicObject(SriMersingDoor[3], -302.752136, 1285.466064, 53.548587, 0.6, 0.000000, 0.000000, 180.000000);
		}
	}

	if(areaid == RSLeftDoorSensor)
	{
		if(!g_RSLeftDoorOpened)
		{
			g_RSLeftDoorOpened = true;
			MoveDynamicObject(RSDoor[0], 1730.488159, -1133.150390, 23.107053, 0.6, 0.000000, 0.000060, 0.000000);
			MoveDynamicObject(RSDoor[1], 1735.489746, -1133.130371, 23.107053, 0.6, 0.000000, -0.000060, 179.999633);
		}
	}

	if(areaid == RSRightDoorSensor)
	{
		if(!g_RSRightDoorOpened)
		{
			g_RSRightDoorOpened = true;
			MoveDynamicObject(RSDoor[2], 1734.469726, -1133.150390, 23.107053, 0.6, 0.000000, 0.000067, 0.000000);
			MoveDynamicObject(RSDoor[3], 1739.460083, -1133.130371, 23.107053, 0.6, 0.000000, -0.000067, 179.999588);
		}
	}

	if(areaid == RSBackDoorSensor)
	{
		if(!g_RSBackDoorOpened)
		{
			g_RSBackDoorOpened = true;
			MoveDynamicObject(RSDoor[4], 1783.229492, -1096.661621, 23.107053, 0.6, 0.000000, 0.000029, 0.000000);
			MoveDynamicObject(RSDoor[5], 1788.711181, -1096.641601, 23.107053, 0.6, 0.000000, -0.000029, 179.999816);
		}
	}

	if(areaid == sBoxDoorSensor)
	{
		if(!g_sBoxDoorOpened)
		{
			g_sBoxDoorOpened = true;
			MoveDynamicObject(sBoxDoor[0], 442.841583, -1810.735839, 6.447765, 0.6, 0.000000, 0.000000, 90.000000);
			MoveDynamicObject(sBoxDoor[1], 442.841583, -1804.843383, 6.447765, 0.6, 0.000000, 0.000000, 270.000000);
		}
	}

	if(areaid == PenjahitDoorSensor)
	{
		if(!g_PenjahitDoorOpened)
		{
			g_PenjahitDoorOpened = true;
			MoveDynamicObject(PenjahitDoor[0], 2530.872314, 2024.442504, 10.170944, 0.6, 0.000082, 0.000000, 91.499748);
			MoveDynamicObject(PenjahitDoor[1], 2530.707275, 2030.390625, 10.170944, 0.6, -0.000082, 0.000000, -88.499748);
		}
	}

	if(areaid == RPSchoolZone)
	{
		SendClientMessage(playerid, X11_YELLOW, "OOC ZONE: Sekarang anda memasuki area "RED"Zona OOC, "YELLOW"seluruh kegiatan di dalam zona ini adalah OOC.");
		SendClientMessage(playerid, X11_YELLOW, "OOC ZONE: Dimohon untuk tertib dan tidak rusuh, hukuman bisa "RED"Jail / Ban!");
	}

	if(areaid == KonserMusicZone)
	{
		if(GM[KonserStarted])
		{
			PlayAudioStreamForPlayer(playerid, GM[KonserMusicLink]);
		}
	}

	if(areaid == PDCMusicZone)
	{
		if(!isnull(GM[PDBCDJLink]))
		{
			PlayAudioStreamForPlayer(playerid, GM[PDBCDJLink]);
		}
	}

	if(IsPlayerInAnyVehicle(playerid))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsStingerVehicle(GetPlayerVehicleID(playerid)))
		{
			foreach(new p : Player)
			{
				new vehicleid = GetPlayerVehicleID(playerid);
				if(IsValidDynamicObject(AccountData[p][PoliceSpikeObjid]))
				{
					if(IsValidDynamicArea(AccountData[p][PoliceSpikeArea]) && AccountData[p][PoliceSpikeArea] == areaid)
					{
						new panels, doors, lights, tires;
						GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

						if((!IsABike(vehicleid) && tires != 15) || (IsABike(vehicleid) && tires != 3))
						{
							if(IsABike(vehicleid)) tires = encode_tires_bike(1, 1);
							else tires = encode_tires(1, 1, 1, 1);
							UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
							return true;
						}
					}
				}
			}
		}
	}

	foreach(new i : Player)
    {
        if(areaid == BoomBoxInfo[i][BoomBoxArea])
        {
            PlayAudioStreamForPlayer(playerid, BoomBoxInfo[i][BoomBoxLink], BoomBoxInfo[i][BoomX], BoomBoxInfo[i][BoomY], BoomBoxInfo[i][BoomZ], 25.0, 1);
        }
    }
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid)
{
	if(areaid == AreaSantaiZone)
	{
		HideAreaSantaiTD(playerid);
	}

	if(areaid == DisnakerDoorSensor)
	{
		if(g_DisnakerDoorOpened)
		{
			g_DisnakerDoorOpened = false;
			MoveDynamicObject(DisnakerDoor[0], 1616.865966, -1271.409057, 16.479890, 0.6, -0.000007, -0.000000, -89.999977);
			MoveDynamicObject(DisnakerDoor[1], 1616.865966, -1274.409667, 16.479890, 0.6, 0.000007, 0.000000, 89.999977);
		}
	}
	if(areaid == PutriDeliDoorSensor)
	{
		if(g_PutriDeliDoorOpened)
		{
			g_PutriDeliDoorOpened = false;
			MoveDynamicObject(PutriDeliDoor[0], 661.260864, -1863.011108, 5.489810, 0.6, 0.000000, 0.000000, 180.000000);
			MoveDynamicObject(PutriDeliDoor[1], 658.260681, -1863.011108, 5.490809, 0.6, 0.000000, 0.000000, 720.000000);
		}
	}

	if(areaid == SriMersingFDoorSensor)
	{
		if(g_SriMersingFDoorOpened)
		{
			g_SriMersingFDoorOpened = false;
			MoveDynamicObject(SriMersingDoor[0], -312.357177, 1302.924804, 53.688583, 0.6, 0.000000, 0.000082, 0.000000);
			MoveDynamicObject(SriMersingDoor[1], -309.357238, 1302.944824, 53.688583, 0.6, 0.000000, -0.000082, 179.999496);
		}
	}

	if(areaid == SriMersingBDoorSensor)
	{
		if(g_SriMersingBDoorOpened)
		{
			g_SriMersingBDoorOpened = false;
			MoveDynamicObject(SriMersingDoor[2], -307.222137, 1285.447509, 53.548583, 0.6, 0.000000, 0.000000, 0.000000);
			MoveDynamicObject(SriMersingDoor[3], -304.222167, 1285.466064, 53.548587, 0.6, 0.000000, 0.000000, 180.000000);
		}
	}

	if(areaid == RSLeftDoorSensor)
	{
		if(g_RSLeftDoorOpened)
		{
			g_RSLeftDoorOpened = false;
			MoveDynamicObject(RSDoor[0], 1731.708740, -1133.150390, 23.107053, 0.6, 0.000000, 0.000060, 0.000000);
			MoveDynamicObject(RSDoor[1], 1734.708618, -1133.130371, 23.107053, 0.6, 0.000000, -0.000060, 179.999633);
		}
	}

	if(areaid == RSRightDoorSensor)
	{
		if(g_RSRightDoorOpened)
		{
			g_RSRightDoorOpened = false;
			MoveDynamicObject(RSDoor[2], 1735.219970, -1133.150390, 23.107053, 0.6, 0.000000, 0.000067, 0.000000);
			MoveDynamicObject(RSDoor[3], 1738.219848, -1133.130371, 23.107053, 0.6, 0.000000, -0.000067, 179.999588);
		}
	}

	if(areaid == RSBackDoorSensor)
	{
		if(g_RSBackDoorOpened)
		{
			g_RSBackDoorOpened = false;
			MoveDynamicObject(RSDoor[4], 1784.720703, -1096.661621, 23.107053, 0.6, 0.000000, 0.000029, 0.000000);
			MoveDynamicObject(RSDoor[5], 1787.720581, -1096.641601, 23.107053, 0.6, 0.000000, -0.000029, 179.999816);
		}
	}

	if(areaid == sBoxDoorSensor)
	{
		if(g_sBoxDoorOpened)
		{
			g_sBoxDoorOpened = false;
			MoveDynamicObject(sBoxDoor[0], 442.841583, -1809.264404, 6.447765, 0.6, 0.000000, 0.000000, 90.000000);
			MoveDynamicObject(sBoxDoor[1], 442.841583, -1806.294311, 6.447765, 0.6, 0.000000, 0.000000, 270.000000);
		}
	}

	if(areaid == PenjahitDoorSensor)
	{
		if(g_PenjahitDoorOpened)
		{
			g_PenjahitDoorOpened = false;
			MoveDynamicObject(PenjahitDoor[0], 2530.833740, 2025.922119, 10.170944, 0.6, 0.000082, 0.000000, 91.499748);
			MoveDynamicObject(PenjahitDoor[1], 2530.744873, 2028.920654, 10.170944, 0.6, -0.000082, 0.000000, -88.499748);
		}
	}

	if(areaid == KonserMusicZone)
	{
		StopAudioStreamForPlayer(playerid);
	}

	if(areaid == PDCMusicZone)
	{
		StopAudioStreamForPlayer(playerid);
	}
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(!AccountData[playerid][pInEvent])
    {
		pCurWeap[playerid] = GetPlayerWeaponEx(playerid);
		if(pCurWeap[playerid] != AttCheckCurWeapon[playerid])
		{
			static weaponid, ammo, objectslot, count, index;

			for (new i = 1; i < 10; i++) //Loop only through the slots that may contain the wearable weapons
			{
				GetPlayerWeaponData(playerid, i, weaponid, ammo);
				index = GetWeaponIndex(weaponid);
			
				if(weaponid && ammo && !GunEdit[playerid][index][Hidden] && IsWeaponWearable(weaponid) && EditingWeapon[playerid] != weaponid)
				{
					objectslot = GetWeaponObjectSlot(weaponid);

					if(GetPlayerWeapon(playerid) != weaponid) //senjata di tangan disarungkan
					{
						RemovePlayerAttachedObject(playerid, objectslot);
						SetPlayerAttachedObject(playerid, objectslot, GetWeaponModel(weaponid), GunEdit[playerid][index][Bone], GunEdit[playerid][index][Position][0], GunEdit[playerid][index][Position][1], GunEdit[playerid][index][Position][2], GunEdit[playerid][index][Position][3], GunEdit[playerid][index][Position][4], GunEdit[playerid][index][Position][5], 1.0, 1.0, 1.0, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
					}
					else if (IsPlayerAttachedObjectSlotUsed(playerid, objectslot)) //senjata di sarung dihapus dan dipindah ke tangan
					{
						RemovePlayerAttachedObject(playerid, objectslot);
						if(IsWeaponTintable(pCurWeap[playerid]) && AccountData[playerid][pVIP] >= 2)
							SetPlayerWeaponTint(playerid, pCurWeap[playerid], GetWeaponIndex(pCurWeap[playerid]));
					}
				}
			}
			for (new i = 4; i < 9; i++) if (IsPlayerAttachedObjectSlotUsed(playerid, i))
			{
				count = 0;

				for(new j = 22; j < 35; j++) if (PlayerHasWeapon(playerid, j) && GetWeaponObjectSlot(j) == i)
					count++;

				for(new l = 2; l < 10; l++) if (PlayerHasWeapon(playerid, l) && GetWeaponObjectSlot(l) == i)
					count++;
				
				if((PlayerHasWeapon(playerid, 41) || PlayerHasWeapon(playerid, 42)) && (GetWeaponObjectSlot(41) == i || GetWeaponObjectSlot(42) == i))
					count++;
					
				if(!count) RemovePlayerAttachedObject(playerid, i);
			}
			AttCheckCurWeapon[playerid] = pCurWeap[playerid];
		}
	}
	return 1;
}

forward ReturnPlayerWorld(playerid);
public ReturnPlayerWorld(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;

	TogglePlayerControllable(playerid, true);
	SetPlayerVirtualWorld(playerid, 0);
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

	EnteringVehID[playerid] = vehicleid;

	if(!ispassenger)
	{
		if(IsVehicleSeatOccupied(vehicleid, 0))
		{
			if(GetVehicleDriver(vehicleid) != playerid)
			{
				StopRunningAnimation(playerid);
				new Float:POS[3];
				GetPlayerPos(playerid, POS[0], POS[1], POS[2]);
				SetPlayerPos(playerid, POS[0], POS[1], POS[2] + 3.5);
				TogglePlayerControllable(playerid, false);
				SetPlayerVirtualWorld(playerid, 80);
				PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
				GameTextForPlayer(playerid, "~r~Jangan CJ!", 9000, 3);
				SetTimerEx("ReturnPlayerWorld", 8500, false, "i", playerid);
			}
		}

		if(IsLSPDVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_LSPD)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
			}
		}

		if(IsLSFDVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_LSFD)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
			}
		}

		if(IsSAGOVVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_SAGOV)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
			}
		}

		if(IsPutrideliVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_PUTRIDELI)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Putri Deli Beach Club!");
			}
		}

		if(IsUberVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_UBER)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
			}
		}

		if(IsBennysVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_BENNYS)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
			}
		}

		if(IsAutomaxVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_AUTOMAX)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Automax Workshop!");
			}
		}

		if(IsHandoverVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_HANDOVER)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Handover Motorworks!");
			}
		}

		if(IsDinarbucksVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_DINARBUCKS)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Loving Donuts!");
			}
		}

		if(IsFOX11LAVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_FOX11)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pewarta Pahlawan Roleplay!");
			}
		}

		if(IsTexasVehicle(vehicleid))
		{
			if(AccountData[playerid][pFaction] != FACTION_TEXAS)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Texas Chicken!");
			}
		}
	}
	else
	{
		if(IsABike(vehicleid) || GetVehicleModel(vehicleid) == 424)
		{
			if(VehicleCore[vehicleid][vCoreLocked])
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");
			}
		}

		foreach(new i : PvtVehicles) if(vehicleid == PlayerVehicle[i][pVehPhysic])
		{
			if(PlayerVehicle[i][pVehTireLocked])
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang dalam kondisi tirelocked!");
			}
		}
	}
	return 1;
}

forward OnInteriorChangeSpec(adminid, playerid);
public OnInteriorChangeSpec(adminid, playerid)
{
	if(!IsPlayerConnected(adminid)) return 0;
	if(!IsPlayerConnected(playerid)) return 0;
	
	SetPlayerInterior(adminid, GetPlayerInterior(playerid));
    SetPlayerVirtualWorld(adminid, GetPlayerVirtualWorld(playerid));
	TogglePlayerSpectating(adminid, true);
	PlayerSpectatePlayer(adminid, playerid);
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	foreach(new i : Player) if(i != playerid)
	{
		if(AccountData[i][pSpawned] && AccountData[i][pSpec] != INVALID_PLAYER_ID)
		{
			if(AccountData[i][pSpec] == playerid)
			{
				if(IsPlayerInAnyVehicle(playerid))
				{
					PlayerSpectateVehicle(i, SavingVehID[playerid]);
				}
				else
				{
					SetTimerEx("OnInteriorChangeSpec", 4500, false, "ii", i, playerid);
				}
			}
		}
	}
    return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

	EnteringVehID[playerid] = INVALID_VEHICLE_ID;
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate != PLAYER_STATE_NONE && newstate != PLAYER_STATE_SPECTATING)
	{
		if(!AVC_PConnected[playerid] && !InCharSelection[playerid] && !pLoginSpawnLoaded[playerid])
		{
			SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Fake Login. "YELLOW"[SCN]");
			return KickEx(playerid);
		}
	}

	if(newstate == PLAYER_STATE_DRIVER) //naik
	{
		if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

		if(GetPlayerSkin(playerid) == 0)
		{
			AccountData[playerid][pSkin] = 1;
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			return KickEx(playerid);
		}

		if(AC_LastState[playerid] == newstate && AC_LastStateTime[playerid] != 0 && (GetTickCount() - AC_LastStateTime[playerid]) < 900)
		{
			SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}diduga Car Grabber.", GetName(playerid), playerid);
		}
		SavingVehID[playerid] = GetPlayerVehicleID(playerid);

		if(GetPlayerVehicleID(playerid) != EnteringVehID[playerid])
		{

		}
		else
		{
			ValidVehicleDriver[SavingVehID[playerid]] = playerid;
		}

		if(ValidVehicleDriver[SavingVehID[playerid]] != INVALID_PLAYER_ID)
		{
			if(GetVehicleDriver(SavingVehID[playerid]) != ValidVehicleDriver[SavingVehID[playerid]]) //jika driver dari kendaraan yang dinaiki tidak sama dengan valid driver sesungguhnya.
			{
				StopRunningAnimation(playerid);
				RemovePlayerFromVehicle(playerid);
				SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You were kicked from the server on suspicion Trolling Car Jacked!");
				return KickEx(playerid);
			}
		}
	
		if(DestroyDynamicMapIcon(AccountData[playerid][pSharedGPSIcon]))
			AccountData[playerid][pSharedGPSIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		if(AccountData[playerid][pKnockdown] && !AccountData[playerid][pDetained])
        {
			new Float:slx, Float:sly, Float:slz;
			GetPlayerPos(playerid, slx, sly, slz);
			SetPlayerPos(playerid, slx, sly, slz + 3.5);
			return 1;
        }

		foreach(new pv : PvtVehicles)
		{
			if(SavingVehID[playerid] == PlayerVehicle[pv][pVehPhysic])
			{
				if(IsABike(SavingVehID[playerid]) || GetVehicleModel(SavingVehID[playerid]) == 424)
				{
					if(VehicleCore[SavingVehID[playerid]][vCoreLocked])
					{
						new Float:slx, Float:sly, Float:slz;
						GetPlayerPos(playerid, slx, sly, slz);
						SetPlayerPos(playerid, slx, sly, slz + 3.5);
						ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");
						return 1;
					}
				}

				if(PlayerVehicle[pv][pVehTireLocked])
				{
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz + 3.5);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang dalam kondisi tirelocked!");
					return 1;
				}
			}
		}

		foreach(new i : Player) if(i != playerid)
		{
			if(AccountData[i][pSpawned] && AccountData[i][pSpec] != INVALID_PLAYER_ID)
			{
				if(AccountData[i][pSpec] == playerid)
				{
					PlayerSpectateVehicle(i, SavingVehID[playerid]);
				}
			}
		}
		
		ShowSpeedoTD(playerid);
		ShowRadarMapForPlayer(playerid);

		if(IsAMowingSidejobVeh(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pMowingSidejobDelay] > 0)
			{
				PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda masih memiliki delay %d menit.", AccountData[playerid][pMowingSidejobDelay]/60));
                RemovePlayerFromVehicle(playerid);
                SetTimerEx("RespawnPV", 1500, false, "d", SavingVehID[playerid]);
				return 1;
			}

            if(AccountData[playerid][pSideJob] != SIDEJOB_MOWING)
            {
                Dialog_Show(playerid, "SidejobMowing", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Sidejob Mowing", "Apakah anda ingin memulai tugas mowing?\nAnda akan menerima bayaran berdasarkan jumlah rumput yang anda potong.", "Yes", "No");
            }
		}

		if(IsASweeperSidejobVeh(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pSweeperSidejobDelay] > 0)
			{
				PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda masih memiliki delay %d menit.", AccountData[playerid][pSweeperSidejobDelay]/60));
                RemovePlayerFromVehicle(playerid);
                SetTimerEx("RespawnPV", 1500, false, "d", SavingVehID[playerid]);
				return 1;
			}

			if(AccountData[playerid][pSideJob] != SIDEJOB_SWEEPER)
            {
                Dialog_Show(playerid, "SidejobSweeper", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Sidejob Sweeper", "Apakah anda ingin memulai tugas sweeper?\nAnda akan menerima bayaran setelah membersihkan jalanan.", "Yes", "No");
            }
		}

		if(IsAForkliftSidejobVeh(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pForkliftSidejobDelay] > 0)
			{
				PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda masih memiliki delay %d menit.", AccountData[playerid][pForkliftSidejobDelay]/60));
                RemovePlayerFromVehicle(playerid);
                SetTimerEx("RespawnPV", 1500, false, "d", SavingVehID[playerid]);
				return 1;
			}

            if(AccountData[playerid][pSideJob] != SIDEJOB_FORKLIFT)
            {
                Dialog_Show(playerid, "SidejobForklift", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Sidejob Forklift", "Apakah anda ingin memulai tugas forklift?\nAnda akan menerima bayaran setelah membongkar muat 10 crates.", "Yes", "No");
            }
		}

		if(IsATrashCollectorSidejobVeh(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pTrashCollectorDelay] > 0)
			{
				PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda masih memiliki delay %d menit.", AccountData[playerid][pTrashCollectorDelay]/60));
                RemovePlayerFromVehicle(playerid);
                SetTimerEx("RespawnPV", 1500, false, "d", SavingVehID[playerid]);
				return 1;
			}

			if(TrashCollectorPlayerVeh[playerid] == SavingVehID[playerid])
			{
				TrashCollectorLeavingTime[playerid] = 0;
				SetVehicleParamsForPlayer(TrashCollectorPlayerVeh[playerid], playerid, 0, 0);
				Streamer_Update(playerid, -1);
			}

            if(AccountData[playerid][pSideJob] != SIDEJOB_TRASHCOLLECTOR)
            {
                Dialog_Show(playerid, "SidejobTrashCollector", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Sidejob Trash Collector", "Apakah anda ingin memulai tugas trash collector?\nAnda akan menerima bayaran setelah mengangkut 25 trash.", "Yes", "No");
            }
		}

		if(SavingVehID[playerid] == g_CarstealCarPhysic[playerid])
		{
			if(g_CarstealCarPhysic[playerid] != INVALID_VEHICLE_ID)
			{
				if(!AccountData[playerid][pDuringCarsteal])
				{
					ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki akses atas kendaraan ini!");
					RemovePlayerFromVehicle(playerid);
					return 1;
				}

				if(g_CarstealCarDelivered[playerid])
				{
					ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon lakukan pembongkaran spare part kendaraan secepatnya!");
					RemovePlayerFromVehicle(playerid);
					return 1;
				}

				new pltcstl[128];
				format(pltcstl, sizeof(pltcstl), ""RED"DICURI");
				SetVehicleNumberPlate(g_CarstealCarPhysic[playerid], pltcstl);
				ShowFivemNotify(playerid, "Pahlawan Roleplay~n~CAR STEAL", "Anda telah menemukan kendaraannya, kembalikan kepada gangster", "hud:radar_qmark", 25);

				ResetAllRaceCP(playerid);
				
				AccountData[playerid][pCarstealRCP] = CreateDynamicRaceCP(1, 930.0488,2079.8757,10.8203, 930.0488,2079.8757,10.8203, 3.5, 0, 0, playerid, 10000.00, -1, 0);
				
				if(!g_CarstealCarFound[playerid])
				{
					new Float:crstlX, Float:crstlY, Float:crstlZ;
					GetVehiclePos(g_CarstealCarPhysic[playerid], crstlX, crstlY, crstlZ);
					foreach(new i : LSPDDuty)
					{
						ShowFivemNotify(i, "Pahlawan Roleplay~n~CAR STEAL", sprintf("Pencurian kendaraan %s berlangsung di %s", GetVehicleModelName(GetVehicleModel(g_CarstealCarPhysic[playerid])), GetLocation(crstlX, crstlY, crstlZ)), "hud:radar_qmark", 25);
			
						if(DestroyDynamicMapIcon(AccountData[playerid][g_CarstealIcon][i]))
							AccountData[playerid][g_CarstealIcon][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

						AccountData[playerid][g_CarstealIcon][i] = CreateDynamicMapIcon(crstlX, crstlY, crstlZ, 0, Y_TOMATO, -1, -1, i, 10000.00, MAPICON_GLOBAL, -1, 0);
					}
				}
				g_CarstealCarFound[playerid] = true;
			}
		}

		if(IsAJobVehicle(SavingVehID[playerid]))
		{
			if(JobVehicle[playerid] != SavingVehID[playerid])
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukanlah kendaraan job anda!");
				return 1;
			}
		}

		if(IsLSPDVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_LSPD)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
				return 1;
			}
		}

		if(IsLSFDVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_LSFD)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
				return 1;
			}
		}

		if(IsSAGOVVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_SAGOV)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
				return 1;
			}
		}

		if(IsPutrideliVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_PUTRIDELI)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Putri Deli Beach Club!");
				return 1;
			}
		}

		if(IsUberVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_UBER)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
				return 1;
			}
		}

		if(IsBennysVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_BENNYS)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
				return 1;
			}
		}

		if(IsAutomaxVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_AUTOMAX)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Automax Workshop!");
				return 1;
			}
		}

		if(IsHandoverVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_HANDOVER)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Handover Motorworks!");
				return 1;
			}
		}

		if(IsDinarbucksVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_DINARBUCKS)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Loving Donuts!");
				return 1;
			}
		}

		if(IsFOX11LAVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_FOX11)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pewarta Pahlawan Roleplay!");
				return 1;
			}
		}

		if(IsTexasVehicle(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pFaction] != FACTION_TEXAS)
			{
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz + 3.5);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Texas Chicken!");
				return 1;
			}
		}

		if(IsABike(SavingVehID[playerid])) //jika motor
		{
			if(IsEngineVehicle(SavingVehID[playerid])) //motor mesin
			{
				new randhelmet = random(5);
				switch(randhelmet)
				{
					case 0:
					{
						SetPlayerAttachedObject(playerid,0,18978,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
					case 1:
					{
						SetPlayerAttachedObject(playerid,0,18977,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
					case 2:
					{
						SetPlayerAttachedObject(playerid,0,18979,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
					case 4:
					{
						SetPlayerAttachedObject(playerid,0,18645,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
					default:
					{
						SetPlayerAttachedObject(playerid,0,18978,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
				}
			}
			else //sepeda
			{
				SetPlayerAttachedObject(playerid,0,19102,2,0.15,0.00,0.00,0.0,0.0,0.0,1.14,1.10,1.11);
			}
		}

		if(IsEngineVehicle(SavingVehID[playerid]))
		{
			if(!GetEngineStatus(SavingVehID[playerid]) && !AccountData[playerid][pTurningEngine])
			{
				AccountData[playerid][pTurningEngine] = true;
				SendRPMeAboveHead(playerid, "Mencoba menghidupkan mesin kendaraannya.");
				SetTimerEx("EngineStatus", 2000, false, "id", playerid, SavingVehID[playerid]);
			}
		}
		AC_LastStateTime[playerid] = GetTickCount();
	}

	if(newstate == PLAYER_STATE_WASTED && OJailData[playerid][jailTime] < 1)
    {
		if(GetPlayerSkin(playerid) == 0)
		{
			AccountData[playerid][pSkin] = 1;
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			return KickEx(playerid);
		}

		if(AccountData[playerid][pInEvent])
		{
			ResetPlayerWeapons(playerid);

			if(EventInfo[eventType] == 1) //jika event tdm
			{
				if(Iter_Contains(EvRedTeam, playerid))
				{
					SetSpawnInfo(playerid, 1, EventInfo[redSkin], EventInfo[redSpawn][0], EventInfo[redSpawn][1], EventInfo[redSpawn][2], EventInfo[redSpawn][3], 0, false, false, false, false, false);
				}

				if(Iter_Contains(EvBlueTeam, playerid))
				{
					SetSpawnInfo(playerid, 2, EventInfo[blueSkin], EventInfo[blueSpawn][0], EventInfo[blueSpawn][1], EventInfo[blueSpawn][2], EventInfo[blueSpawn][3], 0, false, false, false, false, false);
				}
			}
			else if(EventInfo[eventType] == 3) //jika event zombie
			{
				if(Iter_Contains(EvZombieTeam, playerid))
				{
					SetSpawnInfo(playerid, 2, 162, EventInfo[zombieSpawn][0], EventInfo[zombieSpawn][1], EventInfo[zombieSpawn][2], EventInfo[zombieSpawn][3], 0, false, false, false, false, false);
				}

				if(Iter_Contains(EvHumanTeam, playerid))
				{
					SetSpawnInfo(playerid, 1, AccountData[playerid][pSkin], EventInfo[humanSpawn][0], EventInfo[humanSpawn][1], EventInfo[humanSpawn][2], EventInfo[humanSpawn][3], 0, false, false, false, false, false);
				}
			}
			else if(EventInfo[eventType] == 5) //jika event squid game
			{
				if(!AccountData[playerid][pIsUsingUniform])
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], AccountData[playerid][pPos][3], 0, 0, 0, 0, 0, 0);
				else
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pUniform], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], AccountData[playerid][pPos][3], 0, 0, 0, 0, 0, 0);
			}
		}
		else
		{
			/*
			if(AccountData[playerid][pKnockdown]) //mati lagi dalam keadaan knock
			{
				AccountData[playerid][pComma] = true;
			}
			*/
			GetPlayerArmour(playerid, AccountData[playerid][pArmor]);

			AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			AccountData[playerid][pInterior] = GetPlayerInterior(playerid);

			AccountData[playerid][pAccDeathTime] = gettime() + 480;
			AccountData[playerid][pKnockdown] = true;
			AccountData[playerid][pKnockdownTime] = 3600;

			static frmtsql[215];
			mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `player_characters` SET `Char_Knockdown` = 1, `Char_KnockdownTime` = 1800 WHERE `pID` = %d", AccountData[playerid][pID]);
			mysql_pquery(g_SQL, frmtsql);

			GetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
			
			if(!AccountData[playerid][pIsUsingUniform])
			{
				SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], 0.0, 0, false, false, false, false, false);
			}
			else
			{
				SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pUniform], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], 0.0, 0, false, false, false, false, false);
			}

			if(Iter_Count(LSFDDuty) < 2)
				SendClientMessage(playerid, -1, "Anda pingsan tetapi tidak ada MEDIS yang bertugas, gunakan "YELLOW"'/medic' "WHITE"untuk memanggil dokter lokal.");
		}

		if(SavingVehID[playerid] != INVALID_VEHICLE_ID)
		{
			ValidVehicleDriver[SavingVehID[playerid]] = INVALID_PLAYER_ID;
		}
	}

	if(newstate == PLAYER_STATE_PASSENGER) //naik penumpang
    {
		if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

		if(GetPlayerSkin(playerid) == 0)
		{
			AccountData[playerid][pSkin] = 1;
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			return KickEx(playerid);
		}

		if(AC_LastState[playerid] == newstate && AC_LastStateTime[playerid] != 0 && (GetTickCount() - AC_LastStateTime[playerid]) < 900)
		{
			SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}diduga Car Grabber.", GetName(playerid), playerid);
		}
		SavingVehID[playerid] = GetPlayerVehicleID(playerid);
		
		foreach(new i : Player) if(i != playerid)
		{
			if(AccountData[i][pSpawned] && AccountData[i][pSpec] != INVALID_PLAYER_ID)
			{
				if(AccountData[i][pSpec] == playerid)
				{
					PlayerSpectateVehicle(i, SavingVehID[playerid]);
				}
			}
		}

		ShowRadarMapForPlayer(playerid);
		if(GetPlayerVehicleID(playerid) != EnteringVehID[playerid])
		{
			SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena diduga Vehicle Troll!");
			KickEx(playerid);
			return 1;
		}

		AC_LastStateTime[playerid] = GetTickCount();

		if(AccountData[playerid][pKnockdown] && !AccountData[playerid][pDetained])
        {
			RemovePlayerFromVehicle(playerid);
			return 1;
        }

		if(IsABike(SavingVehID[playerid])) //jika motor
		{
			if(IsEngineVehicle(SavingVehID[playerid])) //motor mesin
			{
				new randhelmet = random(5);
				switch(randhelmet)
				{
					case 0:
					{
						SetPlayerAttachedObject(playerid,0,18978,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
					case 1:
					{
						SetPlayerAttachedObject(playerid,0,18977,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
					case 2:
					{
						SetPlayerAttachedObject(playerid,0,18979,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
					case 4:
					{
						SetPlayerAttachedObject(playerid,0,18645,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
					default:
					{
						SetPlayerAttachedObject(playerid,0,18978,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
					}
				}
			}
			else //sepeda
			{
				SetPlayerAttachedObject(playerid,0,19102,2,0.15,0.00,0.00,0.0,0.0,0.0,1.14,1.10,1.11);
			}
		}
	}

	if(oldstate == PLAYER_STATE_PASSENGER && newstate == PLAYER_STATE_ONFOOT) //turun penumpang
	{
		if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

		if(GetPlayerSkin(playerid) == 0)
		{
			AccountData[playerid][pSkin] = 1;
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			return KickEx(playerid);
		}

		if(AC_LastState[playerid] == newstate && AC_LastStateTime[playerid] != 0 && (GetTickCount() - AC_LastStateTime[playerid]) < 900)
		{
			SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}diduga Car Grabber.", GetName(playerid), playerid);
		}

		HideRadarMapForPlayer(playerid);
		EnteringVehID[playerid] = INVALID_VEHICLE_ID;
		SavingVehID[playerid] = INVALID_VEHICLE_ID;

		foreach(new i : Player) if(i != playerid)
		{
			if(AccountData[i][pSpawned] && AccountData[i][pSpec] != INVALID_PLAYER_ID)
			{
				if(AccountData[i][pSpec] == playerid)
				{
					PlayerSpectatePlayer(i, playerid);
				}
			}
		}
		AC_LastStateTime[playerid] = GetTickCount();

		RemovePlayerAttachedObject(playerid, 0);

		if(pToys[playerid][0][toy_model] != 0)
		{
			SetPlayerAttachedObject(playerid,
			0,
			pToys[playerid][0][toy_model],
			pToys[playerid][0][toy_bone],
			pToys[playerid][0][toy_x],
			pToys[playerid][0][toy_y],
			pToys[playerid][0][toy_z],
			pToys[playerid][0][toy_rx],
			pToys[playerid][0][toy_ry],
			pToys[playerid][0][toy_rz],
			pToys[playerid][0][toy_sx],
			pToys[playerid][0][toy_sy],
			pToys[playerid][0][toy_sz],
			pToys[playerid][0][matcolor1][4],
			pToys[playerid][0][matcolor2][4]);
		}

		if(AccountData[playerid][pBuckledOn])
		{
			AccountData[playerid][pBuckledOn] = false;
			SendRPMeAboveHead(playerid, "Melepaskan sabuk pengamannya.");
		}
	}

	if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT) //turun
	{
		if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

		if(GetPlayerSkin(playerid) == 0)
		{
			AccountData[playerid][pSkin] = 1;
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			return KickEx(playerid);
		}

		if(AC_LastState[playerid] == newstate && AC_LastStateTime[playerid] != 0 && (GetTickCount() - AC_LastStateTime[playerid]) < 900)
		{
			SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}diduga Car Grabber.", GetName(playerid), playerid);
		}

		foreach(new i : Player) if(i != playerid)
		{
			if(AccountData[i][pSpawned] && AccountData[i][pSpec] != INVALID_PLAYER_ID)
			{
				if(AccountData[i][pSpec] == playerid)
				{
					TogglePlayerSpectating(i, true);
					PlayerSpectatePlayer(i, playerid);
				}
			}
		}

		if(DestroyDynamicMapIcon(AccountData[playerid][pSharedGPSIcon]))
			AccountData[playerid][pSharedGPSIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		if(AccountData[playerid][pInEvent])
		{
			ResetPlayerWeapons(playerid);

			if(Iter_Contains(EvBlueTeam, playerid))
				Iter_Remove(EvBlueTeam, playerid);
			
			if(Iter_Contains(EvRedTeam, playerid))
				Iter_Remove(EvRedTeam, playerid);

			if(Iter_Contains(EvHumanTeam, playerid))
				Iter_Remove(EvHumanTeam, playerid);
			
			if(Iter_Contains(EvZombieTeam, playerid))
				Iter_Remove(EvZombieTeam, playerid);
			
			if(Iter_Contains(InEvent, playerid))
				Iter_Remove(InEvent, playerid);

			LeaveEvent(playerid);

			SendClientMessage(playerid, -1, "[OOC Event] Anda dieleminasi dari event karena turun dari kendaraan.");

			if(EventInfo[eventType] == 2)
			{
				foreach(new i : InEvent)
				{
					SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"telah tereleminasi karena turun dari kendaraan.", AccountData[playerid][pName]);
				}
			}
		}

		foreach(new pv : PvtVehicles)
		{
			if(PlayerVehicle[pv][pVehPhysic] == SavingVehID[playerid])
			{
				Vehicle_GetStatus(pv);
			}
		}

		if(IsAMowingSidejobVeh(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pSideJob] == SIDEJOB_MOWING)
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda turun dari kendaraan, tugas mowing telah dinyatakan gagal.");
				CancelMowingSideJob(playerid);
			}
		}

		if(IsASweeperSidejobVeh(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pSideJob] == SIDEJOB_SWEEPER)
			{
				if(DestroyDynamicCP(SweeperCP[playerid]))
					SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

				AccountData[playerid][pSideJob] = SIDEJOB_NONE;
				SweeperCPPath[playerid] = 0;
				SweeperRute[playerid] = -1;
				AccountData[playerid][pSweeperSidejobDelay] = 1800;

				SetTimerEx("RespawnPV", 1000, false, "d", SavingVehID[playerid]);
				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda turun dari kendaraan, tugas sweeper telah dinyatakan gagal.");
			}
		}

		if(IsAForkliftSidejobVeh(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pSideJob] == SIDEJOB_FORKLIFT)
			{
				ForkliftUnloadedCrate[playerid] = 0;
				AccountData[playerid][pSideJob] = SIDEJOB_NONE;

				AccountData[playerid][pForkliftSidejobDelay] = 1800;

				SetTimerEx("RespawnPV", 1000, false, "d", SavingVehID[playerid]);

				if(DestroyDynamicCP(ForkliftCP[playerid]))
					ForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

				if(DestroyDynamicCP(ForkliftReturnCP[playerid]))
					ForkliftReturnCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

				if(DestroyDynamicCP(UnloadForkliftCP[playerid]))
					UnloadForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

				if(DestroyDynamicObject(ForkliftCrateObj[playerid]))
					ForkliftCrateObj[playerid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

				TogglePlayerControllable(playerid, true);

				ShowTDN(playerid, NOTIFICATION_ERROR, "Anda turun dari kendaraan, tugas forklift telah dinyatakan gagal.");
			}
		}

		if(IsATrashCollectorSidejobVeh(SavingVehID[playerid]))
		{
			if(AccountData[playerid][pSideJob] == SIDEJOB_TRASHCOLLECTOR)
			{
				SetVehicleParamsForPlayer(TrashCollectorPlayerVeh[playerid], playerid, 1, 0);
				TrashCollectorLeavingTime[playerid] = 60;
			}
		}
		PlayerTextDrawHide(playerid, FooterTD[playerid]);

		if(IsEngineVehicle(SavingVehID[playerid]) && GetEngineStatus(SavingVehID[playerid]))
		{
			SwitchVehicleLight(SavingVehID[playerid], false);
			SwitchVehicleEngine(SavingVehID[playerid], false);

			AccountData[playerid][pTurningEngine] = false;
			SendRPMeAboveHead(playerid, "Mematikan mesin kendaraannya.");
		}

		HideRadarMapForPlayer(playerid);
		HideSpeedoTD(playerid);
		if(SavingVehID[playerid] != INVALID_VEHICLE_ID)
			ValidVehicleDriver[SavingVehID[playerid]] = INVALID_PLAYER_ID;
		EnteringVehID[playerid] = INVALID_VEHICLE_ID;
		SavingVehID[playerid] = INVALID_VEHICLE_ID;

		AC_LastStateTime[playerid] = GetTickCount();
		
		RemovePlayerAttachedObject(playerid, 0);

		if(pToys[playerid][0][toy_model] != 0)
		{
			SetPlayerAttachedObject(playerid,
			0,
			pToys[playerid][0][toy_model],
			pToys[playerid][0][toy_bone],
			pToys[playerid][0][toy_x],
			pToys[playerid][0][toy_y],
			pToys[playerid][0][toy_z],
			pToys[playerid][0][toy_rx],
			pToys[playerid][0][toy_ry],
			pToys[playerid][0][toy_rz],
			pToys[playerid][0][toy_sx],
			pToys[playerid][0][toy_sy],
			pToys[playerid][0][toy_sz],
			pToys[playerid][0][matcolor1][4],
			pToys[playerid][0][matcolor2][4]);
		}

		if(AccountData[playerid][pBuckledOn])
		{
			AccountData[playerid][pBuckledOn] = false;
			SendRPMeAboveHead(playerid, "Melepaskan sabuk pengamannya.");
		}
	}

	if(newstate == PLAYER_STATE_ONFOOT) //anti cheat car destroyer (pada saat turun)
	{
		if(SavingVehID[playerid] != INVALID_VEHICLE_ID)
		{
			ValidVehicleDriver[SavingVehID[playerid]] = INVALID_PLAYER_ID;
		}
	}
	AC_LastState[playerid] = oldstate;
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(AccountData[playerid][pSpawned])
	{
		if(AccountData[playerid][pAdmin] != 0)
		{
			if(AccountData[playerid][pAdminDuty])
			{
				ShowPlayerStats(playerid, clickedplayerid);
			}
		}
	}
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

	if(AccountData[playerid][pSpawned])
	{
		if(AccountData[playerid][pAdmin] != 0)
		{
			if(AccountData[playerid][pAdminDuty])
			{
				if(IsPlayerInAnyVehicle(playerid))
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);
				}
				else
				{
					SetPlayerPos(playerid, fX, fY, fZ);
				}
				Anticheat[playerid][acImmunity] = gettime() + 5;
				return 1;
			}
		}

		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
		{
			new driverid = GetVehicleDriver(GetPlayerVehicleID(playerid));
			if(driverid != INVALID_PLAYER_ID)
			{
				if(DestroyDynamicMapIcon(AccountData[driverid][pSharedGPSIcon]))
					AccountData[driverid][pSharedGPSIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

				AccountData[driverid][pHasSharedGPS] = true;
				AccountData[driverid][pSharedGPSIcon] = CreateDynamicMapIcon(fX, fY, fZ, 0, 0xFF99A4FF, -1, -1, driverid, 10000.00, MAPICON_GLOBAL, -1, 0);
				ShowTDN(driverid, NOTIFICATION_INFO, "Seseorang telah menandai lokasi di map anda.");
			}
		}
	}
	return 1;
}

OnPlayerUseItem(playerid, const name[])
{
	new const itemnames[][32] = {
		"Elektronik Rusak",
		"Ayam",
		"Ayam Potong",
		"Ayam Kemas",
		"Minyak Bumi",
		"Minyak Saringan",
		"Minyak",
		"Ikan",
		"Batu",
		"Batu Cucian",
		"Tembaga",
		"Besi",
		"Emas",
		"Berlian",
		"Plastik",
		"Kentang",
		"Kubis",
		"Bawang",
		"Tomat",
		"Kentang Potong",
		"Kubis Potong",
		"Bawang Potong",
		"Tomat Potong",
		"Air",
		"Gula",
		"Micin",
		"Kertas",
		"Cangkul",
		"Cabai",
		"Tebu",
		"Padi",
		"Chili Sauce",
		"Rice",
		"Sampah Makanan",
		"Botol",
		"Linggis",
		"Kunci T",
		"Alat Hack",
		"Obeng",
		"Komponen",
		"Medkit",
		"Daun Ganja",
		"Efedrin",
		"Stimulan",
		"Sabu Kristal",
		"Hunt Ammo",
		"Daging",
		"Tanduk",
		"Kulit"
    };

	for(new x; x < sizeof(itemnames); x++)
	{
		if(!strcmp(name, itemnames[x]))
		{
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Item ini tidak dapat digunakan!");
		}
	}

	if(!strcmp(name, "Ransel"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		Inventory_Close(playerid);

		pOpenBackpackTimer[playerid] = true;

		SendRPMeAboveHead(playerid, "Mengambil ransel dan membukanya.");
	}

	else if(!strcmp(name, "Toolkit"))
	{
		new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
		if(vehid != INVALID_VEHICLE_ID)
		{
			Inventory_Remove(playerid, name);

			ApplyAnimation(playerid, "CAR", "Fixn_Car_Loop", 5.00, 1, 0, 0, 0, 0, 1);

			ShowItemBox(playerid, "Toolkit", "Removed 1x", 19921, 5);

			AccountData[playerid][pActivityTime] = 1;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMPERBAIKI");
			ShowProgressBar(playerid);

			SendRPMeAboveHead(playerid, "Memperbaiki kendaraannya dengan toolkit.");

			Inventory_Close(playerid);

			AccountData[playerid][pTempVehID] = vehid;
			pRepairingToolkitTimer[playerid] = true;
		}
	}

	else if(!strcmp(name, "BBQ Delicy"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Membuka paket makanan BBQ Delicy.");

		Inventory_Close(playerid);

		pOpenShotDeluxeTimer[playerid] = true;
	}

	else if(!strcmp(name, "Buckshot Special"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Membuka paket makanan Buckshot Special.");

		Inventory_Close(playerid);

		pOpenBuckshotSpecialTimer[playerid] = true;
	}
	else if(!strcmp(name, "Frenchy Velty"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Membuka paket makanan Frenchy Velty.");

		Inventory_Close(playerid);

		pOpenTelaGoodieTimer[playerid] = true;
	}
	else if(!strcmp(name, "Rice Combo"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Membuka paket makanan Rice Combo.");

		Inventory_Close(playerid);

		pOpenAndalasPrideTimer[playerid] = true;
	}
	else if(!strcmp(name, "Minang Combo"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Membuka paket makanan Minang Combo.");

		Inventory_Close(playerid);

		pOpenMinangComboTimer[playerid] = true;
	}
	else if(!strcmp(name, "Malaya Shine"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Membuka paket makanan Malaya Shine.");

		Inventory_Close(playerid);

		pOpenMalayaShineTimer[playerid] = true;
	}
	else if(!strcmp(name, "Fresh Solar"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Membuka paket makanan Fresh Solar.");

		Inventory_Close(playerid);

		pOpenFreshSolarTimer[playerid] = true;
	}
	else if(!strcmp(name, "Softex Flash"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Membuka paket makanan Softex Flash.");

		Inventory_Close(playerid);

		pOpenSoftexFlashTimer[playerid] = true;
	}
	else if(!strcmp(name, "Purple Sweet"))
	{
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUKA");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Membuka paket makanan Purple Sweet.");

		Inventory_Close(playerid);

		pOpenPurpleSweetTimer[playerid] = true;
	}

	else if(!strcmp(name, "Skateboard"))
	{
		if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");

		Inventory_Close(playerid);

		if(AccountData[playerid][pHoldingSkate])
		{
			ApplyAnimation(playerid,"ped","FALL_COLLAPSE",4.1,false,true,true,false,0,true);
			AccountData[playerid][pHoldingSkate] = false;
			AccountData[playerid][pSkating] = false;
			RemovePlayerAttachedObject(playerid, 9);
		}
		else
		{
			AccountData[playerid][pHoldingSkate] = true;
			SetPlayerAttachedObject(playerid, 9, 19878, 6, -0.073999, 0.000000, 0.000000, -86.399948, 1.800001, 82.200019, 1.000000, 1.000000, 1.000000);
		}
	}

	else if(!strcmp(name, "Karung Goni"))
	{
		Inventory_Close(playerid);

		new frmxt[522], count = 0;

		foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 3.2)) 
		{
			if (i % 2 == 0) {
				format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
			}
			else {
				format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
			}
			NearestUser[playerid][count++] = i;
		}

		if(count == 0) 
		{
			PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
			return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Karung Goni", "Tidak ada pemain terdekat!", "Tutup", "");
		}

		Dialog_Show(playerid, "Blindfold", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Karung Goni", frmxt, "Pilih", "Batal");
	}

	else if(!strcmp(name, "Senter"))
	{
		Inventory_Close(playerid);

		if(AccountData[playerid][pHoldFlashlight])
		{
			StopLoopingAnim(playerid);
			AccountData[playerid][pHoldFlashlight] = false;
			AccountData[playerid][pFlashlightOn] = false;
			RemovePlayerAttachedObject(playerid, 1);
			RemovePlayerAttachedObject(playerid, 9);

			if(pToys[playerid][1][toy_model] != 0)
			{
				SetPlayerAttachedObject(playerid,
				1,
				pToys[playerid][1][toy_model],
				pToys[playerid][1][toy_bone],
				pToys[playerid][1][toy_x],
				pToys[playerid][1][toy_y],
				pToys[playerid][1][toy_z],
				pToys[playerid][1][toy_rx],
				pToys[playerid][1][toy_ry],
				pToys[playerid][1][toy_rz],
				pToys[playerid][1][toy_sx],
				pToys[playerid][1][toy_sy],
				pToys[playerid][1][toy_sz],
				pToys[playerid][1][matcolor1][4],
				pToys[playerid][1][matcolor2][4]);
			}
		}
		else
		{
			AccountData[playerid][pHoldFlashlight] = true;
			AccountData[playerid][pFlashlightOn] = false;
			ApplyAnimation(playerid, "ped", "phone_talk", 2.00, true, true, true, true, 1, true);
			SetPlayerAttachedObject(playerid, 9, 18641, 6, 0.096000, 0.006999, -0.054000, -26.000022, -21.500000, 0.000000, 1.000000, 1.000000, 1.000000);

			SendClientMessage(playerid, -1, "Gunakan "YELLOW"tombol 'Y' "WHITE"untuk menyalakan/mematikan lampu flashlight.");
		}
	}

	else if(!strcmp(name, "Disposable Phone"))
	{
		if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
		if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Item ini hanya dapat digunakan oleh member family official!");
		
		Inventory_Close(playerid);

		Dialog_Show(playerid, "DisposPhoneCatalog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Order Gun & Equipment", 
        "Item\tPrice\n\
		Colt-45\t$3,000\n\
        "GRAY"Desert Eagle\t"GRAY"$7,000\n\
        Shotgun\t$6,000\n\
        "GRAY"Tec-9\t"GRAY"$7,000\n\
        Uzi\t$7,000", "Pilih", "Batal");
	}

	else if(!strcmp(name, "Pilox"))
	{
		if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
		
		Inventory_Close(playerid);

		if(CountingPlayerTags(playerid) >= GetPlayerTagLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai batas slot tagging maksimal!");
		
		Dialog_Show(playerid, "GraffitiAdd", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Add Graffiti", 
		"Mohon masukkan tulisan graffiti yang ingin dibuat:\n\
		(n) = text akan berada di bawah/baris baru.\n\
		(r) = warna text merah.\n\
		(b) = warna text hitam.\n\
		(y) = warna text kuning.\n\
		(bl) = warna text biru.\n\
		(g) = warna text hijau.\n\
		(o) = warna text orange.\n\
		(w) = warna text putih.", "Input", "Batal");
	}

	else if(!strcmp(name, "Bibit Cabai"))
	{
		if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
		if(!IsPlayerInDynamicArea(playerid, FarmingZone1) && !IsPlayerInDynamicArea(playerid, FarmingZone2) && !IsPlayerInDynamicArea(playerid, FarmingZone3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di area ladang!");
		if(IsPlayerNearFromPlant(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu dekat dengan tanaman lain!");
		if(!PlayerHasItem(playerid, "Cangkul")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Cangkul!");

		new id = Iter_Free(FarmPlants);
		if(id <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Total tanaman di ladang sudah mencapai batas maksimum server!");
		
		if(PlayerFarmerVars[playerid][pDuringPlantingSeed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang proses menanam suatu bibit, mohon tunggu beberapa saat jangan spam!");

		new brokenObeng = RandomEx(0, 100);
		switch(brokenObeng)
		{
			case 99:
			{
				Inventory_Remove(playerid, "Cangkul");
				return SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Sayang sekali, tidak sengaja anda merusak cangkul.");
			}
		}

		PlayerFarmerVars[playerid][pDuringPlantingSeed] = true;

		ApplyAnimation(playerid, "WUZI", "Wuzi_grnd_chk", 4.1, false, false, false, false, 0, true);
		SendRPMeAboveHead(playerid, "Menanam bibit cabai dengan bantuan kedua tangan.");

		Inventory_Close(playerid);

		Inventory_Remove(playerid, "Bibit Cabai");
		GetPlayerPos(playerid, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2]);
		FarmerPlant[id][Type] = FARMER_PLANT_CABAI;
		FarmerPlant[id][ReadyHarvest] = false;
		FarmerPlant[id][DuringHarvest] = false;
		FarmerPlant[id][Watered] = false;
		FarmerPlant[id][DeadTimer] = 1800;
		FarmerPlant[id][SpawnTimer] = 900;
		FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(810, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 1.5, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
		FarmerPlant[id][FarmerPlantCP] = CreateDynamicCP(FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], 1.5, 0, 0, -1, 0.85, -1, 0);
		Iter_Add(FarmPlants, id);

		static query[555];
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `farmplants` SET `id`=%d, `posX`='%.2f', `posY`='%.2f', `posZ`='%.2f', `plantType`=%d, `spawnTimer`=%d", id, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], FarmerPlant[id][Type], FarmerPlant[id][SpawnTimer]);
		mysql_pquery(g_SQL, query, "OnPlantCreated", "ii", playerid, id);
		SetTimerEx("CooldownFarmPlant", 5255, false, "i", playerid);
	}

	else if(!strcmp(name, "Bibit Tebu"))
	{
		if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
		if(!IsPlayerInDynamicArea(playerid, FarmingZone1) && !IsPlayerInDynamicArea(playerid, FarmingZone2) && !IsPlayerInDynamicArea(playerid, FarmingZone3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di area ladang!");
		if(IsPlayerNearFromPlant(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu dekat dengan tanaman lain!");
		if(!PlayerHasItem(playerid, "Cangkul")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Cangkul!");

		new id = Iter_Free(FarmPlants);
		if(id <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Total tanaman di ladang sudah mencapai batas maksimum server!");
		
		if(PlayerFarmerVars[playerid][pDuringPlantingSeed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang proses menanam suatu bibit, mohon tunggu beberapa saat jangan spam!");

		new brokenObeng = RandomEx(0, 100);
		switch(brokenObeng)
		{
			case 99:
			{
				Inventory_Remove(playerid, "Cangkul");
				return SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Sayang sekali, tidak sengaja anda merusak cangkul.");
			}
		}

		ApplyAnimation(playerid, "WUZI", "Wuzi_grnd_chk", 4.1, false, false, false, false, 0, true);
		SendRPMeAboveHead(playerid, "Menanam bibit tebu dengan bantuan kedua tangan.");

		Inventory_Close(playerid);

		Inventory_Remove(playerid, "Bibit Tebu");
		GetPlayerPos(playerid, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2]);
		FarmerPlant[id][Type] = FARMER_PLANT_TEBU;
		FarmerPlant[id][ReadyHarvest] = false;
		FarmerPlant[id][DuringHarvest] = false;
		FarmerPlant[id][Watered] = false;
		FarmerPlant[id][DeadTimer] = 1800;
		FarmerPlant[id][SpawnTimer] = 900;
		FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(806, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 2.6, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
		FarmerPlant[id][FarmerPlantCP] = CreateDynamicCP(FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], 1.5, 0, 0, -1, 0.85, -1, 0);
		Iter_Add(FarmPlants, id);

		static query[555];
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `farmplants` SET `id`=%d, `posX`='%.2f', `posY`='%.2f', `posZ`='%.2f', `plantType`=%d, `spawnTimer`=%d", id, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], FarmerPlant[id][Type], FarmerPlant[id][SpawnTimer]);
		mysql_pquery(g_SQL, query, "OnPlantCreated", "ii", playerid, id);
		SetTimerEx("CooldownFarmPlant", 5255, false, "i", playerid);
	}

	else if(!strcmp(name, "Bibit Padi"))
	{
		if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
		if(!IsPlayerInDynamicArea(playerid, FarmingZone1) && !IsPlayerInDynamicArea(playerid, FarmingZone2) && !IsPlayerInDynamicArea(playerid, FarmingZone3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di area ladang!");
		if(IsPlayerNearFromPlant(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu dekat dengan tanaman lain!");
		if(!PlayerHasItem(playerid, "Cangkul")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Cangkul!");

		if(PlayerFarmerVars[playerid][pDuringPlantingSeed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang proses menanam suatu bibit, mohon tunggu beberapa saat jangan spam!");

		new id = Iter_Free(FarmPlants);
		if(id <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Total tanaman di ladang sudah mencapai batas maksimum server!");
		
		new brokenObeng = RandomEx(0, 100);
		switch(brokenObeng)
		{
			case 99:
			{
				Inventory_Remove(playerid, "Cangkul");
				return SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Sayang sekali, tidak sengaja anda merusak cangkul.");
			}
		}

		ApplyAnimation(playerid, "WUZI", "Wuzi_grnd_chk", 4.1, false, false, false, false, 0, true);
		SendRPMeAboveHead(playerid, "Menanam bibit padi dengan bantuan kedua tangan.");

		Inventory_Close(playerid);

		Inventory_Remove(playerid, "Bibit Padi");
		GetPlayerPos(playerid, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2]);
		FarmerPlant[id][Type] = FARMER_PLANT_PADI;
		FarmerPlant[id][ReadyHarvest] = false;
		FarmerPlant[id][DuringHarvest] = false;
		FarmerPlant[id][Watered] = false;
		FarmerPlant[id][DeadTimer] = 1800;
		FarmerPlant[id][SpawnTimer] = 900;
		FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(861, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 1.9, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
		FarmerPlant[id][FarmerPlantCP] = CreateDynamicCP(FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], 1.5, 0, 0, -1, 0.85, -1, 0);
		Iter_Add(FarmPlants, id);

		static query[555];
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `farmplants` SET `id`=%d, `posX`='%.2f', `posY`='%.2f', `posZ`='%.2f', `plantType`=%d, `spawnTimer`=%d", id, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], FarmerPlant[id][Type], FarmerPlant[id][SpawnTimer]);
		mysql_pquery(g_SQL, query, "OnPlantCreated", "ii", playerid, id);
		SetTimerEx("CooldownFarmPlant", 5255, false, "i", playerid);
	}

	else if(!strcmp(name, "Bibit Strawberry"))
	{
		if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
		if(IsPlayerInDynamicArea(playerid, FarmingZone1) || IsPlayerInDynamicArea(playerid, FarmingZone2) || IsPlayerInDynamicArea(playerid, FarmingZone3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bibit ini tidak dapat ditanam di ladang ini!");
		if(!IsPlayerInDynamicArea(playerid, FarmingFruitZone)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di ladang seharusnya!");
		if(IsPlayerNearFromPlant(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu dekat dengan tanaman lain!");
		if(!PlayerHasItem(playerid, "Cangkul")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Cangkul!");

		new id = Iter_Free(FarmPlants);
		if(id <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Total tanaman di ladang sudah mencapai batas maksimum server!");
		
		if(PlayerFarmerVars[playerid][pDuringPlantingSeed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang proses menanam suatu bibit, mohon tunggu beberapa saat jangan spam!");

		new brokenObeng = RandomEx(0, 100);
		switch(brokenObeng)
		{
			case 99:
			{
				Inventory_Remove(playerid, "Cangkul");
				return SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Sayang sekali, tidak sengaja anda merusak cangkul.");
			}
		}

		PlayerFarmerVars[playerid][pDuringPlantingSeed] = true;

		ApplyAnimation(playerid, "WUZI", "Wuzi_grnd_chk", 4.1, false, false, false, false, 0, true);
		SendRPMeAboveHead(playerid, "Menanam bibit strawberry dengan bantuan kedua tangan.");

		Inventory_Close(playerid);

		Inventory_Remove(playerid, "Bibit Strawberry");
		GetPlayerPos(playerid, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2]);
		FarmerPlant[id][Type] = FARMER_PLANT_STRAWBERRY;
		FarmerPlant[id][ReadyHarvest] = false;
		FarmerPlant[id][DuringHarvest] = false;
		FarmerPlant[id][Watered] = false;
		FarmerPlant[id][DeadTimer] = 1800;
		FarmerPlant[id][SpawnTimer] = 900;
		FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(810, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 1.5, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
		FarmerPlant[id][FarmerPlantCP] = CreateDynamicCP(FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], 1.5, 0, 0, -1, 0.85, -1, 0);
		Iter_Add(FarmPlants, id);

		static query[555];
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `farmplants` SET `id`=%d, `posX`='%.2f', `posY`='%.2f', `posZ`='%.2f', `plantType`=%d, `spawnTimer`=%d", id, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], FarmerPlant[id][Type], FarmerPlant[id][SpawnTimer]);
		mysql_pquery(g_SQL, query, "OnPlantCreated", "ii", playerid, id);
		SetTimerEx("CooldownFarmPlant", 5255, false, "i", playerid);
	}

	else if(!strcmp(name, "Bibit Jeruk"))
	{
		if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
		if(IsPlayerInDynamicArea(playerid, FarmingZone1) || IsPlayerInDynamicArea(playerid, FarmingZone2) || IsPlayerInDynamicArea(playerid, FarmingZone3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bibit ini tidak dapat ditanam di ladang ini!");
		if(!IsPlayerInDynamicArea(playerid, FarmingFruitZone)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di ladang seharusnya!");
		if(IsPlayerNearFromPlant(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu dekat dengan tanaman lain!");
		if(!PlayerHasItem(playerid, "Cangkul")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Cangkul!");

		new id = Iter_Free(FarmPlants);
		if(id <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Total tanaman di ladang sudah mencapai batas maksimum server!");
		
		if(PlayerFarmerVars[playerid][pDuringPlantingSeed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang proses menanam suatu bibit, mohon tunggu beberapa saat jangan spam!");

		new brokenObeng = RandomEx(0, 100);
		switch(brokenObeng)
		{
			case 99:
			{
				Inventory_Remove(playerid, "Cangkul");
				return SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Sayang sekali, tidak sengaja anda merusak cangkul.");
			}
		}

		PlayerFarmerVars[playerid][pDuringPlantingSeed] = true;

		ApplyAnimation(playerid, "WUZI", "Wuzi_grnd_chk", 4.1, false, false, false, false, 0, true);
		SendRPMeAboveHead(playerid, "Menanam bibit jeruk dengan bantuan kedua tangan.");

		Inventory_Close(playerid);

		Inventory_Remove(playerid, "Bibit Jeruk");
		GetPlayerPos(playerid, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2]);
		FarmerPlant[id][Type] = FARMER_PLANT_JERUK;
		FarmerPlant[id][ReadyHarvest] = false;
		FarmerPlant[id][DuringHarvest] = false;
		FarmerPlant[id][Watered] = false;
		FarmerPlant[id][DeadTimer] = 1800;
		FarmerPlant[id][SpawnTimer] = 900;
		FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(810, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 1.5, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
		FarmerPlant[id][FarmerPlantCP] = CreateDynamicCP(FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], 1.5, 0, 0, -1, 0.85, -1, 0);
		Iter_Add(FarmPlants, id);

		static query[555];
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `farmplants` SET `id`=%d, `posX`='%.2f', `posY`='%.2f', `posZ`='%.2f', `plantType`=%d, `spawnTimer`=%d", id, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], FarmerPlant[id][Type], FarmerPlant[id][SpawnTimer]);
		mysql_pquery(g_SQL, query, "OnPlantCreated", "ii", playerid, id);
		SetTimerEx("CooldownFarmPlant", 5255, false, "i", playerid);
	}

	else if(!strcmp(name, "Bibit Anggur"))
	{
		if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
		if(IsPlayerInDynamicArea(playerid, FarmingZone1) || IsPlayerInDynamicArea(playerid, FarmingZone2) || IsPlayerInDynamicArea(playerid, FarmingZone3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bibit ini tidak dapat ditanam di ladang ini!");
		if(!IsPlayerInDynamicArea(playerid, FarmingFruitZone)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di ladang seharusnya!");
		if(IsPlayerNearFromPlant(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu dekat dengan tanaman lain!");
		if(!PlayerHasItem(playerid, "Cangkul")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Cangkul!");

		new id = Iter_Free(FarmPlants);
		if(id <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Total tanaman di ladang sudah mencapai batas maksimum server!");
		
		if(PlayerFarmerVars[playerid][pDuringPlantingSeed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang proses menanam suatu bibit, mohon tunggu beberapa saat jangan spam!");

		new brokenObeng = RandomEx(0, 100);
		switch(brokenObeng)
		{
			case 99:
			{
				Inventory_Remove(playerid, "Cangkul");
				return SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Sayang sekali, tidak sengaja anda merusak cangkul.");
			}
		}

		PlayerFarmerVars[playerid][pDuringPlantingSeed] = true;

		ApplyAnimation(playerid, "WUZI", "Wuzi_grnd_chk", 4.1, false, false, false, false, 0, true);
		SendRPMeAboveHead(playerid, "Menanam bibit anggur dengan bantuan kedua tangan.");

		Inventory_Close(playerid);

		Inventory_Remove(playerid, "Bibit Anggur");
		GetPlayerPos(playerid, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2]);
		FarmerPlant[id][Type] = FARMER_PLANT_ANGGUR;
		FarmerPlant[id][ReadyHarvest] = false;
		FarmerPlant[id][DuringHarvest] = false;
		FarmerPlant[id][Watered] = false;
		FarmerPlant[id][DeadTimer] = 1800;
		FarmerPlant[id][SpawnTimer] = 900;
		FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(810, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 1.5, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
		FarmerPlant[id][FarmerPlantCP] = CreateDynamicCP(FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], 1.5, 0, 0, -1, 0.85, -1, 0);
		Iter_Add(FarmPlants, id);

		static query[555];
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `farmplants` SET `id`=%d, `posX`='%.2f', `posY`='%.2f', `posZ`='%.2f', `plantType`=%d, `spawnTimer`=%d", id, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], FarmerPlant[id][Type], FarmerPlant[id][SpawnTimer]);
		mysql_pquery(g_SQL, query, "OnPlantCreated", "ii", playerid, id);
		SetTimerEx("CooldownFarmPlant", 5255, false, "i", playerid);
	}

	else if(!strcmp(name, "Gulai Ayam"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 7;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Gulai Ayam", "Removed 1x", 2355, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Gulai Ayam dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Chicken BBQ"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 1;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Chicken BBQ", "Removed 1x", 2355, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Chicken BBQ dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Nasi Padang"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 5;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Nasi Padang", "Removed 1x", 2219, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Nasi Padang dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Roti Jala"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 6;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Roti Jala", "Removed 1x", 2355, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Roti Jala dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Donut"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 2;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Donut", "Removed 1x", 2221, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Donat dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "French Fries"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 3;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "French Fries", "Removed 1x", 2769, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil French Fries dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Fried Rice"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 4;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Fried Rice", "Removed 1x", 2219, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Fried Rice dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Burger"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 8;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Burger", "Removed 1x", 2880, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Burger dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Teriyaki"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 9;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Teriyaki", "Removed 1x", 2355, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Teriyaki dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Fried Chicken"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 10;
		AccountData[playerid][pEatingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk makan dan ~r~'/stopeating' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Fried Chicken", "Removed 1x", 2355, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Fried Chicken dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Snack"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pHunger] += 5;

		PlayEatingAnim(playerid, 19883, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Snack", "Removed 1x", 19565, 5);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 6);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MAKAN");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Mengambil Snack dan mengonsumsinya.");

		Inventory_Close(playerid);

		AccountData[playerid][pEatingDrinking] = true;
		pEatingBarTimer[playerid] = true;
	}
	else if(!strcmp(name, "Cereal"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");
		
		Inventory_Remove(playerid, name);
		AccountData[playerid][pHunger] += 5;
		
		PlayEatingAnim(playerid, 19883, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Cereal", "Removed 1x", 19562, 5);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 6);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MAKAN");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Mengambil Cereal dan mengonsumsinya.");

		Inventory_Close(playerid);

		AccountData[playerid][pEatingDrinking] = true;
		pEatingBarTimer[playerid] = true;
	}
	else if(!strcmp(name, "Nasi Uduk"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pHunger] >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda kenyang dan tidak membutuhkan makanan untuk saat ini!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pHunger] += 15;

		PlayEatingAnim(playerid, 2769, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Nasi Uduk", "Removed 1x", 2769, 5);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 6);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MAKAN");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Mengambil Nasi Uduk dan mengonsumsinya.");

		Inventory_Close(playerid);

		AccountData[playerid][pEatingDrinking] = true;
		pEatingBarTimer[playerid] = true;
	}
	else if(!strcmp(name, "Air Mineral"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		
		Inventory_Remove(playerid, name);
		AccountData[playerid][pThirst] += 15;
		
		PlayDrinkingAnim(playerid, 19570, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Air Mineral", "Removed 1x", 19570, 5);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 6);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MINUM");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Mengambil Air Mineral dan mengonsumsinya.");

		Inventory_Close(playerid);

		AccountData[playerid][pEatingDrinking] = true;
		pEatingBarTimer[playerid] = true;
	}

	else if(!strcmp(name, "Es Lilin"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return  ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 7;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Es Lilin", "Removed 1x", 19565, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Es Lilin dan mengonsumsinya.");

		Inventory_Close(playerid);
	}

	else if(!strcmp(name, "Coca-Cola"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return  ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 8;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Coca-Cola", "Removed 1x", 2647, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Coca-Cola dan mengonsumsinya.");

		Inventory_Close(playerid);
	}

	else if(!strcmp(name, "Rootbeer"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return  ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 9;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Rootbeer", "Removed 1x", 1546, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Rootbeer dan mengonsumsinya.");

		Inventory_Close(playerid);
	}

	else if(!strcmp(name, "Guinness"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return  ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 10;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Guinness", "Removed 1x", 1669, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Guinness dan mengonsumsinya.");

		Inventory_Close(playerid);
	}

	else if(!strcmp(name, "Coconut Water"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return  ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 1;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Coconut Water", "Removed 1x", 19564, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Coconut Water dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Brewed Coffee"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 2;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Brewed Coffee", "Removed 1x", 19835, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Brewed Coffee dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Jus Timun"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 5;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Jus Timun", "Removed 1x", 1546, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Jus Timun dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Sirup Selasih"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 6;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Sirup Selasih", "Removed 1x", 1544, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Sirup Selasih dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Red Velvet"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 3;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Red Velvet", "Removed 1x", 1546, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Red Velvet dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Vanilla Milkshake"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);
		AccountData[playerid][pEatingIndexID] = 4;
		AccountData[playerid][pDrinkingStep] = 5;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk minum dan ~r~'/stopdrinking' ~l~untuk berhenti.");

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Vanilla Milkshake", "Removed 1x", 19569, 4);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		SendRPMeAboveHead(playerid, "Mengambil Vanilla Milkshake dan mengonsumsinya.");

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Cola"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		
		Inventory_Remove(playerid, name);
		AccountData[playerid][pThirst] += 5;

		PlayDrinkingAnim(playerid, 2647, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Cola", "Removed 1x", 2647, 5);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MINUM");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Mengambil Cola dan mengonsumsinya.");

		Inventory_Close(playerid);

		AccountData[playerid][pEatingDrinking] = true;
		pEatingBarTimer[playerid] = true;
	}
	else if(!strcmp(name, "Sprunk"))
	{
		if(Inventory_Count(playerid, "Sampah Makanan") >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuang Sampah Makanan terlebih dahulu!");
		if(AccountData[playerid][pThirst] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda tidak haus untuk saat ini!");
		
		Inventory_Remove(playerid, name);
		AccountData[playerid][pThirst] += 5;

		PlayDrinkingAnim(playerid, 2601, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);

		Inventory_Add(playerid, "Sampah Makanan", 2840);
		ShowItemBox(playerid, "Sprunk", "Removed 1x", 2601, 5);
		ShowItemBox(playerid, "Sampah Makanan", "Received 1x", 2840, 5);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MINUM");
		ShowProgressBar(playerid);

		SendRPMeAboveHead(playerid, "Mengambil Sprunk dan mengonsumsinya.");

		Inventory_Close(playerid);

		AccountData[playerid][pEatingDrinking] = true;
		pEatingBarTimer[playerid] = true;
	}

	else if(!strcmp(name, "Jerigen"))
	{
		if(!AccountData[playerid][pHoldingFuelCan])
		{
			AccountData[playerid][pHoldingFuelCan] = true;
			SetPlayerAttachedObject(playerid, 9, 1650, 6, 0.135999, 0.038000, 0.049999, 0.000000, -100.100059, 0.000000, 1.000000, 1.000000, 1.000000);

			new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
			if(vehid != INVALID_VEHICLE_ID)
			{
				if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
					g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

				g_GasProgressLabel[playerid] = CreateDynamic3DTextLabel("Tekan "GREEN"Y "WHITE"untuk mengisi bbm", Y_WHITE, 0.0, 0.0, 1.10, 5.0, INVALID_PLAYER_ID, vehid, 0, 0, 0, playerid, 5.0, -1, 0);
			}
		}
		else
		{
			AccountData[playerid][pHoldingFuelCan] = false;
			RemovePlayerAttachedObject(playerid, 9);

			if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
				g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		}

		Inventory_Close(playerid);
	}
	else if(!strcmp(name, "Marijuana"))
	{
		if(AccountData[playerid][pArmor] >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai maksimum 100 persen armor!");

		Inventory_Remove(playerid, name);

		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 6.67, false, false, false, false, 0, true);

		ShowItemBox(playerid, "Marijuana", "Removed 1x", 1578, 5);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGHISAP");
		ShowProgressBar(playerid);

		Inventory_Close(playerid);

		pSmokingWeedTimer[playerid] = true;
	}

	else if(!strcmp(name, "Sinte"))
	{
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);

		ShowItemBox(playerid, "Sinte", "Removed 1x", 3027, 5);

		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, false, false, false, false, 0, true);

		Inventory_Close(playerid);
		
		AccountData[playerid][pUsingJoint] = true;
		AccountData[playerid][pIsSmoking] = true;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk menghisap dan ~r~'/stopsmoke' ~l~untuk berhenti.");
	}

	else if(!strcmp(name, "Sabu"))
	{
		if(AccountData[playerid][pArmor] >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai maksimum 100 persen armor!");
		
		Inventory_Remove(playerid, name);

		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 6.67, false, false, false, false, 0, true);

		ShowItemBox(playerid, "Sabu", "Removed 1x", 1575, 5);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "NYABU");
		ShowProgressBar(playerid);

		Inventory_Close(playerid);

		pUsingMethTimer[playerid] = true;
	}
	else if(!strcmp(name, "Heroin"))
	{
		new Float:pkevlar;
		GetPlayerArmour(playerid, pkevlar);
		if(pkevlar >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai maksimum 100 persen armor!");
		
		Inventory_Remove(playerid, name);

		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 6.67, false, false, false, false, 0, true);

		ShowItemBox(playerid, "Heroin", "Removed 1x", 1575, 5);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGHISAP");
		ShowProgressBar(playerid);

		Inventory_Close(playerid);

		pUsingHeroinTimer[playerid] = true;
	}
	else if(!strcmp(name, "Anggur Merah"))
	{	
		Inventory_Remove(playerid, name);

		PlayDrinkingAnim(playerid, 1544, "VENDING", "VEND_Drink2_P", 3.0, true, true, true, true, 1);

		ShowItemBox(playerid, "Anggur Merah", "Removed 1x", 1544, 5);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MINUM");
		ShowProgressBar(playerid);

		Inventory_Close(playerid);

		pDrinkingWhiskyTimer[playerid] = true;
	}
	else if(!strcmp(name, "Tuak"))
	{	
		Inventory_Remove(playerid, name);

		PlayDrinkingAnim(playerid, 1486, "VENDING", "VEND_Drink2_P", 3.0, true, true, true, true, 1);

		ShowItemBox(playerid, "Tuak", "Removed 1x", 1486, 5);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MINUM");
		ShowProgressBar(playerid);

		Inventory_Close(playerid);

		pDrinkingSojuTimer[playerid] = true;
	}

	else if(!strcmp(name, "Perban"))
	{
		new Float:HealthX;
		GetPlayerHealth(playerid, HealthX);
		if(HealthX >= 100.0)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai maksimum 100 persen health!");

		Inventory_Remove(playerid, name);

		ShowItemBox(playerid, "Perban", "Removed 1x", 11736, 5);

		ApplyAnimation(playerid, "COP_AMBIENT","Copbrowse_loop", 4.1, true, false, false, true, 0, true);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENUTUP LUKA");
		ShowProgressBar(playerid);

		Inventory_Close(playerid);

		pUsingPerbanTimer[playerid] = true;
	}

	else if(!strcmp(name, "Pil Stres"))
	{
		Inventory_Remove(playerid, name);

		ShowItemBox(playerid, "Pil Stres", "Removed 1x", 1241, 5);

		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, true, false, false, false, 0, true);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MINUM PIL");
		ShowProgressBar(playerid);

		Inventory_Close(playerid);

		pUsingPilStressTimer[playerid] = true;
	}

	else if(!strcmp(name, "Kevlar"))
	{
		new Float:pkevlar;
		GetPlayerArmour(playerid, pkevlar);
		if(pkevlar >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai maksimum 100 persen armor!");

		Inventory_Remove(playerid, name);

		ShowItemBox(playerid, "Kevlar", "Removed 1x", 19515, 5);

		ApplyAnimation(playerid, "COP_AMBIENT","Copbrowse_loop", 4.1, true, false, false, true, 0, true);

		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMAKAI KEVLAR");
		ShowProgressBar(playerid);

		Inventory_Close(playerid);

		pUsingKevlarTimer[playerid] = true;
	}

	else if(!strcmp(name, "Udud"))
	{
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		Inventory_Remove(playerid, name);

		SendRPMeAboveHead(playerid, "Mengudud.");

		ShowItemBox(playerid, "Udud", "Removed 1x", 19896, 5);

		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, false, false, false, false, 0, true);

		Inventory_Close(playerid);
		
		AccountData[playerid][pIsSmoking] = true;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk menghisap dan ~r~'/stopsmoke' ~l~untuk berhenti.");
	}

	else if(!strcmp(name, "Vape"))
	{
		if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

		if(AccountData[playerid][pVIP] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Donatur VIP Super Pinky!");

		SendRPMeAboveHead(playerid, "Mengambil vape lalu mengaturnya.");

		SetPlayerAttachedObject(playerid, 8, 19823, 6, 0.074999, 0.024000, -0.039999, 0.000000, 0.000000, 0.000000, 0.379000, 0.463000, 0.414000);
		ApplyAnimation(playerid, "SMOKING", "M_smk_tap", 4.1, false, false, false, false, 0, true);

		Inventory_Close(playerid);
		
		pIsVaping[playerid] = true;
		AccountData[playerid][pIsSmoking] = true;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Tekan ~r~'Y' ~l~untuk menghisap dan ~r~'/stopsmoke' ~l~untuk berhenti.");
	}

	else if(!strcmp(name, "Smartphone"))
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
	
		if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
		if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
		if(OJailData[playerid][jailed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
		
		Inventory_Close(playerid);
		
		if(PlayerPhoneData[playerid][phoneIncomingCall] || PlayerPhoneData[playerid][phoneDuringConversation])
		{
			CutCallingLine(playerid);
			return 1;
		}

		if(PlayerPhoneData[playerid][phoneShown])
		{
			if(pRebootingPhoneTimer[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ponsel ini sedang dihidupkan, mohon menunggu hingga selesai!");

			RemovePlayerAttachedObject(playerid, 9);
			StopLoopingAnim(playerid);

			HideAllPhoneTD(playerid);
			PlayerPhoneData[playerid][phoneShown] = false;

			SendRPMeAboveHead(playerid, "Menutup smartphone miliknya.");
		}
		else
		{
			if(PlayerPhoneData[playerid][phoneOn])
			{
				ShowPhoneLockScreenTD(playerid);
			}
			else
			{
				TextDrawShowForPlayer(playerid, LockScreenTD[0]);
				TextDrawShowForPlayer(playerid, LockScreenTD[1]);
				TextDrawShowForPlayer(playerid, LockScreenTD[2]);
				TextDrawShowForPlayer(playerid, LockScreenTD[3]);
				TextDrawShowForPlayer(playerid, LockScreenTD[4]);
				TextDrawShowForPlayer(playerid, LockScreenTD[5]);
				TextDrawShowForPlayer(playerid, LockScreenTD[8]);
				TextDrawShowForPlayer(playerid, LockScreenTD[9]);
				TextDrawShowForPlayer(playerid, LockScreenTD[10]);

				TextDrawShowForPlayer(playerid, RebootScreenTD[0]);
				TextDrawShowForPlayer(playerid, RebootScreenTD[6]);

				TextDrawShowForPlayer(playerid, HomeButtonPhone[0]);
    			TextDrawShowForPlayer(playerid, HomeButtonPhone[1]);
			}
			if(!IsPlayerInAnyVehicle(playerid))
			{
				ApplyAnimation(playerid, "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, true);
				SetPlayerAttachedObject(playerid, 9, 18869, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
			}
			PlayerPhoneData[playerid][phoneShown] = true;

			SendRPMeAboveHead(playerid, "Membuka smartphone miliknya.");
		}
	}

	else if(!strcmp(name, "Changename Card"))
	{
		Inventory_Close(playerid);
		
		Dialog_Show(playerid, "ChangeName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Change Name", 
		"Gunakan format "RED"NamaDepan_NamaBelakang"WHITE".\n\
		Nama tidak boleh mengandung kata kotor, singkatan, atau nama publik figur/terkenal.\n\n\
		Contoh: "YELLOW"John_Doe, Kenji_Tanaka, Budi_Santoso", "Set", "Batal");
	}
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (AccountData[playerid][pInLoginBox])
	{
		if (clickedid == LoginBoxGTD[4]) //password
		{
			Dialog_Show(playerid, "Login", DIALOG_STYLE_PASSWORD, ""RED"UCP - Input Password", ""WHITE"Masukkan kata sandi Anda: "PAHLAWAN"(input below)", "Input", "Cancel");
			//pLoginTimer[playerid] = SetTimerEx("OnPlayerNotLogin", 30000, false, "i", playerid);
		}
		else if (clickedid == LoginBoxGTD[6]) //login
		{
			if (!strlen(AccountData[playerid][pTempPassword]))
			{
				SendClientMessage(playerid, Y_GREY, "ERROR: Password belum diisi.");
				return 1;
			}

			SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Mengecek password anda, mohon tunggu...");
			CancelSelectTextDraw(playerid);

			new string[555];
			mysql_format(g_SQL, string, sizeof(string), "SELECT `Password` FROM `player_ucp` WHERE `UCP` = '%e' LIMIT 1", AccountData[playerid][pUCP]);
			mysql_pquery(g_SQL, string, "OnLoginPassCheck", "is", playerid, AccountData[playerid][pTempPassword]);
		}
		else if (clickedid == LoginBoxGTD[9]) // lupa password
		{
			Dialog_Show(playerid, "ForgotPassword", DIALOG_STYLE_INPUT, ""RED"UCP - Lupa Password", ""WHITE"Silakan masukkan email terdaftar anda: "PAHLAWAN"(input below)", "Kirim Kode", "Batal");
		}
	}

	if (AccountData[playerid][pInVerifyCode])
	{
		if (clickedid == VerifyCodeGTD[9])
		{
			SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Mengecek kode verifikasi anda, mohon tunggu...");
			CancelSelectTextDraw(playerid);

			if (AccountData[playerid][pInResetPassword])
			{
				new string[555];
				mysql_format(g_SQL, string, sizeof(string), "SELECT `Verify_Code`, `Verify_Status` FROM `player_ucp` WHERE `UCP` = '%e' LIMIT 1", AccountData[playerid][pUCP]);
				mysql_pquery(g_SQL, string, "OnVerifyCodeEmailCheck", "is", playerid, AccountData[playerid][pTempPassword]);
			}
			else
			{
				new string[555];
				mysql_format(g_SQL, string, sizeof(string), "SELECT `Verify_Code`, `Verify_Status` FROM `player_ucp` WHERE `UCP` = '%e' LIMIT 1", AccountData[playerid][pUCP]);
				mysql_pquery(g_SQL, string, "OnVerifyCodeCheck", "is", playerid, AccountData[playerid][pTempPassword]);
			}
		}
	}

	for(new i; i < 10; i++) 
	{
        if(clickedid == EmotesTD[i + 7])
		{
            new ePage = i + ((animPage[playerid]-1) * 10);
			if(ePage >= sizeof(g_AnimDetails)) return 1;
			
            ApplyAnimation(playerid, g_AnimDetails[ePage][e_AnimLib], g_AnimDetails[ePage][e_AnimName], g_AnimDetails[ePage][e_AnimDelta], g_AnimDetails[ePage][e_AnimLoop], g_AnimDetails[ePage][e_AnimLX], g_AnimDetails[ePage][e_AnimLY], g_AnimDetails[ePage][e_AnimFreeze], g_AnimDetails[ePage][e_AnimTime]);
        }
    }

	//job locker
	if(clickedid == JobMixTD[9]) //konfirmasi
	{
		if(SemenInput[playerid] != SemenDiAlat[playerid])
		{
			HideJobMixTD(playerid);
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Takaran semen tidak sesuai spek!");
		}
		if(PasirInput[playerid] != PasirDiAlat[playerid])
		{
			HideJobMixTD(playerid);
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Takaran pasir tidak sesuai spek!");
		}
		if(KrikilAInput[playerid] != KrikilADiAlat[playerid])
		{
			HideJobMixTD(playerid);
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Takaran krikil 1-2 tidak sesuai spek!");
		}
		if(KrikilBInput[playerid] != KrikilBDiAlat[playerid])
		{
			HideJobMixTD(playerid);
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Takaran krikil 2-3 tidak sesuai spek!");
		}
		if(AirInput[playerid] != AirDiAlat[playerid])
		{
			HideJobMixTD(playerid);
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Takaran air tidak sesuai spek!");
		}

		HideJobMixTD(playerid);
		AccountData[playerid][pActivityTime] = 1;
		PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "CAMPUR BETON");
		ShowProgressBar(playerid);

		pMixBetonTimer[playerid] = true;

		SendRPMeAboveHead(playerid, "Menunggu campuran beton selesai diaduk.");
	}

	else if(clickedid == LockerRoomTD[1])
	{
		switch(AccountData[playerid][pJob])
		{
			case JOB_MINER:
			{
				if(AccountData[playerid][pGender] == 1)
				{
					AccountData[playerid][pUniform] = 27;
				}
				else
				{
					AccountData[playerid][pUniform] = 191;
				}
				AccountData[playerid][pIsUsingUniform] = true;
			}
			case JOB_BUTCHER:
			{
				if(AccountData[playerid][pGender] == 1)
				{
					AccountData[playerid][pUniform] = 168;
				}
				else
				{
					AccountData[playerid][pUniform] = 201;
				}
				AccountData[playerid][pIsUsingUniform] = true;
			}
			case JOB_OILMAN:
			{
				if(AccountData[playerid][pGender] == 1)
				{
					AccountData[playerid][pUniform] = 260;
				}
				else
				{
					AccountData[playerid][pUniform] = 69;
				}
				AccountData[playerid][pIsUsingUniform] = true;
			}
			case JOB_FISHERMAN:
			{
				if(AccountData[playerid][pGender] == 1)
				{
					AccountData[playerid][pUniform] = 35;
				}
				else
				{
					AccountData[playerid][pUniform] = 41;
				}
				AccountData[playerid][pIsUsingUniform] = true;
			}
			case JOB_PORTER:
			{
				if(AccountData[playerid][pGender] == 1)
				{
					AccountData[playerid][pUniform] = 16;
				}
				else
				{
					AccountData[playerid][pUniform] = 65;
				}
				AccountData[playerid][pIsUsingUniform] = true;
			}
			case JOB_LUMBERJACK:
			{
				if(AccountData[playerid][pGender] == 1)
				{
					AccountData[playerid][pUniform] = 183;
				}
				else
				{
					AccountData[playerid][pUniform] = 41;
				}
				AccountData[playerid][pIsUsingUniform] = true;
			}
			case JOB_TAILOR:
			{
				if(AccountData[playerid][pGender] == 1)
				{
					AccountData[playerid][pUniform] = 20;
				}
				else
				{
					AccountData[playerid][pUniform] = 141;
				}
				AccountData[playerid][pIsUsingUniform] = true;
			}
		}
		SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		HideLockerTD(playerid);
	}
	else if(clickedid == LockerRoomTD[2])
	{
		AccountData[playerid][pIsUsingUniform] = false;
		SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
		HideLockerTD(playerid);
	}
	//job center
	else if(clickedid == JobCenterTD[10])
	{
		HideJobCenterTD(playerid);
	}

	else if(clickedid == JobCenterTD[14]) //farmer
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_FARMER;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[18]) //miner
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_MINER;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[22]) //butcher
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_BUTCHER;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[26]) //oilman
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_OILMAN;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[30]) //angkot driver
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_ANGKOT;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[34]) //fisherman
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_FISHERMAN;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[38]) //kargo
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_CARGO;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[42]) //porter
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_PORTER;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[46]) //porter
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_MIXER;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[50]) //kayu
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_LUMBERJACK;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[54]) //pelaut
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_PELAUT;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[58]) //peternak
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_MILKER;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[62]) //penjahit
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_TAILOR;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memilih pekerjaan sebagai ~p~%s.", GetJobName(playerid)));
	}
	else if(clickedid == JobCenterTD[66]) //pengangguran
	{
		HideJobCenterTD(playerid);
		AccountData[playerid][pJob] = JOB_NONE;
		RefreshMapJob(playerid);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memutuskan untuk menjadi ~p~%s.", GetJobName(playerid)));
	}
	//animation list
	else if(clickedid == EmotesTD[21])
	{
        if(animPage[playerid] * 10 < sizeof(g_AnimDetails)) 
		{
            animPage[playerid]++;
            SyncAnimPage(playerid);
            for (new i; i < 10; i++)
			{
                new index = (animPage[playerid] * 10) + i - 10;
                if (index < 0 || index >= sizeof(g_AnimDetails)) continue;
                PlayerTextDrawSetString(playerid, EmotesPTD[playerid][i], g_AnimDetails[index][e_AnimationName]);
            }
        }
    }
    else if(clickedid == EmotesTD[22])
	{
        if(animPage[playerid] > 1) 
		{
            animPage[playerid]--;
            SyncAnimPage(playerid);
            for (new i; i < 10; i++) 
			{
                new index = (animPage[playerid] * 10) + i - 10;
                if (index < 0 || index >= sizeof(g_AnimDetails)) continue;
                PlayerTextDrawSetString(playerid, EmotesPTD[playerid][i], g_AnimDetails[index][e_AnimationName]);
				PlayerTextDrawShow(playerid, EmotesPTD[playerid][i]);
            }
        }
    }
    else if(clickedid == EmotesTD[23]) 
	{
        for(new x; x < 24; x++)
        {
            TextDrawHideForPlayer(playerid, EmotesTD[x]);
        }
		for(new x; x < 11; x++)
        {
            PlayerTextDrawHide(playerid, EmotesPTD[playerid][x]);
        }
        animPage[playerid] = 1;
        CancelSelectTextDraw(playerid);
    }

	//spawn selector
	else if(clickedid == TollTD[19])
	{
		new x = AccountData[playerid][pTempValue2];
		if(x == -1) return 1;
		
		HideTollTD(playerid);
		if(AccountData[playerid][pOnDuty] && (AccountData[playerid][pFaction] == FACTION_LSPD || AccountData[playerid][pFaction] == FACTION_LSFD))
		{
			ShowTDN(playerid, NOTIFICATION_INFO, "Petugas penegak hukum dan pemerintahan tidak dikenakan biaya tol.");
		}
		else
		{
			if(AccountData[playerid][pMoney] < 80) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memuliki cukup uang untuk membayar tol! ($80)");

			TakePlayerMoneyEx(playerid, 80);
			ShowItemBox(playerid, "Cash", "Removed $80x", 1212, 5);
			ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membayar biaya tol sebesar ~g~$80.");
		}

		TollGateOpened[x] = true;
		MoveDynamicObject(TollGate[x], __g_TollTriggers[x][TollGatePos][0], __g_TollTriggers[x][TollGatePos][1], __g_TollTriggers[x][TollGatePos][2] + 0.1, 0.15, __g_TollTriggers[x][TollGatePos][3], __g_TollTriggers[x][TollRotation], __g_TollTriggers[x][TollGatePos][5]);
		
		SetTimerEx("OnTollPaid", 6500, false, "i", x);
		AccountData[playerid][pTempValue2] = -1;
		PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
	}
	else if(clickedid == InventTD[3]) //tombol use item inventory
	{
		if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
		if(AccountData[playerid][pSelectItem] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item untuk digunakan!");

		if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda pingsan dan tidak dapat menggunakan item apapun!");
		
		OnPlayerUseItem(playerid, InventoryData[playerid][AccountData[playerid][pSelectItem]][invItem]);
	}
	else if(clickedid == InventTD[5]) //tombol give item inventory
	{
		if(AccountData[playerid][pSelectItem] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item untuk diberikan!");
		if(AccountData[playerid][pItemQuantity] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon masukkan jumlah yang ingin diberikan!");
		if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
		
		CancelSelectTextDraw(playerid);
		new frmxt[522], count = 0;

		foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 3.2)) 
		{
			if (i % 2 == 0) {
				format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
			}
			else {
				format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
			}
			NearestUser[playerid][count++] = i;
		}

		if(count == 0) 
		{
			PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
			return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Give Item", "Tidak ada pemain terdekat!", "Tutup", "");
		}

		Dialog_Show(playerid, "InventoryGive", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Give Item", frmxt, "Pilih", "Batal");
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	}
	else if(clickedid == InventTD[7]) //tombol drop item inventory
	{
		if(AccountData[playerid][pSelectItem] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item untuk dibuang!");
		if(AccountData[playerid][pItemQuantity] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon masukkan jumlah item yang ingin dibuang!");
		if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

		new string[32];
		strunpack(string, InventoryData[playerid][AccountData[playerid][pSelectItem]][invItem]);
		if(Inventory_Count(playerid, string) < AccountData[playerid][pItemQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

		if(!strcmp(string, "Changename Card")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuang Changename Card!");

		new gid = Garbage_Nearest(playerid);
		if(gid == -1) //jika tidak dekat dengan tong sampah
		{
			if(!strcmp(string, "Sampah Makanan", false)) 
				if(gid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuang Sampah Makanan sembarangan!");

			static rumuspendapatan;
			if(IsPlayerInRangeOfPoint(playerid, 3.5, 2801.6724,-2547.5388,13.9350))
			{
				if(!strcmp(string, "Daging", false))
				{
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 15;
					
					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 2806, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				else if(!strcmp(string, "Tanduk", false))
				{
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 75;
					
					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19314, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				else if(!strcmp(string, "Kulit", false))
				{
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 150;
					
					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 1828, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, -381.9745,-1438.8531,25.7266))
			{
				if(!strcmp(string, "Cabai", false))
				{
					if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * ChiliSalary;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 2253, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				else if(!strcmp(string, "Tebu", false))
				{
					if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * SugarSalary;

					GivePlayerMoneyEx(playerid, rumuspendapatan);
					
					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 855, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				else if(!strcmp(string, "Padi", false))
				{
					if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * RiceSalary;

					GivePlayerMoneyEx(playerid, rumuspendapatan);
					
					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 2247, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				else if(!strcmp(string, "Strawberry", false))
				{
					if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * StrawberrySalary;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19577, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				else if(!strcmp(string, "Jeruk", false))
				{
					if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * JerukSalary;

					GivePlayerMoneyEx(playerid, rumuspendapatan);
					
					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19574, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				else if(!strcmp(string, "Anggur", false))
				{
					if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * AnggurSalary;

					GivePlayerMoneyEx(playerid, rumuspendapatan);
					
					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19576, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, 2730.1418,-2344.6802,13.6328))
			{
				if(!strcmp(string, "Tembaga", false))
				{
					if(AccountData[playerid][pJob] != JOB_MINER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang penambang!");
					if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengenakan seragam kerja!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 70;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 11748, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, 2700.1089,-2344.0027,13.6328))
			{
				if(!strcmp(string, "Besi", false))
				{
					if(AccountData[playerid][pJob] != JOB_MINER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang penambang!");
					if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengenakan seragam kerja!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 100;

					GivePlayerMoneyEx(playerid, rumuspendapatan);
					
					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19809, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, 2670.6033,-2343.5896,13.6328))
			{
				if(!strcmp(string, "Emas", false))
				{
					if(AccountData[playerid][pJob] != JOB_MINER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang penambang!");
					if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengenakan seragam kerja!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 175;

					GivePlayerMoneyEx(playerid, rumuspendapatan);
					
					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19941, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, 2611.6851,-2365.8826,13.6157))
			{
				if(!strcmp(string, "Berlian", false))
				{
					if(AccountData[playerid][pJob] != JOB_MINER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang penambang!");
					if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengenakan seragam kerja!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 1750;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19874, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, 2402.4326,-1502.1382,23.8349))
			{
				if(!strcmp(string, "Ayam Kemas", false))
				{
					if(AccountData[playerid][pJob] != JOB_BUTCHER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang tukang ayam!");
					if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengenakan seragam kerja!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 45;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 2768, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, -1688.4254,-17.4925,3.5547))
			{
				if(!strcmp(string, "Papan", false))
				{
					if(AccountData[playerid][pJob] != JOB_LUMBERJACK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang tukang kayu!");
					if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengenakan seragam kerja!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 65;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19433, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, 2527.0134,-2134.8589,13.5469))
			{
				if(!strcmp(string, "Minyak", false))
				{
					if(AccountData[playerid][pJob] != JOB_OILMAN) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang tukang minyak!");
					if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengenakan seragam kerja!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 75;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19621, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, -2491.6301,2363.1802,10.2727))
			{
				if(!strcmp(string, "Pakaian", false))
				{
					if(AccountData[playerid][pJob] != JOB_TAILOR) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang penjahit!");
					if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengenakan seragam kerja!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 40;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 2399, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, -19.2178,1175.9481,19.5634))
			{
				if(!strcmp(string, "Susu Fermentasi", false))
				{
					if(AccountData[playerid][pJob] != JOB_MILKER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang peternak!");
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 47;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 19569, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.5, -2057.6643,-2464.8784,31.1797))
			{
				if(!strcmp(string, "Ikan", false))
				{
					rumuspendapatan = AccountData[playerid][pItemQuantity] * 55;

					GivePlayerMoneyEx(playerid, rumuspendapatan);

					ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), 1604, 4);
					ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(rumuspendapatan)), 1212, 5);

					ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
					Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);
					Inventory_Close(playerid);

					PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
					return 1;
				}
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat dijual disini!");
			}
			else
			{
				DropPlayerItem(playerid, AccountData[playerid][pSelectItem], AccountData[playerid][pItemQuantity]);
			}
		}
		else
		{
			ShowItemBox(playerid, string, sprintf("Removed %dx", AccountData[playerid][pItemQuantity]), InventoryData[playerid][AccountData[playerid][pSelectItem]][invModel], 5);
			ApplyAnimation(playerid, "GRENADE", "WEAPON_THROWU", 4.0, false, false, false, false, 0, true); //dekat

			Inventory_Remove(playerid, string, AccountData[playerid][pItemQuantity]);

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

			Inventory_Close(playerid);
		}
		if(AccountData[playerid][pHoldingFuelCan])
		{
			AccountData[playerid][pHoldingFuelCan] = false;
			RemovePlayerAttachedObject(playerid, 9);
			
			if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
				g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		}
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	}
	
	else if(clickedid == InventTD[9]) //tombol close inventory
	{
		Inventory_Close(playerid);
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
	}

	else if(clickedid == ATMTD[16]) //logout ATM
	{
		ClearAnimations(playerid, true);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		HideATMTD(playerid);
	}
	else if(clickedid == ATMTD[37]) //withdraw ATM
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
		Dialog_Show(playerid, "ATMWithdraw", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Withdraw", 
		"Mohon masukkan berapa jumlah yang ingin ditarik:", "Tarik", "Batal");
	}
	else if(clickedid == ATMTD[40]) //deposit ATM
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
		Dialog_Show(playerid, "ATMDeposit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Deposit", 
		"Mohon masukkan berapa jumlah yang ingin disimpan:", "Depo", "Batal");
	}
	else if(clickedid == ATMTD[43]) //transfer ATM
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
		Dialog_Show(playerid, "ATMTransfer", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Transfer", 
		"Mohon masukkan nomor rekening tujuan:", "Set", "Batal");
	}
	else if(clickedid == ATMTD[62]) //quick withdraw 10
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
		AccountData[playerid][pTempValue2] = 1;
		Dialog_Show(playerid, "ATMQuickMenu", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Quick Withdraw", ""WHITE"Apakah anda yakin ingin menarik uang senilai "GREEN"$10,000 "WHITE"dari saldo rekening?\nPilih "YELLOW"'lanjut' "WHITE"untuk melanjutkan transaksi ini!", "Lanjut", "Batal");
	}
	else if(clickedid == ATMTD[64]) //quick withdraw 50
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
		AccountData[playerid][pTempValue2] = 2;
		Dialog_Show(playerid, "ATMQuickMenu", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Quick Withdraw", ""WHITE"Apakah anda yakin ingin menarik uang senilai "GREEN"$50,000 "WHITE"dari saldo rekening?\nPilih "YELLOW"'lanjut' "WHITE"untuk melanjutkan transaksi ini!", "Lanjut", "Batal");
	}
	else if(clickedid == ATMTD[66]) //quick withdraw 25
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
		AccountData[playerid][pTempValue2] = 3;
		Dialog_Show(playerid, "ATMQuickMenu", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Quick Withdraw", ""WHITE"Apakah anda yakin ingin menarik uang senilai "GREEN"$250,000 "WHITE"dari saldo rekening?\nPilih "YELLOW"'lanjut' "WHITE"untuk melanjutkan transaksi ini!", "Lanjut", "Batal");
	}
	else if(clickedid == ATMTD[68]) //quick withdraw 500
	{
		AccountData[playerid][pTempValue2] = 4;
		Dialog_Show(playerid, "ATMQuickMenu", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Quick Withdraw", ""WHITE"Apakah anda yakin ingin menarik uang senilai "GREEN"$500,000 "WHITE"dari saldo rekening?\nPilih "YELLOW"'lanjut' "WHITE"untuk melanjutkan transaksi ini!", "Lanjut", "Batal");
	}

	else if(clickedid == ATMTD[70]) //quick deposit 10
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
		AccountData[playerid][pTempValue2] = 5;
		Dialog_Show(playerid, "ATMQuickMenu", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Quick Deposit", ""WHITE"Apakah anda yakin ingin deposit uang senilai "GREEN"$10,000 "WHITE"ke saldo rekening?\nPilih "YELLOW"'lanjut' "WHITE"untuk melanjutkan transaksi ini!", "Lanjut", "Batal");
	}
	else if(clickedid == ATMTD[72]) //quick deposit 50
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
		AccountData[playerid][pTempValue2] = 6;
		Dialog_Show(playerid, "ATMQuickMenu", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Quick Deposit", ""WHITE"Apakah anda yakin ingin deposit uang senilai "GREEN"$50,000 "WHITE"ke saldo rekening?\nPilih "YELLOW"'lanjut' "WHITE"untuk melanjutkan transaksi ini!", "Lanjut", "Batal");
	}
	else if(clickedid == ATMTD[74]) //quick deposit 25
	{
		if(!AVC_PConnected[playerid]) return Kick(playerid);
		AccountData[playerid][pTempValue2] = 7;
		Dialog_Show(playerid, "ATMQuickMenu", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Quick Deposit", ""WHITE"Apakah anda yakin ingin deposit uang senilai "GREEN"$250,000 "WHITE"ke saldo rekening?\nPilih "YELLOW"'lanjut' "WHITE"untuk melanjutkan transaksi ini!", "Lanjut", "Batal");
	}
	else if(clickedid == ATMTD[76]) //quick deposit 500
	{
		AccountData[playerid][pTempValue2] = 8;
		Dialog_Show(playerid, "ATMQuickMenu", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Quick Deposit", ""WHITE"Apakah anda yakin ingin deposit uang senilai "GREEN"$500,000 "WHITE"ke saldo rekening?\nPilih "YELLOW"'lanjut' "WHITE"untuk melanjutkan transaksi ini!", "Lanjut", "Batal");
	}
	else if(clickedid == RadialTD[7]) //exit radial main menu
	{
		PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);

		CancelSelectTextDraw(playerid);
		HideRadialTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);
	}
	else if(clickedid == RadialTD[0]) //HP
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		if(!PlayerHasItem(playerid, "Smartphone")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki smartphone!");

		if(!AVC_PConnected[playerid]) return Kick(playerid);
		
		if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
		if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
		if(OJailData[playerid][jailed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
		if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

		if(PlayerPhoneData[playerid][phoneIncomingCall] || PlayerPhoneData[playerid][phoneDuringConversation])
		{
			CutCallingLine(playerid);
			return 1;
		}

		if(PlayerPhoneData[playerid][phoneShown])
		{
			if(pRebootingPhoneTimer[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ponsel ini sedang dihidupkan, mohon menunggu hingga selesai!");

			RemovePlayerAttachedObject(playerid, 9);
			StopLoopingAnim(playerid);

			HideAllPhoneTD(playerid);
			PlayerPhoneData[playerid][phoneShown] = false;

			SendRPMeAboveHead(playerid, "Menutup smartphone miliknya.");
		}
		else
		{
			if(PlayerPhoneData[playerid][phoneOn])
			{
				ShowPhoneLockScreenTD(playerid);
			}
			else
			{
				TextDrawShowForPlayer(playerid, LockScreenTD[0]);
				TextDrawShowForPlayer(playerid, LockScreenTD[1]);
				TextDrawShowForPlayer(playerid, LockScreenTD[2]);
				TextDrawShowForPlayer(playerid, LockScreenTD[3]);
				TextDrawShowForPlayer(playerid, LockScreenTD[4]);
				TextDrawShowForPlayer(playerid, LockScreenTD[5]);
				TextDrawShowForPlayer(playerid, LockScreenTD[8]);
				TextDrawShowForPlayer(playerid, LockScreenTD[9]);
				TextDrawShowForPlayer(playerid, LockScreenTD[10]);

				TextDrawShowForPlayer(playerid, RebootScreenTD[0]);
				TextDrawShowForPlayer(playerid, RebootScreenTD[6]);

				TextDrawShowForPlayer(playerid, HomeButtonPhone[0]);
    			TextDrawShowForPlayer(playerid, HomeButtonPhone[1]);
			}
			if(!IsPlayerInAnyVehicle(playerid))
			{
				ApplyAnimation(playerid, "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, true);
				SetPlayerAttachedObject(playerid, 9, 18869, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
			}
			PlayerPhoneData[playerid][phoneShown] = true;

			SendRPMeAboveHead(playerid, "Membuka smartphone miliknya.");
		}
		HideRadialTD(playerid);
	}
	else if(clickedid == RadialTD[1]) //Inventory
	{
		if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
		if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

		AccountData[playerid][pSelectItem] = -1;
		AccountData[playerid][pItemQuantity] = 0;

		HideRadialTD(playerid);
		PlayerPlaySound(playerid, 1039, 0.0, 0.0, 0.0);
		Inventory_Show(playerid);
	}
	else if(clickedid == RadialTD[2]) //fashion
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);

		HideRadialTD(playerid);
		ShowRadialFashionTD(playerid);
	}
	else if(clickedid == RadialTD[3]) //dokumen
	{
		CancelSelectTextDraw(playerid);
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);

		HideRadialTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);
		
		Dialog_Show(playerid, "MyDocuments", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Dokumen", 
		"Lihat Kartu Tanda Anggota (KTA)\n"GRAY"Perlihatkan Kartu Tanda Anggota (KTA)\n\
		Lihat Kartu BPJS\n"GRAY"Perlihatkan Kartu BPJS\n\
		Lihat Surat Keterangan Sehat (SKS)\n"GRAY"Perlihatkan Surat Keterangan Sehat (SKS)\n\
		Lihat Surat Keterangan Catatan Kepolisian (SKCK)\n"GRAY"Perlihatkan Surat Keterangan Catatan Kepolisian (SKCK)\n\
		Lihat Surat Keterangan Warga Baru (SKWB)\n"GRAY"Perlihatkan Surat Keterangan Warga Baru (SKWB)\n\
		Lihat Surat Psikologi (SP)\n"GRAY"Perlihatkan Surat Psikologi (SP)", "Pilih", "Batal");
	}
	else if(clickedid == RadialTD[4]) //invoice
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);

		CancelSelectTextDraw(playerid);
		HideRadialTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		new xjjs[600], count;
		format(xjjs, sizeof(xjjs), "#\tNama Tagihan\tPemberi\tNominal Tagihan\n");
		for(new id; id < MAX_INVOICES; ++id)
		{
			if(InvoiceData[playerid][id][invoiceExists] && InvoiceData[playerid][id][invoiceOwner] == AccountData[playerid][pID]) 
			{
				format(xjjs, sizeof(xjjs), "%s"WHITE"%d\t"WHITE"%s\t"YELLOW"%s\t"RED"%s\n", xjjs, id + 1, InvoiceData[playerid][id][invoiceName], InvoiceData[playerid][id][invoiceIssuerName], FormatMoney(InvoiceData[playerid][id][invoiceCost]));
				ListedInvoices[playerid][count++] = id;
			}
		}

		if(count == 0)
		{
			Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Unpaid Invoice", 
			"Anda tidak memiliki tagihan/invoice apapun.", "Tutup", "");
		}
		else
		{
			if(!IsPlayerInAnyVehicle(playerid))
			{
				SetPlayerAttachedObject(playerid, 9, 19786, 5, 0.182999, 0.048999, -0.112999, -66.699935, -23.799949, -116.699996, 0.130999, 0.136000, 0.142000, 0, 0);
    			ApplyAnimation(playerid, "INT_SHOP","shop_loop", 4.1, true, false, false, true, 0, true);
			}
			Dialog_Show(playerid, "InvoicePay", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Unpaid Invoice", 
			xjjs, "Bayar", "Batal");
		}
	}
	else if(clickedid == RadialTD[5]) //kendaraan
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		HideRadialTD(playerid);
		ShowRadialVehTD(playerid);
	}
	else if(clickedid == RadialTD[6]) //ktp/lisensi
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		HideRadialTD(playerid);
		ShowRadialCardTD(playerid);
	}

	//--------- fashion ---------//
	else if(clickedid == RadialFashionTD[27]) //fashion exit
	{
		PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
		HideRadialFashionTD(playerid);
		ShowRadialTD(playerid);
	}
	else if(clickedid == RadialFashionTD[23]) //helmet/topi
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialFashionTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(pToys[playerid][0][toy_model] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki hat/helmet!");

		AccountData[playerid][pToySelected] = 0;

		new string[666];
		format(string, sizeof(string), "Pengaturan\tParameter\n\
		Edit Posisi\t(Khusus PC)\n\
		"GRAY"Ubah Tulang (Bone)\n\
		Sumbu X:\t%f\n\
		"GRAY"Sumbu Y:\t"GRAY"%f\n\
		Sumbu Z:\t%f\n\
		"GRAY"Rotasi X:\t"GRAY"%f\n\
		Rotasi Y:\t%f\n\
		"GRAY"Rotasi Z:\t"GRAY"%f\n\
		Skala X:\t%f\n\
		"GRAY"Skala Y:\t"GRAY"%f\n\
		Skala Z:\t%f\n\
		"GRAY"Color 1:\t"GRAY"%08x\n\
		Color 2:\t%08x\n\
		"GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
		Sembunyikan\t(Jika ingin disembunyikan)\n\
		"GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
		pToys[playerid][0][toy_x], pToys[playerid][0][toy_y], pToys[playerid][0][toy_z],
		pToys[playerid][0][toy_rx], pToys[playerid][0][toy_ry], pToys[playerid][0][toy_rz],
		pToys[playerid][0][toy_sx], pToys[playerid][0][toy_sy], pToys[playerid][0][toy_sz],
		pToys[playerid][0][matcolor1][4], pToys[playerid][0][matcolor2][4]);
		Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
	}
	else if(clickedid == RadialFashionTD[24]) //kacamata
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialFashionTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(pToys[playerid][1][toy_model] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kacamata!");

		AccountData[playerid][pToySelected] = 1;

		new string[666];
		format(string, sizeof(string), "Pengaturan\tParameter\n\
		Edit Posisi\t(Khusus PC)\n\
		"GRAY"Ubah Tulang (Bone)\n\
		Sumbu X:\t%f\n\
		"GRAY"Sumbu Y:\t"GRAY"%f\n\
		Sumbu Z:\t%f\n\
		"GRAY"Rotasi X:\t"GRAY"%f\n\
		Rotasi Y:\t%f\n\
		"GRAY"Rotasi Z:\t"GRAY"%f\n\
		Skala X:\t%f\n\
		"GRAY"Skala Y:\t"GRAY"%f\n\
		Skala Z:\t%f\n\
		"GRAY"Color 1:\t"GRAY"%08x\n\
		Color 2:\t%08x\n\
		"GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
		Sembunyikan\t(Jika ingin disembunyikan)\n\
		"GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
		pToys[playerid][1][toy_x], pToys[playerid][1][toy_y], pToys[playerid][1][toy_z],
		pToys[playerid][1][toy_rx], pToys[playerid][1][toy_ry], pToys[playerid][1][toy_rz],
		pToys[playerid][1][toy_sx], pToys[playerid][1][toy_sy], pToys[playerid][1][toy_sz],
		pToys[playerid][1][matcolor1][4], pToys[playerid][1][matcolor2][4]);
		Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
	}
	else if(clickedid == RadialFashionTD[25]) //aksesoris
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialFashionTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(pToys[playerid][2][toy_model] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki accessories!");

		AccountData[playerid][pToySelected] = 2;

		new string[666];
		format(string, sizeof(string), "Pengaturan\tParameter\n\
		Edit Posisi\t(Khusus PC)\n\
		"GRAY"Ubah Tulang (Bone)\n\
		Sumbu X:\t%f\n\
		"GRAY"Sumbu Y:\t"GRAY"%f\n\
		Sumbu Z:\t%f\n\
		"GRAY"Rotasi X:\t"GRAY"%f\n\
		Rotasi Y:\t%f\n\
		"GRAY"Rotasi Z:\t"GRAY"%f\n\
		Skala X:\t%f\n\
		"GRAY"Skala Y:\t"GRAY"%f\n\
		Skala Z:\t%f\n\
		"GRAY"Color 1:\t"GRAY"%08x\n\
		Color 2:\t%08x\n\
		"GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
		Sembunyikan\t(Jika ingin disembunyikan)\n\
		"GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
		pToys[playerid][2][toy_x], pToys[playerid][2][toy_y], pToys[playerid][2][toy_z],
		pToys[playerid][2][toy_rx], pToys[playerid][2][toy_ry], pToys[playerid][2][toy_rz],
		pToys[playerid][2][toy_sx], pToys[playerid][2][toy_sy], pToys[playerid][2][toy_sz],
		pToys[playerid][2][matcolor1][4], pToys[playerid][2][matcolor2][4]);
		Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
	}
	else if(clickedid == RadialFashionTD[26]) //tas/koper
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialFashionTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(pToys[playerid][3][toy_model] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki bag/suitcase!");

		AccountData[playerid][pToySelected] = 3;

		new string[666];
		format(string, sizeof(string), "Pengaturan\tParameter\n\
		Edit Posisi\t(Khusus PC)\n\
		"GRAY"Ubah Tulang (Bone)\n\
		Sumbu X:\t%f\n\
		"GRAY"Sumbu Y:\t"GRAY"%f\n\
		Sumbu Z:\t%f\n\
		"GRAY"Rotasi X:\t"GRAY"%f\n\
		Rotasi Y:\t%f\n\
		"GRAY"Rotasi Z:\t"GRAY"%f\n\
		Skala X:\t%f\n\
		"GRAY"Skala Y:\t"GRAY"%f\n\
		Skala Z:\t%f\n\
		"GRAY"Color 1:\t"GRAY"%08x\n\
		Color 2:\t%08x\n\
		"GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
		Sembunyikan\t(Jika ingin disembunyikan)\n\
		"GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
		pToys[playerid][3][toy_x], pToys[playerid][3][toy_y], pToys[playerid][3][toy_z],
		pToys[playerid][3][toy_rx], pToys[playerid][3][toy_ry], pToys[playerid][3][toy_rz],
		pToys[playerid][3][toy_sx], pToys[playerid][3][toy_sy], pToys[playerid][3][toy_sz],
		pToys[playerid][3][matcolor1][4], pToys[playerid][3][matcolor2][4]);
		Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
	}
	//--------- Kendaraan --------
	else if(clickedid == RadialVehTD[43]) //exit
	{
		PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
		HideRadialVehTD(playerid);
		ShowRadialTD(playerid);
	}
	else if(clickedid == RadialVehTD[37]) //kunci
	{
		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    	if(IsPlayerStunned(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
		if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
		if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialVehTD(playerid);

		new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
		if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");

		static string[84];
		foreach(new pv : PvtVehicles)
		{
			if(PlayerVehicle[pv][pVehPhysic] == vehid)
			{
				if(PlayerVehicle[pv][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
				if(PlayerVehicle[pv][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang dalam kondisi tirelocked!");
				
				switch(VehicleCore[vehid][vCoreLocked])
				{
					case false:
					{
						VehicleCore[vehid][vCoreLocked] = true;
						SwitchVehicleDoors(vehid, true);
						format(string, sizeof(string), "~y~%s~n~~r~Terkunci", GetVehicleModelName(GetVehicleModel(PlayerVehicle[pv][pVehPhysic])));
						GameTextForPlayer(playerid, string, 2000, 4);

						if(!GetLightStatus(vehid))
						{
							VehicleCore[vehid][vIsRemoted] = true;
							VehicleCore[vehid][vRemotedCount] = 0;
							VehicleCore[vehid][vRemotedType] = 1;
						}
					}
					case true:
					{
						VehicleCore[vehid][vCoreLocked] = false;
						SwitchVehicleDoors(vehid, false);
						format(string, sizeof(string), "~y~%s~n~~g~Terbuka", GetVehicleModelName(GetVehicleModel(PlayerVehicle[pv][pVehPhysic])));
						GameTextForPlayer(playerid, string, 2000, 4);

						if(!GetLightStatus(vehid))
						{
							VehicleCore[vehid][vIsRemoted] = true;
							VehicleCore[vehid][vRemotedCount] = 0;
							VehicleCore[vehid][vRemotedType] = 2;
						}
					}
				}
				PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
				ApplyAnimation(playerid, "WEAPONS", "SHP_Ar_Ret_S", 4.1, false,true,true,false,0,true);
				return 1;
			}
		}

		if(vehid != JobVehicle[playerid] && vehid != FactionHeliVeh[playerid] && vehid != PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");

		switch(VehicleCore[vehid][vCoreLocked])
		{
			case false:
			{
				VehicleCore[vehid][vCoreLocked] = true;
				SwitchVehicleDoors(vehid, true);
				format(string, sizeof(string), "~y~%s~n~~r~Terkunci", GetVehicleModelName(GetVehicleModel(vehid)));
				GameTextForPlayer(playerid, string, 2000, 4);

				if(!GetLightStatus(vehid))
				{
					VehicleCore[vehid][vIsRemoted] = true;
					VehicleCore[vehid][vRemotedCount] = 0;
					VehicleCore[vehid][vRemotedType] = 1;
				}
			}
			case true:
			{
				VehicleCore[vehid][vCoreLocked] = false;
				SwitchVehicleDoors(vehid, false);
				format(string, sizeof(string), "~y~%s~n~~g~Terbuka", GetVehicleModelName(GetVehicleModel(vehid)));
				GameTextForPlayer(playerid, string, 2000, 4);
				
				if(!GetLightStatus(vehid))
				{
					VehicleCore[vehid][vIsRemoted] = true;
					VehicleCore[vehid][vRemotedCount] = 0;
					VehicleCore[vehid][vRemotedType] = 2;
				}
			}
		}
		PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
		ApplyAnimation(playerid, "WEAPONS", "SHP_Ar_Ret_S", 4.1, false,true,true,false,0,true);
	}
	else if(clickedid == RadialVehTD[38]) //lampu
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialVehTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di kursi pengemudi!");

		new vehid = GetPlayerVehicleID(playerid);
		if(!IsEngineVehicle(vehid))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak memiliki mesin!");

		switch(GetLightStatus(vehid))
		{
			case false:
			{
				foreach(new carid : PvtVehicles)
				{
					if(vehid == PlayerVehicle[carid][pVehPhysic])
					{
						if(PlayerVehicle[carid][pVehNeon] != 0)
						{
							SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], true, PlayerVehicle[carid][pVehNeon], 0);
						}
						else
						{
							SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);
						}
					}
				}
				SwitchVehicleLight(vehid, true);
			}
			case true:
			{
				foreach(new carid : PvtVehicles)
				{
					if(vehid == PlayerVehicle[carid][pVehPhysic])
					{
						SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);
					}
				}
				SwitchVehicleLight(vehid, false);
			}
		}
	}
	else if(clickedid == RadialVehTD[39]) //bagasi
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialVehTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");
		
		new vehid = GetNearestVehicleToPlayer(playerid, 6.66, false);
		if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");

		if(!IsPlayerNearBoot(playerid, vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan trunk kendaraan anda!");

		if(IsABike(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kenaraan ini tidak memiliki trunk!");
		
		if(VehicleCore[vehid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");

		SwitchVehicleBoot(vehid, true);
		
		foreach(new carid : PvtVehicles)
		{
			if(vehid == PlayerVehicle[carid][pVehPhysic])
			{
				if(PlayerVehicle[carid][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang dalam kondisi tirelocked!");
				AccountData[playerid][pTempVehIterID] = carid;
				AccountData[playerid][pMenuShowed] = true;
				Dialog_Show(playerid, "VehicleStorage", DIALOG_STYLE_LIST, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[carid][pVehModelID]), PlayerVehicle[carid][pVehPlate]), "Simpan Barang\nAmbil Barang", "Pilih", "Batal");
			}
		}
	}
	else if(clickedid == RadialVehTD[40]) //holster
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialVehTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");
		
		new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
		if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");

		if(!IsPlayerNearBoot(playerid, vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan trunk kendaraan anda!");

		if(IsABike(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak memiliki trunk!");

		if(VehicleCore[vehid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini seang terkunci!");

		if(IsPlayerHunting[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus keluar dari mode berburu rusa sebelum akses holster");

		SwitchVehicleBoot(vehid, true);

		foreach(new carid : PvtVehicles)
		{
			if(vehid == PlayerVehicle[carid][pVehPhysic])
			{
				if(PlayerVehicle[carid][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang dalam kondisi tirelockedd!");

				AccountData[playerid][pTempVehIterID] = carid;
				AccountData[playerid][pMenuShowed] = true;
				Dialog_Show(playerid, "VehicleHoslter", DIALOG_STYLE_LIST, sprintf("Holster %s", PlayerVehicle[carid][pVehPlate]), "Simpan Senjata\n"GRAY"Ambil Senjata", "Pilih", "Batal");
			}
		}
	}
	else if(clickedid == RadialVehTD[41]) //trunk
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialVehTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		Dialog_Show(playerid, "VehicleTrunk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Trunk", 
		"Buka Trunk Kendaraan\n"GRAY"Masuk ke Trunk Kendaraan\nMasukkan Orang ke Trunk Kendaraan\n"GRAY"Keluarkan dari Trunk Kendaraan", "Pilih", "Batal");
	}
	else if(clickedid == RadialVehTD[42]) //hood
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialVehTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");
		
		new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
		if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");

		if(!IsPlayerNearHood(playerid, vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak cukup dekat dengan hood kendaraan anda!");

		if(IsABike(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak memilki hood!");

		if(VehicleCore[vehid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");

		switch (GetHoodStatus(vehid))
		{
			case false:
			{
				SwitchVehicleBonnet(vehid, true);
			}
			case true:
			{
				SwitchVehicleBonnet(vehid, false);
			}
		}
	}
	// -------------- KTP / Lisensi --------------
	else if(clickedid == RadialCardTD[1]) //exit
	{
		PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
		HideRadialCardTD(playerid);
		ShowRadialTD(playerid);
	}
	else if(clickedid == RadialCardTD[25]) //lihat KTP
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialCardTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(!AccountData[playerid][pHasKTP])
		{
			Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kartu Tanda Penduduk", 
			"Anda tidak memiliki Kartu Tanda Penduduk/sudah expired.", "Tutup", "");
			return 1;
		}

		ShowIDCTD(playerid, playerid);
	}
	else if(clickedid == RadialCardTD[22]) //tunjuk KTP
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialCardTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		new count = 0, frmxt[522];
        foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
		{
			if (i % 2 == 0) {
            format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
            }
            else {
                format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
            }
			NearestUser[playerid][count++] = i;
		}

        if(count > 0)
		{
            Dialog_Show(playerid, "ShowToIDCard", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Tunjukkan KTP", 
			frmxt, "Pilih", "Batal");
		}
	}
	else if(clickedid == RadialCardTD[23]) //lihat lisensi
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialCardTD(playerid);
		
		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);

		if(!CheckPlayerLicense(playerid))
		{
			Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Licenses", 
			"Anda tidak memiliki lisensi.", "Tutup", "");
			return 1;
		}

		ShowLCTD(playerid, playerid);
	}
	else if(clickedid == RadialCardTD[24]) //tunjuk lisensi
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		HideRadialCardTD(playerid);

		ShowServerNameTD(playerid);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			ShowSpeedoTD(playerid);
			
		ShowHBETD(playerid);
		
		new count = 0, frmxt[522];
        foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
		{
			if (i % 2 == 0) {
            format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
            }
            else {
                format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
            }
			NearestUser[playerid][count++] = i;
		}

        if(count > 0)
		{
            Dialog_Show(playerid, "ShowToLicense", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Tunjukkan Lisensi", 
			frmxt, "Pilih", "Batal");
		}
	}
	return 1;
}

public OnDynamicPlayerTextdrawClicked(playerid, PlayerText:playertextid)
{
	SelectCharTDClick(playerid, playertextid);
	SelectSpawnTDClick(playerid, playertextid);
	
	if (AccountData[playerid][pInLoginBox])
	{
		if (playertextid == LoginBoxPTD[playerid][2]) // android select box
		{
			AccountData[playerid][pDevice] = 0; // Android

            // Android
			PlayerTextDrawSetSelectable(playerid, LoginBoxPTD[playerid][2], 0);
			PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][2], 2105376200);
			PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][3], -1);

			// Komputer
			PlayerTextDrawSetSelectable(playerid, LoginBoxPTD[playerid][4], 1);
			PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][4], 421075400);
			PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][5], 1010580680);

			PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][2]);
			PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][3]);
			PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][4]);
			PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][5]);
		}
		else if (playertextid == LoginBoxPTD[playerid][4]) // komputer select box
		{
			AccountData[playerid][pDevice] = 1; // Komputer
            
			// Android
			PlayerTextDrawSetSelectable(playerid, LoginBoxPTD[playerid][2], 1);
			PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][2], 421075400);
			PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][3], 1010580680);

			// Komputer
			PlayerTextDrawSetSelectable(playerid, LoginBoxPTD[playerid][4], 0);
			PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][4], 2105376200);
			PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][5], -1);

			PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][2]);
			PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][3]);
			PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][4]);
			PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][5]);
		}
	}

	if (AccountData[playerid][pInVerifyCode])
	{
		if (playertextid == VerifyCodePTD[playerid][0] || playertextid == VerifyCodePTD[playerid][1]
		|| playertextid == VerifyCodePTD[playerid][2] || playertextid == VerifyCodePTD[playerid][3]
		|| playertextid == VerifyCodePTD[playerid][4] || playertextid == VerifyCodePTD[playerid][5]) // verify code box
		{
			Dialog_Show(playerid, "Verification", DIALOG_STYLE_PASSWORD, ""RED"UCP - Verification Required", ""WHITE"Masukkan 6 digit kode dari Discord Anda: "PAHLAWAN"(input below)", "Continue", "Cancel");
		}
	}

	for(new x; x < MAX_INVENTORY; x++)
	{
		if(playertextid == PrevMod[playerid][x])
		{
			if(InventoryData[playerid][x][invExists])
			{
				if(AccountData[playerid][pSelectItem] > -1)
				{
					PlayerTextDrawColor(playerid, BoxItem[playerid][AccountData[playerid][pSelectItem]], 0x00000066);
					PlayerTextDrawShow(playerid, BoxItem[playerid][AccountData[playerid][pSelectItem]]);
				}
				
				AccountData[playerid][pSelectItem] = x;
				PlayerTextDrawColor(playerid, BoxItem[playerid][x], 0x000000ff);
				PlayerTextDrawShow(playerid, BoxItem[playerid][x]);
				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			}
			else
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada item di slot ini!");
				Inventory_Close(playerid);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}

		else if(playertextid == BoxItem[playerid][x]) //dipindahkan di box yang dipencet
		{
			if(AccountData[playerid][pSelectItem] > -1) //jika sedang dalam select item/sudah memilih item
			{
				if(!InventoryData[playerid][x][invExists]) //jika slot kosong item disana maka dipindah
				{
					new invstr[1028];
					//untuk slot TUJUAN
					InventoryData[playerid][x][invExists] = true;
	        		InventoryData[playerid][x][invModel] = InventoryData[playerid][AccountData[playerid][pSelectItem]][invModel];
	        		InventoryData[playerid][x][invQuantity] = InventoryData[playerid][AccountData[playerid][pSelectItem]][invQuantity];

					strcopy(InventoryData[playerid][x][invItem], InventoryData[playerid][AccountData[playerid][pSelectItem]][invItem]);

					PlayerTextDrawColor(playerid, BoxItem[playerid][AccountData[playerid][pSelectItem]], 0x00000066);
					PlayerTextDrawShow(playerid, BoxItem[playerid][AccountData[playerid][pSelectItem]]);

					PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][x], InventoryData[playerid][AccountData[playerid][pSelectItem]][invModel]);
					PlayerTextDrawShow(playerid, PrevMod[playerid][x]);
					
					PlayerTextDrawSetString(playerid, NameItem[playerid][x], sprintf("%s", InventoryData[playerid][AccountData[playerid][pSelectItem]][invItem]));
					PlayerTextDrawShow(playerid, NameItem[playerid][x]);

					PlayerTextDrawSetString(playerid, QuantItem[playerid][x], sprintf("%dx", InventoryData[playerid][AccountData[playerid][pSelectItem]][invQuantity]));
					PlayerTextDrawShow(playerid, QuantItem[playerid][x]);

					TextDrawShowForPlayer(playerid, InventLineTD[x]);

					mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `inventory` (`Owner_ID`, `invent_Item`, `invent_Model`, `invent_Quantity`) VALUES('%d', '%e', '%d', '%d')", AccountData[playerid][pID], InventoryData[playerid][AccountData[playerid][pSelectItem]][invItem], InventoryData[playerid][AccountData[playerid][pSelectItem]][invModel], InventoryData[playerid][AccountData[playerid][pSelectItem]][invQuantity]);
					mysql_pquery(g_SQL, invstr, "OnInventoryAdd", "id", playerid, x);

					//untuk slot ASAL
					InventoryData[playerid][AccountData[playerid][pSelectItem]][invExists] = false;
	        		InventoryData[playerid][AccountData[playerid][pSelectItem]][invModel] = 0;
	        		InventoryData[playerid][AccountData[playerid][pSelectItem]][invQuantity] = 0;

					InventoryData[playerid][AccountData[playerid][pSelectItem]][invItem][0] = EOS;

					PlayerTextDrawHide(playerid, PrevMod[playerid][AccountData[playerid][pSelectItem]]);
					PlayerTextDrawHide(playerid, NameItem[playerid][AccountData[playerid][pSelectItem]]);
					PlayerTextDrawHide(playerid, QuantItem[playerid][AccountData[playerid][pSelectItem]]);

					TextDrawHideForPlayer(playerid, InventLineTD[AccountData[playerid][pSelectItem]]);

					mysql_format(g_SQL, invstr, sizeof(invstr), "DELETE FROM `inventory` WHERE `Owner_ID` = %d AND `invent_ID` = %d", AccountData[playerid][pID], InventoryData[playerid][AccountData[playerid][pSelectItem]][invID]);
	        		mysql_pquery(g_SQL, invstr);

					AccountData[playerid][pSelectItem] = -1;
				}
			}
		}
	}
	if(playertextid == InventWeightTD[playerid][3]) //tombol set jumlah item inventory yang akan diberi
	{
		if(AccountData[playerid][pSelectItem] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");

		Dialog_Show(playerid, "InventorySetValue", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Set Value", "Mohon masukkan jumlah item yang akan diberikan:", "Set", "Batal");
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	}
	else if(playertextid == pJobMixTD[playerid][5])
	{
		Dialog_Show(playerid, "SetSemenValue", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Batching Plant", "Mohon masukkan jumlah agregat yang akan ditetapkan:", "Set", "Batal");
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	}
	else if(playertextid == pJobMixTD[playerid][6])
	{
		Dialog_Show(playerid, "SetPasirValue", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Batching Plant", "Mohon masukkan jumlah agregat yang akan ditetapkan:", "Set", "Batal");
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	}
	else if(playertextid == pJobMixTD[playerid][7])
	{
		Dialog_Show(playerid, "SetKrikilAValue", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Batching Plant", "Mohon masukkan jumlah agregat yang akan ditetapkan:", "Set", "Batal");
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	}
	else if(playertextid == pJobMixTD[playerid][8])
	{
		Dialog_Show(playerid, "SetKrikilBValue", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Batching Plant", "Mohon masukkan jumlah agregat yang akan ditetapkan:", "Set", "Batal");
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	}
	else if(playertextid == pJobMixTD[playerid][9])
	{
		Dialog_Show(playerid, "SetAirValue", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Batching Plant", "Mohon masukkan jumlah agregat yang akan ditetapkan:", "Set", "Batal");
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	}
	return 0;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid)
{
	return 1;
}

public OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ,Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

	new weaponid = EditingWeapon[playerid];
    if(weaponid)
    {
        if(response == 1)
        {
            new enum_index = GetWeaponIndex(weaponid), weaponname[18], string[1254];
 
            GetWeaponName(weaponid, weaponname, sizeof(weaponname));
           
            GunEdit[playerid][enum_index][Position][0] = fOffsetX;
            GunEdit[playerid][enum_index][Position][1] = fOffsetY;
            GunEdit[playerid][enum_index][Position][2] = fOffsetZ;
            GunEdit[playerid][enum_index][Position][3] = fRotX;
            GunEdit[playerid][enum_index][Position][4] = fRotY;
            GunEdit[playerid][enum_index][Position][5] = fRotZ;
 
            RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));
            SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), GunEdit[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0, GunEdit[playerid][enum_index][WeaponTint], GunEdit[playerid][enum_index][WeaponTint]);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah posisi senjata tersebut!");
           
			mysql_format(g_SQL, string, sizeof(string), "UPDATE `gunpos` SET `PosX_0` = '%.3f', `PosY_0` = '%.3f', `PosZ_0` = '%.3f', `RotX_0` = '%.3f', `RotY_0` = '%.3f', `RotZ_0` = '%.3f', `Bone_0` = %d, `Hidden_0` = %d, `Tint_0` = %d, `PosX_1` = '%.3f', `PosY_1` = '%.3f', `PosZ_1` = '%.3f', `RotX_1` = '%.3f', `RotY_1` = '%.3f', `RotZ_1` = '%.3f', `Bone_1` = %d, `Hidden_1` = %d, `Tint_1` = %d, \
			`PosX_2` = '%.3f', `PosY_2` = '%.3f', `PosZ_2` = '%.3f', `RotX_2` = '%.3f', `RotY_2` = '%.3f', `RotZ_2` = '%.3f', `Bone_2` = %d, `Hidden_2` = %d, `Tint_2` = %d, `PosX_3` = '%.3f', `PosY_3` = '%.3f', `PosZ_3` = '%.3f', `RotX_3` = '%.3f', `RotY_3` = '%.3f', `RotZ_3` = '%.3f', `Bone_3` = %d, `Hidden_3` = %d, `Tint_3` = %d, \
			`PosX_4` = '%.3f', `PosY_4` = '%.3f', `PosZ_4` = '%.3f', `RotX_4` = '%.3f', `RotY_4` = '%.3f', `RotZ_4` = '%.3f', `Bone_4` = %d, `Hidden_4` = %d, `Tint_4` = %d WHERE `Owner` = %d", GunEdit[playerid][0][Position][0], GunEdit[playerid][0][Position][1], GunEdit[playerid][0][Position][2], GunEdit[playerid][0][Position][3], GunEdit[playerid][0][Position][4], GunEdit[playerid][0][Position][5], GunEdit[playerid][0][Bone], GunEdit[playerid][0][Hidden], GunEdit[playerid][0][WeaponTint],
			GunEdit[playerid][1][Position][0], GunEdit[playerid][1][Position][1], GunEdit[playerid][1][Position][2], GunEdit[playerid][1][Position][3], GunEdit[playerid][1][Position][4], GunEdit[playerid][1][Position][5], GunEdit[playerid][1][Bone], GunEdit[playerid][1][Hidden], GunEdit[playerid][1][WeaponTint],
			GunEdit[playerid][2][Position][0], GunEdit[playerid][2][Position][1], GunEdit[playerid][2][Position][2], GunEdit[playerid][2][Position][3], GunEdit[playerid][2][Position][4], GunEdit[playerid][2][Position][5], GunEdit[playerid][2][Bone], GunEdit[playerid][2][Hidden], GunEdit[playerid][2][WeaponTint],
			GunEdit[playerid][3][Position][0], GunEdit[playerid][3][Position][1], GunEdit[playerid][3][Position][2], GunEdit[playerid][3][Position][3], GunEdit[playerid][3][Position][4], GunEdit[playerid][3][Position][5], GunEdit[playerid][3][Bone], GunEdit[playerid][3][Hidden], GunEdit[playerid][3][WeaponTint],
			GunEdit[playerid][4][Position][0], GunEdit[playerid][4][Position][1], GunEdit[playerid][4][Position][2], GunEdit[playerid][4][Position][3], GunEdit[playerid][4][Position][4], GunEdit[playerid][4][Position][5], GunEdit[playerid][4][Bone], GunEdit[playerid][4][Hidden], GunEdit[playerid][4][WeaponTint], AccountData[playerid][pID]);
			mysql_pquery(g_SQL, string);
        }
		else if(response == 0)
		{
			new enum_index = GetWeaponIndex(weaponid);
			SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), GunEdit[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0, GunEdit[playerid][enum_index][WeaponTint], GunEdit[playerid][enum_index][WeaponTint]);
		}
        EditingWeapon[playerid] = 0;
		return 1;
    }
	else
	{
		if(response)
		{
			if(AccountData[playerid][pToySelected] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih fashion untuk diubah!");

			if(fOffsetX > 1.0 && fOffsetX > -1.0)
			{
				SetPlayerAttachedObject(playerid,
				AccountData[playerid][pToySelected],
				modelid,
				boneid,
				pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Koordinat tidak valid!");
			}
			
			if(fOffsetY > 1.0 && fOffsetY > -1.0)
			{
				SetPlayerAttachedObject(playerid,
				AccountData[playerid][pToySelected],
				modelid,
				boneid,
				pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Koordinat tidak valid!");
			}
			
			if(fOffsetZ > 1.0 && fOffsetZ > -1.0)
			{
				SetPlayerAttachedObject(playerid,
				AccountData[playerid][pToySelected],
				modelid,
				boneid,
				pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Koordinat tidak valid!");
			}

			if(fScaleX > 2.0 && fScaleX > -2.0)
			{
				SetPlayerAttachedObject(playerid,
				AccountData[playerid][pToySelected],
				modelid,
				boneid,
				pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid scale!");
			}

			if(fScaleY > 2.0 && fScaleY > -2.0){
				SetPlayerAttachedObject(playerid,
				AccountData[playerid][pToySelected],
				modelid,
				boneid,
				pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid scale!");
			}

			if(fScaleZ > 2.0 && fScaleZ > -2.0){
				SetPlayerAttachedObject(playerid,
				AccountData[playerid][pToySelected],
				modelid,
				boneid,
				pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid scale!");
			}

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah posisi fashion tersebut.");

			pToys[playerid][AccountData[playerid][pToySelected]][toy_x] = fOffsetX;
			pToys[playerid][AccountData[playerid][pToySelected]][toy_y] = fOffsetY;
			pToys[playerid][AccountData[playerid][pToySelected]][toy_z] = fOffsetZ;
			pToys[playerid][AccountData[playerid][pToySelected]][toy_rx] = fRotX;
			pToys[playerid][AccountData[playerid][pToySelected]][toy_ry] = fRotY;
			pToys[playerid][AccountData[playerid][pToySelected]][toy_rz] = fRotZ;
			pToys[playerid][AccountData[playerid][pToySelected]][toy_sx] = fScaleX;
			pToys[playerid][AccountData[playerid][pToySelected]][toy_sy] = fScaleY;
			pToys[playerid][AccountData[playerid][pToySelected]][toy_sz] = fScaleZ;
			
			SetPVarInt(playerid, "UpdatedToy", 1);
			SavePlayerFashionToMysql(playerid);

			RemovePlayerAttachedObject(playerid, AccountData[playerid][pToySelected]);
			SetPlayerAttachedObject(playerid,
				AccountData[playerid][pToySelected],
				modelid,
				boneid,
				fOffsetX,
				fOffsetY,
				fOffsetZ,
				fRotX,
				fRotY,
				fRotZ,
				fScaleX,
				fScaleY,
				fScaleZ,
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
		}
		else
		{
			if(AccountData[playerid][pToySelected] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item untuk diedit!");
			
			ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan perubahan fashion.");

			SetPlayerAttachedObject(playerid,
				AccountData[playerid][pToySelected],
				modelid,
				boneid,
				pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
				pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
		}
		TogglePlayerControllable(playerid, true);
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{	
	/*new Float:vx,Float:vy,Float:vz;
	GetPlayerVelocity(playerid,vx,vy,vz);
	if(PRESSED(KEY_JUMP) && (vy > 0.01 || vy <-0.01 || vx > 0.01 || vx <-0.01) && !IsPlayerInAnyVehicle(playerid) && !BunnyHopDetected[playerid])
	{
		if(vz > 0.01 || vz < -0.01) return 1;
		BunnyHopDetected[playerid] = true;
		BunnyHopTimer[playerid] = SetTimerEx("BunnyHopDetecion", 500, true, "i", playerid);
	}*/

	if((newkeys & KEY_JUMP) && !IsPlayerInAnyVehicle(playerid))
    {
		if(!Iter_Contains(InEvent, playerid))
		{
			AccountData[playerid][AntiBHOP] ++;
			SetTimerEx("ResetAntiBH", 7500, false, "i", playerid);
			if(AccountData[playerid][AntiBHOP] >= 3)
			{
				ClearAnimations(playerid, 1);
				ApplyAnimation(playerid,"ped","FALL_COLLAPSE",4.1,false,true,true,false,0,true);
				AccountData[playerid][AntiBHOP] = 0;
			}
		}
	}
	
	else if(newkeys & KEY_SPRINT && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pHoldingSkate])
	{
		if(!AccountData[playerid][pSkating])
		{
			AccountData[playerid][pSkating] = true;
			ApplyAnimation(playerid,"SKATE","skate_sprint",0.67,true,true,true,true,true,true);
			SetPlayerAttachedObject(playerid, 9, 19878, 9, 0.152000, 0.046000, -0.023999, 14.200016, -89.100028, -98.299942, 1.000000, 1.000000, 1.000000);
		}
		else
		{
			AccountData[playerid][pSkating] = false;
			ApplyAnimation(playerid,"ped","FALL_COLLAPSE",4.1,false,true,true,false,0,true);
			SetPlayerAttachedObject(playerid, 9, 19878, 6, -0.073999, 0.000000, 0.000000, -86.399948, 1.800001, 82.200019, 1.000000, 1.000000, 1.000000);
		}
	}

	else if(newkeys & KEY_CTRL_BACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pActivityTime] > 0)
        {
			if(pTakingKanabisTimer[playerid] && AccountData[playerid][pInCannabis] > -1)
			{
				pTakingKanabisTimer[playerid] = false;
				KanabisData[AccountData[playerid][pInCannabis]][kanabisTaken] = false;

				AccountData[playerid][pInCannabis] = -1;

				HideProgressBar(playerid);

				ClearAnimations(playerid, true);
				StopLoopingAnim(playerid);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				TogglePlayerControllable(playerid, true);

				AccountData[playerid][pActivityTime] = 0;
			}
			if(pProcessKanabisTimer[playerid])
			{
				pProcessKanabisTimer[playerid] = false;

				HideProgressBar(playerid);

				ClearAnimations(playerid, true);
				StopLoopingAnim(playerid);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				TogglePlayerControllable(playerid, true);

				AccountData[playerid][pActivityTime] = 0;
			}
			if(AccountData[playerid][pJob] == JOB_FARMER)
			{
				if(CheckFarmerTimer(playerid))
				{
					pTakingPlantTimer[playerid] = false;
					pProcessChiliTimer[playerid] = false;
					pProcessRiceTimer[playerid] = false;
					pPorcessSugarTimer[playerid] = false;

					AccountData[playerid][pActivityTime] = 0;
					HideProgressBar(playerid);

					ClearAnimations(playerid, true);
					StopLoopingAnim(playerid);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					TogglePlayerControllable(playerid, true);
				}
			}
			else if(AccountData[playerid][pJob] == JOB_LUMBERJACK)
			{
				if(CheckLumberjackTimer(playerid))
				{
					pTakeWoodTimer[playerid] = false;
					pCutWoodTimer[playerid] = false;
					pGetBoardTimer[playerid] = false;

					AccountData[playerid][pActivityTime] = 0;

					AccountData[playerid][pCountingValue] = 0;
					HideProgressBar(playerid);

					ClearAnimations(playerid, true);
					StopLoopingAnim(playerid);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					TogglePlayerControllable(playerid, true);
				}
			}
			else if(AccountData[playerid][pJob] == JOB_MINER)
			{
				if(CheckMinerTimer(playerid))
				{
					pTakingStoneTimer[playerid] = false;
					pWashingStoneTimer[playerid] = false;
					pSmeltingStoneTimer[playerid] = false;

					AccountData[playerid][pActivityTime] = 0;
					HideProgressBar(playerid);

					ClearAnimations(playerid, true);
					StopLoopingAnim(playerid);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					TogglePlayerControllable(playerid, true);

					if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
                		RemovePlayerAttachedObject(playerid, 9);
				}
			}
			else if(AccountData[playerid][pJob] == JOB_BUTCHER)
			{
				if(CheckButcherTimer(playerid))
				{
					pTakingChickTimer[playerid] = false;
					pCutingChickTimer[playerid] = false;
					pPackingChickTimer[playerid] = false;

					AccountData[playerid][pActivityTime] = 0;
					HideProgressBar(playerid);

					ClearAnimations(playerid, true);
					StopLoopingAnim(playerid);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					TogglePlayerControllable(playerid, true);
				}
			}
			else if(AccountData[playerid][pJob] == JOB_OILMAN)
			{
				if(CheckOilmanTimer(playerid))
				{
					pTakingOilTimer[playerid] = false;
					pRefiningOilTimer[playerid] = false;
					pMixingOilTimer[playerid] = false;

					AccountData[playerid][pActivityTime] = 0;
					HideProgressBar(playerid);

					ClearAnimations(playerid, true);
					StopLoopingAnim(playerid);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					TogglePlayerControllable(playerid, true);
				}
			}
			else if(AccountData[playerid][pJob] == JOB_FISHERMAN)
			{
				if(CheckFishermanTimer(playerid))
				{
					pTakingFishTimer[playerid] = false;

					AccountData[playerid][pActivityTime] = 0;
					HideProgressBar(playerid);
					TogglePlayerControllable(playerid, true);
				}
			}
			else if(AccountData[playerid][pJob] == JOB_MILKER)
			{
				if(CheckMilkerTimer(playerid))
				{
					pTakingSusuTimer[playerid] = false;
					pProcessSusuTimer[playerid] = false;

					AccountData[playerid][pActivityTime] = 0;
					HideProgressBar(playerid);

					ClearAnimations(playerid, true);
					StopLoopingAnim(playerid);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					TogglePlayerControllable(playerid, true);
				}
			}
			else if(AccountData[playerid][pJob] == JOB_TAILOR)
			{
				if(CheckTailorTimer(playerid))
				{
					pTakingWoolTimer[playerid] = false;
					pMakingFabricTimer[playerid] = false;
					pClothingTimer[playerid] = false;

					AccountData[playerid][pActivityTime] = 0;
					HideProgressBar(playerid);

					ClearAnimations(playerid, true);
					StopLoopingAnim(playerid);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					TogglePlayerControllable(playerid, true);
				}
			}
		}
    }
	else if(newkeys & KEY_YES)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			if(AccountData[playerid][pIsSmoking])
			{
				if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

				if(pIsVaping[playerid]) //jika vape
				{
					if(AccountData[playerid][pIsSmokeBlowing]) return 1;

					AccountData[playerid][pIsSmokeBlowing] = true;
					AccountData[playerid][pSmokedTimes]++;
					SetTimerEx("StartSmoking", 2100, false, "i", playerid);
					ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, false, false, false, false, 0, true);
				}
				else
				{
					if(AccountData[playerid][pIsSmokeBlowing]) return 1;

					AccountData[playerid][pIsSmokeBlowing] = true;
					AccountData[playerid][pSmokedTimes]++;
					SetTimerEx("StartSmoking", 3500, false, "i", playerid);
					ApplyAnimation(playerid, "GANGS", "smkcig_prtl", 4.1, false, true, true, true, 1, true);
				}
			}
		}

		if(AccountData[playerid][pEatingStep] > 0)
		{
			if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

			AccountData[playerid][pEatingStep]--;

			switch(AccountData[playerid][pEatingIndexID])
			{
				case 1: //kemangi
				{
					AccountData[playerid][pHunger] += 20;
					PlayEatingAnim(playerid, 2355, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
				case 2:
				{
					AccountData[playerid][pHunger] += 20;
					PlayEatingAnim(playerid, 19579, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
				case 3:
				{
					AccountData[playerid][pHunger] += 10;
					PlayEatingAnim(playerid, 2769, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
				case 4: //sate
				{
					AccountData[playerid][pHunger] += 10;
					PlayEatingAnim(playerid, 2219, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
				case 5: //beef truffle
				{
					AccountData[playerid][pHunger] += 20;
					PlayEatingAnim(playerid, 2219, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
				case 6: //chicken garlic
				{
					AccountData[playerid][pHunger] += 10;
					PlayEatingAnim(playerid, 2355, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
				case 7: //ayam gulai
				{
					AccountData[playerid][pHunger] += 15;
					PlayEatingAnim(playerid, 2355, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
				case 8: //burger
				{
					AccountData[playerid][pHunger] += 25;
					PlayEatingAnim(playerid, 2703, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
				case 9: //teriyaki
				{
					AccountData[playerid][pHunger] += 15;
					PlayEatingAnim(playerid, 2355, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
				case 10: //fried chicken
				{
					AccountData[playerid][pHunger] += 20;
					PlayEatingAnim(playerid, 2355, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
				}
			}
			AccountData[playerid][pEatingDrinking] = true;
			AccountData[playerid][pActivityTime] = 1;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MAKAN");
			ShowProgressBar(playerid);
			pEatingBarTimer[playerid] = true;

			if(AccountData[playerid][pEatingStep] <= 0)
			{
				AccountData[playerid][pEatingIndexID] = 0;
				AccountData[playerid][pEatingStep] = 0;
				ShowTDN(playerid, NOTIFICATION_WARNING, "Anda telah selesai mengonsumsi makanan dan menghabiskannya.");
			}
		}

		if(AccountData[playerid][pDrinkingStep] > 0)
		{
			if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

			AccountData[playerid][pDrinkingStep]--;

			switch(AccountData[playerid][pEatingIndexID])
			{
				case 1: //sunda kelapa
				{
					AccountData[playerid][pThirst] += 20;
					PlayDrinkingAnim(playerid, 19564, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
				case 2:
				{
					AccountData[playerid][pThirst] += 20;
					PlayDrinkingAnim(playerid, 19835, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
				case 3:
				{
					AccountData[playerid][pThirst] += 10;
					PlayDrinkingAnim(playerid, 1546, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
				case 4: //es cendol
				{
					AccountData[playerid][pThirst] += 10;
					PlayDrinkingAnim(playerid, 19569, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
				case 5: //lemon tea
				{
					AccountData[playerid][pThirst] += 20;
					PlayDrinkingAnim(playerid, 1546, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
				case 6: //ice milk yuzu
				{
					AccountData[playerid][pThirst] += 10;
					PlayDrinkingAnim(playerid, 19563, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
				case 7: //es lilin
				{
					AccountData[playerid][pThirst] += 15;
					PlayDrinkingAnim(playerid, 19565, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
				case 8: //coca-cola
				{
					AccountData[playerid][pThirst] += 25;
					PlayDrinkingAnim(playerid, 2647, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
				case 9: //rootbeer
				{
					AccountData[playerid][pThirst] += 15;
					PlayDrinkingAnim(playerid, 1546, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
				case 10: //guinness
				{
					AccountData[playerid][pThirst] += 20;
					PlayDrinkingAnim(playerid, 1669, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
				}
			}

			AccountData[playerid][pEatingDrinking] = true;
			AccountData[playerid][pActivityTime] = 1;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MINUM");
			ShowProgressBar(playerid);
			pEatingBarTimer[playerid] = true;

			if(AccountData[playerid][pDrinkingStep] <= 0)
			{
				AccountData[playerid][pEatingIndexID] = 0;
				AccountData[playerid][pDrinkingStep] = 0;
				ShowTDN(playerid, NOTIFICATION_WARNING, "Anda telah selesai minum dan menghabiskannya.");
			}
		}
	}
	else if(newkeys & KEY_NO && !AccountData[playerid][pKnockdown])
	{
		if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return 1;
		if(AccountData[playerid][pInEvent]) return 1;
		if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat akses radial menu saat ini!");

		SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Gunakan "CMDEA"'/cursor' "WHITE"jika mouse hilang dari layar/textdraw tidak bisa ditekan!");
		ShowRadialTD(playerid);
    }
	return 1;
}

public OnDialogPerformed(playerid, const dialog[], response, success) 
{
    return 1;
}

public OnVehicleHealthChange(vehicleid, Float:newhealth, Float:oldhealth)
{
	if(newhealth < 350.0) // Batasi kendaraan agar tidak langsung meledak
    {
        SetValidVehicleHealth(vehicleid, 350.0);
        SwitchVehicleEngine(vehicleid, false);
    }
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	if(!Iter_Contains(Vehicle, vehicleid)) return 0;

	new impstr[158];
	foreach(new i : Player)
	{
		if(vehicleid == JobVehicle[i])
		{
			DestroyVehicle(JobVehicle[i]);
		}
		
		if(vehicleid == TrailerVehicle[i])
		{
			DestroyVehicle(TrailerVehicle[i]);
		}

		if(vehicleid == FactionHeliVeh[i])
		{
			DestroyVehicle(FactionHeliVeh[i]);
		}

		if(vehicleid == ShowroomVeh[i])
		{
			DestroyVehicle(ShowroomVeh[i]);
		}

		if(AccountData[i][pFaction] != FACTION_NONE)
		{
			if(vehicleid == PlayerFactionVehicle[i][AccountData[i][pFaction]])
			{
				if(VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vIsDeath])
				{
					if(IsValidVehicle(PlayerFactionVehicle[i][AccountData[i][pFaction]]))
						DestroyVehicle(PlayerFactionVehicle[i][AccountData[i][pFaction]]);
					LSPDPlayerCallsign[i][0] = EOS;

					static string[168];
					mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", AccountData[i][pID]);
					mysql_pquery(g_SQL, string);
				}
				else
				{
					SetVehiclePos(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehPos][0], PlayerFactionVehStats[i][pFactVehPos][1], PlayerFactionVehStats[i][pFactVehPos][2]);
					SetVehicleZAngle(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehPos][3]);
					ChangeVehicleColor(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehColor1], PlayerFactionVehStats[i][pFactVehColor2]);
					VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vCoreFuel] = PlayerFactionVehStats[i][pFactVehFuel];
					VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vMaxHealth] = PlayerFactionVehStats[i][pFactVehMaxHealth];
					VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vIsBodyUpgraded] = PlayerFactionVehStats[i][pFactVehBodyUpgraded];
					VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vIsBodyBroken] = PlayerFactionVehStats[i][pFactVehBodyBroken];
					SetVehicleVirtualWorldEx(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehWorld]);

					if(PlayerFactionVehStats[i][pFactVehHealth] < 350.0)
					{
						SetValidVehicleHealth(PlayerFactionVehicle[i][AccountData[i][pFaction]], 350.0);
					}
					else
					{
						SetValidVehicleHealth(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehHealth]);
					}
					UpdateVehicleDamageStatus(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehDamage][0], PlayerFactionVehStats[i][pFactVehDamage][1], PlayerFactionVehStats[i][pFactVehDamage][2], PlayerFactionVehStats[i][pFactVehDamage][3]);
					SwitchVehicleEngine(PlayerFactionVehicle[i][AccountData[i][pFaction]], false);
					SwitchVehicleDoors(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehLocked]);
					VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vCoreLocked] = PlayerFactionVehStats[i][pFactVehLocked];
				}
			}
		}
			
		if(vehicleid == EventVehicle[i])
		{
			DestroyVehicle(EventVehicle[i]);
		}

		if((pInSpecMode[i] == 2 || pInSpecMode[i] == 3) && SavingVehID[i] == vehicleid)
		{
			GetVehicleBoot(vehicleid, AccountData[i][pPos][0], AccountData[i][pPos][1], AccountData[i][pPos][2]);

			AccountData[i][pInterior] = GetVehicleInterior(vehicleid);
			AccountData[i][pWorld] = GetVehicleVirtualWorld(vehicleid);
			
			if(!AccountData[i][pIsUsingUniform])
				SetSpawnInfo(i, NO_TEAM, AccountData[i][pSkin], AccountData[i][pPos][0], AccountData[i][pPos][1], AccountData[i][pPos][2], 180.0, 0, 0, 0, 0, 0, 0);
			else
				SetSpawnInfo(i, NO_TEAM, AccountData[i][pUniform], AccountData[i][pPos][0], AccountData[i][pPos][1], AccountData[i][pPos][2], 180, 0, 0, 0, 0, 0, 0);

			TogglePlayerSpectating(i, false);

			PlayerSpectatePlayer(i, INVALID_PLAYER_ID);
			PlayerSpectateVehicle(i, INVALID_VEHICLE_ID);
			
			SavingVehID[i] = INVALID_VEHICLE_ID;
			pInSpecMode[i] = 0;

			ShowTDN(i, NOTIFICATION_INFO, "Anda telah keluar dari trunk kendaraan.");

			PlayerPlaySound(i, 12200, 0, 0, 0);
		}

		if(AccountData[i][pDuringCarsteal])
		{
			if(vehicleid == g_CarstealCarPhysic[i])
			{
				DestroyVehicle(g_CarstealCarPhysic[i]);

				g_CarstealCountdown = 0;
				AccountData[i][pDuringCarsteal] = false;
				g_IsCarstealStarted = false;
				g_CarstealCarFound[i] = false;
				g_CarstealCooldown = gettime() + 1800;

				ResetAllRaceCP(i);
				
				foreach(new x : LSPDDuty)
				{
					if(DestroyDynamicMapIcon(AccountData[i][g_CarstealIcon][x]))
						AccountData[i][g_CarstealIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
				}

				ShowFivemNotify(i, "Pahlawan Roleplay~n~CAR STEAL", "Kendaraan carsteal telah hancur, misi dinyatakan gagal!", "hud:radar_qmark", 25);
			}
		}
	}
	
	foreach(new vid : PvtVehicles)
	{
		if(vehicleid == PlayerVehicle[vid][pVehPhysic])
		{
			if(!PlayerVehicle[vid][pVehInsuranced])
			{
				// masukin variable dari database player biar mobilnya gak spawn polosan
				SetVehiclePos(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehPos][0], PlayerVehicle[vid][pVehPos][1], PlayerVehicle[vid][pVehPos][2]);
				SetVehicleZAngle(vehicleid, PlayerVehicle[vid][pVehPos][3]);
				ChangeVehicleColor(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehColor1], PlayerVehicle[vid][pVehColor2]);
				VehicleCore[PlayerVehicle[vid][pVehPhysic]][vCoreFuel] = PlayerVehicle[vid][pVehFuel];
				SetVehicleNumberPlate(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehPlate]);
				SetVehicleVirtualWorldEx(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehWorld]);
				LinkVehicleToInteriorEx(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehInterior]);

				if(PlayerVehicle[vid][pVehHealth] < 350.0)
				{
					SetValidVehicleHealth(PlayerVehicle[vid][pVehPhysic], 350.0);
				}
				else
				{
					SetValidVehicleHealth(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehHealth]);
					VehicleCore[PlayerVehicle[vid][pVehPhysic]][vMaxHealth] = PlayerVehicle[vid][pVehMaxHealth];
					VehicleCore[PlayerVehicle[vid][pVehPhysic]][vIsBodyUpgraded] = PlayerVehicle[vid][pVehBodyUpgraded];
					VehicleCore[PlayerVehicle[vid][pVehPhysic]][vIsBodyBroken] = PlayerVehicle[vid][pVehBodyBroken];
				}
				UpdateVehicleDamageStatus(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehDamage][0], PlayerVehicle[vid][pVehDamage][1], PlayerVehicle[vid][pVehDamage][2], PlayerVehicle[vid][pVehDamage][3]);
				if(PlayerVehicle[vid][pVehPaintjob] != -1)
				{
					ChangeVehiclePaintjob(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehPaintjob]);
				}
				
				for(new z = 0; z < 17; z++)
				{
					if(PlayerVehicle[vid][pVehMod][z]) AddVehicleComponent(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehMod][z]);
				}

				if(PlayerVehicle[vid][pVehLocked])
				{
					SwitchVehicleDoors(PlayerVehicle[vid][pVehPhysic], true);
					VehicleCore[PlayerVehicle[vid][pVehPhysic]][vCoreLocked] = true;
				}
				else
				{
					SwitchVehicleDoors(PlayerVehicle[vid][pVehPhysic], false);
					VehicleCore[PlayerVehicle[vid][pVehPhysic]][vCoreLocked] = false;
				}

				if(IsEngineVehicle(PlayerVehicle[vid][pVehPhysic]))
				{
					SwitchVehicleEngine(PlayerVehicle[vid][pVehPhysic], false);
				}
				else
				{
					SwitchVehicleEngine(PlayerVehicle[vid][pVehPhysic], true);
				}
			}
			else
			{
				if(PlayerVehicle[vid][pVehRental] > -1 || PlayerVehicle[vid][pVehRentTime] > 0) //jika rental
				{
					PlayerVehicle[vid][pVehRental] = -1;
					PlayerVehicle[vid][pVehRentTime] = 0;

					if(Iter_Contains(Vehicle, PlayerVehicle[vid][pVehPhysic]))
					{
						SetVehicleNeonLights(PlayerVehicle[vid][pVehPhysic], false, PlayerVehicle[vid][pVehNeon], 0);

					}
					DestroyVehicle(PlayerVehicle[vid][pVehPhysic]);
					PlayerVehicle[vid][pVehHandbraked] = false;
					mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
					mysql_pquery(g_SQL, impstr);
					mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
					mysql_pquery(g_SQL, impstr);
					mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[vid][pVehID]);
					mysql_pquery(g_SQL, impstr);
					mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
            		mysql_pquery(g_SQL, impstr);

					for(new x; x < MAX_BAGASI_ITEMS; x++)
					{
						VehicleBagasi[vid][x][vehicleBagasiExists] = false;
						VehicleBagasi[vid][x][vehicleBagasiID] = 0;
						VehicleBagasi[vid][x][vehicleBagasiVDBID] = 0;
						VehicleBagasi[vid][x][vehicleBagasiTemp][0] = EOS;
						VehicleBagasi[vid][x][vehicleBagasiModel] = 0;
						VehicleBagasi[vid][x][vehicleBagasiQuant] = 0;
					}

					for(new z; z < 3; z++)
					{
						VehicleHolster[vid][vHolsterTaken][z] = false;
						VehicleHolster[vid][vHolsterID][z] = -1;
						VehicleHolster[vid][vHolsterWeaponID][z] = 0;
						VehicleHolster[vid][vHolsterWeaponAmmo][z] = 0;
					}

					for(new x; x < 6; x++)
					{
						vtData[vid][x][vtoy_modelid] = 0;
						vtData[vid][x][vtoy_text][0] = EOS;
						strcopy(vtData[vid][x][vtoy_font], "Arial");
						vtData[vid][x][vtoy_fontsize] = 11;
						vtData[vid][x][vtoy_fontcolor][0] = 255;
						vtData[vid][x][vtoy_fontcolor][1] = 0;
						vtData[vid][x][vtoy_fontcolor][2] = 0;
						vtData[vid][x][vtoy_fontcolor][3] = 0;
						vtData[vid][x][vtoy_fontcolor][4] = 0;
						vtData[vid][x][vtoy_objectcolor][0] = 255;
						vtData[vid][x][vtoy_objectcolor][1] = 0;
						vtData[vid][x][vtoy_objectcolor][2] = 0;
						vtData[vid][x][vtoy_objectcolor][3] = 0;
						vtData[vid][x][vtoy_objectcolor][4] = 0;
						vtData[vid][x][vtoy_x] = 0.0;
						vtData[vid][x][vtoy_y] = 0.0;
						vtData[vid][x][vtoy_z] = 0.0;
						vtData[vid][x][vtoy_rx] = 0.0;
						vtData[vid][x][vtoy_ry] = 0.0;
						vtData[vid][x][vtoy_rz] = 0.0;
					}

					Iter_Remove(PvtVehicles, vid);
				}
				else //jika bukan rental
				{
					if(Iter_Contains(Vehicle, PlayerVehicle[vid][pVehPhysic]))
					{
						SetVehicleNeonLights(PlayerVehicle[vid][pVehPhysic], false, PlayerVehicle[vid][pVehNeon], 0);
					}
					DestroyVehicle(PlayerVehicle[vid][pVehPhysic]);
					PlayerVehicle[vid][pVehInsuranced] = true;
					PlayerVehicle[vid][pVehHandbraked] = false;
					mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Insuranced` = 1 WHERE `id`=%d", PlayerVehicle[vid][pVehID]);
					mysql_pquery(g_SQL, impstr);
					// mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
					// mysql_pquery(g_SQL, impstr);
					// mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
					// mysql_pquery(g_SQL, impstr);
				}
			}
		}
	}

	for(new i; i < MAX_ADMIN_VEHICLES; i++)
	{
		if(vehicleid == GM[adminV][i])
		{
			DestroyVehicle(GM[adminV][i]);
		}
	}
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(playerid != INVALID_PLAYER_ID)
	{
		if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

		if(GetPlayerSkin(playerid) == 0)
		{
			AccountData[playerid][pSkin] = 1;
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			KickEx(playerid);
			return 0;
		}

		if(!AVC_PConnected[playerid])
		{
			Kick(playerid);
			return 0;
		}
		
		new string[144];
		if(!AccountData[playerid][pInEvent])
		{
			//anti cit senjata terlarang
			if(IsProhibitedWeapon(weaponid))
			{
				Kick(playerid);
				return 0;
			}

			if(weaponid >= 1 && weaponid <= 45)
			{
				if(weaponid != 40 && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponType] == WEAPON_TYPE_NONE)
				{
					format(string, sizeof(string), "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena diduga Weapon Hack. "YELLOW"[WS] [%s]", ReturnWeaponName(weaponid));
					SendClientMessage(playerid, Y_RED, string);
					SetWeapons(playerid); //Reload old weapons
					KickEx(playerid);
					return 0;
				}
			}
		}
		else
		{
			if(Iter_Contains(EvRedTeam, playerid))
			{
				if(weaponid != 0 && weaponid != EventInfo[redWeapon][0] && weaponid != EventInfo[redWeapon][1] && weaponid != EventInfo[redWeapon][2])
				{
					format(string, sizeof(string), "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena diduga Weapon Hack "YELLOW"[WS] [%s].", ReturnWeaponName(weaponid));
					SendClientMessage(playerid, Y_RED, string);
					SetWeapons(playerid); //Reload old weapons
					KickEx(playerid);
					return 0;
				}
			}
			else if(Iter_Contains(EvBlueTeam, playerid))
			{
				if(weaponid != 0 && weaponid != EventInfo[blueWeapon][0] && weaponid != EventInfo[blueWeapon][1] && weaponid != EventInfo[blueWeapon][2])
				{
					format(string, sizeof(string), "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena diduga Weapon Hack "YELLOW"[WS] [%s].", ReturnWeaponName(weaponid));
					SendClientMessage(playerid, Y_RED, string);
					SetWeapons(playerid); //Reload old weapons
					KickEx(playerid);
					return 0;
				}
			}
		}
	}

	switch(weaponid){ case 0..18, 39..54: return 1;} //invalid weapons

	if(1 <= weaponid <= 46 && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponID] == weaponid)
	{
		GunData[playerid][g_aWeaponSlots[weaponid]][WeaponAmmo]--;
		if(GunData[playerid][g_aWeaponSlots[weaponid]][WeaponID] != 0 && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponAmmo] <= 0)
		{
			GunData[playerid][g_aWeaponSlots[weaponid]][WeaponID] = 0;
			GunData[playerid][g_aWeaponSlots[weaponid]][WeaponAmmo] = 0;
			GunData[playerid][g_aWeaponSlots[weaponid]][WeaponType] = WEAPON_TYPE_NONE;
			ResetWeapon(playerid, weaponid);
		}
	}

	if(IsPlayerHunting[playerid] && weaponid == 34)
    {
		if(Inventory_Count(playerid, "Hunt Ammo") > 0) Inventory_Remove(playerid, "Hunt Ammo");
    }

	if(hittype == BULLET_HIT_TYPE_PLAYER) //Taser system;
	{
		if(weaponid == 9)
		{
			return 0;
		}

		if(IsPlayerHunting[playerid] && weaponid == 34)
        {
            return 0;
        }

		if(!AccountData[playerid][pInEvent] && (AccountData[playerid][pFaction] != FACTION_LSPD || AccountData[playerid][pFaction] != FACTION_SAGOV))
		{
			static Float:shotX, Float:shotY, Float:shotZ, string[144];
			GetPlayerPos(playerid, shotX, shotY, shotZ);

			format(string, sizeof(string), "RADIO: "WHITE"Terjadi penembakan di daerah %s!", GetLocation(shotX, shotY, shotZ));
			if(gettime() > DelayShotNotif[playerid])
			{
				foreach(new i : LSPDDuty)
				{
					SendClientMessage(i, 0xFFD39BFF, string);
					DelayShotNotif[playerid] = gettime() + 10;
				}
			}
		}
	}	
	else if(hittype == BULLET_HIT_TYPE_VEHICLE)
	{
		if(weaponid == 9)
		{
			return 0;
		}
		
		if(IsPlayerHunting[playerid] && weaponid == 34)
        {
            return 0;
        }
	}
	return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z)
{
    return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if(weaponid == 37 && issuerid == INVALID_PLAYER_ID) //anti cheat flamethrower
	{
		new Float:phealthx;
		GetPlayerHealth(playerid, phealthx);
		SetPlayerHealthEx(playerid, phealthx+amount);
	}

	if(IsFirearmWeapon(weaponid))
	{
		if(issuerid != INVALID_PLAYER_ID)
		{
			if(!AccountData[playerid][pInEvent] && !AccountData[issuerid][pInEvent])
			{
				new Float:realdamage, Float:armour, Float:healthx;
				GetPlayerArmour(playerid, armour);
				GetPlayerHealth(playerid, healthx);

				if(AccountData[playerid][pHasArmor] && armour > 0.0)
				{
					if(AccountData[playerid][pFaction] != FACTION_LSPD)
					{
						if(bodypart == 4 || bodypart == 5 || bodypart == 6 || bodypart == 7 || bodypart == 8) //groin, tangan, kaki
						{
							realdamage = amount - (amount * 0.25);
							
							//jika memakai armor dan yang ditembak selain torso dan bukan kepala maka damage di alihkan ke darah merah dikurang 25%
							SetPlayerArmour(playerid, armour);
							SetPlayerHealthEx(playerid, healthx - realdamage);
						}

						if(bodypart == 9) //kepala
						{
							realdamage = amount + (amount * 0.15);

							//jika memakai armor dan yang ditembak adalah kepala maka damage ke darah merah ditambah 15%
							SetPlayerArmour(playerid, armour);
							SetPlayerHealthEx(playerid, healthx - realdamage);
						}
					}
				}
				else
				{
					if(bodypart == 9) //kepala
					{
						realdamage = amount + (amount * 0.15);
						SetPlayerHealthEx(playerid, healthx - realdamage);
					}

					if(bodypart == 4 || bodypart == 5 || bodypart == 6 || bodypart == 7 || bodypart == 8)
					{
						realdamage = amount - (amount * 0.25);
						SetPlayerHealthEx(playerid, healthx - realdamage);
					}
				}
			}
		}
	}

	if(!AccountData[playerid][pInEvent])
	{
		if(issuerid != INVALID_PLAYER_ID)
		{
			if(IsPlayerInDynamicArea(playerid, AirportGreenZone) || AccountData[playerid][pInDoor] == 41 || AccountData[playerid][pInDoor] == 44)
			{
				AntiGZRetard[issuerid]++;
				ShowTDN(issuerid, NOTIFICATION_ERROR, "Anda akan ditendang dari server jika membuat kerusuhan di lokasi ini!");

				Dialog_Show(issuerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Anti Retard", ""RED"PERINGATAN KERAS!\n\n"YELLOW"Anda dilarang rusuh di area ini atau akan segera ditendang dari server!", "Tutup", "");
				if(AntiGZRetard[issuerid] == 3)
				{
					SendClientMessage(issuerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena rusuh di area ini!");
					KickEx(issuerid);
				}
			}

			if(GetPlayerSkin(issuerid) == 0)
			{
				AccountData[issuerid][pSkin] = 1;
				SetPlayerSkin(issuerid, AccountData[playerid][pSkin]);
				return KickEx(issuerid);
			}
		}
	}
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

	if(!AccountData[playerid][pInEvent])
	{
		if(weaponid >= 1 && weaponid <= 45)
		{
			if(weaponid != 40 && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponType] == WEAPON_TYPE_NONE)
			{
				SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack "YELLOW"[%s].", ReturnWeaponName(weaponid));
				SetWeapons(playerid); //Reload old weapons
				KickEx(playerid);
				return 1;
			}

			if(!AccountData[playerid][pTaser] && !AccountData[playerid][pUseBeanbag])
			{
				if(weaponid != 40 && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponID] != weaponid)
				{
					SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack "YELLOW"[%s].", ReturnWeaponName(weaponid));
					SetWeapons(playerid); //Reload old weapons
					KickEx(playerid);
					return 1;
				}
			}
		}
	}

	if((AccountData[playerid][pFaction] == FACTION_LSPD || AccountData[playerid][pFaction] == FACTION_SAGOV) && AccountData[playerid][pTaser] && weaponid == 23)
	{
		if(!IsPlayerStunned(damagedid))
			Tazer_OnPlayerGiveDamage(playerid, damagedid, weaponid);
	}

	if(AccountData[playerid][pFaction] == FACTION_LSPD && AccountData[playerid][pUseBeanbag] && weaponid == 25)
	{
		if(!IsPlayerStunned(damagedid))
			Beanbag_OnPlayerGiveDamage(playerid, damagedid, weaponid);
	}

	if(AccountData[playerid][pFaction] == FACTION_LSPD && AccountData[playerid][pTackleEnable])
	{
		if(!IsPlayerStunned(damagedid))
			Tackle_OnPlayerGiveDamage(playerid, damagedid, weaponid);
	}
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

    printf("Vehicle %d was modded by ID %d with the componentid %d", vehicleid, playerid, componentid);
	switch(componentid)
    {
        case 1008..1010: if(IsPlayerInInvalidNosVehicle(playerid)) RemoveVehicleComponent(vehicleid, componentid);
    }
    if(!IsComponentidCompatible(GetVehicleModel(vehicleid), componentid)) RemoveVehicleComponent(vehicleid, componentid);
    if(GetPlayerInterior(playerid) == 0)
    {
        SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}You have been kicked from the server due to suspected Vehicle Tuning Hack!");
		KickEx(playerid); // Anti-tuning hacks script
        return 0;
    }
    return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
    if(!success)
    {
        printf("[RCON LOGIN] %s GAGAL LOGIN RCON MENGGUNAKAN PASSWORD %s", ip, password);
        new pip[16];
        foreach(new i : Player)
		{
            GetPlayerIp(i, pip, sizeof(pip));
            if(!strcmp(ip, pip, true))
            {
				RconAttempt[i]++;
				SendAdm(i, "Stop attempting to log in with RCON, or you will be banned shortly! [%d/3]", RconAttempt[i]);

				if(RconAttempt[i] >= 3)
				{
					SendAdm(i, "You have been kicked from the server for failed RCON attempts!");
                	BlockIpAddress(ip, 60000);
					KickEx(i);
				}
            }
        }
    }
    return 1;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned]) return Kick(playerid);

	if(IsLSPDVehicle(vehicleid) || IsLSFDVehicle(vehicleid))
    {
		if(newstate == 1)
		{
			for(new x; x < 5; x++)
			{
				if(DestroyDynamicObject(FactionVehSiren[vehicleid][x]))
					FactionVehSiren[vehicleid][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
			}
			
			if(GetVehicleModel(vehicleid) == 426) //premier
			{
				FactionVehSiren[vehicleid][0] = CreateDynamicObject(18646,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][0], vehicleid, -0.440, -0.060, 0.880, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][1] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][1], vehicleid, 0.639, -1.750, 0.360, 0.000, 0.000, 0.000);
			}
			else if(GetVehicleModel(vehicleid) == 560) //sultan
			{
				FactionVehSiren[vehicleid][0] = CreateDynamicObject(18646,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][0], vehicleid, -0.360, 0.010, 0.870, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][1] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][1], vehicleid, 0.550, -1.330, 0.479, 0.000, 0.000, 0.000);
			}
			else if(GetVehicleModel(vehicleid) == 415) //cheetah
			{
				FactionVehSiren[vehicleid][0] = CreateDynamicObject(18646, 0, 0, 0, 0, 0, 0, -1, -1, -1, 200.00, 200.00, -1);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][0], vehicleid, -0.230, -0.190, 0.659, 0.000, 0.000, 0.000);
			}
			else if(GetVehicleModel(vehicleid) == 541) //bullet
			{
				FactionVehSiren[vehicleid][0] = CreateDynamicObject(18646,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][0], vehicleid, -0.330, -0.240, 0.680, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][1] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][1], vehicleid, 0.000, 1.989, -0.390, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][2] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][2], vehicleid, -0.420, -2.269, 0.120, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][3] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][3], vehicleid, 0.409, -2.249, 0.120, 0.000, 180.000, 0.000);
				FactionVehSiren[vehicleid][4] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][4], vehicleid, 0.000, -1.801, 0.030, 0.000, 0.000, 180.000);
			}
			else if(GetVehicleModel(vehicleid) == 411) //infernus
			{
				FactionVehSiren[vehicleid][0] = CreateDynamicObject(18646,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][0], vehicleid, -0.360, -0.060, 0.760, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][1] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][1], vehicleid, 0.000, 2.591, -0.380, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][2] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][2], vehicleid, 0.000, -2.200, -0.160, 0.000, 0.000, 180.000);
				FactionVehSiren[vehicleid][3] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][3], vehicleid, -0.530, -2.480, -0.070, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][4] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][4], vehicleid, 0.529, -2.480, -0.070, 0.000, 180.000, 0.000);
			}
			else if(GetVehicleModel(vehicleid) == 451) //turismo
			{
				FactionVehSiren[vehicleid][0] = CreateDynamicObject(18646,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][0], vehicleid, -0.270, -0.360, 0.620, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][1] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][1], vehicleid, 0.000, 2.220, -0.470, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][2] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][2], vehicleid, 0.000, -2.110, -0.320, 0.000, 0.000, 180.000);
				FactionVehSiren[vehicleid][3] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][3], vehicleid, -0.610, -2.520, -0.200, 0.000, 0.000, 0.000);
				FactionVehSiren[vehicleid][4] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
				AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][4], vehicleid, 0.620, -2.520, -0.200, 0.000, 180.000, 0.000);
			}
			else if(GetVehicleModel(vehicleid) == 416) //ambulance
			{
				FactionVehSiren[vehicleid][0] = CreateDynamicObject(11701,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
    			AttachDynamicObjectToVehicle(FactionVehSiren[vehicleid][0], vehicleid, 0.000, 0.890, 1.230, 0.000, 0.000, 0.000);
			}
		}
		else
		{
			for(new x; x < 5; x++)
			{
				if(DestroyDynamicObject(FactionVehSiren[vehicleid][x]))
					FactionVehSiren[vehicleid][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
			}
		}
	}
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

YCMD:pl(playerid, params[], help)
{
    new sounds;

    if(sscanf(params, "d", sounds))
    {
        SUM(playerid, "/pl [sound id]");
        return 1;
    }

    PlayerPlaySound(playerid, sounds, 0.0, 0.0, 0.0);
    return 1;
}

//hotkeys
forward FS_OpenInventory(playerid);
public FS_OpenInventory(playerid)
{
	if(!AccountData[playerid][pSpawned]) return 1;
	if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
	if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(pShortcutResultShown[playerid]) return 1;

	AccountData[playerid][pSelectItem] = -1;
	AccountData[playerid][pItemQuantity] = 0;

	HideRadialTD(playerid);
	HideServerNameTD(playerid);
    HideSpeedoTD(playerid);
    HideHBETD(playerid);

	PlayerPlaySound(playerid, 1039, 0.0, 0.0, 0.0);
	Inventory_Show(playerid);

	pShortcutResultShown[playerid] = true;
	return 1;
}

forward FS_OpenSmartphone(playerid);
public FS_OpenSmartphone(playerid)
{
	if(!AccountData[playerid][pSpawned]) return 1;
	if(!PlayerHasItem(playerid, "Smartphone")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki smartphone!");

	if(!AVC_PConnected[playerid]) return Kick(playerid);
	
	if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(OJailData[playerid][jailed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(pShortcutResultShown[playerid]) return 1;
	
	if(PlayerPhoneData[playerid][phoneIncomingCall] || PlayerPhoneData[playerid][phoneDuringConversation])
	{
		CutCallingLine(playerid);
		return 1;
	}

	if(PlayerPhoneData[playerid][phoneShown])
	{
		if(pRebootingPhoneTimer[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ponsel ini sedang dihidupkan, mohon menunggu hingga selesai!");

		RemovePlayerAttachedObject(playerid, 9);
		StopLoopingAnim(playerid);

		HideAllPhoneTD(playerid);
		PlayerPhoneData[playerid][phoneShown] = false;

		SendRPMeAboveHead(playerid, "Menutup smartphone miliknya.");
	}
	else
	{
		if(PlayerPhoneData[playerid][phoneOn])
		{
			ShowPhoneLockScreenTD(playerid);
		}
		else
		{
			TextDrawShowForPlayer(playerid, LockScreenTD[0]);
			TextDrawShowForPlayer(playerid, LockScreenTD[1]);
			TextDrawShowForPlayer(playerid, LockScreenTD[2]);
			TextDrawShowForPlayer(playerid, LockScreenTD[3]);
			TextDrawShowForPlayer(playerid, LockScreenTD[4]);
			TextDrawShowForPlayer(playerid, LockScreenTD[5]);
			TextDrawShowForPlayer(playerid, LockScreenTD[8]);
			TextDrawShowForPlayer(playerid, LockScreenTD[9]);
			TextDrawShowForPlayer(playerid, LockScreenTD[10]);

			TextDrawShowForPlayer(playerid, RebootScreenTD[0]);
			TextDrawShowForPlayer(playerid, RebootScreenTD[6]);

			TextDrawShowForPlayer(playerid, HomeButtonPhone[0]);
			TextDrawShowForPlayer(playerid, HomeButtonPhone[1]);
		}
		if(!IsPlayerInAnyVehicle(playerid))
		{
			ApplyAnimation(playerid, "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, true);
			SetPlayerAttachedObject(playerid, 9, 18869, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
		}
		PlayerPhoneData[playerid][phoneShown] = true;

		SendRPMeAboveHead(playerid, "Membuka smartphone miliknya.");
	}
	HideRadialTD(playerid);

	pShortcutResultShown[playerid] = true;

	SelectTextDraw(playerid, 0xff91a4cc);
	return 1;
}

forward FS_ChangeVoiceRadius(playerid);
public FS_ChangeVoiceRadius(playerid)
{
	if(!AccountData[playerid][pSpawned]) return 1;
	switch(pVoiceDistanceStatus[playerid])
	{
		case 0: // Bisik ke Normal
		{
			pVoiceDistanceStatus[playerid] = 1;
			CallRemoteFunction("UpdatePlayerVoiceDistance", "if", playerid, 14.7);
			PlayerTextDrawShow(playerid, PHBE[playerid][18]); // Voice 1
			PlayerTextDrawShow(playerid, PHBE[playerid][17]); // Voice 2
			PlayerTextDrawHide(playerid, PHBE[playerid][16]); // Voice 3
		}
		case 1: // Normal ke Bisik
		{
			pVoiceDistanceStatus[playerid] = 2;
			CallRemoteFunction("UpdatePlayerVoiceDistance", "if", playerid, 6.7);
			PlayerTextDrawShow(playerid, PHBE[playerid][18]); // Voice 1
			PlayerTextDrawHide(playerid, PHBE[playerid][17]); // Voice 2
			PlayerTextDrawHide(playerid, PHBE[playerid][16]); // Voice 3
		}
		case 2: // Bisik ke Teriak
		{
			pVoiceDistanceStatus[playerid] = 0;
			CallRemoteFunction("UpdatePlayerVoiceDistance", "if", playerid, 40.7);
			PlayerTextDrawShow(playerid, PHBE[playerid][18]); // Voice 1
			PlayerTextDrawShow(playerid, PHBE[playerid][17]); // Voice 2
			PlayerTextDrawShow(playerid, PHBE[playerid][16]); // Voice 3
		}
	}
	return 1;
}

forward FS_OpenRadio(playerid);
public FS_OpenRadio(playerid)
{
	if(!AccountData[playerid][pSpawned]) return 1;
	if(!PlayerVoiceData[playerid][pHasRadio]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki radio!");
    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya untuk suut ini!");
	if(pShortcutResultShown[playerid]) return 1;
	
    new strls[128];
    format(strls, sizeof(strls), "%d", PlayerVoiceData[playerid][pRadioFreq]);
    PlayerTextDrawSetString(playerid, RadioVoiceFreqTD[playerid], strls);
    ShowRadioVoiceTD(playerid);

    if(!IsPlayerInAnyVehicle(playerid))
	{
        ApplyAnimation(playerid, "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, true);
	    SetPlayerAttachedObject(playerid, 9, 19942, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
    }

	pShortcutResultShown[playerid] = true;
	return 1;
}

forward FS_ResetAnimation(playerid);
public FS_ResetAnimation(playerid)
{
	if(!AccountData[playerid][pSpawned]) return 1;
	if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(IsPlayerStunned(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(OJailData[playerid][jailed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pInEvent]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(!gPlayerUsingLoopingAnim[playerid]) return 1;
	
	gPlayerUsingLoopingAnim[playerid] = false;
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	RemovePlayerAttachedObject(playerid, 9);
	StopRunningAnimation(playerid);
	return 1;
}

forward FS_UseItemOnSlot(playerid, slots);
public FS_UseItemOnSlot(playerid, slots)
{
	if(!AccountData[playerid][pSpawned]) return 1;
	if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
	if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(IsPlayerStunned(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(pShortcutResultShown[playerid]) return 1;
	if(!InventoryData[playerid][slots][invExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada item di dalam slot!");
	
	HideRadialTD(playerid);
	OnPlayerUseItem(playerid, InventoryData[playerid][slots][invItem]);
	return 1;
}

forward FS_VehicleLockStatus(playerid);
public FS_VehicleLockStatus(playerid)
{
	if(!AccountData[playerid][pSpawned]) return 1;
	if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(IsPlayerStunned(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(pShortcutResultShown[playerid]) return 1;

	HideRadialTD(playerid);

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new vehid = GetPlayerVehicleID(playerid);
		if(vehid == INVALID_VEHICLE_ID) return 1;
		
		foreach(new pv : PvtVehicles)
		{
			if(PlayerVehicle[pv][pVehPhysic] == vehid)
			{
				if(PlayerVehicle[pv][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
				if(PlayerVehicle[pv][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini adlam kondisi tirelocked!");

				static string[84];
				switch(VehicleCore[vehid][vCoreLocked])
				{
					case false:
					{
						VehicleCore[vehid][vCoreLocked] = true;
						SwitchVehicleDoors(vehid, true);
						format(string, sizeof(string), "~y~%s~n~~r~Terkunci", GetVehicleModelName(GetVehicleModel(PlayerVehicle[pv][pVehPhysic])));
						GameTextForPlayer(playerid, string, 2000, 4);

						if(!GetLightStatus(vehid))
						{
							VehicleCore[vehid][vIsRemoted] = true;
							VehicleCore[vehid][vRemotedCount] = 0;
							VehicleCore[vehid][vRemotedType] = 1;
						}
					}
					case true:
					{
						VehicleCore[vehid][vCoreLocked] = false;
						SwitchVehicleDoors(vehid, false);
						format(string, sizeof(string), "~y~%s~n~~g~Terbuka", GetVehicleModelName(GetVehicleModel(PlayerVehicle[pv][pVehPhysic])));
						GameTextForPlayer(playerid, string, 2000, 4);

						if(!GetLightStatus(vehid))
						{
							VehicleCore[vehid][vIsRemoted] = true;
							VehicleCore[vehid][vRemotedCount] = 0;
							VehicleCore[vehid][vRemotedType] = 2;
						}
					}
				}
				PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
				ApplyAnimation(playerid, "WEAPONS", "SHP_Ar_Ret_S", 4.1, false,true,true,false,0,true);
			}
		}
	}
	else
	{
		new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
		if(vehid == INVALID_VEHICLE_ID) return 1;
		
		static string[84];
		foreach(new pv : PvtVehicles)
		{
			if(PlayerVehicle[pv][pVehPhysic] == vehid)
			{
				if(PlayerVehicle[pv][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
				if(PlayerVehicle[pv][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini adlam kondisi tirelocked!");

				switch(VehicleCore[vehid][vCoreLocked])
				{
					case false:
					{
						VehicleCore[vehid][vCoreLocked] = true;
						SwitchVehicleDoors(vehid, true);
						format(string, sizeof(string), "~y~%s~n~~r~Terkunci", GetVehicleModelName(GetVehicleModel(PlayerVehicle[pv][pVehPhysic])));
						GameTextForPlayer(playerid, string, 2000, 4);

						if(!GetLightStatus(vehid))
						{
							VehicleCore[vehid][vIsRemoted] = true;
							VehicleCore[vehid][vRemotedCount] = 0;
							VehicleCore[vehid][vRemotedType] = 1;
						}
					}
					case true:
					{
						VehicleCore[vehid][vCoreLocked] = false;
						SwitchVehicleDoors(vehid, false);
						format(string, sizeof(string), "~y~%s~n~~g~Terbuka", GetVehicleModelName(GetVehicleModel(PlayerVehicle[pv][pVehPhysic])));
						GameTextForPlayer(playerid, string, 2000, 4);


						if(!GetLightStatus(vehid))
						{
							VehicleCore[vehid][vIsRemoted] = true;
							VehicleCore[vehid][vRemotedCount] = 0;
							VehicleCore[vehid][vRemotedType] = 2;
						}
					}
				}
				PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
				ApplyAnimation(playerid, "WEAPONS", "SHP_Ar_Ret_S", 4.1, false,true,true,false,0,true);
			}
		}
	}
	return 1;
}
