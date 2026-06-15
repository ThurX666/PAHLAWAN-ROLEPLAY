new MySQL:g_SQL;
new g_MysqlRaceCheck[MAX_PLAYERS];
new bool:InCharSelection[MAX_PLAYERS]; // Menandai apakah player sedang di menu pilih karakter

new PlayerCharID[MAX_PLAYERS][MAX_CHARS];
new PlayerChar[MAX_PLAYERS][MAX_CHARS][MAX_PLAYER_NAME + 1];
new PlayerCharLevel[MAX_PLAYERS][MAX_CHARS];
new PlayerCharCash[MAX_PLAYERS][MAX_CHARS];
new PlayerCharBank[MAX_PLAYERS][MAX_CHARS];
new PlayerCharSkin[MAX_PLAYERS][MAX_CHARS];
new PlayerCharLastLogin[MAX_PLAYERS][MAX_CHARS][50];
new PlayerCharLastLoginUnix[MAX_PLAYERS][MAX_CHARS];  // BARU: Untuk hitungan sistem (Integer)

new PlayerUID[MAX_PLAYERS];
new PlayerUCP[MAX_PLAYERS][22];
new PlayerUCPVipStatus[MAX_PLAYERS][50];
new PlayerUCPVipTime[MAX_PLAYERS];
new PlayerUCPGold[MAX_PLAYERS];
//
new PlayerSelectCharTD[MAX_PLAYERS];
new LobbyActorID[MAX_PLAYERS][MAX_CHARS];
new LobbyVirtualWorld[MAX_PLAYERS];
//
new PlayerSelectSpawnTD[MAX_PLAYERS];
new Float:PlayerCharLastSpawnX[MAX_PLAYERS][MAX_CHARS];
new Float:PlayerCharLastSpawnY[MAX_PLAYERS][MAX_CHARS];
new Float:PlayerCharLastSpawnZ[MAX_PLAYERS][MAX_CHARS];
new Float:PlayerCharLastSpawnA[MAX_PLAYERS][MAX_CHARS];

new HouseMemberName[MAX_PLAYERS][3][MAX_PLAYER_NAME + 1];

new
    lastDrunkLevel[MAX_PLAYERS],
    currFPS[MAX_PLAYERS];

//spec object
new pInSpecMode[MAX_PLAYERS];

new animPage[MAX_PLAYERS];
new pCurWeap[MAX_PLAYERS];
new AttCheckCurWeapon[MAX_PLAYERS];

new bool:HBETDHidden[MAX_PLAYERS];
new SpawnLocIdx[MAX_PLAYERS];

new bool:TogOOC;

new bool:pIsVaping[MAX_PLAYERS];

//hotkey
new pVoiceDistanceStatus[MAX_PLAYERS];
new pShortcutResultShown[MAX_PLAYERS];

//new STREAMER_TAG_OBJECT:EMSClothing[MAX_PLAYERS][2];
new STREAMER_TAG_3D_TEXT_LABEL:pFactionLabel[MAX_PLAYERS][3];
new STREAMER_TAG_3D_TEXT_LABEL:g_GasProgressLabel[MAX_PLAYERS];
new STREAMER_TAG_3D_TEXT_LABEL:FactionVehCallsign[MAX_VEHICLES];
new STREAMER_TAG_OBJECT:FactionVehSiren[MAX_VEHICLES][5];
new STREAMER_TAG_OBJECT:FactionVehObject[MAX_VEHICLES][23];
new STREAMER_TAG_OBJECT: UfoObjID[MAX_VEHICLES][2];

new Text:BlackJackTD[10];
new Text:BlindfoldTD;
new Text:Event_SGTD;
new Text:KillEffectTD;
new Text:GarbageHideTD[2];

new TempString[MAX_PLAYERS][144];
new Temptargetid[MAX_PLAYERS];
new TempRows[MAX_PLAYERS];
new ListedUser[MAX_PLAYERS][100];
new NearestUser[MAX_PLAYERS][100];
new PlayerListitem[MAX_PLAYERS][200];
new NearestSingle[MAX_PLAYERS];
new NearestVehicleID[MAX_PLAYERS];

new UCPRegisterDate[MAX_PLAYERS][50];

new ModshopModel = mS_INVALID_LISTID;

new AntiGZRetard[MAX_PLAYERS];

new OldChiliSalary,
    OldRiceSalary,
    OldSugarSalary,
    OldStrawberrySalary,
    OldJerukSalary,
    OldAnggurSalary,
    ChiliSalary = 30,
    RiceSalary = 30,
    SugarSalary = 30,
    StrawberrySalary = 40,
    JerukSalary = 40,
    AnggurSalary = 40;

//cheat
new s_playerWarnings[MAX_PLAYERS];

new PlayerFactionVehicle[MAX_PLAYERS][MAX_FACTIONS];

enum e_factvehstats
{
    pFactVehModel,
    Float:pFactVehPos[4],
    pFactVehDamage[4],
    Float:pFactVehHealth,
    pFactVehFuel,
    bool:pFactVehLocked,
    pFactVehWorld,
    pFactVehColor1,
    pFactVehColor2,
    Float:pFactVehMaxHealth,
    bool:pFactVehBodyUpgraded,
    bool:pFactVehBodyBroken
};
new PlayerFactionVehStats[MAX_PLAYERS][e_factvehstats];
new LSPDPlayerCallsign[MAX_PLAYERS][32];

new AC_CMDSpamTime[MAX_PLAYERS];
new AC_ChatSpamTime[MAX_PLAYERS];
new AC_LastState[MAX_PLAYERS];
new AC_LastStateTime[MAX_PLAYERS];
new bool:AVC_PConnected[MAX_PLAYERS];

//temporary saving veh id
new SavingVehID[MAX_PLAYERS];
new EnteringVehID[MAX_PLAYERS];
new ValidVehicleDriver[MAX_VEHICLES];

new SeenPutrideliMenu[MAX_PLAYERS];

new STREAMER_TAG_RACE_CP:EventRaceRCP[MAX_PLAYERS];
new EventVehicle[MAX_PLAYERS];

//notif item box
enum eItemBox
{
	ItemBoxIcon,
	ItemBoxMessage[320],
	ItemBoxJumlahMessage[200],
	ItemBoxSize
};
new InfoItemBox[MAX_PLAYERS][5][eItemBox];
new MaxPlayerItemBox[MAX_PLAYERS];
new PlayerText:TextDrawItemBox[MAX_PLAYERS][5*10];
new IndexItemBox[MAX_PLAYERS];

enum e_playwarns
{
	bool:warnExists,
	warnOwner,
	warnType,
	warnIssuer[24],
	warnDate[32],
	warnDateTime[64],
	warnReason[32]
};
new PlayerWarning[MAX_PLAYERS][100][e_playwarns];

enum e_votesnames
{
    bool:voteStarted,
    voteTime,
    voteText[128],
    voteYes,
    voteNo
};
new VoteInfo[e_votesnames];

new const g_VehicleColors[] = {
    0x000000FF, 0xFFFFFFFF, 0x2A77A1FF, 0x840410FF, 0x263739FF, 0x86446EFF, 0xD78E10FF, 0x4C75B7FF, 0xBDBEC6FF, 0x5E7072FF, 
    0x46597AFF, 0x656A79FF, 0x5D7E8DFF, 0x58595AFF, 0xD6DAD6FF, 0x9CA1A3FF, 0x335F3FFF, 0x730E1AFF, 0x7B0A2AFF, 0x9F9D94FF, 
    0x3B4E78FF, 0x732E3EFF, 0x691E3BFF, 0x96918CFF, 0x515459FF, 0x3F3E45FF, 0xA5A9A7FF, 0x635C5AFF, 0x3D4A68FF, 0x979592FF, 
    0x421F21FF, 0x5F272BFF, 0x8494ABFF, 0x767B7CFF, 0x646464FF, 0x5A5752FF, 0x252527FF, 0x2D3A35FF, 0x93A396FF, 0x6D7A88FF, 
    0x221918FF, 0x6F675FFF, 0x7C1C2AFF, 0x5F0A15FF, 0x193826FF, 0x5D1B20FF, 0x9D9872FF, 0x7A7560FF, 0x989586FF, 0xADB0B0FF, 
    0x848988FF, 0x304F45FF, 0x4D6268FF, 0x162248FF, 0x272F4BFF, 0x7D6256FF, 0x9EA4ABFF, 0x9C8D71FF, 0x6D1822FF, 0x4E6881FF, 
    0x9C9C98FF, 0x917347FF, 0x661C26FF, 0x949D9FFF, 0xA4A7A5FF, 0x8E8C46FF, 0x341A1EFF, 0x6A7A8CFF, 0xAAAD8EFF, 0xAB988FFF, 
    0x851F2EFF, 0x6F8297FF, 0x585853FF, 0x9AA790FF, 0x601A23FF, 0x20202CFF, 0xA4A096FF, 0xAA9D84FF, 0x78222BFF, 0x0E316DFF, 
    0x722A3FFF, 0x7B715EFF, 0x741D28FF, 0x1E2E32FF, 0x4D322FFF, 0x7C1B44FF, 0x2E5B20FF, 0x395A83FF, 0x6D2837FF, 0xA7A28FFF, 
    0xAFB1B1FF, 0x364155FF, 0x6D6C6EFF, 0x0F6A89FF, 0x204B6BFF, 0x2B3E57FF, 0x9B9F9DFF, 0x6C8495FF, 0x4D8495FF, 0xAE9B7FFF, 
    0x406C8FFF, 0x1F253BFF, 0xAB9276FF, 0x134573FF, 0x96816CFF, 0x64686AFF, 0x105082FF, 0xA19983FF, 0x385694FF, 0x525661FF, 
    0x7F6956FF, 0x8C929AFF, 0x596E87FF, 0x473532FF, 0x44624FFF, 0x730A27FF, 0x223457FF, 0x640D1BFF, 0xA3ADC6FF, 0x695853FF, 
    0x9B8B80FF, 0x620B1CFF, 0x5B5D5EFF, 0x624428FF, 0x731827FF, 0x1B376DFF, 0xEC6AAEFF, 0x000000FF, 0x177517FF, 0x210606FF, 
    0x125478FF, 0x452A0DFF, 0x571E1EFF, 0x010701FF, 0x25225AFF, 0x2C89AAFF, 0x8A4DBDFF, 0x35963AFF, 0xB7B7B7FF, 0x464C8DFF, 
    0x84888CFF, 0x817867FF, 0x817A26FF, 0x6A506FFF, 0x583E6FFF, 0x8CB972FF, 0x824F78FF, 0x6D276AFF, 0x1E1D13FF, 0x1E1306FF, 
    0x1F2518FF, 0x2C4531FF, 0x1E4C99FF, 0x2E5F43FF, 0x1E9948FF, 0x1E9999FF, 0x999976FF, 0x7C8499FF, 0x992E1EFF, 0x2C1E08FF, 
    0x142407FF, 0x993E4DFF, 0x1E4C99FF, 0x198181FF, 0x1A292AFF, 0x16616FFF, 0x1B6687FF, 0x6C3F99FF, 0x481A0EFF, 0x7A7399FF, 
    0x746D99FF, 0x53387EFF, 0x222407FF, 0x3E190CFF, 0x46210EFF, 0x991E1EFF, 0x8D4C8DFF, 0x805B80FF, 0x7B3E7EFF, 0x3C1737FF, 
    0x733517FF, 0x781818FF, 0x83341AFF, 0x8E2F1CFF, 0x7E3E53FF, 0x7C6D7CFF, 0x020C02FF, 0x072407FF, 0x163012FF, 0x16301BFF, 
    0x642B4FFF, 0x368452FF, 0x999590FF, 0x818D96FF, 0x99991EFF, 0x7F994CFF, 0x839292FF, 0x788222FF, 0x2B3C99FF, 0x3A3A0BFF, 
    0x8A794EFF, 0x0E1F49FF, 0x15371CFF, 0x15273AFF, 0x375775FF, 0x060820FF, 0x071326FF, 0x20394BFF, 0x2C5089FF, 0x15426CFF, 
    0x103250FF, 0x241663FF, 0x692015FF, 0x8C8D94FF, 0x516013FF, 0x090F02FF, 0x8C573AFF, 0x52888EFF, 0x995C52FF, 0x99581EFF, 
    0x993A63FF, 0x998F4EFF, 0x99311EFF, 0x0D1842FF, 0x521E1EFF, 0x42420DFF, 0x4C991EFF, 0x082A1DFF, 0x96821DFF, 0x197F19FF, 
    0x3B141FFF, 0x745217FF, 0x893F8DFF, 0x7E1A6CFF, 0x0B370BFF, 0x27450DFF, 0x071F24FF, 0x784573FF, 0x8A653AFF, 0x732617FF, 
    0x319490FF, 0x56941DFF, 0x59163DFF, 0x1B8A2FFF, 0x38160BFF, 0x041804FF, 0x355D8EFF, 0x2E3F5BFF, 0x561A28FF, 0x4E0E27FF, 
    0x706C67FF, 0x3B3E42FF, 0x2E2D33FF, 0x7B7E7DFF, 0x4A4442FF, 0x28344EFF
};

