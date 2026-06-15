#include <YSI_Coding\y_hooks>

//event type 1. TDM, 2. Racing

#define MAX_ERACE_CP 30

enum e_EVENTSTUFF
{
    eventMusic[144],

    redSkin,
    Float:redHealth,
    Float:redArmour,
    Float:redSpawn[4],
    redWeapon[3],
    redTeamScore,

    blueSkin,
    Float:blueHealth,
    Float:blueArmour,
    Float:blueSpawn[4],
    blueWeapon[3],
    blueTeamScore,

    arenaVWID,
    arenaIntid,
    timeLimit,
    targetScore,
    maxPlayer,
    partPrize,
    winnerPrize,

    //race
    Float:raceSpawn[4],
    raceVehicle,
    racecWinners,
    raceEnding,
    raceShowVeh,

    eventType,
    bool:eventStarted,
    bool:eventOpened,
    eventOpentime,

    //zombie
    Float:zombieSpawn[4],
    Float:humanSpawn[4],
    Float:boundPoint1[3],
    Float:boundPoint2[3],
    zombieZone1,
    zombieZone2,
    STREAMER_TAG_AREA:zombieArea,

    //squid game
    bool:SGLightRed
};
new EventInfo[e_EVENTSTUFF];

enum e_racecpinfo
{
    Float:raceCPCoord[3]
};
new EventRaceCP[MAX_ERACE_CP + 1][e_racecpinfo];

new Iterator:InEvent<MAX_PLAYERS>;
new Iterator:EvRedTeam<MAX_PLAYERS>;
new Iterator:EvBlueTeam<MAX_PLAYERS>;
new Iterator:EvRaceCP<MAX_ERACE_CP>;
new Iterator:EvHumanTeam<MAX_PLAYERS>;
new Iterator:EvZombieTeam<MAX_PLAYERS>;
new Iterator:AvailTiles<324>;

new STREAMER_TAG_OBJECT:Event_SGGate;
new STREAMER_TAG_AREA:Event_SGFinish;

new pZombieClass[MAX_PLAYERS];
new pZombieAbilityCD[MAX_PLAYERS];

enum e_falloutinfo
{
    Float:fallobjX,
    Float:fallobjY,
    Float:fallobjZ,
    Float:fallobjRX,
    Float:fallobjRY,
    Float:fallobjRZ,
    
    STREAMER_TAG_OBJECT:TileObject,
    shakestep,
    shaketimer
};
new Event_FalloutInfo[324][e_falloutinfo];

new Float:falloutRandSpawn[][4] = 
{
    {575.7056,-2041.1534,40.1931,270.3755},
    {575.8790,-2008.6975,40.1931,269.4355},
    {597.0226,-2002.6229,40.1931,184.8346},
    {600.4514,-2031.1135,40.1931,183.5813},
    {614.4720,-2040.8907,40.1931,271.6288},
    {621.5296,-2005.5585,40.1931,356.5430},
    {628.8704,-2024.9995,40.1931,178.8813},
    {628.0302,-2044.1144,40.1931,88.0137}
};

new Float:squidgameRandSpawn[][4] = 
{
    {-54.5416,2522.8171,16.4922,268.1822},
    {-55.1216,2503.8464,16.4844,272.0147},
    {-55.8271,2486.0574,16.4844,268.8814},
    {-39.7091,2484.8594,16.4844,268.1822},
    {-38.6535,2499.7664,16.4844,269.9897},
    {-38.1775,2518.6506,16.4844,269.1222}
};