//Anti Weapon Hack
new const g_aWeaponSlots[] = {
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 10, 10, 8, 8, 8, 0, 0, 0, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 4, 6, 6, 7, 7, 7, 7, 8, 12, 9, 9, 9, 11, 11, 11
};

//pajak
new Float:RumusPajakTabungan[MAX_PLAYERS], 
    Float:RumusPajakKendaraan[MAX_PLAYERS],
    TempMoneyLaundry[MAX_PLAYERS],
    Float:TempMoneyLaundryR[MAX_PLAYERS];

new const g_Alphabet[26][] = {
	"A", "B", "C", "D", "E", "F", "G", "H", 
	"I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", 
	"X", "Y", "Z"
};


new const g_MixAlphabet[60][] = {
	"A", "B", "C", "D", "E", "F", "G", "H", 
	"J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", 
	"X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "m",
    "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2",
    "3", "4", "5", "6", "7", "8", "9"
};

//activity
new IsPlayerHunting[MAX_PLAYERS];

//anti bunny hopping
//new BunnyHopDetected[MAX_PLAYERS];
//new BunnyHopTimer[MAX_PLAYERS];

//new sclstr[512];

new __g_RandomSkinMale[] = {
    2, 3, 20, 59, 60,
    147, 186, 7, 240, 249
};

new __g_RandomSkinFemale[] = {
    12, 40, 55, 76, 93,
    226, 238, 169, 237, 263
};

enum
{
    JOB_NONE,
    JOB_FARMER,
    JOB_MINER,
    JOB_BUTCHER,
    JOB_OILMAN,
    JOB_ANGKOT,
    JOB_FISHERMAN,
    JOB_CARGO,
    JOB_PORTER,
    JOB_MIXER,
    JOB_LUMBERJACK,
    JOB_PELAUT,
    JOB_MILKER,
    JOB_TAILOR
};

enum
{
    FACTION_NONE, //0
    FACTION_LSPD, //1
    FACTION_LSFD, //2
    FACTION_PUTRIDELI, //3
    FACTION_SAGOV, //4
    FACTION_BENNYS, //5
    FACTION_UBER, //6
    FACTION_DINARBUCKS, //7
    FACTION_FOX11, //8
    FACTION_AUTOMAX, //9
    FACTION_HANDOVER, //10
    FACTION_SRIMERSING, //11
    FACTION_TEXAS, //12
    FACTION_FEDERAL //13
};

enum
{
    SIDEJOB_NONE,
    SIDEJOB_MOWING,
    SIDEJOB_SWEEPER,
    SIDEJOB_FORKLIFT,
    SIDEJOB_TRASHCOLLECTOR,
    SIDEJOB_PIZZA
};

new Float:Velocity[MAX_PLAYERS][3];

new bool:gPlayerUsingLoopingAnim[MAX_PLAYERS];
new bool:gPlayerAnimLibsPreloaded[MAX_PLAYERS];

//admin duty
new STREAMER_TAG_3D_TEXT_LABEL:AdminLabel[MAX_PLAYERS];

new STREAMER_TAG_RACE_CP:JobCP[MAX_PLAYERS];

// Server Uptime
new
	WorldTime = 20,
	WorldWeather = 0;

new FactBadTaxTime;

//====== QUIZ
new bool:quiz,
	answers[256],
	bool:answermade,
	qprs;

// dimensi waktu / server clock
new
    real_life_clock_minutes = 0,
    real_life_clock_hours = 1;
    
new DelayShotNotif[MAX_PLAYERS];

new JobVehicle[MAX_PLAYERS];
new TrailerVehicle[MAX_PLAYERS];
new FactionHeliVeh[MAX_PLAYERS];
new ShowroomVeh[MAX_PLAYERS];
new DMVVeh[MAX_PLAYERS];

new STREAMER_TAG_ACTOR:pDrugSellActor[MAX_PLAYERS];
new STREAMER_TAG_MAP_ICON:pDrugSellIcon[MAX_PLAYERS];
new STREAMER_TAG_3D_TEXT_LABEL:pDrugSellLabel[MAX_PLAYERS];
new pDrugSellStep[MAX_PLAYERS];
new pDrugSellChosen[MAX_PLAYERS];

//rcon
new RconAttempt[MAX_PLAYERS];

//mdc
enum e_mdcinfo
{
    //personal information
    pID,
    Name[24],
    Birthday[50],
    Phone[13],
    Job,
    Faction,
    FactionRank,
    bool:GVL1Lic,
    GVL1LicTime,
    bool:GVL2Lic,
    GVL2LicTime,
    bool:MBLic,
    MBLicTime,
    bool:BLic,
    BLicTime,
    bool:Air1Lic,
    Air1LicTime,
    bool:Air2Lic,
    Air2LicTime,
    bool:FirearmLic,
    FirearmLicTime,
    bool:HuntingLic,
    HuntingLicTime,

    //active charges
    chargeID,
    chargeTime[128],
    chargeDesc[144],
    chargeIssuer[25],

    //active warrants
    warrantID,
    warrantTime[128],
    warrantDesc[144],
    warrantIssuer[25],
    warrantSuspect[25],

    //broadcast
    broadcastTime[128],
    broadcastDesc[144],
    broadcastIssuer[25],

    //arrest record
    arrrecordID,
    arrrecordTime[128],
    arrrecordDets[144],
    arrrecordOfficer[25]
};
new MDC_Data[MAX_PLAYERS][e_mdcinfo],
    MDC_ListedData[MAX_PLAYERS][30][e_mdcinfo];

// Countdown
new Count = -1;
new countTimer;
new showCD[MAX_PLAYERS];
new CountText[20][20] =
{
	"~r~1",
	"~g~2",
	"~y~3",
	"~g~4",
	"~b~5",
    "~r~6",
	"~g~7",
	"~y~8",
	"~g~9",
	"~b~10",
    "~r~11",
	"~g~12",
	"~y~13",
	"~g~14",
	"~b~15",
    "~r~16",
	"~g~17",
	"~y~18",
	"~g~19",
	"~b~20"
};

//enum jail ooc
enum E_OOCJAIL
{
	bool:jailed,
	jailCell,
	jailAdmin[MAX_PLAYER_NAME + 1],
	jailTime,
	jailDur,
	jailReason[60],
	jailFine
};
new OJailData[MAX_PLAYERS][E_OOCJAIL];

enum e_deathcauses
{
    bool:Drown,
    bool:Burns,
    bool:Fallen,
    bool:Bruised,
    bool:Shoted
};
new DeathCause[MAX_PLAYERS][e_deathcauses];

//verify code
new tempverify[MAX_PLAYERS],
    temprecovery[MAX_PLAYERS],
    bool:TempFreeCar[MAX_PLAYERS];

//toggle
enum E_TOGGLEP
{
	bool:TogPM,
	bool:TogGOOC,
    bool:TogLogin,
    bool:TogLevel,
    bool:TogAdv,
    bool:TogAdmCmd,
    bool:TogBroadcast
};
new ToggleInfo[MAX_PLAYERS][E_TOGGLEP];

//documents
enum e_DOCUMENTS
{
    bool:BPJS,
    BPJSClass,
    BPJSDur,
    BPJSIssuer[24],
    BPJSIssuerRank[128],
    BPJSIssueDate[128],
    
    bool:SKS,
    SKSDur,
    SKSText[64],
    SKSIssuer[24],
    SKSIssuerRank[128],
    SKSIssueDate[128],

    bool:SKCK,
    SKCKDur,
    SKCKText[64],
    SKCKIssuer[24],
    SKCKIssuerRank[128],
    SKCKIssueDate[128],

    bool:SKWB,
    SKWBDur,
    SKWBText[64],
    SKWBIssuer[24],
    SKWBIssuerRank[128],
    SKWBIssueDate[128],

    bool:SP,
    SPDur,
    SPText[64],
    SPIssuer[24],
    SPIssuerRank[128],
    SPIssueDate[128]
};
new DocumentInfo[MAX_PLAYERS][e_DOCUMENTS];

enum e_advertsinfo
{
    bool:adActive,
    bool:adSubmitted,
    adNumb[13],
    adIssuer[MAX_PLAYER_NAME + 1],
    adDetail[144]
};
new AdvertisementEnum[MAX_ADVERTISEMENT][e_advertsinfo];

enum
{
    BUS_NONE,
    BUS_SFBLUE,
    BUS_LSYELLOW,
    BUS_LVRED
};

new Float: g_DrugsSellActorPos[][4] =
{
    {-2452.8271,-2757.8672,4.5914,285.2004},
    {-2437.9556,-2753.8264,4.8256,285.2004},
    {-2432.2813,-2764.3137,3.7308,205.9263},
    {-2411.6526,-2768.7378,3.2758,249.1668},
    {-2412.2551,-2782.3164,3.0000,168.9527},
    {-2419.5103,-2783.0605,3.0000,94.69200},
    {-2422.5635,-2791.7188,3.0000,159.5526},
    {-2417.1360,-2802.5530,3.0000,209.0598},
    {-2423.9070,-2817.6145,3.0000,147.3326},
    {-2437.1257,-2823.3088,3.0000,111.2989},
    {-2449.9646,-2829.9673,3.0000,110.4314},
    {-2452.1235,-2821.6782,3.0000,13.22460},
    {-2447.7139,-2811.4084,3.0000,328.2246},
    {-2443.5022,-2804.1765,3.0000,13.22460},
    {-2453.1047,-2798.1482,3.0000,58.22460},
    {-2448.7302,-2788.7739,3.1215,317.4508},
    {-2453.9712,-2782.7671,3.0000,66.17850},
    {-2460.1274,-2774.3113,3.2652,357.2444},
    {-2473.8003,-2792.0093,3.1523,139.7891},
    {-2481.9263,-2806.1121,3.0000,149.5025},
    {-2487.2122,-2822.4114,3.0000,178.0161},
    {-2486.6978,-2839.8564,3.0000,179.5828},
    {-2477.3420,-2847.6941,3.0000,274.2104},
    {-2471.1033,-2838.7332,3.0000,319.2104},
    {-2463.7676,-2838.2280,3.0000,274.2104},
    {-2457.5671,-2844.5278,3.0000,245.3354},
    {-2450.9849,-2835.4775,3.0000,4.210400},
    {-2450.5249,-2826.5208,3.0000,0.377800},
    {-2440.8792,-2826.3062,3.0000,269.5103},
    {-2435.2234,-2832.6797,3.0000,220.3165},
    {-2422.8162,-2846.4875,3.0000,220.3165},
    {-2432.2146,-2855.1824,3.0000,131.6423},
    {-2456.7712,-2854.4907,3.0000,89.65530}
};

new Float: g_ComServicePoint[21][3] =
{
	{-205.3741, 2669.2166, 63.9355}, //  1
    {-199.6462, 2658.3794, 63.5255}, //  2
    {-199.6247, 2677.2180, 63.5355}, //  3
    {-205.7946, 2684.4402, 63.9255}, //  4
    {-222.9973, 2685.6504, 63.9355}, //  5
    {-237.7459, 2685.5833, 63.9355}, //  6
    {-236.3216, 2690.1921, 63.5355}, //  7
    {-223.2358, 2695.1545, 62.6875}, //  8
    {-237.8670, 2671.0366, 63.9355}, //  9
    {-238.0647, 2655.0535, 63.9255}, //  10
    {-245.8234, 2667.5776, 63.5355}, //  11
    {-244.7945, 2658.2937, 63.5255}, //  12
    {-244.1869, 2677.4944, 63.5355}, //  13
    {-250.9051, 2669.6760, 62.6875}, //  14
    {-250.2792, 2649.2695, 62.6458}, //  15
    {-225.2315, 2652.7781, 63.9355}, //  16
    {-219.0587, 2646.9983, 63.5255}, //  17
    {-239.2541, 2646.7170, 63.5255}, //  18
    {-214.5097, 2660.4851, 64.2955}, //  19
    {-212.0511, 2679.2195, 64.2955}, //  20
    {-231.7729, 2679.6079, 64.2955} //  21
};

new Float: CommaSpawn[][4] = {
    {1762.5658,-1111.2732,28.7661,180.7146},
    {1762.6541,-1115.8354,28.7661,180.7146},
    {1762.6615,-1120.3250,28.7661,179.4613}
};

new Float: AirportLSSpawn[][4] = 
{
    {1749.9087,-2514.8140,13.5969,87.7341},
    {1749.7318,-2517.7883,13.5969,89.1559},
    {1746.4976,-2517.7249,13.5969,89.3009},
    {1746.6389,-2514.8525,13.5969,89.2776}
};

new Light_Truck[][2] = {
    {422, 41000}, //bobcat
    {543, 39000}, //sadler
    {478, 40000}, //walton
    {554, 47500}, //yosemite
    {600, 41000} //picador
};

new Heavy_Truck[][2] = {
    {414, 130000}, //mule
    {455, 200000}, //flatbed
    {456, 135000}, //yankee
    {499, 150000} //benson
};

new SUVWagon[][2] = {
    {579, 250000}, //huntley
    {400, 170000}, //landstalker
    {404, 120000}, //perenniel
    {489, 200000},  //Rancher
    {479, 135000}, //regina
    {458, 135000}, //solair
    {418, 120000}, //Moonbeam
    {482, 150000},  //Burrito
    {459, 160000}  //rc van
};

new Motorbike[][2] = {
    {462, 25000}, //Faggio = 1,190.00
    {581, 45000}, //BF-400 = 2,200.00
    {521, 90000}, //FCR-900 = 3,150.00
    {461, 60000}, //PCJ-600 - 2,500.00
    {468, 125000}, //sanchez 1,420.00
    {463, 150000}, //freeway = 1,560.00
    {586, 60000} //wayfarer = 1,380.00
};

new Lowriders[][2] = {
    {536, 85500}, //blade
    {575, 75000},  //broadway
    {534, 85000}, //remington
    {567, 90000}, //savanna
    {412, 75000}, //voodo
    {576, 71000} //tornado
};

new TwoDoor_Compact[][2] = {
    {549, 80000}, //tampa
    {491, 75000}, //virgo
    {480, 250000}, //comet
    {442, 82000}, //romero
    {439, 81000}, //stallion
    {419, 81000}, //esperanto
    {545, 105000}, //hustler
    {602, 200000}, //alpha
    {496, 84000}, //blista compact
    {401, 75000}, //bravura
    {527, 81000}, //cadrona
    {533, 81000}, //feltzer
    {526, 83900}, //fortune
    {410, 81000},  //manana
    {436, 80500}, //previon
    {542, 80000}, //clover
    {475, 85000}, //sabre
    {555, 83000}, //windsor
    {518, 91000}, //buccaner
    {589, 150000},  //club
    {474, 250000}, //hermes
    {517, 82000}, //majestic
    {500, 200000} //mesa
};

new FourDoor_Luxury[][2] = {
    {445, 105000}, //admiral
    {507, 105000}, //elegant
    {492, 105000}, //greenwood
    {585, 105000}, //emperor
    {546, 105000}, //intruder
    {551, 105000}, //merit
    {516, 105000}, //nebula
    {426, 200000}, //premier
    {547, 105000}, //primo
    {405, 105000}, //sentinel
    {580, 105000}, //stafford
    {550, 105000}, //sunrise
    {566, 105000}, //tahoma
    {540, 105000}, //vincent
    {421, 105000}, //washington
    {529, 105000}, //willard
    {561, 250000}, //stratum
    {560, 250000}, //sultan
    {467, 105000}, //oceanic
    {466, 105000} //glendale
};

enum e_vehspec
{
    Model,
    BaggageWeight
};

new VehicleSpec[][e_vehspec] = {
    {400, 25},
    {401, 20},
    {402, 20},
    {404, 25},
    {405, 20},
    {407, 10},
    {409, 20},
    {410, 15},
    {411, 20},
    {412, 15},
    {413, 35},
    {414, 55},
    {415, 20},
    {416, 15},
    {417, 25},
    {418, 15},
    {419, 15},
    {420, 15},
    {421, 15},
    {422, 40},
    {423, 25},
    {424, 25},
    {426, 15},
    {427, 15},
    {428, 15},
    {429, 25},
    {430, 10},
    {434, 25},
    {435, 120},
    {436, 15},
    {438, 15},
    {439, 10},
    {440, 40},
    {442, 10},
    {445, 15},
    {446, 10},
    {450, 120},
    {451, 25},
    {452, 10},
    {453, 15},
    {454, 10},
    {455, 80},
    {456, 80},
    {457, 10},
    {458, 15},
    {459, 30},
    {466, 15},
    {467, 15},
    {470, 25},
    {472, 10},
    {473, 10},
    {474, 10},
    {475, 10},
    {477, 25},
    {478, 35},
    {479, 20},
    {480, 10},
    {482, 30},
    {483, 50},
    {484, 10},
    {485, 15},
    {487, 25},
    {488, 15},
    {489, 25},
    {490, 25},
    {491, 15},
    {492, 15},
    {493, 10},
    {494, 25},
    {495, 55},
    {496, 15},
    {497, 10},
    {498, 45},
    {499, 70},
    {500, 15},
    {502, 25},
    {503, 25},
    {504, 25},
    {505, 25},
    {506, 25},
    {507, 15},
    {508, 100},
    {511, 10},
    {512, 10},
    {513, 10},
    {516, 15},
    {517, 15},
    {518, 15},
    {519, 10},
    {525, 15},
    {526, 10},
    {527, 10},
    {528, 10},
    {529, 10},
    {533, 10},
    {534, 10},
    {535, 25},
    {536, 10},
    {539, 10},
    {540, 10},
    {541, 25},
    {542, 10},
    {543, 35},
    {544, 10},
    {545, 10},
    {546, 10},
    {547, 10},
    {548, 30},
    {549, 10},
    {550, 15},
    {551, 15},
    {552, 10},
    {554, 45},
    {555, 15},
    {558, 25},
    {559, 25},
    {560, 15},
    {561, 15},
    {562, 25},
    {563, 10},
    {565, 25},
    {566, 15},
    {567, 15},
    {568, 15},
    {571, 10},
    {572, 10},
    {573, 100},
    {575, 10},
    {576, 15},
    {578, 80},
    {579, 25},
    {580, 25},
    {582, 25},
    {583, 10},
    {585, 10},
    {587, 25},
    {588, 25},
    {589, 10},
    {591, 120},
    {595, 10},
    {596, 10},
    {597, 10},
    {598, 10},
    {599, 10},
    {600, 30},
    {601, 10},
    {602, 15},
    {603, 25},
    {604, 15},
    {605, 35},
    {609, 45}
};

new Float:HintPickup[][3] =
{
    {1689.6466,-2246.9500,13.5396},
    {829.7463,-1360.9578,-0.5015}
};

enum e_factionbrankas
{
    factionBrankasID,
    factionBrankasFID,
    factionBrankasTemp[32],
    factionBrankasModel,
    factionBrankasQuant,

    //not saved
    bool:factionBrankasExists
};
new FactionBrankas[MAX_FACTIONS_ITEMS][e_factionbrankas];
new index_pagination[MAX_PLAYERS];
new MDC_ChargesHistoryPagination[MAX_PLAYERS];
new ListedMember[MAX_PLAYERS][MAX_MEMBER_ROWS]; // var global

new RusunExpired,
    PolisiMoneyVault,
    EMSMoneyVault,
    PutrideliMoneyVault,
    PemerMoneyVault,
    BennysMoneyVault,
    UberMoneyVault,
    DinarbucksMoneyVault,
    Fox11MoneyVault,
    AutomaxMoneyVault,
    HandoverMoneyVault,
    SriMersingMoneyVault,
    TexasChickenMoneyVault;
    
//--------- Pengecekan Jumlah On Duty Faction ------------//
new Iterator:LSPDDuty<MAX_PLAYERS>;
new Iterator:LSFDDuty<MAX_PLAYERS>;
new Iterator:PutrideliDuty<MAX_PLAYERS>;
new Iterator:PemerDuty<MAX_PLAYERS>;
new Iterator:BennysDuty<MAX_PLAYERS>;
new Iterator:UberDuty<MAX_PLAYERS>;
new Iterator:DinarbucksDuty<MAX_PLAYERS>;
new Iterator:Fox11Duty<MAX_PLAYERS>;
new Iterator:AutomaxDuty<MAX_PLAYERS>;
new Iterator:HandoverDuty<MAX_PLAYERS>;
new Iterator:SriMersingDuty<MAX_PLAYERS>;
new Iterator:TexasChickenDuty<MAX_PLAYERS>;

//TIMERS
new pLoginTimer[MAX_PLAYERS] = {-1, ...};
new pLoginWarningTimer[MAX_PLAYERS] = {-1, ...};
new pLoginTransitionTimer[MAX_PLAYERS] = {-1, ...};
new pCarstealLabelTimer[MAX_PLAYERS] = {-1, ...};
new pUnfreezeTimer[MAX_PLAYERS] = {-1, ...};

new bool:pAllowSpawn[MAX_PLAYERS];
new bool:pLoginSpawnLoaded[MAX_PLAYERS];

new pPorterCarrying[MAX_PLAYERS];
new pPorterDropIDX[MAX_PLAYERS];

new bool:pCookingHouseTimer[MAX_PLAYERS];
new bool:pHCraftBandageTimer[MAX_PLAYERS];

new bool:pFactionCraftingTimer[MAX_PLAYERS];
new bool:pRepairingToolkitTimer[MAX_PLAYERS];
new bool:pMedisLokalTimer[MAX_PLAYERS];
new bool:pCraftingWeaponTimer[MAX_PLAYERS];
new bool:pCraftingDrugTimer[MAX_PLAYERS];
new bool:pTakingKanabisTimer[MAX_PLAYERS];
new bool:pProcessKanabisTimer[MAX_PLAYERS];
new bool:pSellingTurtleTimer[MAX_PLAYERS];
new bool:pSellingSharkTimer[MAX_PLAYERS];
new bool:pConsfMeatTimer[MAX_PLAYERS];
new bool:pCarstealPartTimer[MAX_PLAYERS];
new bool:pSellingMarijuanaTimer[MAX_PLAYERS];
new bool:pMoneyLaundryTimer[MAX_PLAYERS];
new bool:pMechRepairEngineTimer[MAX_PLAYERS];
new bool:pMechRepairBodyTimer[MAX_PLAYERS];
new bool:pMechRepairTiresTimer[MAX_PLAYERS];
new bool:pMechUpgradeEngine[MAX_PLAYERS];
new bool:pMechUpgradeBody[MAX_PLAYERS];
new bool:pRefuelJerrycanTimer[MAX_PLAYERS];
new bool:pRefuelingTimer[MAX_PLAYERS];

new bool:pOpenBackpackTimer[MAX_PLAYERS];