Event_FalloutTileCreate()
{
    for(new x; x < 324; x++)
    {
        KillTimer(Event_FalloutInfo[x][shaketimer]);
        Event_FalloutInfo[x][shaketimer] = -1;

        Event_FalloutInfo[x][shakestep] = 0;

        if(DestroyDynamicObject(Event_FalloutInfo[x][TileObject]))
            Event_FalloutInfo[x][TileObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        Iter_Add(AvailTiles, x);
    }

    Event_FalloutInfo[0][TileObject] = CreateDynamicObject(19353, 632.148132, -1996.105712, 39.107166, 0.000000, 90.000000, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[0][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[1][TileObject] = CreateDynamicObject(19353, 632.148132, -1999.315185, 39.107166, 0.000000, 90.000000, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[1][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[2][TileObject] = CreateDynamicObject(19353, 632.148132, -2002.525268, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[2][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[3][TileObject] = CreateDynamicObject(19353, 632.148132, -2005.734741, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[3][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[4][TileObject] = CreateDynamicObject(19353, 632.148132, -2008.945678, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[4][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[5][TileObject] = CreateDynamicObject(19353, 632.148132, -2012.155151, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[5][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[6][TileObject] = CreateDynamicObject(19353, 632.148132, -2015.365234, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[6][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[7][TileObject] = CreateDynamicObject(19353, 632.148132, -2018.574707, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[7][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[8][TileObject] = CreateDynamicObject(19353, 632.148132, -2021.775146, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[8][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[9][TileObject] = CreateDynamicObject(19353, 632.148132, -2024.984619, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[9][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[10][TileObject] = CreateDynamicObject(19353, 632.148132, -2028.194702, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[10][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[11][TileObject] = CreateDynamicObject(19353, 632.148132, -2031.404174, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[11][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[12][TileObject] = CreateDynamicObject(19353, 632.148132, -2034.615112, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[12][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[13][TileObject] = CreateDynamicObject(19353, 632.148132, -2037.824584, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[13][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[14][TileObject] = CreateDynamicObject(19353, 632.148132, -2041.034667, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[14][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[15][TileObject] = CreateDynamicObject(19353, 632.148132, -2044.244140, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[15][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[16][TileObject] = CreateDynamicObject(19353, 632.148132, -2047.453857, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[16][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[17][TileObject] = CreateDynamicObject(19353, 632.148132, -2050.663330, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[17][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[18][TileObject] = CreateDynamicObject(19353, 628.647583, -2050.663330, 39.107166, 0.000007, 90.000000, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[18][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[19][TileObject] = CreateDynamicObject(19353, 628.647583, -2047.453857, 39.107166, 0.000007, 90.000000, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[19][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[20][TileObject] = CreateDynamicObject(19353, 628.647583, -2044.243774, 39.107166, 0.000007, 90.000007, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[20][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[21][TileObject] = CreateDynamicObject(19353, 628.647583, -2041.034301, 39.107166, 0.000007, 90.000007, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[21][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[22][TileObject] = CreateDynamicObject(19353, 628.647583, -2037.823364, 39.107166, 0.000007, 90.000007, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[22][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[23][TileObject] = CreateDynamicObject(19353, 628.647583, -2034.613891, 39.107166, 0.000007, 90.000007, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[23][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[24][TileObject] = CreateDynamicObject(19353, 628.647583, -2031.403808, 39.107166, 0.000007, 90.000015, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[24][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[25][TileObject] = CreateDynamicObject(19353, 628.647583, -2028.194335, 39.107166, 0.000007, 90.000015, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[25][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[26][TileObject] = CreateDynamicObject(19353, 628.647583, -2024.993896, 39.107166, 0.000007, 90.000007, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[26][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[27][TileObject] = CreateDynamicObject(19353, 628.647583, -2021.784423, 39.107166, 0.000007, 90.000007, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[27][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[28][TileObject] = CreateDynamicObject(19353, 628.647583, -2018.574340, 39.107166, 0.000007, 90.000015, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[28][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[29][TileObject] = CreateDynamicObject(19353, 628.647583, -2015.364868, 39.107166, 0.000007, 90.000015, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[29][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[30][TileObject] = CreateDynamicObject(19353, 628.647583, -2012.153930, 39.107166, 0.000007, 90.000015, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[30][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[31][TileObject] = CreateDynamicObject(19353, 628.647583, -2008.944458, 39.107166, 0.000007, 90.000015, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[31][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[32][TileObject] = CreateDynamicObject(19353, 628.647583, -2005.734375, 39.107166, 0.000007, 90.000022, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[32][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[33][TileObject] = CreateDynamicObject(19353, 628.647583, -2002.524902, 39.107166, 0.000007, 90.000022, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[33][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[34][TileObject] = CreateDynamicObject(19353, 628.647583, -1999.315185, 39.107166, 0.000007, 90.000030, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[34][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[35][TileObject] = CreateDynamicObject(19353, 628.647583, -1996.105712, 39.107166, 0.000007, 90.000030, 179.999877, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[35][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[36][TileObject] = CreateDynamicObject(19353, 625.148742, -1996.105712, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[36][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[37][TileObject] = CreateDynamicObject(19353, 625.148742, -1999.315185, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[37][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[38][TileObject] = CreateDynamicObject(19353, 625.148742, -2002.525268, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[38][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[39][TileObject] = CreateDynamicObject(19353, 625.148742, -2005.734741, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[39][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[40][TileObject] = CreateDynamicObject(19353, 625.148742, -2008.945678, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[40][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[41][TileObject] = CreateDynamicObject(19353, 625.148742, -2012.155151, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[41][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[42][TileObject] = CreateDynamicObject(19353, 625.148742, -2015.365234, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[42][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[43][TileObject] = CreateDynamicObject(19353, 625.148742, -2018.574707, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[43][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[44][TileObject] = CreateDynamicObject(19353, 625.148742, -2021.775146, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[44][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[45][TileObject] = CreateDynamicObject(19353, 625.148742, -2024.984619, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[45][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[46][TileObject] = CreateDynamicObject(19353, 625.148742, -2028.194702, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[46][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[47][TileObject] = CreateDynamicObject(19353, 625.148742, -2031.404174, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[47][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[48][TileObject] = CreateDynamicObject(19353, 625.148742, -2034.615112, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[48][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[49][TileObject] = CreateDynamicObject(19353, 625.148742, -2037.824584, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[49][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[50][TileObject] = CreateDynamicObject(19353, 625.148742, -2041.034667, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[50][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[51][TileObject] = CreateDynamicObject(19353, 625.148742, -2044.244140, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[51][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[52][TileObject] = CreateDynamicObject(19353, 625.148742, -2047.453857, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[52][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[53][TileObject] = CreateDynamicObject(19353, 625.148742, -2050.663330, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[53][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[54][TileObject] = CreateDynamicObject(19353, 621.648193, -2050.663330, 39.107166, 0.000007, 89.999992, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[54][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[55][TileObject] = CreateDynamicObject(19353, 621.648193, -2047.453857, 39.107166, 0.000007, 89.999992, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[55][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[56][TileObject] = CreateDynamicObject(19353, 621.648193, -2044.243774, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[56][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[57][TileObject] = CreateDynamicObject(19353, 621.648193, -2041.034301, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[57][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[58][TileObject] = CreateDynamicObject(19353, 621.648193, -2037.823364, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[58][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[59][TileObject] = CreateDynamicObject(19353, 621.648193, -2034.613891, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[59][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[60][TileObject] = CreateDynamicObject(19353, 621.648193, -2031.403808, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[60][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[61][TileObject] = CreateDynamicObject(19353, 621.648193, -2028.194335, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[61][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[62][TileObject] = CreateDynamicObject(19353, 621.648193, -2024.993896, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[62][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[63][TileObject] = CreateDynamicObject(19353, 621.648193, -2021.784423, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[63][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[64][TileObject] = CreateDynamicObject(19353, 621.648193, -2018.574340, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[64][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[65][TileObject] = CreateDynamicObject(19353, 621.648193, -2015.364868, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[65][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[66][TileObject] = CreateDynamicObject(19353, 621.648193, -2012.153930, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[66][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[67][TileObject] = CreateDynamicObject(19353, 621.648193, -2008.944458, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[67][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[68][TileObject] = CreateDynamicObject(19353, 621.648193, -2005.734375, 39.107166, 0.000007, 90.000015, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[68][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[69][TileObject] = CreateDynamicObject(19353, 621.648193, -2002.524902, 39.107166, 0.000007, 90.000015, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[69][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[70][TileObject] = CreateDynamicObject(19353, 621.648193, -1999.315185, 39.107166, 0.000007, 90.000022, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[70][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[71][TileObject] = CreateDynamicObject(19353, 621.648193, -1996.105712, 39.107166, 0.000007, 90.000022, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[71][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[72][TileObject] = CreateDynamicObject(19353, 618.149719, -1996.105712, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[72][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[73][TileObject] = CreateDynamicObject(19353, 618.149719, -1999.315185, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[73][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[74][TileObject] = CreateDynamicObject(19353, 618.149719, -2002.525268, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[74][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[75][TileObject] = CreateDynamicObject(19353, 618.149719, -2005.734741, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[75][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[76][TileObject] = CreateDynamicObject(19353, 618.149719, -2008.945678, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[76][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[77][TileObject] = CreateDynamicObject(19353, 618.149719, -2012.155151, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[77][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[78][TileObject] = CreateDynamicObject(19353, 618.149719, -2015.365234, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[78][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[79][TileObject] = CreateDynamicObject(19353, 618.149719, -2018.574707, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[79][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[80][TileObject] = CreateDynamicObject(19353, 618.149719, -2021.775146, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[80][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[81][TileObject] = CreateDynamicObject(19353, 618.149719, -2024.984619, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[81][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[82][TileObject] = CreateDynamicObject(19353, 618.149719, -2028.194702, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[82][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[83][TileObject] = CreateDynamicObject(19353, 618.149719, -2031.404174, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[83][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[84][TileObject] = CreateDynamicObject(19353, 618.149719, -2034.615112, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[84][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[85][TileObject] = CreateDynamicObject(19353, 618.149719, -2037.824584, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[85][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[86][TileObject] = CreateDynamicObject(19353, 618.149719, -2041.034667, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[86][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[87][TileObject] = CreateDynamicObject(19353, 618.149719, -2044.244140, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[87][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[88][TileObject] = CreateDynamicObject(19353, 618.149719, -2047.453857, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[88][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[89][TileObject] = CreateDynamicObject(19353, 618.149719, -2050.663330, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[89][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[90][TileObject] = CreateDynamicObject(19353, 614.649169, -2050.663330, 39.107166, 0.000007, 89.999984, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[90][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[91][TileObject] = CreateDynamicObject(19353, 614.649169, -2047.453857, 39.107166, 0.000007, 89.999984, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[91][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[92][TileObject] = CreateDynamicObject(19353, 614.649169, -2044.243774, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[92][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[93][TileObject] = CreateDynamicObject(19353, 614.649169, -2041.034301, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[93][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[94][TileObject] = CreateDynamicObject(19353, 614.649169, -2037.823364, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[94][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[95][TileObject] = CreateDynamicObject(19353, 614.649169, -2034.613891, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[95][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[96][TileObject] = CreateDynamicObject(19353, 614.649169, -2031.403808, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[96][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[97][TileObject] = CreateDynamicObject(19353, 614.649169, -2028.194335, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[97][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[98][TileObject] = CreateDynamicObject(19353, 614.649169, -2024.993896, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[98][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[99][TileObject] = CreateDynamicObject(19353, 614.649169, -2021.784423, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[99][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[100][TileObject] = CreateDynamicObject(19353, 614.649169, -2018.574340, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[100][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[101][TileObject] = CreateDynamicObject(19353, 614.649169, -2015.364868, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[101][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[102][TileObject] = CreateDynamicObject(19353, 614.649169, -2012.153930, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[102][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[103][TileObject] = CreateDynamicObject(19353, 614.649169, -2008.944458, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[103][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[104][TileObject] = CreateDynamicObject(19353, 614.649169, -2005.734375, 39.107166, 0.000007, 90.000007, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[104][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[105][TileObject] = CreateDynamicObject(19353, 614.649169, -2002.524902, 39.107166, 0.000007, 90.000007, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[105][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[106][TileObject] = CreateDynamicObject(19353, 614.649169, -1999.315185, 39.107166, 0.000007, 90.000015, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[106][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[107][TileObject] = CreateDynamicObject(19353, 614.649169, -1996.105712, 39.107166, 0.000007, 90.000015, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[107][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[108][TileObject] = CreateDynamicObject(19353, 611.148193, -1996.105712, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[108][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[109][TileObject] = CreateDynamicObject(19353, 611.148193, -1999.315185, 39.107166, 0.000000, 90.000007, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[109][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[110][TileObject] = CreateDynamicObject(19353, 611.148193, -2002.525268, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[110][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[111][TileObject] = CreateDynamicObject(19353, 611.148193, -2005.734741, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[111][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[112][TileObject] = CreateDynamicObject(19353, 611.148193, -2008.945678, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[112][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[113][TileObject] = CreateDynamicObject(19353, 611.148193, -2012.155151, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[113][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[114][TileObject] = CreateDynamicObject(19353, 611.148193, -2015.365234, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[114][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[115][TileObject] = CreateDynamicObject(19353, 611.148193, -2018.574707, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[115][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[116][TileObject] = CreateDynamicObject(19353, 611.148193, -2021.775146, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[116][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[117][TileObject] = CreateDynamicObject(19353, 611.148193, -2024.984619, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[117][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[118][TileObject] = CreateDynamicObject(19353, 611.148193, -2028.194702, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[118][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[119][TileObject] = CreateDynamicObject(19353, 611.148193, -2031.404174, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[119][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[120][TileObject] = CreateDynamicObject(19353, 611.148193, -2034.615112, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[120][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[121][TileObject] = CreateDynamicObject(19353, 611.148193, -2037.824584, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[121][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[122][TileObject] = CreateDynamicObject(19353, 611.148193, -2041.034667, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[122][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[123][TileObject] = CreateDynamicObject(19353, 611.148193, -2044.244140, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[123][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[124][TileObject] = CreateDynamicObject(19353, 611.148193, -2047.453857, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[124][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[125][TileObject] = CreateDynamicObject(19353, 611.148193, -2050.663330, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[125][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[126][TileObject] = CreateDynamicObject(19353, 607.647644, -2050.663330, 39.107166, 0.000007, 89.999992, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[126][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[127][TileObject] = CreateDynamicObject(19353, 607.647644, -2047.453857, 39.107166, 0.000007, 89.999992, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[127][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[128][TileObject] = CreateDynamicObject(19353, 607.647644, -2044.243774, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[128][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[129][TileObject] = CreateDynamicObject(19353, 607.647644, -2041.034301, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[129][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[130][TileObject] = CreateDynamicObject(19353, 607.647644, -2037.823364, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[130][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[131][TileObject] = CreateDynamicObject(19353, 607.647644, -2034.613891, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[131][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[132][TileObject] = CreateDynamicObject(19353, 607.647644, -2031.403808, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[132][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[133][TileObject] = CreateDynamicObject(19353, 607.647644, -2028.194335, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[133][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[134][TileObject] = CreateDynamicObject(19353, 607.647644, -2024.993896, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[134][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[135][TileObject] = CreateDynamicObject(19353, 607.647644, -2021.784423, 39.107166, 0.000007, 90.000000, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[135][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[136][TileObject] = CreateDynamicObject(19353, 607.647644, -2018.574340, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[136][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[137][TileObject] = CreateDynamicObject(19353, 607.647644, -2015.364868, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[137][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[138][TileObject] = CreateDynamicObject(19353, 607.647644, -2012.153930, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[138][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[139][TileObject] = CreateDynamicObject(19353, 607.647644, -2008.944458, 39.107166, 0.000007, 90.000007, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[139][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[140][TileObject] = CreateDynamicObject(19353, 607.647644, -2005.734375, 39.107166, 0.000007, 90.000015, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[140][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[141][TileObject] = CreateDynamicObject(19353, 607.647644, -2002.524902, 39.107166, 0.000007, 90.000015, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[141][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[142][TileObject] = CreateDynamicObject(19353, 607.647644, -1999.315185, 39.107166, 0.000007, 90.000022, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[142][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[143][TileObject] = CreateDynamicObject(19353, 607.647644, -1996.105712, 39.107166, 0.000007, 90.000022, 179.999832, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[143][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[144][TileObject] = CreateDynamicObject(19353, 604.148803, -1996.105712, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[144][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[145][TileObject] = CreateDynamicObject(19353, 604.148803, -1999.315185, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[145][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[146][TileObject] = CreateDynamicObject(19353, 604.148803, -2002.525268, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[146][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[147][TileObject] = CreateDynamicObject(19353, 604.148803, -2005.734741, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[147][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[148][TileObject] = CreateDynamicObject(19353, 604.148803, -2008.945678, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[148][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[149][TileObject] = CreateDynamicObject(19353, 604.148803, -2012.155151, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[149][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[150][TileObject] = CreateDynamicObject(19353, 604.148803, -2015.365234, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[150][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[151][TileObject] = CreateDynamicObject(19353, 604.148803, -2018.574707, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[151][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[152][TileObject] = CreateDynamicObject(19353, 604.148803, -2021.775146, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[152][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[153][TileObject] = CreateDynamicObject(19353, 604.148803, -2024.984619, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[153][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[154][TileObject] = CreateDynamicObject(19353, 604.148803, -2028.194702, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[154][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[155][TileObject] = CreateDynamicObject(19353, 604.148803, -2031.404174, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[155][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[156][TileObject] = CreateDynamicObject(19353, 604.148803, -2034.615112, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[156][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[157][TileObject] = CreateDynamicObject(19353, 604.148803, -2037.824584, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[157][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[158][TileObject] = CreateDynamicObject(19353, 604.148803, -2041.034667, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[158][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[159][TileObject] = CreateDynamicObject(19353, 604.148803, -2044.244140, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[159][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[160][TileObject] = CreateDynamicObject(19353, 604.148803, -2047.453857, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[160][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[161][TileObject] = CreateDynamicObject(19353, 604.148803, -2050.663330, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[161][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[162][TileObject] = CreateDynamicObject(19353, 600.648254, -2050.663330, 39.107166, 0.000007, 89.999984, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[162][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[163][TileObject] = CreateDynamicObject(19353, 600.648254, -2047.453857, 39.107166, 0.000007, 89.999984, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[163][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[164][TileObject] = CreateDynamicObject(19353, 600.648254, -2044.243774, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[164][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[165][TileObject] = CreateDynamicObject(19353, 600.648254, -2041.034301, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[165][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[166][TileObject] = CreateDynamicObject(19353, 600.648254, -2037.823364, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[166][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[167][TileObject] = CreateDynamicObject(19353, 600.648254, -2034.613891, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[167][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[168][TileObject] = CreateDynamicObject(19353, 600.648254, -2031.403808, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[168][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[169][TileObject] = CreateDynamicObject(19353, 600.648254, -2028.194335, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[169][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[170][TileObject] = CreateDynamicObject(19353, 600.648254, -2024.993896, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[170][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[171][TileObject] = CreateDynamicObject(19353, 600.648254, -2021.784423, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[171][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[172][TileObject] = CreateDynamicObject(19353, 600.648254, -2018.574340, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[172][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[173][TileObject] = CreateDynamicObject(19353, 600.648254, -2015.364868, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[173][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[174][TileObject] = CreateDynamicObject(19353, 600.648254, -2012.153930, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[174][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[175][TileObject] = CreateDynamicObject(19353, 600.648254, -2008.944458, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[175][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[176][TileObject] = CreateDynamicObject(19353, 600.648254, -2005.734375, 39.107166, 0.000007, 90.000007, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[176][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[177][TileObject] = CreateDynamicObject(19353, 600.648254, -2002.524902, 39.107166, 0.000007, 90.000007, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[177][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[178][TileObject] = CreateDynamicObject(19353, 600.648254, -1999.315185, 39.107166, 0.000007, 90.000015, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[178][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[179][TileObject] = CreateDynamicObject(19353, 600.648254, -1996.105712, 39.107166, 0.000007, 90.000015, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[179][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[180][TileObject] = CreateDynamicObject(19353, 597.149780, -1996.105712, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[180][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[181][TileObject] = CreateDynamicObject(19353, 597.149780, -1999.315185, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[181][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[182][TileObject] = CreateDynamicObject(19353, 597.149780, -2002.525268, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[182][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[183][TileObject] = CreateDynamicObject(19353, 597.149780, -2005.734741, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[183][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[184][TileObject] = CreateDynamicObject(19353, 597.149780, -2008.945678, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[184][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[185][TileObject] = CreateDynamicObject(19353, 597.149780, -2012.155151, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[185][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[186][TileObject] = CreateDynamicObject(19353, 597.149780, -2015.365234, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[186][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[187][TileObject] = CreateDynamicObject(19353, 597.149780, -2018.574707, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[187][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[188][TileObject] = CreateDynamicObject(19353, 597.149780, -2021.775146, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[188][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[189][TileObject] = CreateDynamicObject(19353, 597.149780, -2024.984619, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[189][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[190][TileObject] = CreateDynamicObject(19353, 597.149780, -2028.194702, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[190][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[191][TileObject] = CreateDynamicObject(19353, 597.149780, -2031.404174, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[191][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[192][TileObject] = CreateDynamicObject(19353, 597.149780, -2034.615112, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[192][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[193][TileObject] = CreateDynamicObject(19353, 597.149780, -2037.824584, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[193][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[194][TileObject] = CreateDynamicObject(19353, 597.149780, -2041.034667, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[194][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[195][TileObject] = CreateDynamicObject(19353, 597.149780, -2044.244140, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[195][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[196][TileObject] = CreateDynamicObject(19353, 597.149780, -2047.453857, 39.107166, 0.000000, 90.000053, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[196][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[197][TileObject] = CreateDynamicObject(19353, 597.149780, -2050.663330, 39.107166, 0.000000, 90.000053, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[197][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[198][TileObject] = CreateDynamicObject(19353, 593.649230, -2050.663330, 39.107166, 0.000007, 89.999977, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[198][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[199][TileObject] = CreateDynamicObject(19353, 593.649230, -2047.453857, 39.107166, 0.000007, 89.999977, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[199][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[200][TileObject] = CreateDynamicObject(19353, 593.649230, -2044.243774, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[200][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[201][TileObject] = CreateDynamicObject(19353, 593.649230, -2041.034301, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[201][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[202][TileObject] = CreateDynamicObject(19353, 593.649230, -2037.823364, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[202][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[203][TileObject] = CreateDynamicObject(19353, 593.649230, -2034.613891, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[203][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[204][TileObject] = CreateDynamicObject(19353, 593.649230, -2031.403808, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[204][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[205][TileObject] = CreateDynamicObject(19353, 593.649230, -2028.194335, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[205][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[206][TileObject] = CreateDynamicObject(19353, 593.649230, -2024.993896, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[206][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[207][TileObject] = CreateDynamicObject(19353, 593.649230, -2021.784423, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[207][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[208][TileObject] = CreateDynamicObject(19353, 593.649230, -2018.574340, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[208][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[209][TileObject] = CreateDynamicObject(19353, 593.649230, -2015.364868, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[209][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[210][TileObject] = CreateDynamicObject(19353, 593.649230, -2012.153930, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[210][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[211][TileObject] = CreateDynamicObject(19353, 593.649230, -2008.944458, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[211][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[212][TileObject] = CreateDynamicObject(19353, 593.649230, -2005.734375, 39.107166, 0.000007, 90.000000, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[212][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[213][TileObject] = CreateDynamicObject(19353, 593.649230, -2002.524902, 39.107166, 0.000007, 90.000000, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[213][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[214][TileObject] = CreateDynamicObject(19353, 593.649230, -1999.315185, 39.107166, 0.000007, 90.000007, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[214][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[215][TileObject] = CreateDynamicObject(19353, 593.649230, -1996.105712, 39.107166, 0.000007, 90.000007, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[215][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[216][TileObject] = CreateDynamicObject(19353, 590.149047, -1996.105712, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[216][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[217][TileObject] = CreateDynamicObject(19353, 590.149047, -1999.315185, 39.107166, 0.000000, 90.000015, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[217][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[218][TileObject] = CreateDynamicObject(19353, 590.149047, -2002.525268, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[218][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[219][TileObject] = CreateDynamicObject(19353, 590.149047, -2005.734741, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[219][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[220][TileObject] = CreateDynamicObject(19353, 590.149047, -2008.945678, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[220][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[221][TileObject] = CreateDynamicObject(19353, 590.149047, -2012.155151, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[221][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[222][TileObject] = CreateDynamicObject(19353, 590.149047, -2015.365234, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[222][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[223][TileObject] = CreateDynamicObject(19353, 590.149047, -2018.574707, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[223][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[224][TileObject] = CreateDynamicObject(19353, 590.149047, -2021.775146, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[224][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[225][TileObject] = CreateDynamicObject(19353, 590.149047, -2024.984619, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[225][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[226][TileObject] = CreateDynamicObject(19353, 590.149047, -2028.194702, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[226][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[227][TileObject] = CreateDynamicObject(19353, 590.149047, -2031.404174, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[227][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[228][TileObject] = CreateDynamicObject(19353, 590.149047, -2034.615112, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[228][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[229][TileObject] = CreateDynamicObject(19353, 590.149047, -2037.824584, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[229][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[230][TileObject] = CreateDynamicObject(19353, 590.149047, -2041.034667, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[230][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[231][TileObject] = CreateDynamicObject(19353, 590.149047, -2044.244140, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[231][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[232][TileObject] = CreateDynamicObject(19353, 590.149047, -2047.453857, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[232][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[233][TileObject] = CreateDynamicObject(19353, 590.149047, -2050.663330, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[233][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[234][TileObject] = CreateDynamicObject(19353, 586.648498, -2050.663330, 39.107166, 0.000007, 89.999984, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[234][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[235][TileObject] = CreateDynamicObject(19353, 586.648498, -2047.453857, 39.107166, 0.000007, 89.999984, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[235][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[236][TileObject] = CreateDynamicObject(19353, 586.648498, -2044.243774, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[236][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[237][TileObject] = CreateDynamicObject(19353, 586.648498, -2041.034301, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[237][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[238][TileObject] = CreateDynamicObject(19353, 586.648498, -2037.823364, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[238][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[239][TileObject] = CreateDynamicObject(19353, 586.648498, -2034.613891, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[239][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[240][TileObject] = CreateDynamicObject(19353, 586.648498, -2031.403808, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[240][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[241][TileObject] = CreateDynamicObject(19353, 586.648498, -2028.194335, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[241][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[242][TileObject] = CreateDynamicObject(19353, 586.648498, -2024.993896, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[242][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[243][TileObject] = CreateDynamicObject(19353, 586.648498, -2021.784423, 39.107166, 0.000007, 89.999992, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[243][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[244][TileObject] = CreateDynamicObject(19353, 586.648498, -2018.574340, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[244][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[245][TileObject] = CreateDynamicObject(19353, 586.648498, -2015.364868, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[245][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[246][TileObject] = CreateDynamicObject(19353, 586.648498, -2012.153930, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[246][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[247][TileObject] = CreateDynamicObject(19353, 586.648498, -2008.944458, 39.107166, 0.000007, 90.000000, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[247][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[248][TileObject] = CreateDynamicObject(19353, 586.648498, -2005.734375, 39.107166, 0.000007, 90.000007, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[248][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[249][TileObject] = CreateDynamicObject(19353, 586.648498, -2002.524902, 39.107166, 0.000007, 90.000007, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[249][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[250][TileObject] = CreateDynamicObject(19353, 586.648498, -1999.315185, 39.107166, 0.000007, 90.000015, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[250][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[251][TileObject] = CreateDynamicObject(19353, 586.648498, -1996.105712, 39.107166, 0.000007, 90.000015, 179.999786, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[251][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[252][TileObject] = CreateDynamicObject(19353, 583.149658, -1996.105712, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[252][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[253][TileObject] = CreateDynamicObject(19353, 583.149658, -1999.315185, 39.107166, 0.000000, 90.000022, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[253][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[254][TileObject] = CreateDynamicObject(19353, 583.149658, -2002.525268, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[254][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[255][TileObject] = CreateDynamicObject(19353, 583.149658, -2005.734741, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[255][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[256][TileObject] = CreateDynamicObject(19353, 583.149658, -2008.945678, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[256][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[257][TileObject] = CreateDynamicObject(19353, 583.149658, -2012.155151, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[257][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[258][TileObject] = CreateDynamicObject(19353, 583.149658, -2015.365234, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[258][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[259][TileObject] = CreateDynamicObject(19353, 583.149658, -2018.574707, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[259][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[260][TileObject] = CreateDynamicObject(19353, 583.149658, -2021.775146, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[260][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[261][TileObject] = CreateDynamicObject(19353, 583.149658, -2024.984619, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[261][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[262][TileObject] = CreateDynamicObject(19353, 583.149658, -2028.194702, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[262][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[263][TileObject] = CreateDynamicObject(19353, 583.149658, -2031.404174, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[263][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[264][TileObject] = CreateDynamicObject(19353, 583.149658, -2034.615112, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[264][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[265][TileObject] = CreateDynamicObject(19353, 583.149658, -2037.824584, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[265][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[266][TileObject] = CreateDynamicObject(19353, 583.149658, -2041.034667, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[266][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[267][TileObject] = CreateDynamicObject(19353, 583.149658, -2044.244140, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[267][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[268][TileObject] = CreateDynamicObject(19353, 583.149658, -2047.453857, 39.107166, 0.000000, 90.000053, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[268][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[269][TileObject] = CreateDynamicObject(19353, 583.149658, -2050.663330, 39.107166, 0.000000, 90.000053, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[269][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[270][TileObject] = CreateDynamicObject(19353, 579.649108, -2050.663330, 39.107166, 0.000007, 89.999977, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[270][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[271][TileObject] = CreateDynamicObject(19353, 579.649108, -2047.453857, 39.107166, 0.000007, 89.999977, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[271][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[272][TileObject] = CreateDynamicObject(19353, 579.649108, -2044.243774, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[272][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[273][TileObject] = CreateDynamicObject(19353, 579.649108, -2041.034301, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[273][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[274][TileObject] = CreateDynamicObject(19353, 579.649108, -2037.823364, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[274][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[275][TileObject] = CreateDynamicObject(19353, 579.649108, -2034.613891, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[275][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[276][TileObject] = CreateDynamicObject(19353, 579.649108, -2031.403808, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[276][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[277][TileObject] = CreateDynamicObject(19353, 579.649108, -2028.194335, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[277][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[278][TileObject] = CreateDynamicObject(19353, 579.649108, -2024.993896, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[278][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[279][TileObject] = CreateDynamicObject(19353, 579.649108, -2021.784423, 39.107166, 0.000007, 89.999984, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[279][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[280][TileObject] = CreateDynamicObject(19353, 579.649108, -2018.574340, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[280][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[281][TileObject] = CreateDynamicObject(19353, 579.649108, -2015.364868, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[281][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[282][TileObject] = CreateDynamicObject(19353, 579.649108, -2012.153930, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[282][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[283][TileObject] = CreateDynamicObject(19353, 579.649108, -2008.944458, 39.107166, 0.000007, 89.999992, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[283][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[284][TileObject] = CreateDynamicObject(19353, 579.649108, -2005.734375, 39.107166, 0.000007, 90.000000, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[284][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[285][TileObject] = CreateDynamicObject(19353, 579.649108, -2002.524902, 39.107166, 0.000007, 90.000000, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[285][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[286][TileObject] = CreateDynamicObject(19353, 579.649108, -1999.315185, 39.107166, 0.000007, 90.000007, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[286][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[287][TileObject] = CreateDynamicObject(19353, 579.649108, -1996.105712, 39.107166, 0.000007, 90.000007, 179.999740, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[287][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[288][TileObject] = CreateDynamicObject(19353, 576.150634, -1996.105712, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[288][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[289][TileObject] = CreateDynamicObject(19353, 576.150634, -1999.315185, 39.107166, 0.000000, 90.000030, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[289][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[290][TileObject] = CreateDynamicObject(19353, 576.150634, -2002.525268, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[290][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[291][TileObject] = CreateDynamicObject(19353, 576.150634, -2005.734741, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[291][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[292][TileObject] = CreateDynamicObject(19353, 576.150634, -2008.945678, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[292][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[293][TileObject] = CreateDynamicObject(19353, 576.150634, -2012.155151, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[293][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[294][TileObject] = CreateDynamicObject(19353, 576.150634, -2015.365234, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[294][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[295][TileObject] = CreateDynamicObject(19353, 576.150634, -2018.574707, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[295][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[296][TileObject] = CreateDynamicObject(19353, 576.150634, -2021.775146, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[296][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[297][TileObject] = CreateDynamicObject(19353, 576.150634, -2024.984619, 39.107166, 0.000000, 90.000038, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[297][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[298][TileObject] = CreateDynamicObject(19353, 576.150634, -2028.194702, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[298][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[299][TileObject] = CreateDynamicObject(19353, 576.150634, -2031.404174, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[299][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[300][TileObject] = CreateDynamicObject(19353, 576.150634, -2034.615112, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[300][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[301][TileObject] = CreateDynamicObject(19353, 576.150634, -2037.824584, 39.107166, 0.000000, 90.000045, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[301][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[302][TileObject] = CreateDynamicObject(19353, 576.150634, -2041.034667, 39.107166, 0.000000, 90.000053, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[302][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[303][TileObject] = CreateDynamicObject(19353, 576.150634, -2044.244140, 39.107166, 0.000000, 90.000053, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[303][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[304][TileObject] = CreateDynamicObject(19353, 576.150634, -2047.453857, 39.107166, 0.000000, 90.000061, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[304][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[305][TileObject] = CreateDynamicObject(19353, 576.150634, -2050.663330, 39.107166, 0.000000, 90.000061, 0.000000, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[305][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[306][TileObject] = CreateDynamicObject(19353, 572.650085, -2050.663330, 39.107166, 0.000007, 89.999969, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[306][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[307][TileObject] = CreateDynamicObject(19353, 572.650085, -2047.453857, 39.107166, 0.000007, 89.999969, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[307][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[308][TileObject] = CreateDynamicObject(19353, 572.650085, -2044.243774, 39.107166, 0.000007, 89.999977, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[308][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[309][TileObject] = CreateDynamicObject(19353, 572.650085, -2041.034301, 39.107166, 0.000007, 89.999977, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[309][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[310][TileObject] = CreateDynamicObject(19353, 572.650085, -2037.823364, 39.107166, 0.000007, 89.999977, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[310][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[311][TileObject] = CreateDynamicObject(19353, 572.650085, -2034.613891, 39.107166, 0.000007, 89.999977, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[311][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[312][TileObject] = CreateDynamicObject(19353, 572.650085, -2031.403808, 39.107166, 0.000007, 89.999984, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[312][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[313][TileObject] = CreateDynamicObject(19353, 572.650085, -2028.194335, 39.107166, 0.000007, 89.999984, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[313][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[314][TileObject] = CreateDynamicObject(19353, 572.650085, -2024.993896, 39.107166, 0.000007, 89.999977, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[314][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[315][TileObject] = CreateDynamicObject(19353, 572.650085, -2021.784423, 39.107166, 0.000007, 89.999977, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[315][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[316][TileObject] = CreateDynamicObject(19353, 572.650085, -2018.574340, 39.107166, 0.000007, 89.999984, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[316][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[317][TileObject] = CreateDynamicObject(19353, 572.650085, -2015.364868, 39.107166, 0.000007, 89.999984, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[317][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[318][TileObject] = CreateDynamicObject(19353, 572.650085, -2012.153930, 39.107166, 0.000007, 89.999984, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[318][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[319][TileObject] = CreateDynamicObject(19353, 572.650085, -2008.944458, 39.107166, 0.000007, 89.999984, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[319][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[320][TileObject] = CreateDynamicObject(19353, 572.650085, -2005.734375, 39.107166, 0.000007, 89.999992, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[320][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[321][TileObject] = CreateDynamicObject(19353, 572.650085, -2002.524902, 39.107166, 0.000007, 89.999992, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[321][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
    Event_FalloutInfo[322][TileObject] = CreateDynamicObject(19353, 572.650085, -1999.315185, 39.107166, 0.000007, 90.000000, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[322][TileObject], 0, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
    Event_FalloutInfo[323][TileObject] = CreateDynamicObject(19353, 572.650085, -1996.105712, 39.107166, 0.000007, 90.000000, 179.999694, 45, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(Event_FalloutInfo[323][TileObject], 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
}

JoinEventTDM(playerid)
{
    ResetPlayerWeapons(playerid);
    
    AccountData[playerid][pInEvent] = true;

    //saving player last status & position
    if(!AccountData[playerid][pIsUsingUniform])
        AccountData[playerid][pSkin] = GetPlayerSkin(playerid);
    AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
    AccountData[playerid][pInterior] = GetPlayerInterior(playerid);
    GetPlayerHealth(playerid, AccountData[playerid][pHealth]);
    GetPlayerArmour(playerid, AccountData[playerid][pArmor]);
    GetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
    GetPlayerFacingAngle(playerid, AccountData[playerid][pPos][3]);
    
    Anticheat[playerid][acImmunity] = gettime() + 5;

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

    if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
	{
		TogglePlayerControllable(AccountData[playerid][DraggingID], true);
		ShowTDN(AccountData[playerid][DraggingID], NOTIFICATION_INFO, "Anda sudah tidak lagi diseret/digendong.");
		AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
		AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
	}

    if(AccountData[playerid][pAdminDuty])
    {
        SetPlayerName(playerid, AccountData[playerid][pName]);
        AccountData[playerid][pAdminDuty] = false;

        if(DestroyDynamic3DTextLabel(AdminLabel[playerid]))
            AdminLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    //assign player team & event variables
    if(Iter_Count(EvRedTeam) <= Iter_Count(EvBlueTeam))
    {
        SetPlayerSkin(playerid, EventInfo[redSkin]);
        SetPlayerPos(playerid, EventInfo[redSpawn][0],EventInfo[redSpawn][1], EventInfo[redSpawn][2]);
        SetPlayerFacingAngle(playerid, EventInfo[redSpawn][3]);
        SetPlayerVirtualWorld(playerid, playerid+1);
        SetPlayerInterior(playerid, EventInfo[arenaIntid]);
        TogglePlayerControllable(playerid, false);
        SetPlayerTeam(playerid, 1);
        SetPlayerColor(playerid, 0xFF0000FF);
        Iter_Add(EvRedTeam, playerid);

        SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda berhasil berpartisipasi sebagai "RED"Red Team!");
    }
    else
    {
        SetPlayerSkin(playerid, EventInfo[blueSkin]);
        SetPlayerPos(playerid, EventInfo[blueSpawn][0],EventInfo[blueSpawn][1], EventInfo[blueSpawn][2]);
        SetPlayerFacingAngle(playerid, EventInfo[blueSpawn][3]);
        SetPlayerVirtualWorld(playerid, playerid+1);
        SetPlayerInterior(playerid, EventInfo[arenaIntid]);
        TogglePlayerControllable(playerid, false);
        SetPlayerTeam(playerid, 2);
        SetPlayerColor(playerid, 0x009DC4FF);
        Iter_Add(EvBlueTeam, playerid);

        SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda berhasil berpartisipasi sebagai {009dc4}Blue Team!");
    }
    Iter_Add(InEvent, playerid);

    SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Gunakan "RED"'/event leave' "YELLOW"untuk meninggalkan arena, "RED"'/killme' "YELLOW"jika stuck/berada di luar arena!");
    return 1;
}

JoinEventRace(playerid)
{
    ResetPlayerWeapons(playerid);
    
    AccountData[playerid][pInEvent] = true;

    DisableRemoteVehicleCollisions(playerid, true);

    //saving player last status & position
    if(!AccountData[playerid][pIsUsingUniform])
        AccountData[playerid][pSkin] = GetPlayerSkin(playerid);
    AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
    AccountData[playerid][pInterior] = GetPlayerInterior(playerid);
    GetPlayerHealth(playerid, AccountData[playerid][pHealth]);
    GetPlayerArmour(playerid, AccountData[playerid][pArmor]);
    GetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
    GetPlayerFacingAngle(playerid, AccountData[playerid][pPos][3]);
    
    Anticheat[playerid][acImmunity] = gettime() + 5;

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

    if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
	{
		TogglePlayerControllable(AccountData[playerid][DraggingID], true);
		ShowTDN(AccountData[playerid][DraggingID], NOTIFICATION_INFO, "Anda sudah tidak lagi diseret/digendong.");
		AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
		AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
	}

    if(AccountData[playerid][pAdminDuty])
    {
        SetPlayerName(playerid, AccountData[playerid][pName]);
        AccountData[playerid][pAdminDuty] = false;

        if(DestroyDynamic3DTextLabel(AdminLabel[playerid]))
            AdminLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    ResetAllRaceCP(playerid);

    SetPlayerVirtualWorld(playerid, playerid+1);
    SetPlayerInterior(playerid, EventInfo[arenaIntid]);

    EventVehicle[playerid] = CreateVehicle(EventInfo[raceVehicle], EventInfo[raceSpawn][0],EventInfo[raceSpawn][1], EventInfo[raceSpawn][2], EventInfo[raceSpawn][3], random(255), random(255), 60000, false);
    VehicleCore[EventVehicle[playerid]][vCoreFuel] = 100;
    SetValidVehicleHealth(EventVehicle[playerid], 2000.0); 
    VehicleCore[EventVehicle[playerid]][vMaxHealth] = 2000.0;
    VehicleCore[EventVehicle[playerid]][vIsBodyUpgraded] = true;
    VehicleCore[EventVehicle[playerid]][vIsBodyBroken] = false;
    VehicleCore[EventVehicle[playerid]][vCoreLocked] = false;
    SwitchVehicleEngine(EventVehicle[playerid], true);
    SwitchVehicleDoors(EventVehicle[playerid], false);
    SetVehicleVirtualWorldEx(EventVehicle[playerid], playerid+1);
    LinkVehicleToInterior(EventVehicle[playerid], EventInfo[arenaIntid]);
    PutPlayerInVehicleEx(playerid, EventVehicle[playerid], 0);
    TogglePlayerControllable(playerid, false);
    SetPlayerColor(playerid, 0x00FF00FF);

    SetVehicleParamsEx(EventVehicle[playerid], 1, 1, 0, 0, 0, 0, 0);
    SetVehicleNumberPlate(EventVehicle[playerid], ""RED"EVENT");

    AccountData[playerid][pRaceEventStep] = 0;

    if(!isnull(EventInfo[eventMusic]))
        PlayAudioStreamForPlayer(playerid, EventInfo[eventMusic]);

    SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda berhasil berpartisipasi ke dalam event racing!");

    Iter_Add(InEvent, playerid);

    SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Gunakan "RED"'/event leave' "YELLOW"untuk meninggalkan arena!");
    return 1;
}

JoinEventZombie(playerid)
{
    ResetPlayerWeapons(playerid);
    
    AccountData[playerid][pInEvent] = true;

    //saving player last status & position
    if(!AccountData[playerid][pIsUsingUniform])
        AccountData[playerid][pSkin] = GetPlayerSkin(playerid);
    AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
    AccountData[playerid][pInterior] = GetPlayerInterior(playerid);
    GetPlayerHealth(playerid, AccountData[playerid][pHealth]);
    GetPlayerArmour(playerid, AccountData[playerid][pArmor]);
    GetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
    GetPlayerFacingAngle(playerid, AccountData[playerid][pPos][3]);
    
    Anticheat[playerid][acImmunity] = gettime() + 5;

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

    if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
	{
		TogglePlayerControllable(AccountData[playerid][DraggingID], true);
		ShowTDN(AccountData[playerid][DraggingID], NOTIFICATION_INFO, "Anda sudah tidak lagi diseret/digendong.");
		AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
		AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
	}

    if(AccountData[playerid][pAdminDuty])
    {
        SetPlayerName(playerid, AccountData[playerid][pName]);
        AccountData[playerid][pAdminDuty] = false;

        if(DestroyDynamic3DTextLabel(AdminLabel[playerid]))
            AdminLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    //assign player event stats
    SetPlayerPos(playerid, EventInfo[humanSpawn][0],EventInfo[humanSpawn][1], EventInfo[humanSpawn][2]);
    SetPlayerFacingAngle(playerid, EventInfo[humanSpawn][3]);
    SetPlayerVirtualWorld(playerid, playerid+1);
    SetPlayerInterior(playerid, 0);
    SetPlayerTeam(playerid, 1);
    SetPlayerColor(playerid, 0x00FF00FF);
    Iter_Add(EvHumanTeam, playerid);
    Iter_Add(InEvent, playerid);

    new max_X, min_X, max_Y, min_Y;
    max_X = max(floatround(EventInfo[boundPoint1][0]), floatround(EventInfo[boundPoint2][0]));
    min_X = min(floatround(EventInfo[boundPoint1][0]), floatround(EventInfo[boundPoint2][0]));
    min_Y = min(floatround(EventInfo[boundPoint1][1]), floatround(EventInfo[boundPoint2][1]));
    max_Y = max(floatround(EventInfo[boundPoint1][1]), floatround(EventInfo[boundPoint2][1]));

    SetPlayerWorldBounds(playerid, max_X, min_X, max_Y, min_Y);
    GangZoneShowForPlayer(playerid, EventInfo[zombieZone1], 0xFF0000B3);
    GangZoneShowForPlayer(playerid, EventInfo[zombieZone2], 0xFFFFFF66);

    SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda berhasil berpartisipasi di Event Zombie Survival!");
    SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Gunakan "RED"'/event leave' "YELLOW"untuk meninggalkan arena!");
    return 1;
}

JoinEventFallout(playerid)
{
    ResetPlayerWeapons(playerid);
    
    AccountData[playerid][pInEvent] = true;

    //saving player last status & position
    if(!AccountData[playerid][pIsUsingUniform])
        AccountData[playerid][pSkin] = GetPlayerSkin(playerid);
    AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
    AccountData[playerid][pInterior] = GetPlayerInterior(playerid);
    GetPlayerHealth(playerid, AccountData[playerid][pHealth]);
    GetPlayerArmour(playerid, AccountData[playerid][pArmor]);
    GetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
    GetPlayerFacingAngle(playerid, AccountData[playerid][pPos][3]);
    
    Anticheat[playerid][acImmunity] = gettime() + 5;

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

    if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
	{
		TogglePlayerControllable(AccountData[playerid][DraggingID], true);
		ShowTDN(AccountData[playerid][DraggingID], NOTIFICATION_INFO, "Anda sudah tidak lagi diseret/digendong.");
		AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
		AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
	}

    if(AccountData[playerid][pAdminDuty])
    {
        SetPlayerName(playerid, AccountData[playerid][pName]);
        AccountData[playerid][pAdminDuty] = false;

        if(DestroyDynamic3DTextLabel(AdminLabel[playerid]))
            AdminLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    //assign player event stats
    new randsx = random(sizeof(falloutRandSpawn));
    SetPlayerPos(playerid, falloutRandSpawn[randsx][0], falloutRandSpawn[randsx][1], falloutRandSpawn[randsx][2]+0.75);
    SetPlayerFacingAngle(playerid, falloutRandSpawn[randsx][3]);
    SetPlayerVirtualWorld(playerid, 45);
    SetPlayerInterior(playerid, 0);
    SetPlayerColor(playerid, 0x00FF00FF);
    Iter_Add(InEvent, playerid);

    TogglePlayerControllable(playerid, false);

    SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda berhasil berpartisipasi di Event Chess Fall, bertahanlah hingga akhir!");
    SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Gunakan "RED"'/event leave' "YELLOW"untuk meninggalkan arena!");
    return 1;
}

JoinEventSquidGame(playerid)
{
    ResetPlayerWeapons(playerid);
    
    AccountData[playerid][pInEvent] = true;

    //saving player last status & position
    if(!AccountData[playerid][pIsUsingUniform])
        AccountData[playerid][pSkin] = GetPlayerSkin(playerid);
    AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
    AccountData[playerid][pInterior] = GetPlayerInterior(playerid);
    GetPlayerHealth(playerid, AccountData[playerid][pHealth]);
    GetPlayerArmour(playerid, AccountData[playerid][pArmor]);
    GetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
    GetPlayerFacingAngle(playerid, AccountData[playerid][pPos][3]);
    
    Anticheat[playerid][acImmunity] = gettime() + 5;

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

    if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
	{
		TogglePlayerControllable(AccountData[playerid][DraggingID], true);
		ShowTDN(AccountData[playerid][DraggingID], NOTIFICATION_INFO, "Anda sudah tidak lagi diseret/digendong.");
		AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
		AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
	}

    if(AccountData[playerid][pAdminDuty])
    {
        SetPlayerName(playerid, AccountData[playerid][pName]);
        AccountData[playerid][pAdminDuty] = false;

        if(DestroyDynamic3DTextLabel(AdminLabel[playerid]))
            AdminLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    //assign player event stats
    new randsx = random(sizeof(squidgameRandSpawn));
    SetPlayerPos(playerid, squidgameRandSpawn[randsx][0], squidgameRandSpawn[randsx][1], squidgameRandSpawn[randsx][2]+0.75);
    SetPlayerFacingAngle(playerid, squidgameRandSpawn[randsx][3]);
    SetPlayerVirtualWorld(playerid, 25);
    SetPlayerInterior(playerid, 0);
    SetPlayerColor(playerid, 0x00FF00FF);
    Iter_Add(InEvent, playerid);

    SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Anda berhasil berpartisipasi di Event Squid Game, bertahanlah hingga akhir!");
    SendClientMessage(playerid, X11_YELLOW, "[OOC Event] Gunakan "RED"'/event leave' "YELLOW"untuk meninggalkan arena!");
    return 1;
}

forward SwitchingLight();
public SwitchingLight()
{
    if(!EventInfo[eventStarted]) return 0;

    if(EventInfo[SGLightRed]) //jika sedang red maka dihijaukan
    {
        TextDrawSetString(Event_SGTD, "GREEN LIGHT");
        TextDrawBoxColor(Event_SGTD, 0x00FF00FF);
        foreach(new i : InEvent)
        {
            TextDrawShowForPlayer(i, Event_SGTD);
            PlayAudioStreamForPlayer(i, "http://103.178.153.173/kokoasm.mp3");
        }
        SetTimer("SwitchingLight", 5050, false);
        EventInfo[SGLightRed] = false;
    }
    else
    {
        EventInfo[SGLightRed] = true;
        TextDrawSetString(Event_SGTD, "RED LIGHT");
        TextDrawBoxColor(Event_SGTD, 0xFF0000FF);

        foreach(new i : InEvent)
        {
            StopAudioStreamForPlayer(i);
            TextDrawShowForPlayer(i, Event_SGTD);
        }
        SetTimer("SwitchingLight", 5000, false);
    }
    return 1;
}

forward LeaveEvent(playerid);
public LeaveEvent(playerid)
{
    ResetPlayerWeapons(playerid);
    AccountData[playerid][pInEvent] = false;

    SetPlayerHealth(playerid, AccountData[playerid][pHealth]);

    Anticheat[playerid][acArmorTime] = gettime() + 11;
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

    DestroyVehicle(EventVehicle[playerid]);

    AccountData[playerid][pRaceEventStep] = -1;

    if(DestroyDynamicRaceCP(EventRaceRCP[playerid]))
        EventRaceRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

    //return player saved status before joining event
    TextDrawHideForPlayer(playerid, GlobalFooterTD);
    SetPlayerColor(playerid, 0xFFFFFFFF);

    TextDrawHideForPlayer(playerid, Event_SGTD);

    DisableRemoteVehicleCollisions(playerid, false);

    StopAudioStreamForPlayer(playerid);

    if(AccountData[playerid][pKnockdown])
    {
        HideKnockTD(playerid);
        SetPlayerHealthEx(playerid, 100.0);
        AccountData[playerid][pKnockdown] = false;
        AccountData[playerid][pKnockdownTime] = 0;
        AccountData[playerid][pHunger] = 50;
        AccountData[playerid][pThirst] = 50;
        AccountData[playerid][pStress] = 0;
    }

    SetPlayerWorldBounds(playerid, 20000.0000, -20000.0000, 20000.0000, -20000.0000);
    GangZoneHideForPlayer(playerid, EventInfo[zombieZone1]);
    GangZoneHideForPlayer(playerid, EventInfo[zombieZone2]);
    pZombieClass[playerid] = 0;

    if(!AccountData[playerid][pIsUsingUniform])
        SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], AccountData[playerid][pPos][3], 0, 0, 0, 0, 0, 0);
    else
        SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pUniform], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], AccountData[playerid][pPos][3], 0, 0, 0, 0, 0, 0);
    pAllowSpawn[playerid] = true;
    SpawnPlayer(playerid);
}

forward ResetEvent();
public ResetEvent()
{
    EventInfo[redSkin] = 167;
    EventInfo[redHealth] = 100.00;
    EventInfo[redArmour] = 100.00;

    EventInfo[redSpawn][0] = 0.0;
    EventInfo[redSpawn][1] = 0.0;
    EventInfo[redSpawn][2] = 0.0;
    EventInfo[redSpawn][3] = 0.0;

    EventInfo[redWeapon][0] = 24;
    EventInfo[redWeapon][1] = 27;
    EventInfo[redWeapon][2] = 31;

    EventInfo[redTeamScore] = 0;

    EventInfo[blueSkin] = 16;
    EventInfo[blueHealth] = 100.00;
    EventInfo[blueArmour] = 100.00;

    EventInfo[blueSpawn][0] = 0.0;
    EventInfo[blueSpawn][1] = 0.0;
    EventInfo[blueSpawn][2] = 0.0;
    EventInfo[blueSpawn][3] = 0.0;

    EventInfo[blueWeapon][0] = 24;
    EventInfo[blueWeapon][1] = 27;
    EventInfo[blueWeapon][2] = 31;

    EventInfo[blueTeamScore] = 0;

    EventInfo[arenaVWID] = 45;
    EventInfo[arenaIntid] = 0;
    EventInfo[timeLimit] = 10*60;
    EventInfo[targetScore] = 100;
    EventInfo[maxPlayer] = 100;
    EventInfo[partPrize] = 500;
    EventInfo[winnerPrize] = 1500;

    EventInfo[eventStarted] = false;
    EventInfo[eventOpened] = false;
    EventInfo[eventOpentime] = 0;

    EventInfo[raceSpawn][0] = 0.0;
    EventInfo[raceSpawn][1] = 0.0;
    EventInfo[raceSpawn][2] = 0.0;
    EventInfo[raceSpawn][3] = 0.0;
    EventInfo[raceVehicle] = 560;
    EventInfo[eventType] = 0;
    EventInfo[racecWinners] = 0;
    EventInfo[raceEnding] = 0;
    EventInfo[raceShowVeh] = 0;
    EventInfo[eventMusic][0] = EOS;

    foreach(new rcpid : EvRaceCP)
    {
        EventRaceCP[rcpid][raceCPCoord][0] = 0.0;
        EventRaceCP[rcpid][raceCPCoord][1] = 0.0;
        EventRaceCP[rcpid][raceCPCoord][2] = 0.0;
    }

    EventInfo[zombieSpawn][0] = 0.0;
    EventInfo[zombieSpawn][1] = 0.0;
    EventInfo[zombieSpawn][2] = 0.0;
    EventInfo[zombieSpawn][3] = 0.0;
    EventInfo[humanSpawn][0] = 0.0;
    EventInfo[humanSpawn][1] = 0.0;
    EventInfo[humanSpawn][2] = 0.0;
    EventInfo[humanSpawn][3] = 0.0;
    EventInfo[boundPoint1][0] = 0.0;
    EventInfo[boundPoint1][1] = 0.0;
    EventInfo[boundPoint1][2] = 0.0;
    EventInfo[boundPoint2][0] = 0.0;
    EventInfo[boundPoint2][1] = 0.0;
    EventInfo[boundPoint2][2] = 0.0;

    Iter_Clear(InEvent);
    Iter_Clear(EvRedTeam);
    Iter_Clear(EvBlueTeam);
    Iter_Clear(EvRaceCP);
    Iter_Clear(EvHumanTeam);
    Iter_Clear(EvZombieTeam);
    Iter_Clear(AvailTiles);

    if(EventInfo[zombieZone1] != INVALID_GANG_ZONE)
    {
        GangZoneDestroy(EventInfo[zombieZone1]);
        EventInfo[zombieZone1] = INVALID_GANG_ZONE;
    }

    if(EventInfo[zombieZone2] != INVALID_GANG_ZONE)
    {
        GangZoneDestroy(EventInfo[zombieZone2]);
        EventInfo[zombieZone2] = INVALID_GANG_ZONE;
    }

    if(DestroyDynamicArea(EventInfo[zombieArea]))
        EventInfo[zombieArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    for(new x; x < 324; x++)
    {
        KillTimer(Event_FalloutInfo[x][shaketimer]);
        Event_FalloutInfo[x][shaketimer] = -1;

        Event_FalloutInfo[x][shakestep] = 0;

        if(DestroyDynamicObject(Event_FalloutInfo[x][TileObject]))
            Event_FalloutInfo[x][TileObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }

    if(DestroyDynamicObject(Event_SGGate))
        Event_SGGate = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(Event_SGFinish))
        Event_SGFinish = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    TextDrawHideForAll(Event_SGTD);

    foreach(new i : Player)
    {
        if((AccountData[i][pAdmin] >= 1 || AccountData[i][pSteward]) && AccountData[i][pSpawned])
        {
            SendClientMessage(i, Y_LIGHTRED, "AdmCmd: Lapangan event telah dibersihkan, semua telah direset!");
        }
    }
}

hook OnGameModeInit()
{
    new STREAMER_TAG_OBJECT: sgshtxt;
    sgshtxt = CreateDynamicObject(8172, 14.178329, 2527.419677, 13.693308, 0.000007, 270.000000, 89.999977, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    SetDynamicObjectMaterial(sgshtxt, 1, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    sgshtxt = CreateDynamicObject(8172, 14.178329, 2477.962402, 13.693308, -0.000007, 270.000000, -89.999977, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    SetDynamicObjectMaterial(sgshtxt, 1, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    sgshtxt = CreateDynamicObject(8172, 175.218597, 2527.419677, 13.693308, 0.000022, 270.000000, 89.999931, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    SetDynamicObjectMaterial(sgshtxt, 1, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    sgshtxt = CreateDynamicObject(8172, 175.218597, 2477.962402, 13.693308, -0.000022, 270.000000, -89.999931, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    SetDynamicObjectMaterial(sgshtxt, 1, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    sgshtxt = CreateDynamicObject(18981, -66.907066, 2490.152832, 20.895668, 0.000000, 0.000000, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 14668, "711c", "CJ_7_11_TILE", 0x00000000);
    sgshtxt = CreateDynamicObject(18981, -66.907066, 2515.151611, 20.895668, 0.000000, 0.000000, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 14668, "711c", "CJ_7_11_TILE", 0x00000000);
    sgshtxt = CreateDynamicObject(18981, 256.263183, 2490.152832, 20.895668, 0.000000, 0.000022, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 4829, "airport_las", "Grass_128HV", 0x00000000);
    sgshtxt = CreateDynamicObject(18981, 256.263183, 2515.151611, 20.895668, 0.000000, 0.000022, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 4829, "airport_las", "Grass_128HV", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, -29.665124, 2482.645507, 10.257443, 0.000000, 0.000022, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, -29.665124, 2492.245605, 10.257443, 0.000000, 0.000022, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, -29.665124, 2501.859619, 10.257443, 0.000000, 0.000029, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, -29.665124, 2511.459716, 10.257443, 0.000000, 0.000029, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, -29.665124, 2513.199951, 10.242050, 0.500786, 0.000037, -0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, -29.665124, 2522.803222, 10.262878, 0.000787, 0.000037, -0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(18981, 244.343139, 2515.151367, 15.241044, 0.300018, 90.000038, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 10101, "2notherbuildsfe", "sl_vicbrikwall01", 0x00000000);
    sgshtxt = CreateDynamicObject(18981, 244.343139, 2490.182617, 15.110306, 0.300018, 90.000038, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 10101, "2notherbuildsfe", "sl_vicbrikwall01", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, 227.284896, 2482.645507, 10.257443, 0.000000, 0.000000, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, 227.284896, 2492.245605, 10.257443, 0.000000, 0.000000, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, 227.284896, 2501.859619, 10.257443, 0.000000, 0.000007, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, 227.284896, 2511.459716, 10.257443, 0.000000, 0.000007, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, 227.284896, 2513.199951, 10.372051, 0.900786, 0.000014, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    sgshtxt = CreateDynamicObject(19379, 227.284896, 2522.799072, 10.522844, 0.900786, 0.000014, 0.000000, 25, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(sgshtxt, 0, 18646, "matcolours", "red-4", 0x00000000);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CreateDynamicObject(19129, 243.836929, 2517.592773, 15.760516, 0.299998, 0.000000, 0.000000, 25, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19129, 243.836929, 2487.912353, 15.605107, 0.299998, 0.000000, 0.000000, 25, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(658, 225.942733, 2503.114501, 15.441811, 0.000000, 0.000000, 0.000000, 25, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(14467, 223.351257, 2502.812255, 18.135559, 0.000000, 0.000000, 630.000000, 25, 0, -1, 200.00, 200.00); 
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(AccountData[playerid][pInEvent] && Iter_Contains(InEvent, playerid))
    {
        if(EventInfo[eventType] == 3 && EventInfo[eventStarted])
        {
            if(newkeys & KEY_JUMP && pZombieClass[playerid] == 2 && gettime() > pZombieAbilityCD[playerid] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                new Float:vpz[3];
                GetPlayerVelocity(playerid, vpz[0], vpz[1], vpz[2]);
                SetPlayerVelocity(playerid, vpz[0], vpz[1], vpz[2] + 1.25);

                pZombieAbilityCD[playerid] = gettime() + 5;
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pInEvent] && Iter_Contains(InEvent, playerid))
    {
        if(EventInfo[eventType] == 5 && EventInfo[eventStarted] && areaid == Event_SGFinish)
        {
            EventInfo[racecWinners]++;    
            if(EventInfo[racecWinners] == 1)
            {
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"telah sampai ke finish di "GREEN"posisi 1, "YELLOW"hadiah "DARKGREEN"$%s", AccountData[playerid][pName], FormatMoney(EventInfo[winnerPrize]));
                }
                GivePlayerMoneyEx(playerid, EventInfo[winnerPrize]);
            }
            else if(EventInfo[racecWinners] == 2)
            {
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"telah sampai ke finish di "GREEN"posisi 2, "YELLOW"hadiah "DARKGREEN"$%s", AccountData[playerid][pName], FormatMoney(floatround(EventInfo[winnerPrize] * 0.75)));
                }
                GivePlayerMoneyEx(playerid, floatround(EventInfo[winnerPrize] * 0.75));
            }
            else if(EventInfo[racecWinners] == 3)
            {
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"telah sampai ke finish di "GREEN"posisi 3, "YELLOW"hadiah "DARKGREEN"$%s", AccountData[playerid][pName], FormatMoney(floatround(EventInfo[winnerPrize] * 0.5)));
                }
                GivePlayerMoneyEx(playerid, floatround(EventInfo[winnerPrize] * 0.5));
            }
            else if(EventInfo[racecWinners] == 5)
            {
                EventInfo[timeLimit] = 0;
                EventInfo[raceEnding] = 30;
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"telah sampai ke finish di "GREEN"posisi %d.", AccountData[playerid][pName], EventInfo[racecWinners]);
                    GameTextForPlayer(i, "Event selesai~n~~r~mengembalikan posisi:~n~30s", 1500, 6);
                }
            }
            else
            {
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"telah sampai ke finish di "GREEN"posisi %d.", AccountData[playerid][pName], EventInfo[racecWinners]);
                }
            }
            GivePlayerMoneyEx(playerid, EventInfo[partPrize]);
            SetTimerEx("LeaveEvent", 5000, false, "i", playerid);
            Iter_Remove(InEvent, playerid);
        }
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP: checkpointid)
{
    if(checkpointid == EventRaceRCP[playerid] && AccountData[playerid][pInEvent] && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new rcpid = AccountData[playerid][pRaceEventStep];

        if(DestroyDynamicRaceCP(EventRaceRCP[playerid]))
            EventRaceRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

        //finish
        if(EventRaceCP[rcpid+1][raceCPCoord][0] == 0.0 && EventRaceCP[rcpid+1][raceCPCoord][1] == 0.0 && EventRaceCP[rcpid+1][raceCPCoord][2] == 0.0)
        {
            EventInfo[racecWinners]++;
            
            if(EventInfo[racecWinners] == 1)
            {
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"has won "DARKGREEN"$%s "YELLOW"for finishing in "GREEN"1st place.", AccountData[playerid][pName], FormatMoney(EventInfo[winnerPrize]));
                }
                GivePlayerMoneyEx(playerid, EventInfo[winnerPrize]);
            }
            else if(EventInfo[racecWinners] == 2)
            {
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"has won "DARKGREEN"$%s "YELLOW"for finishing in "GREEN"2nd place.", AccountData[playerid][pName], FormatMoney(floatround(EventInfo[winnerPrize] * 0.75)));
                }
                GivePlayerMoneyEx(playerid, floatround(EventInfo[winnerPrize] * 0.75));
            }
            else if(EventInfo[racecWinners] == 3)
            {
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"has won "DARKGREEN"$%s "YELLOW"for finishing in "GREEN"3rd place.", AccountData[playerid][pName], FormatMoney(floatround(EventInfo[winnerPrize] * 0.5)));
                }
                GivePlayerMoneyEx(playerid, floatround(EventInfo[winnerPrize] * 0.5));
            }
            else if(EventInfo[racecWinners] == 5)
            {
                EventInfo[raceEnding] = 30;
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"has finished in "GREEN"%dth place.", AccountData[playerid][pName], EventInfo[racecWinners]);
                    GameTextForPlayer(i, "Event selesai~n~~r~mengembalikan posisi:~n~30s", 1500, 6);
                }
            }
            else
            {
                foreach(new i : InEvent)
                {
                    SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"has finished in "GREEN"%dth place.", AccountData[playerid][pName], EventInfo[racecWinners]);
                }
            }
            GivePlayerMoneyEx(playerid, EventInfo[partPrize]);
            SendClientMessageEx(playerid, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));
        
            ResetPlayerWeapons(playerid);

            if(Iter_Contains(EvBlueTeam, playerid))
                Iter_Remove(EvBlueTeam, playerid);
            
            if(Iter_Contains(EvRedTeam, playerid))
                Iter_Remove(EvRedTeam, playerid);
            
            if(Iter_Contains(InEvent, playerid))
                Iter_Remove(InEvent, playerid);

            LeaveEvent(playerid);

            SendClientMessage(playerid, -1, "[OOC Event] Anda akan keluar dari event, mohon tunggu hingga dikembalikan ke posisi semula.");

            PlayerPlaySound(playerid, 183, 0.0, 0.0, 0.0);
            GameTextForPlayer(playerid, "mission passed!~n~~w~respect+", 8900, 0);
            SetTimerEx("StopMissPassed", 8000, false, "i", playerid);
        }
        else
        {
            AccountData[playerid][pRaceEventStep]++;

            EventRaceRCP[playerid] = CreateDynamicRaceCP(0, EventRaceCP[AccountData[playerid][pRaceEventStep]][raceCPCoord][0], EventRaceCP[AccountData[playerid][pRaceEventStep]][raceCPCoord][1], EventRaceCP[AccountData[playerid][pRaceEventStep]][raceCPCoord][2], EventRaceCP[AccountData[playerid][pRaceEventStep]+1][raceCPCoord][0], EventRaceCP[AccountData[playerid][pRaceEventStep]+1][raceCPCoord][1], EventRaceCP[AccountData[playerid][pRaceEventStep]+1][raceCPCoord][2], 3.5, -1, -1, playerid, 10000.00, -1, 0);

            PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
        }
    }
    return 1;
}

task UpdateEvOpTime[1000]() 
{
    if(EventInfo[eventOpened])
    {
        if(EventInfo[eventOpentime] > 0)
        {
            EventInfo[eventOpentime]--;

            foreach(new p : InEvent)
            {
                GameTextForPlayer(p, sprintf("Mohon Tunggu~n~~r~%d detik", EventInfo[eventOpentime]), 1000, 6);
                PlayerPlaySound(p, 1137, 0.0, 0.0, 0.0);
            }

            if(EventInfo[eventType] == 1)
            {
                foreach(new d : InEvent)
                {
                    if(Iter_Contains(EvRedTeam, d))
                    {
                        if(GetPlayerDistanceFromPoint(d, EventInfo[redSpawn][0], EventInfo[redSpawn][1], EventInfo[redSpawn][2]) >= 3.0)
                        {
                            SetPlayerPos(d, EventInfo[redSpawn][0],EventInfo[redSpawn][1], EventInfo[redSpawn][2]);
                        }
                    }

                    if(Iter_Contains(EvBlueTeam, d))
                    {
                        if(GetPlayerDistanceFromPoint(d, EventInfo[blueSpawn][0], EventInfo[blueSpawn][1], EventInfo[blueSpawn][2]) >= 3.0)
                        {
                            SetPlayerPos(d, EventInfo[blueSpawn][0],EventInfo[blueSpawn][1], EventInfo[blueSpawn][2]);
                        }
                    }
                }
            }
            else if(EventInfo[eventType] == 2) //balap
            {
                foreach(new d : InEvent)
                {
                    if(GetPlayerDistanceFromPoint(d, EventInfo[raceSpawn][0], EventInfo[raceSpawn][1], EventInfo[raceSpawn][2]) >= 5.0)
                    {
                        if(Iter_Contains(Vehicle, EventVehicle[d]))
                        {
                            SetVehiclePos(EventVehicle[d], EventInfo[raceSpawn][0],EventInfo[raceSpawn][1], EventInfo[raceSpawn][2]);
                            SetVehicleZAngle(EventVehicle[d], EventInfo[raceSpawn][2]);
                        }
                    }
                }
            }
        }
        else
        {
            EventInfo[eventOpened] = false;
            EventInfo[eventStarted] = true;
            EventInfo[eventOpentime] = 0;
            
            if(EventInfo[eventType] == 1)
            {
                foreach(new i : InEvent)
                {
                    PlayerPlaySound(i, 3201, 0.0, 0.0, 0.0);
                    GameTextForPlayer(i, "~g~Lets go!", 6555, 6);
                    SetPlayerVirtualWorld(i, EventInfo[arenaVWID]);

                    if(Iter_Contains(EvRedTeam, i))
                    {
                        SetPlayerHealth(i, EventInfo[redHealth]);
                        Anticheat[i][acArmorTime] = gettime() + 11;
                        SetPlayerArmour(i, EventInfo[redArmour]);

                        GivePlayerWeapon(i, EventInfo[redWeapon][0], 700);
                        GivePlayerWeapon(i, EventInfo[redWeapon][1], 700);
                        GivePlayerWeapon(i, EventInfo[redWeapon][2], 700);
                    }

                    if(Iter_Contains(EvBlueTeam, i))
                    {
                        SetPlayerHealth(i, EventInfo[blueHealth]);
                        Anticheat[i][acArmorTime] = gettime() + 11;
                        SetPlayerArmour(i, EventInfo[blueArmour]);

                        GivePlayerWeapon(i, EventInfo[blueWeapon][0], 700);
                        GivePlayerWeapon(i, EventInfo[blueWeapon][1], 700);
                        GivePlayerWeapon(i, EventInfo[blueWeapon][2], 700);
                    }

                    TextDrawShowForPlayer(i, GlobalFooterTD);
                    TogglePlayerControllable(i, true);
                }
            }
            else if(EventInfo[eventType] == 2)
            {
                EventInfo[raceShowVeh] = 30;

                foreach(new i : InEvent)
                {
                    PlayerPlaySound(i, 3201, 0.0, 0.0, 0.0);
                    GameTextForPlayer(i, "Its lights out~n~and~n~~r~away we go!", 6555, 6);
                    TogglePlayerControllable(i, true);

                    new rcpid = AccountData[i][pRaceEventStep];
                    EventRaceRCP[i] = CreateDynamicRaceCP(0, EventRaceCP[rcpid][raceCPCoord][0], EventRaceCP[rcpid][raceCPCoord][1], EventRaceCP[rcpid][raceCPCoord][2], EventRaceCP[rcpid+1][raceCPCoord][0], EventRaceCP[rcpid+1][raceCPCoord][1], EventRaceCP[rcpid+1][raceCPCoord][2], 3.5, -1, -1, i, 10000.00, -1, 0);
                }
            }
            else if(EventInfo[eventType] == 3)
            {
                new Float:zombieRequired;
                zombieRequired = Iter_Count(InEvent) * 0.25;
                
                while(Iter_Count(EvZombieTeam) < floatround(zombieRequired))
                {
                    new zbid = Iter_Random(EvHumanTeam);
                    Iter_Remove(EvHumanTeam, zbid);

                    SetPlayerColor(zbid, 0xFF0000FF);
                    SetPlayerSkin(zbid, 162);
                    SetPlayerHealth(zbid, 105.00);

                    GivePlayerWeapon(zbid, 9, 1);

                    Anticheat[zbid][acImmunity] = gettime() + 5;
                    SetPlayerPos(zbid, EventInfo[zombieSpawn][0],EventInfo[zombieSpawn][1], EventInfo[zombieSpawn][2]);
                    SetPlayerTeam(zbid, 2);
                    SendClientMessage(zbid, X11_YELLOW, "[OOC Event] Anda telah terpilih menjadi "RED"Zombie!");

                    pZombieClass[zbid] = 0;

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
                                    SetPlayerSkin(zbid, 5);
                                    Anticheat[zbid][acArmorTime] = gettime() + 11;
                                    SetPlayerArmour(zbid, 254.00);
                                    pZombieClass[zbid] = 1;

                                    SendClientMessage(zbid, X11_YELLOW, "[OOC Event] Anda sekarang menjadi "RED"Zombie Badak, "YELLOW"darah sangat tebal!");
							        GameTextForPlayer(zbid, "~r~Zombie Badak~n~~b~darah tebal!", 6555, 3);
                                }
                                case 1: //cungkring
                                {
                                    SetPlayerSkin(zbid, 230);
                                    pZombieClass[zbid] = 2;

                                    SendClientMessage(zbid, X11_YELLOW, "[OOC Event] Anda sekarang menjadi "RED"Zombie Cungkring, "YELLOW"lompat sangat tinggi!");
							        GameTextForPlayer(zbid, "~r~Zombie Cungkring~n~~b~lompat tinggi!", 6555, 3);
                                }
                                case 2: //jihad
                                {
                                    SetPlayerSkin(zbid, 264);
                                    pZombieClass[zbid] = 3;

                                    SendClientMessage(zbid, X11_YELLOW, "[OOC Event] Anda sekarang menjadi "RED"Zombie Jihadis, "YELLOW"meledak ketika mati!");
							        GameTextForPlayer(zbid, "~r~Zombie Jihadis~n~~b~meledak ketika mati!", 6555, 3);
                                }
                            }
                        }
                    }

                    Iter_Add(EvZombieTeam, zbid);
                }

                foreach(new i : InEvent)
                {
                    Anticheat[i][acImmunity] = gettime() + 5;

                    PlayerPlaySound(i, 3201, 0.0, 0.0, 0.0);
                    GameTextForPlayer(i, "~b~Virus Datang!~n~~r~Zombie Telah Muncul!", 6555, 6);
                    SetPlayerVirtualWorld(i, EventInfo[arenaVWID]);

                    if(Iter_Contains(EvHumanTeam, i))
                    {
                        SetPlayerHealth(i, 100.00);
                        Anticheat[i][acArmorTime] = gettime() + 11;

                        GivePlayerWeapon(i, 24, 9999);
                        GivePlayerWeapon(i, 25, 9999);
                        GivePlayerWeapon(i, 31, 9999);

                        SendClientMessage(i, X11_YELLOW, "[OOC Event] Bertahanlah dari serangan "RED"Zombie "YELLOW"sampai akhir!");
                    }

                    TextDrawShowForPlayer(i, GlobalFooterTD);
                    TogglePlayerControllable(i, true);
                }
            }
            else if(EventInfo[eventType] == 4)
            {
                foreach(new i : InEvent)
                {
                    SetPlayerHealth(i, 100.00);
                    Anticheat[i][acArmorTime] = gettime() + 11;
                    SetPlayerArmour(i, 100.00);

                    PlayerPlaySound(i, 3201, 0.0, 0.0, 0.0);
                    GameTextForPlayer(i, "~b~Jadilah orang terakhir!", 6555, 6);
                    TogglePlayerControllable(i, true);
                }
            }
            else if(EventInfo[eventType] == 5)
            {
                if(DestroyDynamicObject(Event_SGGate))
                    Event_SGGate = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                
                TextDrawSetString(Event_SGTD, "GREEN LIGHT");
                TextDrawBoxColor(Event_SGTD, 0x00FF00FF);
                
                foreach(new i : InEvent)
                {
                    SetPlayerHealth(i, 100.00);
                    Anticheat[i][acArmorTime] = gettime() + 11;
                    SetPlayerArmour(i, 100.00);

                    PlayerPlaySound(i, 3201, 0.0, 0.0, 0.0);
                    GameTextForPlayer(i, "~y~Bergeraklah ketika hijau!", 6555, 6);
                    TogglePlayerControllable(i, true);
                    
                    TextDrawShowForPlayer(i, Event_SGTD);
                    TextDrawShowForPlayer(i, GlobalFooterTD);
                    
                    PlayAudioStreamForPlayer(i, "http://103.178.153.173/kokoasm.mp3");
                }
                SetTimer("SwitchingLight", 5555, false);
            }
        }
    }
    return 1;
}

forward ShakeTile(titleid);
public ShakeTile(titleid)
{
    switch(Event_FalloutInfo[titleid][shakestep])
    {
        case 0, 5:
        {
            SetDynamicObjectRot(Event_FalloutInfo[titleid][TileObject], Event_FalloutInfo[titleid][fallobjRX], Event_FalloutInfo[titleid][fallobjRY] + 7, Event_FalloutInfo[titleid][fallobjRZ]);
        }
        case 1, 6:
        {
            SetDynamicObjectRot(Event_FalloutInfo[titleid][TileObject], Event_FalloutInfo[titleid][fallobjRX], Event_FalloutInfo[titleid][fallobjRY], Event_FalloutInfo[titleid][fallobjRZ]);
        }
        case 2, 7:
        {
            SetDynamicObjectRot(Event_FalloutInfo[titleid][TileObject], Event_FalloutInfo[titleid][fallobjRX], Event_FalloutInfo[titleid][fallobjRY] - 7, Event_FalloutInfo[titleid][fallobjRZ]);
        }
        case 3, 8:
        {
            SetDynamicObjectRot(Event_FalloutInfo[titleid][TileObject], Event_FalloutInfo[titleid][fallobjRX], Event_FalloutInfo[titleid][fallobjRY], Event_FalloutInfo[titleid][fallobjRZ]);
        }
        case 4, 9:
        {
            SetDynamicObjectRot(Event_FalloutInfo[titleid][TileObject], Event_FalloutInfo[titleid][fallobjRX], Event_FalloutInfo[titleid][fallobjRY], Event_FalloutInfo[titleid][fallobjRZ]);
        }
        case 10:
        {
            new Float:X, Float:Y, Float:Z;
            GetDynamicObjectPos(Event_FalloutInfo[titleid][TileObject], X, Y, Z);
            MoveDynamicObject(Event_FalloutInfo[titleid][TileObject], X, Y, Z - 100, 4);
        }
        case 11..99:
        {
            SetDynamicObjectRot(Event_FalloutInfo[titleid][TileObject], Event_FalloutInfo[titleid][fallobjRX] - ((Event_FalloutInfo[titleid][shakestep] * 7) - 20), 0, 0);
        }
        case 100:
        {
            if(DestroyDynamicObject(Event_FalloutInfo[titleid][TileObject]))
                Event_FalloutInfo[titleid][TileObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
            
            KillTimer(Event_FalloutInfo[titleid][shaketimer]);
            Event_FalloutInfo[titleid][shaketimer] = -1;
        }
    }

    Event_FalloutInfo[titleid][shakestep]++;
    return 1;
}

task fallout_CheckTile[1000]() 
{
    if(EventInfo[eventStarted] && EventInfo[eventType] == 4)
    {
        new randtile = Iter_Random(AvailTiles);
        Iter_Remove(AvailTiles, randtile);

        if(randtile != INVALID_ITERATOR_SLOT)
        {
            if(IsValidDynamicObject(Event_FalloutInfo[randtile][TileObject]) && Event_FalloutInfo[randtile][shakestep] == 0)
            {
                GetDynamicObjectPos(Event_FalloutInfo[randtile][TileObject], Event_FalloutInfo[randtile][fallobjX], Event_FalloutInfo[randtile][fallobjY], Event_FalloutInfo[randtile][fallobjZ]);
                GetDynamicObjectRot(Event_FalloutInfo[randtile][TileObject], Event_FalloutInfo[randtile][fallobjRX], Event_FalloutInfo[randtile][fallobjRY], Event_FalloutInfo[randtile][fallobjRZ]);
                Event_FalloutInfo[randtile][shaketimer] = SetTimerEx("ShakeTile", 555, true, "i", randtile);

            }
        }
    }
    return 1;
}

task UpdateEvCurTime[1000]()
{
    if(EventInfo[eventStarted])
    {
        if(EventInfo[eventType] == 1)
        {
            if(EventInfo[timeLimit] > 0)
            {
                EventInfo[timeLimit]--;

                static jjs[212];
                format(jjs, sizeof(jjs), "Target Skor: %d~n~~r~Red Team: %d~n~~b~Blue Team: %d~n~~w~Time: %02d:%02d", EventInfo[targetScore], EventInfo[redTeamScore], EventInfo[blueTeamScore], EventInfo[timeLimit]/60, EventInfo[timeLimit]%3600%60);
                TextDrawSetString(GlobalFooterTD, jjs);

                if(EventInfo[redTeamScore] >= EventInfo[targetScore])
                {
                    EventInfo[eventStarted] = false;
                    EventInfo[timeLimit] = 0;
                    SendClientMessageToAll(Y_WHITE, "[i] Event telah dinyatakan selesai, "RED"Red Team "WHITE"memenangkan pertandingan.");

                    foreach(new i : InEvent)
                    {
                        ResetPlayerWeapons(i);

                        GameTextForPlayer(i, "Event selesai~n~~r~Mengembalikan posisi...", 5000, 6);

                        if(Iter_Contains(EvRedTeam, i))
                        {
                            GivePlayerMoneyEx(i, EventInfo[winnerPrize]);
                            SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Selamat! Anda mendapatkan "GREEN"$%s "WHITE"sebagai hadiah kemenangan.", FormatMoney(EventInfo[winnerPrize]));
                        }
                        GivePlayerMoneyEx(i, EventInfo[partPrize]);

                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));

                        StopAudioStreamForPlayer(i);
                        SetTimerEx("LeaveEvent", 5000, false, "i", i);
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
                else if(EventInfo[blueTeamScore] >= EventInfo[targetScore])
                {
                    EventInfo[eventStarted] = false;
                    EventInfo[timeLimit] = 0;
                    SendClientMessageToAll(Y_WHITE, "[i] Event telah dinyatakan selesai, {009dc4}Blue Team "WHITE"memenangkan pertandingan.");

                    foreach(new i : InEvent)
                    {
                        ResetPlayerWeapons(i);

                        GameTextForPlayer(i, "Event selesai~n~~r~Mengembalikan posisi...", 5000, 6);

                        if(Iter_Contains(EvBlueTeam, i))
                        {
                            GivePlayerMoneyEx(i, EventInfo[winnerPrize]);
                            SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Selamat! Anda mendapatkan "GREEN"$%s "WHITE"sebagai hadiah kemenangan.", FormatMoney(EventInfo[winnerPrize]));
                        }
                        GivePlayerMoneyEx(i, EventInfo[partPrize]);

                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));

                        StopAudioStreamForPlayer(i);
                        SetTimerEx("LeaveEvent", 5000, false, "i", i);
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
            }
            else
            {
                EventInfo[eventStarted] = false;
                EventInfo[timeLimit] = 0;

                if(EventInfo[redTeamScore] == EventInfo[blueTeamScore]) //seri maaka tidak ada yang menang
                {
                    SendClientMessageToAll(Y_WHITE, "[i] Event telah dinyatakan selesai, tidak ada yang memenangkan pertandingan/seri.");

                    foreach(new i : InEvent)
                    {
                        ResetPlayerWeapons(i);

                        GameTextForPlayer(i, "Event selesai~n~~r~Mengembalikan posisi...", 5000, 6);

                        GivePlayerMoneyEx(i, EventInfo[partPrize]);

                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));

                        StopAudioStreamForPlayer(i);
                        SetTimerEx("LeaveEvent", 5000, false, "i", i);
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
                else
                {
                    if(EventInfo[redTeamScore] > EventInfo[blueTeamScore])
                        SendClientMessageToAll(Y_WHITE, "[i] Event telah dinyatakan selesai, "RED"Red Team "WHITE"memenangkan pertandingan.");
                    else
                        SendClientMessageToAll(Y_WHITE, "[i] Event telah dinyatakan selesai, {009dc4}Blue Team "WHITE"memenangkan pertandingan.");


                    foreach(new i : InEvent)
                    {
                        ResetPlayerWeapons(i);

                        GameTextForPlayer(i, "Event selesai~n~~r~Mengembalikan posisi...", 5000, 6);

                        if(EventInfo[redTeamScore] > EventInfo[blueTeamScore])
                        {
                            if(Iter_Contains(EvRedTeam, i))
                            {
                                GivePlayerMoneyEx(i, EventInfo[winnerPrize]);

                                SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Selamat! Anda mendapatkan "GREEN"$%s "WHITE"sebagai hadiah kemenangan.", FormatMoney(EventInfo[winnerPrize]));
                            }
                        }
                        else
                        {
                            if(Iter_Contains(EvBlueTeam, i))
                            {
                                GivePlayerMoneyEx(i, EventInfo[winnerPrize]);
                                
                                SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Selamat! Anda mendapatkan "GREEN"$%s "WHITE"sebagai hadiah kemenangan.", FormatMoney(EventInfo[winnerPrize]));
                            }
                        }

                        StopAudioStreamForPlayer(i);

                        GivePlayerMoneyEx(i, EventInfo[partPrize]);

                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));

                        SetTimerEx("LeaveEvent", 5000, false, "i", i);
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
            }
        }
        else if(EventInfo[eventType] == 2)
        {
            if(EventInfo[raceShowVeh] > 0)
            {
                EventInfo[raceShowVeh]--;

                if(EventInfo[raceShowVeh] <= 0)
                {
                    EventInfo[raceShowVeh] = 0;

                    foreach(new i : InEvent)
                    {
                        SetPlayerVirtualWorld(i, EventInfo[arenaVWID]);
                        SetVehicleVirtualWorld(EventVehicle[i], EventInfo[arenaVWID]);
                    }
                }
            }

            if(EventInfo[raceEnding] > 0)
            {
                EventInfo[raceEnding]--;
                static jjs[212];
                format(jjs, sizeof(jjs), "Event selesai~n~~r~mengembalikan posisi:~n~%ds", EventInfo[raceEnding]);
                foreach(new i : InEvent)
                {
                    GameTextForPlayer(i, jjs, 1500, 6);
                }

                if(EventInfo[raceEnding] <= 0)
                {
                    SendClientMessageToAll(Y_WHITE, "[i] Racing Event telah dinyatakan selesai, terima kasih atas partisipasi anda.");

                    EventInfo[eventStarted] = false;
                    EventInfo[raceEnding] = 0;

                    foreach(new i : InEvent)
                    {
                        DestroyVehicle(EventVehicle[i]);

                        DisableRemoteVehicleCollisions(i, false);

                        ResetPlayerWeapons(i);

                        LeaveEvent(i);

                        GivePlayerMoneyEx(i, EventInfo[partPrize]);
                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
            }

            if(Iter_Count(InEvent) < 1)
            {
                SendClientMessageToAll(Y_WHITE, "[i] Racing Event telah dinyatakan selesai, terima kasih atas partisipasi anda.");

                EventInfo[eventStarted] = false;
                EventInfo[raceEnding] = 0;

                foreach(new i : InEvent)
                {
                    DestroyVehicle(EventVehicle[i]);

                    DisableRemoteVehicleCollisions(i, false);

                    LeaveEvent(i);

                    GivePlayerMoneyEx(i, EventInfo[partPrize]);
                    SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));
                }

                SetTimer("ResetEvent", 6500, false);
            }
        }
        else if(EventInfo[eventType] == 3)
        {
            if(EventInfo[timeLimit] > 0)
            {
                EventInfo[timeLimit]--;

                static jjs[212];
                format(jjs, sizeof(jjs), "Evakuasi: %02d:%02d~n~Survivors: ~b~%d", EventInfo[timeLimit]/60, EventInfo[timeLimit]%3600%60, Iter_Count(EvHumanTeam));
                TextDrawSetString(GlobalFooterTD, jjs);

                if(Iter_Count(EvHumanTeam) < 1)
                {
                    EventInfo[eventStarted] = false;
                    EventInfo[timeLimit] = 0;
                    SendClientMessageToAll(Y_WHITE, "[i] Event telah dinyatakan selesai, "RED"Zombie "WHITE"memenangkan pertandingan.");

                    foreach(new i : InEvent)
                    {
                        ResetPlayerWeapons(i);

                        GameTextForPlayer(i, "Event selesai~n~~r~Mengembalikan posisi...", 5000, 6);

                        if(Iter_Contains(EvZombieTeam, i))
                        {
                            GivePlayerMoneyEx(i, EventInfo[winnerPrize]);
                            SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Selamat! Anda mendapatkan "GREEN"$%s "WHITE"sebagai hadiah kemenangan.", FormatMoney(EventInfo[winnerPrize]));
                        }
                        GivePlayerMoneyEx(i, EventInfo[partPrize]);

                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));

                        SetTimerEx("LeaveEvent", 5000, false, "i", i);
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
            }
            else
            {
                EventInfo[eventStarted] = false;
                EventInfo[timeLimit] = 0;

                if(Iter_Count(EvHumanTeam) < 1)
                {
                    SendClientMessageToAll(Y_WHITE, "[i] Event telah dinyatakan selesai, "RED"Zombie "WHITE"memenangkan pertandingan.");

                    foreach(new i : InEvent)
                    {
                        ResetPlayerWeapons(i);

                        GameTextForPlayer(i, "Event selesai~n~~r~Mengembalikan posisi...", 5000, 6);

                        if(Iter_Contains(EvZombieTeam, i))
                        {
                            GivePlayerMoneyEx(i, EventInfo[winnerPrize]);
                            SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Selamat! Anda mendapatkan "GREEN"$%s "WHITE"sebagai hadiah kemenangan.", FormatMoney(EventInfo[winnerPrize]));
                        }
                        GivePlayerMoneyEx(i, EventInfo[partPrize]);

                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));

                        SetTimerEx("LeaveEvent", 5000, false, "i", i);
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
                else //jika manusia bertahan
                {
                    SendClientMessageToAll(Y_WHITE, "[i] Event telah dinyatakan selesai, {009dc4}Survivor "WHITE"memenangkan pertandingan.");

                    foreach(new i : InEvent)
                    {
                        ResetPlayerWeapons(i);

                        GameTextForPlayer(i, "Event selesai~n~~r~Mengembalikan posisi...", 5000, 6);

                        if(Iter_Contains(EvHumanTeam, i))
                        {
                            GivePlayerMoneyEx(i, EventInfo[winnerPrize]);
                            SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Selamat! Anda mendapatkan "GREEN"$%s "WHITE"sebagai hadiah kemenangan.", FormatMoney(EventInfo[winnerPrize]));
                        }
                        GivePlayerMoneyEx(i, EventInfo[partPrize]);

                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));

                        StopAudioStreamForPlayer(i);
                        SetTimerEx("LeaveEvent", 5000, false, "i", i);
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
            }
        }
        else if(EventInfo[eventType] == 4)
        {
            if(Iter_Count(InEvent) < 2)
            {
                EventInfo[eventStarted] = false;
                EventInfo[timeLimit] = 0;

                foreach(new i : InEvent)
                {
                    SendClientMessageToAllEx(Y_WHITE, "[i] Event telah dinyatakan selesai, "RED"%s "WHITE"bertahan hingga akhir dan meemnangkan pertandingan.", AccountData[i][pName]);

                    ResetPlayerWeapons(i);

                    GameTextForPlayer(i, "Event selesai~n~~r~Mengembalikan posisi...", 5000, 6);

                    GivePlayerMoneyEx(i, EventInfo[winnerPrize]);
                    SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Selamat! Anda mendapatkan "GREEN"$%s "WHITE"sebagai hadiah kemenangan.", FormatMoney(EventInfo[winnerPrize]));
                    GivePlayerMoneyEx(i, EventInfo[partPrize]);
                    SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));

                    StopAudioStreamForPlayer(i);
                    SetTimerEx("LeaveEvent", 5000, false, "i", i);
                }
                SetTimer("ResetEvent", 6500, false);
            }
            else
            {
                new Float:vpos[3];
                foreach(new i : InEvent)
                {
                    GetPlayerPos(i, vpos[0], vpos[1], vpos[2]);
                    if(vpos[2] < 37.0 || vpos[2] > 55.0)
                    {
                        GivePlayerMoneyEx(i, EventInfo[partPrize]);

                        foreach(new p : InEvent)
                        {
                            SendClientMessageEx(p, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"telah tereleminasi karena terjatuh.", AccountData[i][pName]);  
                        }

                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));
                        SetTimerEx("LeaveEvent", 5000, false, "i", i);
                        Iter_Remove(InEvent, i);
                    }
                }
            }
        }
        else if(EventInfo[eventType] == 5)
        {
            if(EventInfo[timeLimit] > 0)
            {
                EventInfo[timeLimit]--;

                static jjs[212];
                format(jjs, sizeof(jjs), "Time Left: %02d:%02d~n~Pemain: ~b~%d", EventInfo[timeLimit]/60, EventInfo[timeLimit]%3600%60, Iter_Count(InEvent));
                TextDrawSetString(GlobalFooterTD, jjs);

                if(Iter_Count(InEvent) < 1)
                {
                    EventInfo[eventStarted] = false;
                    EventInfo[timeLimit] = 0;

                    SendClientMessageToAll(Y_WHITE, "[i] Event Squid Game telah dinyatakan selesai, terima kasih atas partisipasi anda.");

                    SetTimer("ResetEvent", 6500, false);
                }

                if(EventInfo[SGLightRed])
                {
                    foreach(new i : InEvent)
                    {
                        if(GetPlayerAnimationIndex(i) != 1189 && GetPlayerAnimationIndex(i) != 1275)
                        {
                            foreach(new p : InEvent)
                            {
                                SendClientMessageEx(p, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"telah tereleminasi karena bergerak.", AccountData[i][pName]);  
                            }

                            SetPlayerHealth(i, 0.0);
                            GivePlayerMoneyEx(i, EventInfo[partPrize]);
                            SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));
                            Iter_Remove(InEvent, i);
                        }
                    }
                }
            }
            else
            {
                if(EventInfo[racecWinners] < 5)
                {
                    EventInfo[eventStarted] = false;
                    EventInfo[timeLimit] = 0;

                    SendClientMessageToAll(Y_WHITE, "[i] Event Squid Game telah dinyatakan selesai, terima kasih atas partisipasi anda.");
                    foreach(new i : InEvent)
                    {
                        ResetPlayerWeapons(i);

                        GameTextForPlayer(i, "Event selesai~n~~r~Mengembalikan posisi...", 5000, 6);
                        GivePlayerMoneyEx(i, EventInfo[partPrize]);

                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));

                        SetTimerEx("LeaveEvent", 5000, false, "i", i);
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
            }

            if(EventInfo[raceEnding] > 0)
            {
                EventInfo[raceEnding]--;
                static jjs[212];
                format(jjs, sizeof(jjs), "Event selesai~n~~r~mengembalikan posisi:~n~%ds", EventInfo[raceEnding]);
                foreach(new i : InEvent)
                {
                    GameTextForPlayer(i, jjs, 1500, 6);
                }

                if(EventInfo[raceEnding] <= 0)
                {
                    SendClientMessageToAll(Y_WHITE, "[i] Event Squid Game telah dinyatakan selesai, terima kasih atas partisipasi anda.");

                    EventInfo[eventStarted] = false;
                    EventInfo[raceEnding] = 0;

                    foreach(new i : InEvent)
                    {
                        ResetPlayerWeapons(i);
                        LeaveEvent(i);
                        GivePlayerMoneyEx(i, EventInfo[partPrize]);
                        SendClientMessageEx(i, Y_YELLOW, "[OOC Event] "WHITE"Anda mendapatkan "GREEN"$%s "WHITE"sebagai bonus hadiah partisipasi.", FormatMoney(EventInfo[partPrize]));
                    }
                    SetTimer("ResetEvent", 6500, false);
                }
            }
        }
    }
    return 1;
}

ptask CheckPlayerZombZone[1555](playerid) 
{
    if(AccountData[playerid][pSpawned] && AccountData[playerid][pInEvent] && EventInfo[eventType] == 3)
	{
        if(!IsPlayerInDynamicArea(playerid, EventInfo[zombieArea]))
        {
            if(Iter_Contains(EvZombieTeam, playerid))
            {
                Anticheat[playerid][acImmunity] = gettime() + 5;
                SetPlayerPos(playerid, EventInfo[zombieSpawn][0], EventInfo[zombieSpawn][1], EventInfo[zombieSpawn][2]);
            }

            if(Iter_Contains(EvHumanTeam, playerid))
            {
                Anticheat[playerid][acImmunity] = gettime() + 5;
                SetPlayerPos(playerid, EventInfo[humanSpawn][0], EventInfo[humanSpawn][1], EventInfo[humanSpawn][2]);
            }
        }
	}
    return 1;
}

YCMD:event(playerid, params[], help)
{
    new type[24], string[128];
    if(sscanf(params, "s[24]S()[128]", type, string)) return SUM(playerid, "/event [name]~n~create, start, join, leave");

    if(!strcmp(type, "create", true))
    {
        if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

        if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

        new etype;

        if(sscanf(string, "d", etype))
            return SUM(playerid, "/event create [type] [1. TDM, 2. Racing, 3. Zombie, 4. Fallout, 5. Squid Game]");

        if(etype < 1 || etype > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event type must be 1 - 5!");

        if(etype == 1)
        {
            static sdta[625];
            format(sdta, sizeof(sdta), "Implementation\tStatus\n\
            Red Team skin\t%d\n\
            Red Team health\t%.2f\n\
            Red Team armour\t%.2f\n\
            Red Team spawn point\t%s\n\
            Red Team weapon #1\t%s\n\
            Red Team weapon #2\t%s\n\
            Red Team weapon #3\t%s\n\
            Blue Team skin\t%d\n\
            Blue Team health\t%.2f\n\
            Blue Team armour\t%.2f\n\
            Blue Team spawn point\t%s\n\
            Blue Team weapon #1\t%s\n\
            Blue Team weapon #2\t%s\n\
            Blue Team weapon #3\t%s\n\
            Arena VWID\t%d\n\
            Arena Interior ID\t%d\n\
            Time limitation (minutes)\t%d minute(s)\n\
            Target score\t%d\n\
            Max Players\t%d\n\
            Participation prize\t"GREEN"$%s\n\
            Winner prize\t"GREEN"$%s",
            EventInfo[redSkin],
            EventInfo[redHealth],
            EventInfo[redArmour],
            (EventInfo[redSpawn][0] > 0.0 || EventInfo[redSpawn][1] > 0.0 || EventInfo[redSpawn][2] > 0.0) ? (""GREEN"Assigned") : (""RED"Unassigned"),
            ReturnWeaponName(EventInfo[redWeapon][0]),
            ReturnWeaponName(EventInfo[redWeapon][1]),
            ReturnWeaponName(EventInfo[redWeapon][2]),
            EventInfo[blueSkin],
            EventInfo[blueHealth],
            EventInfo[blueArmour],
            (EventInfo[blueSpawn][0] > 0.0 || EventInfo[blueSpawn][1] > 0.0 || EventInfo[blueSpawn][2] > 0.0) ? (""GREEN"Assigned") : (""RED"Unassigned"),
            ReturnWeaponName(EventInfo[blueWeapon][0]),
            ReturnWeaponName(EventInfo[blueWeapon][1]),
            ReturnWeaponName(EventInfo[blueWeapon][2]),
            EventInfo[arenaVWID],
            EventInfo[arenaIntid],
            EventInfo[timeLimit]/60,
            EventInfo[targetScore],
            EventInfo[maxPlayer],
            FormatMoney(EventInfo[partPrize]),
            FormatMoney(EventInfo[winnerPrize]));
            Dialog_Show(playerid, "EventTDMCreator", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Event Creator", 
            sdta, "Setup", "Batal");
        }
        else if(etype == 2)
        {
            static sdta[625];
            format(sdta, sizeof(sdta), "Implementation\tStatus\n\
            Race Spawn Point\t%s\n\
            Vehicle Model\t%s\n\
            Event Music\t%s\n\
            Add Race Checkpoint\t%d checkpoint(s) added\n\
            Clear All Race Checkpoints\t%d checkpoint(s) added\n\
            Arena VWID\t%d\n\
            Arena Interior ID\t%d\n\
            Max Players\t%d\n\
            Participation prize\t"GREEN"$%s\n\
            Winner prize\t"GREEN"$%s",
            (EventInfo[raceSpawn][0] > 0.0 || EventInfo[raceSpawn][1] > 0.0 || EventInfo[raceSpawn][2] > 0.0) ? (""GREEN"Assigned") : (""RED"Unassigned"),
            GetVehicleModelName(EventInfo[raceVehicle]),
            (!isnull(EventInfo[eventMusic])) ? (""GREEN"Yes") : (""RED"No"),
            Iter_Count(EvRaceCP),
            Iter_Count(EvRaceCP),
            EventInfo[arenaVWID],
            EventInfo[arenaIntid],
            EventInfo[maxPlayer],
            FormatMoney(EventInfo[partPrize]),
            FormatMoney(EventInfo[winnerPrize]));
            Dialog_Show(playerid, "EventRace", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Race Event Creator", 
            sdta, "Setup", "Batal");
        }
        else if(etype == 3)
        {
            static sdta[625];
            format(sdta, sizeof(sdta), "Implementation\tStatus\n\
            Zombie Spawn Point\t%s\n\
            Survivor Spawn Point\t%s\n\
            RB Point #1\t%s\n\
            RB Point #2\t%s\n\
            Arena VWID\t%d\n\
            Max Players\t%d\n\
            Participation prize\t"GREEN"$%s\n\
            Winner prize\t"GREEN"$%s",
            (EventInfo[zombieSpawn][0] > 0.0 || EventInfo[zombieSpawn][1] > 0.0 || EventInfo[zombieSpawn][2] > 0.0) ? (""GREEN"Assigned") : (""RED"Unassigned"),
            (EventInfo[humanSpawn][0] > 0.0 || EventInfo[humanSpawn][1] > 0.0 || EventInfo[humanSpawn][2] > 0.0) ? (""GREEN"Assigned") : (""RED"Unassigned"),
            (EventInfo[boundPoint1][0] > 0.0 || EventInfo[boundPoint1][1] > 0.0) ? (""GREEN"Assigned") : (""RED"Unassigned"),
            (EventInfo[boundPoint2][0] > 0.0 || EventInfo[boundPoint2][1] > 0.0) ? (""GREEN"Assigned") : (""RED"Unassigned"),
            EventInfo[arenaVWID],
            EventInfo[maxPlayer],
            FormatMoney(EventInfo[partPrize]),
            FormatMoney(EventInfo[winnerPrize]));
            Dialog_Show(playerid, "EventZombie", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Zombie Event Creator", 
            sdta, "Setup", "Batal");
        }
        else if(etype == 4)
        {
            static sdta[625];
            format(sdta, sizeof(sdta), "Implementation\tStatus\n\
            Max Players\t%d\n\
            Participation prize\t"GREEN"$%s\n\
            Winner prize\t"GREEN"$%s",
            EventInfo[maxPlayer],
            FormatMoney(EventInfo[partPrize]),
            FormatMoney(EventInfo[winnerPrize]));
            Dialog_Show(playerid, "EventFallout", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Fallout Event Creator", 
            sdta, "Setup", "Batal");
        }
        else if(etype == 5)
        {
            static sdta[625];
            format(sdta, sizeof(sdta), "Implementation\tStatus\n\
            Max Players\t%d\n\
            Participation prize\t"GREEN"$%s\n\
            Winner prize\t"GREEN"$%s",
            EventInfo[maxPlayer],
            FormatMoney(EventInfo[partPrize]),
            FormatMoney(EventInfo[winnerPrize]));
            Dialog_Show(playerid, "EventSquidGame", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Squid Game Event Creator", 
            sdta, "Setup", "Batal");
        }
    }
    else if(!strcmp(type, "start", true))
    {
        if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
        
        new etype;

        if(sscanf(string, "d", etype))
            return SUM(playerid, "/event start [type] [1. TDM, 2. Racing, 3. Zombie, 4. Fallout, 5. Squid Game]");

        if(etype < 1 || etype > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event type must be 1 - 5!");

        if(etype == 1)
        {
            if(EventInfo[redSpawn][0] == 0.0 && EventInfo[redSpawn][1] == 0.0 && EventInfo[redSpawn][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Red Team Spawn belum ditetapkan!");
            if(EventInfo[blueSpawn][0] == 0.0 && EventInfo[blueSpawn][1] == 0.0 && EventInfo[blueSpawn][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Blue Team Spawn belum ditetapkan!");
            
            if(EventInfo[eventStarted] || EventInfo[eventOpened]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ada event yang sedang berlangsung!");

            EventInfo[eventOpened] = true;
            EventInfo[eventOpentime] = 25;
            EventInfo[eventType] = 1;

            SendClientMessageToAll(Y_YELLOW, "[OOC Event] "MAGENTA"Team Deathmatch "WHITE"akan segera dimulai, gunakan "RED"'/event join' "WHITE"untuk berpartisipasi!");
            SendClientMessageToAllEx(Y_WHITE, "~> Hadiah Partisipasi: "GREEN"$%s "WHITE"// Hadiah Team Pemenang: "GREEN"$%s "WHITE"// Target Skor: "YELLOW"%d", FormatMoney(EventInfo[partPrize]), FormatMoney(EventInfo[winnerPrize]), EventInfo[targetScore]);
        }
        else if(etype == 2)
        {
            if(EventInfo[raceSpawn][0] == 0.0 && EventInfo[raceSpawn][1] == 0.0 && EventInfo[raceSpawn][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Racing spawn point belum ditetapkan!");
            if(EventRaceCP[0][raceCPCoord][0] == 0.0 && EventRaceCP[0][raceCPCoord][1] == 0.0 && EventRaceCP[0][raceCPCoord][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Setidaknya membutuhkan minimal 1 race checkpoint untuk dijalankan!");

            if(EventInfo[eventStarted] || EventInfo[eventOpened]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ada event yang sedang berlangsung!");

            EventInfo[eventOpened] = true;
            EventInfo[eventOpentime] = 25;
            EventInfo[eventType] = 2;

            SendClientMessageToAll(Y_YELLOW, "[OOC Event] "MAGENTA"Racing Event "WHITE"akan segera dimulai, gunakan "RED"'/event join' "WHITE"untuk berpartisipasi!");
            SendClientMessageToAllEx(Y_WHITE, "~> Hadiah Partisipasi: "GREEN"$%s "WHITE"// Hadiah Total Pemenang: "GREEN"$%s "WHITE"", FormatMoney(EventInfo[partPrize]), FormatMoney(EventInfo[winnerPrize]));
        }
        else if(etype == 3)
        {
            if(EventInfo[zombieSpawn][0] == 0.0 && EventInfo[zombieSpawn][1] == 0.0 && EventInfo[zombieSpawn][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Red Team Spawn belum ditetapkan!");
            if(EventInfo[humanSpawn][0] == 0.0 && EventInfo[humanSpawn][1] == 0.0 && EventInfo[humanSpawn][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Blue Team Spawn belum ditetapkan!");
            if(EventInfo[boundPoint1][0] == 0.0 && EventInfo[boundPoint1][1] == 0.0 && EventInfo[boundPoint1][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bound point 1 belum ditetapkan!");
            if(EventInfo[boundPoint2][0] == 0.0 && EventInfo[boundPoint2][1] == 0.0 && EventInfo[boundPoint2][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bound point 2 belum ditetapkan!");

            if(EventInfo[eventStarted] || EventInfo[eventOpened]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ada event yang sedang berlangsung!");

            EventInfo[eventOpened] = true;
            EventInfo[eventOpentime] = 25;
            EventInfo[eventType] = 3;

            EventInfo[zombieZone1] = GangZoneCreate(-20000.0000, -20000.0000, 20000.0000, 20000.0000);
            EventInfo[zombieZone2] = GangZoneCreate(EventInfo[boundPoint1][0], EventInfo[boundPoint2][1], EventInfo[boundPoint2][0], EventInfo[boundPoint1][1]);
            EventInfo[zombieArea] = CreateDynamicRectangle(EventInfo[boundPoint1][0], EventInfo[boundPoint2][1], EventInfo[boundPoint2][0], EventInfo[boundPoint1][1], -1, 0, -1);
            
            SendClientMessageToAll(Y_YELLOW, "[OOC Event] "MAGENTA"Zombie Survival "WHITE"akan segera dimulai, gunakan "RED"'/event join' "WHITE"untuk berpartisipasi!");
            SendClientMessageToAllEx(Y_WHITE, "~> Hadiah Partisipasi: "GREEN"$%s "WHITE"// Hadiah Total Pemenang: "GREEN"$%s "WHITE"", FormatMoney(EventInfo[partPrize]), FormatMoney(EventInfo[winnerPrize]));
        }
        else if(etype == 4)
        {
            if(EventInfo[eventStarted] || EventInfo[eventOpened]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ada event yang sedang berlangsung!");

            EventInfo[eventOpened] = true;
            EventInfo[eventOpentime] = 25;
            EventInfo[eventType] = 4;

            //tile creating
            Event_FalloutTileCreate();
            
            SendClientMessageToAll(Y_YELLOW, "[OOC Event] "MAGENTA"Chess Fall "WHITE"akan segera dimulai, gunakan "RED"'/event join' "WHITE"untuk berpartisipasi!");
            SendClientMessageToAllEx(Y_WHITE, "~> Hadiah Partisipasi: "GREEN"$%s "WHITE"// Hadiah Total Pemenang: "GREEN"$%s "WHITE"", FormatMoney(EventInfo[partPrize]), FormatMoney(EventInfo[winnerPrize]));
        }
        else if(etype == 5)
        {
            if(EventInfo[eventStarted] || EventInfo[eventOpened]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ada event yang sedang berlangsung!");

            EventInfo[eventOpened] = true;
            EventInfo[eventOpentime] = 25;
            EventInfo[eventType] = 5;
            EventInfo[SGLightRed] = false;
            EventInfo[timeLimit] = 3*60;

            //tile creating
            if(DestroyDynamicObject(Event_SGGate))
                Event_SGGate = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            if(DestroyDynamicArea(Event_SGFinish))
                Event_SGFinish = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

            TextDrawHideForAll(Event_SGTD);
                
            Event_SGGate = CreateDynamicObject(8172, -29.601673, 2502.822509, 13.543309, -0.000007, 270.000000, 180.000030, 25, 0, -1, 200.00, 200.00); // gerbang
            Event_SGFinish = CreateDynamicRectangle(227.2201,2477.5962, 256.0689,2528.0020, 25, 0, -1);

            SendClientMessageToAll(Y_YELLOW, "[OOC Event] "MAGENTA"Squid Game "WHITE"akan segera dimulai, gunakan "RED"'/event join' "WHITE"untuk berpartisipasi!");
            SendClientMessageToAllEx(Y_WHITE, "~> Hadiah Partisipasi: "GREEN"$%s "WHITE"// Hadiah Total Pemenang: "GREEN"$%s "WHITE"", FormatMoney(EventInfo[partPrize]), FormatMoney(EventInfo[winnerPrize]));
        }
    }
    else if(!strcmp(type, "join", true))
    {
        if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengikuti event dalam keadaan pingsan!");
        if(OJailData[playerid][jailed] || AccountData[playerid][pArrested]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengikuti event dalam keadaan dipenjara!");
        if(Iter_Count(InEvent) >= EventInfo[maxPlayer]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event tersebut sudah penuh!");
        if(!EventInfo[eventOpened]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event yang sedang berlangsung/event telah dimulai!");
        if(AccountData[playerid][pInEvent]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah berpartisipasi ke dalam event!");
        
        pZombieClass[playerid] = 0;
        if(AccountData[playerid][pHoldingSkate])
		{
			AccountData[playerid][pHoldingSkate] = false;
			AccountData[playerid][pSkating] = false;
			RemovePlayerAttachedObject(playerid, 9);
		}

        if(EventInfo[eventType] == 1)
        {
            JoinEventTDM(playerid);
        }
        else if(EventInfo[eventType] == 2)
        {
            JoinEventRace(playerid);
        }
        else if(EventInfo[eventType] == 3)
        {
            JoinEventZombie(playerid);
        }
        else if(EventInfo[eventType] == 4)
        {
            JoinEventFallout(playerid);
        }
        else if(EventInfo[eventType] == 5)
        {
            JoinEventSquidGame(playerid);
        }
    }
    else if(!strcmp(type, "leave", true))
    {
        if(!AccountData[playerid][pInEvent]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berpartisipasi ke dalam event apapun!");

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

        SendClientMessage(playerid, -1, "[OOC Event] Anda akan keluar dari event, mohon tunggu hingga dikembalikan ke posisi semula.");
    }
    return 1;
}

YCMD:killme(playerid, params[], help)
{
    if(!AccountData[playerid][pInEvent]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berpartisipasi ke dalam event apapun!");
    if(!EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event yang sedang berlangsung!");
    if(EventInfo[eventType] == 3 || EventInfo[eventType] == 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis event ini tidak dapat menggunakan killme!");

    SetPlayerHealth(playerid, 0.0);
    return 1;
}