new bool:pOpenShotDeluxeTimer[MAX_PLAYERS];
new bool:pOpenBuckshotSpecialTimer[MAX_PLAYERS];
new bool:pOpenTelaGoodieTimer[MAX_PLAYERS];
new bool:pOpenAndalasPrideTimer[MAX_PLAYERS];
new bool:pOpenMinangComboTimer[MAX_PLAYERS];
new bool:pOpenMalayaShineTimer[MAX_PLAYERS];
new bool:pOpenFreshSolarTimer[MAX_PLAYERS];
new bool:pOpenSoftexFlashTimer[MAX_PLAYERS];
new bool:pOpenPurpleSweetTimer[MAX_PLAYERS];

new bool:pCookingTimer[MAX_PLAYERS];
new bool:pDNRCookingTimer[MAX_PLAYERS];
new bool:pSriMersingCookingTimer[MAX_PLAYERS];
new bool:pTexasCookingTimer[MAX_PLAYERS];
new bool:pEatingBarTimer[MAX_PLAYERS];
new bool:pBreakingVehDoorTimer[MAX_PLAYERS];
new bool:pImpoundingInsuTimer[MAX_PLAYERS];
new bool:pImpoundingSamsatTimer[MAX_PLAYERS];
new bool:pUsingPerbanTimer[MAX_PLAYERS];
new bool:pUsingKevlarTimer[MAX_PLAYERS];
new bool:pSmokingWeedTimer[MAX_PLAYERS];
new bool:pUsingMethTimer[MAX_PLAYERS];
new bool:pUsingPilStressTimer[MAX_PLAYERS];
new bool:pTakingTrashTimer[MAX_PLAYERS];
new bool:ForkliftLoadTimer[MAX_PLAYERS];
new bool:ForkliftUnloadTimer[MAX_PLAYERS];
new bool:pDeliveringPizzaTimer[MAX_PLAYERS];
new bool:RevivingPlayerTimer[MAX_PLAYERS];
new bool:pRebootingPhoneTimer[MAX_PLAYERS];

//Job
new bool:pTakingPlantTimer[MAX_PLAYERS];
new bool:pProcessChiliTimer[MAX_PLAYERS];
new bool:pProcessRiceTimer[MAX_PLAYERS];
new bool:pPorcessSugarTimer[MAX_PLAYERS];
new bool:pTakingStoneTimer[MAX_PLAYERS];
new bool:pWashingStoneTimer[MAX_PLAYERS];
new bool:pSmeltingStoneTimer[MAX_PLAYERS];
new bool:pTakingChickTimer[MAX_PLAYERS];
new bool:pCutingChickTimer[MAX_PLAYERS];
new bool:pPackingChickTimer[MAX_PLAYERS];
new bool:pTakingOilTimer[MAX_PLAYERS];
new bool:pRefiningOilTimer[MAX_PLAYERS];
new bool:pMixingOilTimer[MAX_PLAYERS];
new bool:pAngkotTimer[MAX_PLAYERS];
new bool:pLoadCargoTimer[MAX_PLAYERS];
new bool:pTakingFishTimer[MAX_PLAYERS];
new bool:pMixBetonTimer[MAX_PLAYERS];
new bool:pSlumpTimer[MAX_PLAYERS];
new bool:pMixerDumpTimer[MAX_PLAYERS];
new bool:pTakeWoodTimer[MAX_PLAYERS];
new bool:pCutWoodTimer[MAX_PLAYERS];
new bool:pGetBoardTimer[MAX_PLAYERS];
new bool:SailDockTimer[MAX_PLAYERS];
new bool:pTakingSusuTimer[MAX_PLAYERS];
new bool:pProcessSusuTimer[MAX_PLAYERS];
new bool:pTakingWoolTimer[MAX_PLAYERS];
new bool:pMakingFabricTimer[MAX_PLAYERS];
new bool:pClothingTimer[MAX_PLAYERS];

new bool:p_BankRTakeMoneyTimer[MAX_PLAYERS];
new bool:pMakeEfedrinTimer[MAX_PLAYERS];
new bool:pMakeStimulanTimer[MAX_PLAYERS];
new bool:pMakeMethMentahTimer[MAX_PLAYERS];
new bool:pMakeMethTimer[MAX_PLAYERS];
new bool:pUsingHeroinTimer[MAX_PLAYERS];
new bool:pDrinkingWhiskyTimer[MAX_PLAYERS];
new bool:pDrinkingSojuTimer[MAX_PLAYERS];

new bool:pTaggingTimer[MAX_PLAYERS];

new bool:pKompensasiTimer[MAX_PLAYERS];

//---------------------------------------/
new Float:__g_FarmWellPos[][3] =
{
    {-312.3332,-973.5988,50.3645},
    {-309.6795,-1303.9504,9.9697},
    {-242.6911,-1447.5558,4.7002},
    {-370.3098,-1552.0508,21.2334},
    {-503.2663,-1432.4285,13.4369},
    {-540.5636,-1283.7151,23.1708}
};

new Float:__g_TreePos[][3] =
{
    {-1980.4341,-2373.6079,30.6318},
    {-1991.0830,-2365.1870,30.6318},
    {-1979.7312,-2357.9182,30.6318},
    {-1945.1931,-2390.0569,30.5878},
    {-1950.1744,-2407.7231,30.6250},
    {-1937.0966,-2414.9226,30.6250},
    {-1933.8219,-2404.8052,30.6250}
};

new Float:__g_CutLog[][3] =
{
    {-1452.8270,-1526.4911,101.7710},
    {-1463.4725,-1526.4904,101.7710},
    {-1463.5078,-1521.6418,101.7710},
    {-1453.0154,-1521.6418,101.7710}
};

new Float:__g_PackLog[][3] =
{
    {-1443.1813,-1585.8983,101.7710},
    {-1450.3267,-1585.6499,101.7610}
};

new Float:__g_MakeFabric[][3] =
{
    {2533.0374,2038.1162,11.2394},
    {2533.6921,2018.7837,11.2374}
};

new Float:__g_MakeClothes[][3] =
{
    {2536.2612,2025.0282,11.2394},
    {2536.0298,2032.4335,11.2394}
};

new Float:__g_MilkProcessPos[][3] =
{
    {-2484.8118,-165.5218,25.6172},
    {-2488.1567,-165.5220,25.6172},
    {-2489.2715,-161.4807,25.6172},
    {-2485.3647,-161.4803,25.6172}
};

new Float:PorterDropCoord[][3] =
{
    {2323.3389,596.2735,7.9351},
    {2336.8845,554.0403,7.9351},
    {2350.8552,554.1630,7.9351},
    {2269.8518,553.9836,7.9351},
    {2252.8513,553.9343,7.9351},
    {2250.1328,579.0118,7.9351},
    {2265.6797,578.8082,8.0336}
};

new Float:__g_OilTakePos[][3] =
{
    {2738.7480,-6866.6616,25.2101},
    {2748.1255,-6865.6533,25.2101},
    {2758.3403,-6870.8252,25.2101},
    {2758.3403,-6862.6045,25.2101},
    {2706.2212,-6866.6494,25.2101},
    {2697.0100,-6867.6216,25.2101},
    {2686.5686,-6862.6006,25.2101},
    {2686.5698,-6870.8882,25.2101}
};

new Float:__g_TutorialPos[][3] =
{
    {1251.0101,-2025.3743,59.6768},
    {1661.6832,-2251.6846,13.3544},
    {2818.7622,-1087.9659,30.7355},
    {652.7518,-1852.6155,5.4609},
    {1883.9709,-1884.2982,13.4684},
    {2094.7273,-1368.9843,24.0243},
    {397.1428,-1345.1005,14.6264},
    {-84.2098,-1172.3118,2.2233},
    {542.0338,-1476.0135,14.5485},
    {946.2979,2420.0854,10.8549},
    {-2258.6907,2371.7905,5.0507},
    {1307.5687,733.5302,10.9375},
    {367.7464,-2040.0721,7.6719},
    {2486.3435,-1949.6277,13.4588},
    {2081.6267,-2033.3889,13.5469},
    {2223.0425,-1159.7186,25.7331},
    {2058.2466,-1879.0549,13.5893},
    {-1991.1475,-938.5275,32.0312},
    {1196.2809,-1336.6830,12.9700},
    {639.6709,-1356.1313,12.9519},
    {138.1396,1966.6945,19.5023}
};
new STREAMER_TAG_RACE_CP:pTutorialRCP[MAX_PLAYERS];
new pTutorialStep[MAX_PLAYERS];

//---------------------------------------/
enum ___g_GPSDetails
{
    Float:Pos[3],
    JobName[64],
    Name[64]
};

new _g_GPS_Job[][___g_GPSDetails] =
{
    {{2117.4211,-1182.7363,24.0903},""MAGENTA"Potong Rumput",""MAGENTA"Kerja Sampingan (Sidejob)"},
    {{608.9968,-1510.5494,14.6442},""MAGENTA"Pembersih Jalanan",""MAGENTA"Kerja Sampingan (Sidejob)"},
    {{-1732.6582,-65.4632,3.5547},""MAGENTA"Forklift",""MAGENTA"Kerja Sampingan (Sidejob)"},
    {{1067.1381,1333.2260,10.8203},""MAGENTA"Tukang Sampah",""MAGENTA"Kerja Sampingan (Sidejob)"},
    {{2119.4346,-1787.9850,13.5547},""MAGENTA"Pengantar Pizza",""MAGENTA"Kerja Sampingan (Sidejob)"},

    {{-381.9745,-1438.8531,25.7266},"Petani","Ladang Pertanian"},
    {{-347.8932,-1046.3129,59.8125},"Petani","Ladang Pertanian Buah"},

    {{2380.0393,-2265.4482,13.5469},"Penambang #1","Locker"},
    {{622.1395,859.2790,-42.9534},"Penambang #2","Pertambangan"},
    {{-2.3599,1361.3862,9.1719},"Penambang #3","Pencucian"},
    {{2189.1790,-2265.2002,13.0212},"Penambang #4","Peleburan"},
    {{2686.7214,-2339.6372,13.1531},"Penambang #5","Penjualan"},

    {{2186.0496,-2652.3823,13.0664},"Tukang Ayam #1","Locker"},
    {{-2096.1965,-2447.2014,29.9888},"Tukang Ayam #2 - #4","Rumah Potong"},
    {{2396.7388,-1501.0944,23.3545},"Tukang Ayam #5","Penjualan"},

    {{2445.5918,-2619.7668,17.9107},"Tukang Minyak #1","Locker"},
    {{2685.6641,-6822.6533,-0.2701},"Tukang Minyak #2 - #3","Kilang Minyak"},
    {{2489.7302,-2682.2266,13.6643},"Tukang Minyak #4","Pencampuran"},
    {{2527.0134,-2134.8589,13.5469},"Tukang Minyak #5","Penjualan"},

    {{1691.8894,-1458.7782,13.5469},"Supir Angkot","Mulai Kerja"},
    {{-1699.5300,37.1927,3.5547},"Supir Kargo","Mulai Kerja"},
    {{640.5365,1237.4777,11.6895},"Supir Mixer","Mulai Kerja"},

    {{2530.4011,-2434.6401,17.8828},"Nelayan #1","Locker"},
    {{2905.7522,-2106.1326,2.3035},"Nelayan #2","Dermaga Kapal"},
    {{5164.2573,-2347.5452,-0.9292},"Nelayan #3","Area Jala Ikan"},
    {{-2057.6643,-2464.8784,31.1797},"Nelayan #4","Penjualan"},
    
    {{2386.5820,563.6393,10.3691},"Porter #1","Locker"},
    {{2388.9077,586.0323,7.9351},"Porter #2","Mulai Kerja"},

    {{-491.5486,-193.8380,78.3525},"Tukang Kayu #1","Locker"},
    {{-1937.9092,-2431.1553,30.1862},"Tukang Kayu #2","Pengambilan Kayu"},
    {{-1443.3311,-1521.7987,101.7578},"Tukang Kayu #3","Pemotongan"},
    {{-1446.7828,-1592.6364,101.7578},"Tukang Kayu #4","Pembuatan Papan"},
    {{-1688.4254,-17.4925,3.5547},"Tukang Kayu #5","Penjualan"},

    {{1627.7319,639.1720,10.8203},"Pelaut","Mulai Kerja"},

    {{-1483.9875,2038.6873,47.0168},"Peternak #1","Peternakan"},
    {{-2482.8499,-176.8699,25.6172},"Peternak #2","Pengolahan Susu"},
    {{-19.2178,1175.9481,19.5634},"Peternak #3","Penjualan"},

    {{2556.8508,2023.0450,10.8256},"Penjahit #1","Locker"},
    {{1938.5723,165.7293,37.2813},"Penjahit #2","Pengambilan Wool"},
    {{2533.6921,2018.7837,11.2374},"Penjahit #3","Kantor Penjahit"},
    {{-2491.6301,2363.1802,10.2727},"Penjahit #4","Penjualan"}
};

new _g_GPS_Public[][___g_GPSDetails] =
{
    {{1611.5487,-1280.4707,17.4574},""MAGENTA"Dinas Tenaga Kerja (DISNAKER Pahlawan Roleplay)"},
    {{1280.2830,-1335.5088,13.3711},"(( Roleplay School ))"},
    {{-30.2743,-461.8211,1.9641},"Warung Lokal Pecel Lele"},
    {{1248.6881,-2055.4368,59.3761},""MAGENTA"Balai Kota Pemerintahan"},
    {{1468.6134,-1157.6217,23.7928},"Bank Pacific Standard"},
    {{556.216,-1477.16,14.6929},"Diamond Royal Casino"},
    {{2180.6221,-1985.8651,13.5506},""MAGENTA"BOTOT (Penjualan Botol & Plastik)"},
    {{640.0092,-1360.2280,13.4218},"Pewarta Pahlawan Roleplay"},
    {{1730.9509,-1158.1989,23.6400},""MAGENTA"Rumah Sakit Kota Pahlawan Roleplay"},
    {{-301.3481,1318.3994,54.1729},"Sri Mersing Resto"},
    {{651.5056,-1828.7012,5.6535},"Putri Deli Beach Club"},
    {{1035.6764,-1328.6409,12.9690},"Loving Donuts"},
    {{2687.5742,718.6926,10.6719},"Texas Chicken"},
    {{-2431.2061,1029.5918,50.3906},""YELLOW"Asuransi Kota Pahlawan Roleplay"},
    {{397.4295,-1344.3303,14.6274},"Showroom/Cardealer"},
    {{1541.8152,-1296.8776,16.0313},"Gedung Pernikahan"},
    {{316.1955,-1841.1615,7.0050},"Pos Balon Udara Pahlawan Roleplay"},
    {{910.0120,2421.2253,10.6719},""MAGENTA"SAMSAT Kota Pahlawan Roleplay"},
    {{1138.9628,1371.0724,10.6719},"Akdemi Kepolisian Pahlawan Roleplay"},
    {{2423.7078,-1232.7535,24.7044},"Bahamas LS"},
    {{384.2046,-1900.0710,7.8359},""MAGENTA"Karnaval (( Tempat Menurunkan Stress ))"},
    {{2222.1545,-1136.6956,25.6250},""ORANGE"Atok Alang (Rusun)"},
    {{-2516.3613,1221.6318,37.4283},""ORANGE"Mama Yukero (Rusun)"},
    {{2021.8124,2148.6938,10.8203},""ORANGE"Buntil (Rusun)"},
    {{2083.8362,-2034.3964,13.5469},""PURPLE"Gudang Amplas"},
    {{1708.4121,1068.6736,10.8203},""PURPLE"Gudang Panglima Denai"},
    {{-141.9428,1128.2909,19.7500},""PURPLE"Gudang I Wayan Dipta"},
    {{-2265.3677,2393.0896,4.9684},""PURPLE"Gudang A.H Nasution"},
    {{-1858.0305,-204.8161,18.3896},""PURPLE"Gudang I Gusti Ngurah Rai"},
    {{-279.3699,-2195.0791,28.6847},""PURPLE"Gudang Sisingamangaraja XII"},
    {{-168.2616,1032.5665,19.7344},"Pembelian Komponen"},
    {{185.3883,-248.5895,1.4297},"Handover Motorworks (Bengkel)"},
    {{-1827.0193,159.7523,15.1172},"Automax Workshop (Bengkel)"},
    {{1347.3947,745.5940,10.6719},"Bennys Workshop (Bengkel)"},
    {{-1984.0829,-929.7976,32.0312},"Kantor Uber"},
    {{2479.1294,-1963.1271,16.7578},""MAGENTA"Mega Mall #LS"},
    {{-1881.4132,823.1917,35.1767},""MAGENTA"Mega Mall #SF"},
    {{795.0921,1687.0704,5.2813},""MAGENTA"Pawn Shop (Penukaran Material)"},
    {{2079.0525,-1876.5023,13.3359},"Modification Shop (Modshop)"},
    {{1014.4050,-1850.2255,13.1478},"Pentas Konser Polygon"},
    {{-2262.2756,-156.0122,35.1719},"Cobra GYM"}
};

new _g_originName[][] = 
{
    "Indonesia",
    "United States of America",
    "United Kingdom",
    "Afghanistan",
    "Albania",
    "Algeria",
    "Andorra",
    "Angola",
    "Antigua and Barbuda",
    "Argentina",
    "Armenia",
    "Australia",
    "Austria",
    "Azerbaijan",
    "Bahamas",
    "Bahrain",
    "Bangladesh",
    "Barbados",
    "Belarus",
    "Belgium",
    "Belize",
    "Benin",
    "Bhutan",
    "Bolivia",
    "Bosnia and Herzegovina",
    "Botswana",
    "Brazil",
    "Brunei Darussalam",
    "Bulgaria",
    "Burkina Faso",
    "Burundi",
    "Cabo Verde",
    "Cambodia",
    "Cameroon",
    "Canada",
    "Central African",
    "Chad",
    "Chile",
    "China",
    "Colombia",
    "Comoros",
    "Congo",
    "Congo",
    "Costa Rica",
    "Cote de Ivoire",
    "Croatia",
    "Cuba",
    "Cyprus",
    "Czech",
    "Denmark",
    "Djibouti",
    "Dominica",
    "Dominican",
    "Ecuador",
    "Egypt",
    "El Salvador",
    "Equatorial Guinea",
    "Eritrea",
    "Estonia",
    "Eswatini",
    "Ethiopia",
    "Fiji",
    "Finland",
    "France",
    "Gabon",
    "Gambia",
    "Georgia",
    "Germany",
    "Ghana",
    "Greece",
    "Grenada",
    "Guatemala",
    "Guinea",
    "Guinea Bissau",
    "Guyana",
    "Haiti",
    "Holy See (Vatican)",
    "Honduras",
    "Hungary",
    "Iceland",
    "India",
    "Iran",
    "Iraq",
    "Ireland",
    "Israel",
    "Italy",
    "Jamaica",
    "Japan",
    "Jordan",
    "Kazakhstan",
    "Kenya",
    "Kiribati",
    "North Korea",
    "South Korea",
    "Kuwait",
    "Kyrgyzstan",
    "Laos",
    "Latvia",
    "Lebanon",
    "Lesotho",
    "Liberia",
    "Libya",
    "Liechtenstein",
    "Lithuania",
    "Luxembourg",
    "Madagascar",
    "Malawi",
    "Malaysia",
    "Maldives",
    "Mali",
    "Malta",
    "Marshall Islands",
    "Mauritania",
    "Mauritius",
    "Mexico",
    "Micronesia",
    "Moldova",
    "Monaco",
    "Mongolia",
    "Montenegro",
    "Morocco",
    "Mozambique",
    "Myanmar",
    "Namibia",
    "Nauru",
    "Nepal",
    "Netherlands",
    "New Zealand",
    "Nicaragua",
    "Niger",
    "Nigeria",
    "North Macedonia",
    "Norway",
    "Oman",
    "Pakistan",
    "Palau",
    "Palestine",
    "Panama",
    "Papua New Guinea",
    "Paraguay",
    "Peru",
    "Philippines",
    "Poland",
    "Portugal",
    "Qatar",
    "Romania",
    "Russian Federation",
    "Rwanda",
    "Saint Kitts and Nevis",
    "Saint Lucia",
    "Saint Vincent and the Grenadines",
    "Samoa",
    "San Marino",
    "Sao Tome and Principe",
    "Saudi Arabia",
    "Senegal",
    "Serbia",
    "Seychelles",
    "Sierra Leone",
    "Singapore",
    "Slovakia",
    "Slovenia",
    "Solomon Islands",
    "Somalia",
    "South Africa",
    "South Sudan",
    "Spain",
    "Sri Lanka",
    "Sudan",
    "Suriname",
    "Sweden",
    "Switzerland",
    "Syrian Arab Republic",
    "Tajikistan",
    "Tanzania",
    "Thailand",
    "Timor-Leste",
    "Togo",
    "Tonga",
    "Trinidad and Tobago",
    "Tunisia",
    "Turkey",
    "Turkmenistan",
    "Tuvalu",
    "Uganda",
    "Ukraine",
    "United Arab Emirates",
    "Uruguay",
    "Uzbekistan",
    "Vanuatu",
    "Venezuela",
    "Vietnam",
    "Yemen",
    "Zambia",
    "Zimbabwe"
};

/*
//-----------------[RP Quiz] -----------/
enum ___g_RPQuizDetails
{
    RPQuiz_Question[1528],
    RPQuiz_Answer[64]
};

new g_RPQuizData[][___g_RPQuizDetails] =
{
    {""YELLOW"Q: "WHITE"Ketika anda sedang dalam perjalanan, anda melihat sekumpulan petugas kepolisian yang sedang menangani suatu kasus.\n\
	Namun anda menerobos paksa untuk masuk ke dalam area yang tengah diamankan seolah-olah tidak terjadi apa-apa.\n\
	Perilaku ini termasuk pelanggaran pada?\n\n\
	A. Powergaming\n\
	B. Non-RP Driving\n\
	C. Metagaming\n\
	D. Non-RP Behavior\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"/me mengeluarkan AK-47 dari dalam kantung celana dengan bantuan tangan kanan adalah pelanggaran server?\n\n\
    A. Powergaming\n\
    B. Mixing\n\
    C. Diperbolehkan karena roleplay-nya sudah sangat detail\n\
    D. Metagaming\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Di bawah ini contoh roleplay yang benar, kecuali?\n\n\
    A. /me mengeluarkan ember berisi air dari dalam tas lalu menyirami api di depannya\n\
    B. /me melemparkan tinjuan dengan tangan kirinya ke arah muka Gilberd, merubah posisinya untuk\n\
    bertahan kemudian dengan cepat\n\
    C. /me mengeluarkan handphone dari kantung celananya, menggunakan jempol jari kiri untuk membuka aplikasi Yellowpage\n\
    D. /me mengangkat jari tengah tangan kanannya ke arah Kepala Polisi\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Jumlah maksimal uang yang boleh dirampok dan boleh untuk discam/ditipu adalah?\n\n\
    A. Rampok $500 dan scam $5,000\n\
    B. Rampok $2,500 dan scam $5,000\n\
    C. Rampok $3,000 dan scam $10,000\n\
    D. Rampok $2,500 dan scam $1,000\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Meroleplaykan tidak membawa Kartu Identitas/KTP merupakan pelanggaran dari\n\n\
    A. Metagaming\n\
    B. Force RP\n\
    C. Refuse RP\n\
    D. No Identity Roleplay\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Jika anda sedang kebingungan di dalam server, lalu CMD apa yang tepat untuk bertanya kepada admin?\n\n\
    A. /report\n\
    B. /fixme\n\
    C. /ask\n\
    D. /help\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Jika karakter anda mengalami masalah dengan suatu hal, apa yang anda lakukan untuk melaporkan pada admin?\n\n\
    A. /report\n\
    B. /fixme\n\
    C. /ask\n\
    D. /help\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Kondisi dimana karakter dikatakan telah meninggal dunia secara permanen dan tak dapat dimainkan lagi adalah?\n\n\
    A. Player Killed\n\
    B. Revenge Killing\n\
    C. Character Killed\n\
    D. Permanent Killed\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Memanfaatkan ilmu pengetahuan mengenai hal IC yang didapatkan melalui wadah OOC disebut apa?\n\n\
    A. Olympic Swimming\n\
    B. Supergaming\n\
    C. Powergaming\n\
    D. Metagaming\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Anda sedang berjalan santai di Restoran, tiba-tiba ada seseorang yang anda tidak kenal menghampiri karaktermu\n\
    dan memanggilmu dengan menyebut nickname yang ada di atas kepala karaktermu. Pelanggaran apa yang telah terjadi?\n\n\
    A. Revenge Killing\n\
    B. Metagaming\n\
    C. Richplay\n\
    D. Powergaming\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Pilihlah salah satu kondisi mana yang mengharuskan anda untuk tidak keluar dari server/game!\n\n\
    A. Saat memesan Burger di Restoran\n\
    B. Saat sedang nongkrong dengan teman\n\
    C. Ketika sedang ditodong senjata oleh perampok\n\
    D. Ketika sedang membuat Driving License\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Anda melihat sekumpulan petugas polisi yang terlihat begitu sibuk dalam satu kasus darurat, kemudian anda mendekat\n\
    seolah-olah tidak terjadi apa-apa dan anda bertanya dimana lokasi untuk membuat Driving License.\n\
    Perilaku ini termasuk pelanggaran dalam?\n\n\
    A. Powergaming\n\
	B. Non-RP Driving\n\
	C. Metagaming\n\
	D. Non-RP Behavior\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Anda ditodong dengan senjata oleh perampok maka roleplay manakah yang benar, kecuali?\n\n\
    A. Mengikuti setiap perintah perampok agar tidak disakiti\n\
	B. Membuka handphone lalu menghubungi 911 untuk memanggil Polisi\n\
	C. Me-roleplay-kan rasa takut akan perampokan yang sedang terjadi\n\
	D. Rela menyerahkan uang kepada perampok\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Anda sebagai penjual memiliki janji temu untuk melakukan transaksi senjata api dengan seseorang\n\
    kemudian anda berhasil menetapkan harga dan disetujui oleh orang tersebut.\n\
    Namun ketika transaksi selesai anda memberikan senjata dengan peluru yang hanya tersisa satu butir.\n\
    Berapa jumlah maksimal uang yang anda minta ketika bertransaksi?\n\n\
    A. $500 karena itu adalah batas begal/rampok\n\
	B. $3,000 karena itu adalah batas begal/rampok\n\
	C. $3,000 karena itu adalah batas penipuan/scam\n\
	D. $10,000 karena itu adalah batas penipuan/scam\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Anda diberhentikan oleh seorang petugas kepolisian karena melakukan suatu kesalahan\n\
    maka apa yang akan anda lakukan, kecuali?\n\n\
    A. Membiarkan petugas melaksanakan tugasnya\n\
	B. Tidak mematuhinya dan berusaha kabur sejauh mungkin\n\
	C. Keluar dari game/server agar tidak dihukum\n\
	D. Bertanya kepada petugas mengapa anda diberhentikan\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Me-roleplay-kan rasa takut atau RP Fear adalah representatif dari rasa takut manusia di dunia nyata, kecuali?\n\n\
    A. Ketika sedang ditodong pistol oleh perampok anda mengeluarkan senjata tumpul\n\
    dan memukulinya dengan roleplay (/me) yang detail\n\
	B. Menjerit histeris di dalam bank sesaat terjadi perampokan bank\n\
	C. Inisiatif mengeluarkan uang kepada perampok\n\
	D. Menangis sambil memohon untuk tidak disakiti\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Anda roleplay sebagai seorang gangster dan melihat seorang polisi sedang melintas patroli\n\
    kemudian anda menghina dan melontarkan kata-kata kasar kepada petugas tersebut dengan tujuan roleplay ingin pursuit/dikejar.\n\
    Pelanggaran apa yang telah berlaku dalam kondisi ini?\n\n\
    A. Tidak ada karena roleplay nya jelas\n\
	B. Tidak ada karena itu contoh Nice RP (RP-nya bagus banget)\n\
	C. Tidak ada karena hinaan dan caciannya melalui IC\n\
	D. Cop Baiting/Provoke LEO\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Ketika anda sedang roleplay tiba-tiba di hadapan anda melintas seorang admin yang sedang on duty\n\
    maka apa yang akan anda lakukan?\n\n\
    A. Menyapa admin tersebut karena anda menunjukkan rasa hormat dan ramah\n\
	B. Meminta uang kepada admin tersebut\n\
	C. Mengabaikannya dan menganggapnya seolah-olah tidak ada kemudian melanjutkan roleplay\n\
	D. Menghampirinya dan mengelilinginya bersama dengan teman-teman anda\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Ketika terjadi kejar-mengejar (pursuit) antara anda dengan polisi, anda memutuskan\n\
    untuk menceburkan diri ke laut dan berenang menjauh dari daratan\n\
    dengan niat supaya tidak bisa ditangkap oleh Polisi, pelanggaran apa yang berlaku?\n\n\
    A. Tidak ada karena itu roleplay\n\
	B. Olympic Swimming\n\
	C. Athletic Swimming\n\
	D. Tidak ada karena itu termasuk alur cerita RP\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Situasi dimana karakter berlari secara zig-zag untuk menghindari tembakan disebut?\n\n\
    A. Car Ramming\n\
	B. Cover Evading\n\
	C. Ban Evading\n\
	D. Chicken Running\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Anda menggunakan '/pm' atau menghubungi teman anda melalui discord untuk menemui anda di Santa Marina Beach\n\
    Pelanggaran apa yang berlaku bagi anda?\n\n\
    A. Mixing\n\
	B. Supergaming\n\
	C. Metagaming\n\
	D. Powergaming\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Bagaimana penggunaan /me yang benar?\n\n\
    A. /me bentar bro AFK.\n\
	B. /me mengambil RPG dari kantungnya.\n\
	C. /me mengambil dompet dari saku belakang celananya.\n\
	D. /me lucu banget adminnya rek\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},
    
    {""YELLOW"Q: "WHITE"Jika anda menggunakan RP Bahasa Inggris dengan teman-teman anda dan orang lain datang\n\
    menggunakan Bahasa Indonesia, apa yang harus anda lakukan?\n\n\
    A. Melanjutkan RP Bahasa Inggris dengan teman anda dan tidak memperdulikan RP orang lain\n\
	B. Meledek orang yang tidak bisa berbahasa inggris\n\
	C. Mengganti RP dengan Bahasa Indonesia dan menanggapi RP orang lain\n\
	D. Pergi tanpa memberikan orang lain kesempatan untuk melakukan roleplay dengan anda\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Apakah yang akan anda lakukan bila tiba-tiba anda sedang jalan di tempat sepi tanpa\n\
    senjata dan di todong dengan pisau oleh 4 orang?\n\n\
    A. Kabur ketika di todong\n\
	B. Melawan dengan tangan kosong\n\
	C. Pada saat di todong menelfon teman\n\
	D. Mengikuti roleplay dirampok \n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Apa yang anda lakukan bila anda bersama teman anda (2 orang) ingin merampok lalu anda melihat 6 orang sedang jalan kaki?\n\n\
    A. Langsung datang dan menodong 6 orang tersebut tanpa memperdulikan jumlah\n\
	B. Tidak jadi merampok karena mempertimbangkan RP Fear 2 vs 6\n\
	C. Menabrak 6 orang  tersebut\n\
	D. Menembak 6 orang tersebut dan mengambil barang mereka ketika mereka mati\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Kendaran Anda disita / impound oleh polisi, apa yang Anda lakukan?\n\n\
    A. Lapor admin karena anda tidak menerimanya\n\
	B. Datang ke kantor polisi dan bertanya cara melepaskan kendaraan anda\n\
	C. Menghampiri polisi yang sedang patroli dan memintanya untuk mengeluarkan kendaraan yang disita\n\
	D. Melakukan provokasi di depan kantor polisi untuk mengeluarkan kendaraan disita\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Apakah yang akan anda lakukan bila melihat 6 orang kulit hitam di trotoar Idlewood dan anda hanyalah warga biasa?\n\n\
    A. Mendekati dan meledek mereka hitam\n\
	B. Menabrakkan kendaraan anda ke mereka\n\
	C. Tidak memperdulikan mereka dan terus berjalan saja\n\
	D. Merusuhi mereka\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Kendaraan anda tidak dikunci dan hilang karena dicuri oleh seseorang, apa yang anda lakukan?\n\n\
    A. Melaporkan kepada Admin (/report) untuk meminta kendaraan anda\n\
	B. Mencarinya melalui /myv atau melaporkan ke pihak kepolisian\n\
	C. Memukul-mukul player lain karena kendaran hilang\n\
	D. Melaporkan Admin karena tidak ingin membantu\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Batas maksimal roleplay perampokan/rob terhadap player adalah?\n\n\
    A. $2,000\n\
	B. $3,000\n\
	C. $5,000\n\
	D. $500\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Minimal level untuk melakukan roleplay kriminal?\n\n\
    A. Pelaku dan korban sama-sama level 3\n\
	B. Bebas tidak ada level karena level itu OOC\n\
	C. Pelaku dan korban sama-sama level 5\n\
	D. Pelaku level 5 dan korban level 3\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Penggunaan /b yang baik dan benar adalah?\n\n\
    A. /b Bang showroom ada di mana ya?\n\
	B. /b Bentar mau relog\n\
	C. /b Woi gw lapar minta makan dong\n\
	D. /b Kakak cantik tinggalnya di mana, mau aku antar gak?\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Membunuh player tanpa alasan yang jelas diperbolehkan ketika?\n\n\
    A. Membunuh player tanpa alasan tidak diperbolehkan sama sekali\n\
	B. Player A berkata kasar kepada diri Anda\n\
	C. Player B melakukan pembunuhan tanpa alasan juga\n\
	D. Player A sedang afk ditempat publik\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Apa yang anda lakukan bila admin tiba-tiba teleport ke player di dekat anda dan anda tidak diajaknya berbicara?\n\n\
    A. Mendekati admin dan teriak 'DEWA DEWA'\n\
	B. Mendekati admin karena kepo dengan permasalahan\n\
	C. Berpura-pura tidak melihat admin dan melanjutkan RP anda\n\
	D. Melakukan insult pada admin\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Diperbolehkan melakukan tindakan kriminal di tempat-tempat di bawah, kecuali?\n\n\
    A. Tempat berburu.\n\
	B. Tempat sepi.\n\
	C. Idlewood.\n\
	D. Depan kantor polisi.\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Cara membuat iklan yang baik dan benar adalah?\n\n\
    A. Buka HP - Yellow - Jual ginjal murmer uy\n\
	B. Buka HP - Yellow - Jual Sultan full modif, PM ID 666\n\
	C. Buka HP - Yellow - Beli pesawat nego, gak nego mati\n\
	D. Buka HP - Yellow - Jual Premier dengan kondisi yang masih bagus, berminat langsung call\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Salah satu hal yang dilarang di server ini adalah?\n\n\
    A. Berkendara layaknya orang normal\n\
	B. Melakukan roleplay secara terus menerus\n\
	C. Memukul player lain tanpa alasan\n\
	D. Mematuhi peraturan-peraturan server\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Tidak memberikan kesempatan roleplay terhadap lawan roleplay anda, disebut?\n\n\
    A. Sepuh Roleplay\n\
	B. Jago Roleplay\n\
	C. Force Roleplay\n\
	D. Revenge Killing\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Jika anda tiba-tiba ditembak orang tanpa alasan yang jelas apa yang harus anda lakukan?\n\n\
    A. Mengikuti RP nya dan screenshot setelah itu /report\n\
	B. Menghentikan roleplay dan langsung /b\n\
	C. Berteriak di voice in game “GUA LAPORIN DEWA LU”\n\
	D. Segera /q sebelum terlambat\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Apa yang anda lakukan bila EMS sedang sibuk menangani korban darurat di dekat anda dan anda\n\
    bukan keluarga atau teman/orang penting bagi korban tersebut?\n\n\
    A. Mendekati EMS dan berkata ingin membeli perban\n\
	B. Mendekati EMS dan meminta EMS melakukan treatment pada anda\n\
	C. Tidak memperdulikan situasi tersebut\n\
	D. Menabrak EMS\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Jika anda tidak dalam keadaan darurat, hidup anda tidak terancam dan\n\
    anda sedang mengendarai kendaraan anda lalu anda melihat 1 mobil polisi berjalan di depan anda, apa yang anda lakukan?\n\n\
    A. Menabrak kendaraan polisi tersebut\n\
	B. Menghiraukannya dan tetap berjalan\n\
	C. Menembaki kendaraan polisi tersebut tanpa alasan roleplay yang jelas\n\
	D. Menghina polisi tersebut kemudian memukuli mobilnya\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Seseorang mencoret-coret tembok gedung faction pemerintahan dengan menggunakan kata-kata kasar cacian\n\
    tanpa adanya alur cerita roleplay yang jelas, pelanggaran apa yang berlaku pada orang tersebut?\n\n\
    A. Tidak ada karena itu bagian dari roleplay dan keseruan roleplay\n\
	B. Tidak ada karena itu diperbolehkan dan kita tidak boleh mengatur RP orang lain\n\
	C. Powergaming karena itu mustahil dilakukan di dunia nyata\n\
	D. Non-RP Behavior karena tidak mencerminkan manusia yang waras dan sewajarnya\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Berapakah jumlah maksimal pihak perampok jika ingin melakukan roleplay perampokan toko?\n\n\
    A. Pihak perampok harus berjumlah maksimal 5 orang\n\
	B. Tidak ada batas karena di real life perampokan bisa berapa saja\n\
	C. Maksimal jumlah perampok ialah 4 orang\n\
	D. Pihak perampok harus berjumlah maksimal 8 orang\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Seseorang ingin merampok toko namun ia tidak memiliki sandera, pada akhirnya ia 'bermain mata' dengan teman dekatnya\n\
    dan bekerja sama agar temannya tersebut mau menjadi sandera untuk melancarkan aksinya.\n\
    Pelanggaran apa yang berlaku bagi mereka?\n\n\
    A. Situasi perampokan apapun tidak diperkenankan memiliki sandera palsu\n\
	B. Sah-sah aja karena ini roleplay, semua bisa terjadi dan kita tidak boleh mengatur roleplay mereka\n\
	C. Tidak ada pelanggaran yang berlaku karena roleplay mereka sangat bagus dan detail\n\
	D. Non-RP Robbery\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Jika anda menjadi seorang polisi namun anda dengan terang-terangan mencabut kanabis atau melakukan tindak kriminal\n\
    maka pelanggaran apa yang dapat dijatuhkan untuk anda?\n\n\
    A. Tidak ada karena itu merupakan alur roleplay saya sendiri dan saya berhak atas jalan cerita karakter saya\n\
	B. Tidak ada karena semua orang bebas melakukan apa saja semau mereka, yang baik bisa jadi jahat\n\
	C. Namanya juga roleplay kita bebas mau jadi seperti apa bahkan juga boleh jadi superhero\n\
	D. Non-RP Behavior, seharusnya saya menyadari jabatan dan pekerjaan saya sebagai penegak hukum dan roleplay sebagaimana seorang polisi itu sendiri\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Berikut ini contoh penggunaan /ado yang salah adalah?\n\n\
    A. /ado menunggu Delon\n\
	B. /ado kursi lipat\n\
	C. /ado box peralatan mekanik\n\
	D. /ado kotak P3K dan BLS Kit\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Berikut ini manakah penjelasan yang benar sebagai penggunaan /ado?\n\n\
    A. Digunakan untuk mendukung jalannya roleplay biasanya lebih banyak digunakan untuk me-roleplay-kan\n\
    objek yang tak tampak seolah-olah ada\n\
	B. Digunakan pada saat ingin AFK (/ado melamun)\n\
	C. Digunakan hanya ketika kita ingin mengobrol dengan orang sekitar dan kita lagi gabisa voice\n\
	D. Digunakan untuk promosi server lain\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Berikut ini manakah penggunaan /ado yang benar?\n\n\
    A. /ado ban Offroad untuk mobil di dalam rak\n\
	B. /ado tas milik Jose di atas meja\n\
	C. Tidak ada yang benar, keduanya salah\n\
	D. Keduanya benar\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Berikut ini manakah penggunaan /ado yang benar?\n\n\
    A. /ado memukuli orang di depannya dengan sangat keras\n\
	B. /ado menunggu Delon\n\
	C. Tidak ada yang benar, keduanya salah\n\
	D. Keduanya benar\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Berikut ini manakah penggunaan /ame yang benar?\n\n\
    A. /ame menghina orang di depannya dengan cacian yang menyakitkan\n\
	B. /ame mengangkat box dari rak dengan bantuan kedua tangan\n\
	C. Tidak ada yang benar, keduanya salah\n\
	D. Keduanya benar\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Berikut ini manakah penggunaan /ame yang benar?\n\n\
    A. /ame memukuli tiang listrik dengan bantuan kedua tangan hingga roboh\n\
	B. /ame terlihat rambutnya dihembus-hembus oleh angin\n\
	C. Tidak ada yang benar, keduanya salah\n\
	D. Keduanya benar\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Berikut ini manakah penggunaan /me yang benar?\n\n\
    A. /me mengeluarkan box sampah makanan burger dari kantung celananya lalu membuangnya ke tempat sampah\n\
	B. /me terlihat cuaca begitu bagus\n\
	C. Tidak ada yang benar, keduanya salah\n\
	D. Keduanya benar\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Berikut ini manakah penggunaan /me yang benar?\n\n\
    A. /me memotong batang pohon dengan bantuan Chainsaw yang siap digunakan dengan energi baterai yang mumpuni\n\
	B. /me menyembunyikan dirinya di balik pepohonan dan mendengarkan pembicaraan Rose dengan Jack\n\
	C. Tidak ada yang benar, keduanya salah\n\
	D. Keduanya benar\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Seorang pengemudi mobil berkendara secara ugal-ugalan, lawan arus dan menabrak hampir semua yang ada di hadapannya\n\
    termasuk gedung, rumah ataupun tiang-tiang listrik bahkan ia juga menabrak beberapa pejalan kaki karena gaya mengemudi yang ekstrim\n\
    Pelanggaran apa yang berlaku bagi pengemudi tersebut?\n\n\
    A. Non-RP Driving\n\
	B. Non-RP Behavior\n\
	C. Non-RP Fear\n\
	D. Idiotic Driving\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Selama mengemudi di server ini mana pernyataan berikut yang benar, kecuali?\n\n\
    A. Kita harus tetap berkendara secara realistis dan patuh terhadap rambu yang ada\n\
	B. Kita harus berkendara di sebelah kiri jalan karena kita kultur Korea Selatan\n\
	C. Kita harus tetap berada di jalur kanan meskipun server ini kultur Indonesia tapi ikuti bawaan GTA\n\
	D. Kita tidak boleh menabrak player dengan sengaja dengan niat melukai\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Di bawah ini yang tepat untuk meminta diantarkan ke suatu lokasi, kecuali?\n\n\
    A. Buka HP - Yellow\n\
	B. Meminta tolong kepada orang di sekitar\n\
	C. Menghubungi layanan darurat untuk meminta diantarkan\n\
	D. Menelpon teman dan meminta diantarkan ke suatu tempat\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Apa yang harus anda lakukan jika anda dikejar polisi dan terkepung serta mobil anda habis bensin?\n\n\
    A. /q segera sebelum terlambat\n\
	B. /b sabar dulu abis bensin\n\
	C. Mengikuti roleplay yang di berikan oleh polisi\n\
	D. /do bang mau afk dulu\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Anda harus tetap ber-roleplay dalam setiap keadaan selama berada di server, kecuali?\n\n\
    A. Memesan taxi dari aplikasi handphone\n\
	B. Antre di Restoran untuk membeli kebutuhan makanan dan minuman\n\
	C. Pada saat di-jail admin\n\
	D. Ketika menjadi sandera pada situasi perampokan toko\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Ketika anda di-jail oleh admin dan satu sel dengan 2 orang lainnya, mereka berbicara melalui voice IC tetapi membahas\n\
    hal-hal di luar roleplay ataupun hal-hal OOC maka pelanggaran apa yang cocok untuk kedua orang tersebut?\n\n\
    A. Mixing karena membahas hal OOC melalui sarana voice IC itu termasuk mixing\n\
	B. Metagaming karena mereka berada di jail OOC\n\
	C. Tidak ada salah karena status jail-nya adalah jail admin dan itu adalah full OOC\n\
	D. Non-RP Microphone\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Pada saat admin mengurung anda ke dalam admin jail, anda berada satu sel dengan seseorang wanita yang dimana anda tertarik padanya\n\
    lalu anda langsung meminta nomor HP IC nya melalui voice IC dan langsung mencatatnya untuk bahan roleplay anda ke depannya.\n\
    Pelanggaran apa yang pantas dijatuhi untuk anda?\n\n\
    A. Mixing karena anda membahasnya lewat OOC\n\
	B. Tidak ada karena lagi di admin jail jadi bebas, suka-suka player\n\
	C. Metagaming karena anda memanfaatkan jail admin yang sifatnya OOC untuk mendapatkan pengetahuan (berupa no HP IC) dari sana\n\
	D. Tidak bersalah karena sama-sama di jail admin\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {""YELLOW"Q: "WHITE"Di bawah ini adalah contoh Metagaming, kecuali?\n\n\
    A. Mendeskripsikan tersangka pembunuhan dengan /me mendeskripsikan Jeffrey_Chen\n\
	B. Ketika 1 karakter anda sudah mati setelah tembak-tembakan anda menggunakan karakter lain untuk kembali ke tempat anda mati\n\
	C. Menembaki orang tanpa alasan yang jelas\n\
	D. Menyebut nama orang yang tidak dikenal berdasarkan nametag diatas kepala\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Dibawah ini adalah contoh Powergaming, kecuali?\n\n\
    A. /me mengeluarkan RPG dari sempak\n\
	B. Melompat dari gedung ke gedung saat pursuit (montage)\n\
	C. /me megnangkat truk didepannya dengan satu tangan\n\
	D. Menyebut nama orang di atas kepala padahal secara RP tidak kenal\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Anda sedang dalam pengejaran polisi lalu anda menggunakan mobil sultan mengarah ke parkiran paling atas gedung\n\
    lalu anda melompat ke gedung lain, hal tersebut merupakan pelanggaran?\n\n\
    A. Powergaming\n\
	B. Metagaming\n\
	C. Deathmatching\n\
	D. Olympic Swimming\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Jika anda melihat orang yang anda kejar melompat dari atas gedung ke gedung lain dengan kendaraan, apa yang harus anda lakukan?\n\n\
    A. Meninggalkan roleplay tersebut\n\
	B. /report di in game ditambah screenshot/Rekam lalu kirim di discord server bagian player reports\n\
	C. Menembaki orang yang melompat \n\
	D. Berlarian tanpa arah yang jelas dan berteriak 'PUJA KERANG AJAIB'\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "B"},

    {""YELLOW"Q: "WHITE"Berikut ini adalah contoh mixing, kecuali?\n\n\
    A. Berbicara di voice in game 'ANJAY MANTAP SLURR JAWIRR SANGADH'\n\
	B. Menyebut nama teman RP kita bukan dengan nama karakter IC tapi nama asli OOC\n\
	C. 'Admin tolong gua bug'\n\
	D. Melaporkan pencurian kendaraan ke hotline darurat\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Apa yang Anda lakukan jika bertemu dengan Newbie yang melanggar peraturan server?\n\n\
    A. Mengikuti Newbie tersebut untuk melanggar peraturan bersama\n\
	B. Mendukung Newbie tersebut agar lebih bersemangat untuk melanggar peraturan\n\
	C. Memberitahukan Newbie tersebut agar tidak melanggar peraturan\n\
	D. Membunuh Newbie tersebut agar dia tidak melanggar peraturan\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},
    
    {""YELLOW"Q: "WHITE"Berapa lama waktu yang dibutuhkan untuk kembali mengikuti Roleplay di tempat yang sama\n\
    atau kelompok yang sama setelah karakter Anda mengalami Player Killed / PK?\n\n\
    A. 30 menit\n\
	B. 60 menit\n\
	C. 90 menit\n\
	D. 30 detik\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "A"},

    {""YELLOW"Q: "WHITE"Ketika anda dirampok oleh player lain, mereka mengambil makanan dan minuman milikmu\n\
    maka hukuman apa yang telah berlaku bagi si perampok?\n\n\
    A. Tidak ada, itu merupakan RP yang jelas\n\
	B. Tentu mereka tidak bersalah karena saya sedang dirampok\n\
	C. Melaporkan ke discord atau /report karena makanan dan minuman tidak boleh diambil\n\
	D. Tidak bersalah, menerima dengan lapang dada\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Seluruh barang termasuk senjata diperbolehkan diambil oleh pihak perampok apabila mereka\n\
    sedang melakukan rob terhadap player lain, kecuali?\n\n\
    A. Kondom dan dildo\n\
	B. Uang dan wanita\n\
	C. AK47 dan uang\n\
	D. Item yang didapat dari hasil pekerjaan, makanan & minuman\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Apa perbedaan Character Killed dan Player Killed?\n\n\
    A. CK di mana karakter meninggal dan hidup lagi, PK di mana karakter meninggal dan hidup lagi\n\
	B. CK adalah karakter meninggal dan PK adalah player meninggal\n\
	C. CK di mana karakter meninggal secara permanen, sedangkan PK di mana karakter mengalami lupa ingatan dan lupa dengan kejadian sebelumnya\n\
	D. Character Killed adalah CK dan Player Killed adalah PK\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Menabrakkan kendaraan anda ke orang lain tanpa alasan yang jelas dan berkali-kali\n\
    secara sengaja merupakan pelanggaran?\n\n\
    A. Deathmatch\n\
	B. Mixing\n\
	C. Metagaming\n\
	D. Car Ramming\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Apa definisi roleplay yang benar?\n\n\
    A. Roleplay adalah respect walau bagaimanapun roleplay yang diberikan kita harus menerima dengan alasan respect\n\
	B. Roleplay adalah seni ledakan\n\
	C. Roleplay adalah sebuah permainan yang dimana karakter saling berinteraksi sebagai dirinya sendiri (player)\n\
	D. Roleplay adalah sebuah permainan dimana kita berperan layaknya manusia di dunia nyata\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Berikut ini adalah contoh roleplay yang benar, kecuali?\n\n\
    A. Menjadi karyawan Restoran dan melayani pelanggan\n\
	B. Menjadi organized crime yang memiliki bisnis legal sebagai penyamaran\n\
	C. Menjadi polisi dan menjaga keamanan warga\n\
	D. Roleplay menjadi batman\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Berikut adalah contoh dari Refuse RP, kecuali??\n\n\
    A. Anda pingsan, EMT sudah datang dan dokter di RS sedang meroleplaykan perawatan tapi anda tiba-tiba memutuskan koma\n\
	B. Anda sedang dalam pengejaran polisi lalu anda /q (keluar dari server)\n\
	C. Anda sedang dalam situasi tembak-menembak lalu anda /q (logout dari server)\n\
	D. Anda menjalankan roleplay sebagai penghibur di klub malam\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Apa yang anda lakukan ketika melihat player melakukan perampokan terhadap player yang sedang melakukan Sidejob?\n\n\
    A. Melaporkan ke polisi melalui /911\n\
	B. Berteriak agar perampok takut dan kabur\n\
	C. Melaporkan ke Admin melalui /ask\n\
	D. Melaporkan ke Admin melalui /report atau ke discord\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Anda sedang berjalan-jalan sendirian lalu anda melihat seseorang yang sedang di rampok oleh 4 orang, maka hal yang tidak harus anda lakukan, kecuali?\n\n\
    A. Mendatangi rampok tersebut dan meminta foto\n\
    B. Mendatangi rampok tersebut\n\
    C. Menembaki rampok tersebut\n\
    D. Menghubungi layanan darurat dan menjelaskan perampokan yang terjadi pada polisi\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "D"},

    {""YELLOW"Q: "WHITE"Manakah dari berikut ini yang merupakan penggunaan /attempt yang tepat?\n\n\
    A. /attempt mengambil dompet dari celananya\n\
    B. /attempt berjalan melewati kerumunan\n\
    C. /attempt untuk hidup setelah dirawat dokter\n\
    D. Melakukan spam pada /attempt hingga sukses\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"},

    {""YELLOW"Q: "WHITE"Berikut merupakan penggunaan /attempt yang salah, kecuali?\n\n\
    A. /attempt menghidupkan mayat didepannya dan sukses\n\
    B. /attempt berhasil sembuh setelah ditangani dokter dan sukses\n\
    C. /attempt memukul bola 8 dengan stik billiard untuk memasukkan ke lobang sebelah kanan\n\
    D. /attempt memukul orang di depannya dan sukses\n\n\
    "RED"(Tuliskan jawaban dalam bentuk huruf pilihan berganda hanya diisi dengan A, B, C atau D)", "C"}
};
*/


new const g_ServerHintTips[][144] =
{
    "Kamu tau gak? Sejujurnya sidejob itu menguntungkan kalau lagi jenuh ngerjain job utama, lokasinya juga ada di GPS.",
    "Cobalah bekerja sebagai Farmer atau Butcher, soalnya pedagang butuh beberapa barang tersebut.",
    "Aku sayang Wahyu <3",
    "Selain karnaval kamu bisa merokok, konsumsi marijuana ataupun minuman alkohol untuk menurunkan stress.",
    "Bro mancing deh biar nurunin stress juga, terus ikan juga mahal.",
    "Tau nggak kalau minuman alkohol itu ngurangin stress lumayan, tapi sama kayak marijuana.",
    "Dapatin armor bisa dengan kevlar atau sinte ataupun konsumsi heroin.",
    "Mancing bisa dapat ikan, penyu atau hiu tapi hanya ikan saja yang legal.",
    "Kamu bisa ajak teman untuk bermain di Pahlawan Roleplay dan kerja bareng disini!",
    "Pahlawan Roleplay dibuat ketika Wahyu sedang tersenyum :)",
    "Mancing juga bisa untuk menurunkan stress dengan sangat cepat.",
    "Kalau kamu kecelakaan, kesehatan kamu dapat berkurang tergantung tingkat keparahan!",
    "Kalau gak mau kena damage yang besar ketika kecelakaan, gunakan "WHITE"'/sb' {077292}supaya pake seatbelt!",
    "Kenapa sih kalian kacangin aku, aku ini imut :)",
    "Aku mencintai Pahlawan Roleplay sebagaimana rumahku sendiri, kamu pasti sama kaya aku <3",
    "Bagiku gak ada kota lain yang seperti Pahlawan Roleplay, cinta pertamaku.",
    "Kamu tidak punya KTP untuk bekerja? Lakukan sidejob aja selama menunggu layanan buka.",
    "Kerja sidejob tidak butuh KTP, lokasinya ada di "WHITE"GPS -> Lokasi Kerja -> cari (kerja sampingan).",
    "Jika bosan menunggu layanan KTP buka, kerja sidejob terlebih dahulu saja.",
    "Aku sayang dengan semua warga Pahlawan Roleplay!!! <3",
    "Kamu kalau mau ngecit jangan disini, ini Pahlawan Roleplay adalah rumah kita bersama!",
    "Hari ini aku gabut, enak RP apa yah? Eh lupa, aku kan cuma BOT :'( hikks",
    "Di discord ada channel panduan, baca deh banyak banget informasi yang belum tentu kamu tau.",
    "Kalau kamu nemuin orang yang melanggar rules gunakan "WHITE"'/report' {077292}atau ke discord ya.",
    "Jangan gunain "WHITE"'/ask' {077292}buat laporin sesuatu karena itu untuk bertanya!",
    "Apasih marah-marah mulu, imut gini~ :)",
    "Warga baru mending kerja bus aja deh, gak ribet dan gak susah.",
    "Sidejob kayak forklift atau trash collector itu lumayan buat kantong!",
    "Kerja itu-itu mulu, ga bosen? Coba kerja sidejob, gak perlu join ke balkot dateng aja ke GPS.",
    "Kamu bisa gunain "WHITE"'/delay' {077292}untuk ngeliat cooldown sendiri.",
    "Di server ini ada rusa, kamu bisa hunting mereka, ngurangin stress loh lumayan.",
    "Kalo kamu stress berat sambil nyetir, mobilmu oleng bahkan bisa pingsan.",
    "Gada yang bisa duain Pahlawan Roleplay, gada lawan hehe~ <3",
    "Kalau kamu gamau kena stress, donasi "WHITE"VIP Pinkyman Pinky {077292}cek discord!",
    "Selain donasi rumah, kamu bisa dapatkan fitur utamanya dengan sewa rusun (ngekos) pake uang IC, lokasi di GPS.",
    "Setiap kali sewa gudangmu berakhir, barangmu tidak hilang dan kamu harus menyewa lagi untuk mengambilnya.",
    "Rusun itu waktu sewanya berakhir serentak, jadi jangan sampai rugi ketika ingin menyewa.",
    "Sewa rusun maka kamu dapat menyimpan pakaian beserta toys nya, menyimpang barang dan senjata.",
    "Jika ingin melihat daftar update terbaru dari server bisa buka discord.",
    "Hati-hati berburu rusa karena kamu bisa diserang beruang dan kesehatanmu berkurang.",
    "Kamu bisa membeli skateboard di warung untuk alat transportasi.",
    "Jika tidak ada pegawai restoran dan kamu butuh makanan, pergilah ke pecel lele kaki lima di server ini.",
    "Slip gaji didapatkan dari paycheck server setiap 15 menit dan harus dicairkan di Balai Kota.",
    "Asuransi, mengambil job di balai kota dan beberapa kegiatan lainnya memerlukan KTP.",
    "Sedang stuck/bug? Cobalah cek "WHITE"'/fixme' {077292}carilah mana yang sesuai.",
    "Jika tidak dapat melihat apapun di visual cobalah "WHITE"'/fixme' {077292}dan cari yang sesuai.",
    "Kamu bisa memperpanjang KTP di kantor Balai Kota dengan menjumpai pegawai!",
    "Hargai orang lain yang bermain di server ini, agar kamu tidak dimusuhi!",
    "Seluruh kendaraan yang jenisnya bukan Offroad tidak boleh Offroad meskipun sudah modif ban!",
    "Jika kamu player PC kamu dapat menggunakan keybind yang ada di channel {713eca}#keybind",
    "Kalau kamu koma, seluruh uang di saku dan senjata yang kamu pegang bakalan ilang!",
    "Woi, jangan rusuh ah. Bikin badmood aja sihh!!",
    "Ah, jadi laper pengen makan seblak~ :3",
    "Kakaaaaaaak, ajarin akuuu erpiih dongg!! :3",
    "Kamu bisa nyimpan pakaian sama toys pake "WHITE"'/sc' {077292}terus kalau mau dipake harus di rumah atau rusun sewaan.",
    "Jika sedang di luar garkot, gunakan "WHITE"'/handbrake' {077292}maka kendaraan diparkir tidak hilang.",
    "Kalau parkir di luar garkot, pakai "WHITE"'/handbrake' {077292}supaya tidak hilang di visual!",
    "Membuat lisensi berburu dapat dilakukan bersama fraksi kepolisian!",
    "Jangan pernah menggunakan file illegal yang menguntungkan pribadi!",
    "Respect terhadap pemain lain diutamakan daripada ego sendiri!",
    "Tidak diperbolehkan melakukan pelecahan seksual di in-game baik RP meskipun saling setuju!",
    "Pelecehan seksual, ataupun penghinaan SARA tidak diperbolehkan di Pahlawan Roleplay!",
    "Jadikanlah Pahlawan Roleplay sebagai komunitas yang sehat dengan bantuan kalian semua!",
    "Aku cemburu kalau ngeliat kamu ada di server lain :(",
    "Cukup Pahlawan Roleplay aja yang di hati, jangan ada server lain :)",
    "Pahlawan Roleplay mengajarkan kita arti sebuah kebersamaan dan kekeluargaan yang hangat."
};
