#include <YSI_Coding\y_hooks>

new bool:pumpkinFounded,
    pumpkinIndex,
    STREAMER_TAG_PICKUP:pumpkinPickup,
    STREAMER_TAG_3D_TEXT_LABEL:pumpkinLabel,
    Halloween_Minute;

enum e_PumpkinHalloween
{
    Float:Pos[3],
    Cash
};

new PumpkinLocation[][e_PumpkinHalloween] =
{
    //{X CO-ORD,Y CO-ORD,Z CO-ORD,MONEY,"REGION SUCH AS SF/LS/LV","AREA SUCH AS DOHERTY/DOWNTOWN/WILLOWFIELD"},
    {{-2172.0171,-1843.8499,214.7547},19056},
    {{-2432.5957,-1620.1436,526.8685},21032},
    {{-2432.5957,-1620.1436,526.8685},21032},
    {{-2528.2793,-1025.5176,102.1070},18076},
    {{-2528.2793,-1025.5176,102.1070},18076},
    {{-8.2656,-266.3369,11.9437},16921},
    {{-2120.4558,-1300.9391,77.9728},22053},
    {{-1956.4731,764.5522,55.7254},13998},
    {{-1963.7705,487.2920,31.9687},16098},
    {{-2542.7930,-353.2107,37.0313},15666},
    {{-1509.4563,1370.2919,3.0108},18223},
    {{-2189.1086,-269.0943,40.7195},24012},
    {{-1074.6843,-1234.5952,129.2188},25112},
    {{-2807.5503,1162.7417,20.3125},19729},
    {{-2268.7791,2664.1946,73.5156},14309},
    {{-1205.4790,-2349.8513,2.0340},39112},
    {{-1933.9781,211.7276,25.3226},16908},
    {{-2576.5107,1187.6368,41.8775},21087},
    {{2667.6277,2307.3535,24.0614},29872},
    {{-743.1037,-1933.7535,7.9191},14098},
    {{2146.2021,94.8287,27.1627},17609},
    {{2634.9646,263.1964,54.3462},15489},
    {{2581.4714,-1473.8392,24.0000},13062},
    {{2438.9673,-1901.5713,13.5534},17822},
    {{2476.8198,-1972.9170,16.6281},15809},
    {{2545.9392,-2248.8154,13.5469},23091},
    {{836.7835,-1856.7886,8.3893},8092},
    {{664.9876,-1380.3512,21.8417},19872},
    {{588.3129,-1555.4790,15.6424},20112},
    {{459.0752,-1276.6705,15.4114},19221},
    {{471.4406,-269.6804,7.3002},41022},
    {{1271.9558,295.4855,20.6563},21011},
    {{2189.4036,-697.5020,56.4319},39012},
    {{2372.1699,-2135.6299,27.1750},28765},
    {{2274.2246,-2563.0544,19.9043},29052},
    {{1926.8618,-2692.0869,19.3672},11098},
    {{1024.0765,-313.3355,73.9931},22098},
    {{1629.1864,7.0049,9.2344},26543},
    {{770.7070,-1084.6780,24.0859},22041},
    {{1435.1244,-1093.3391,17.5879},16822},
    {{2792.7664,698.0993,9.8893},23659},
    {{2892.5449,948.4681,10.6730},39621},
    {{2345.3472,1293.8081,67.4688},27001},
    {{1400.8108,2767.2092,10.8203},51091},
    {{2465.7429,2226.0747,10.8203},25002},
    {{2479.1763,1921.0494,10.4679},24069},
    {{1765.3286,592.7733,13.0000},18092},
    {{586.6403,392.7565,15.8715},1922},
    {{1407.5444,2142.0837,12.0156},19112},
    {{2626.3064,2417.3677,10.8132},10921},
    {{2879.5156,1595.7340,10.8203},11092},
    {{2819.0471,1670.2314,10.8203},11021},
    {{397.1421,-1924.0480,7.8359},11021},
    {{-575.3457,-1484.0999,14.3511},11021},
    {{2243.4036,1131.7672,10.8203},26822},
    {{-781.4629,2147.3931,60.3828},28711},
    {{-86.8024,2642.1128,58.6177},36081},
    {{384.6790,2435.0015,16.5000},22901},
    {{110.7553,1019.9230,13.6094},11021},
    {{2807.2952,-1760.1057,11.8478},11021},
    {{2826.1438,-1453.0588,16.2500},11021},
    {{2528.8271,-1704.7632,13.3849},11021},
    {{2309.4153,-1637.9360,18.5078},11021},
    {{1040.5138,-285.2617,73.9922},11021},
    {{1848.1530,-1593.6870,23.8835},11021},
    {{826.2070,2665.7825,28.9297},40921},
    {{1047.2354,2921.5979,48.3125},50982},
    {{-1133.1697,-1084.2583,129.2188},11021},
    {{1294.8359,-1442.7338,14.9363},11021},
    {{1104.4827,-1333.9176,13.7878},11021},
    {{1248.5995,-1229.8175,13.6797},11021},
    {{-92.1334,-1560.6532,2.6107},11021},
    {{-349.9793,-1036.1240,59.6641},11021},
    {{-85.7244,-102.0955,6.4844},11021},
    {{319.2642,21.8955,4.3809},11021},
    {{742.3448,272.3130,27.1395},11021},
    {{1305.4237,340.6125,25.6946},11021},
    {{1417.9177,222.2229,19.5547},11021},
    {{2189.4036,-697.5020,56.4319},39012},
    {{2372.1699,-2135.6299,27.1750},28765},
    {{2274.2246,-2563.0544,19.9043},29052},
    {{1926.8618,-2692.0869,19.3672},11098},
    {{1024.0765,-313.3355,73.9931},22098},
    {{1629.1864,7.0049,9.2344},26543},
    {{770.7070,-1084.6780,24.0859},22041},
    {{1435.1244,-1093.3391,17.5879},16822},
    {{2792.7664,698.0993,9.8893},23659},
    {{2892.5449,948.4681,10.6730},39621},
    {{2345.3472,1293.8081,67.4688},27001},
    {{1400.8108,2767.2092,10.8203},51091},
    {{2465.7429,2226.0747,10.8203},25002},
    {{2479.1763,1921.0494,10.4679},24069},
    {{1765.3286,592.7733,13.0000},18092},
    {{586.6403,392.7565,15.8715},1922},
    {{1407.5444,2142.0837,12.0156},19112},
    {{2252.4656,67.7325,26.4844},11021},
    {{-32.1546,-1117.8408,1.0781},11021},
    {{2314.9888,41.4295,26.4844},11021},
    {{2598.3906,227.4479,59.2353},11021},
    {{-2172.0171,-1843.8499,214.7547},19056},
    {{-2432.5957,-1620.1436,526.8685},21032},
    {{-2432.5957,-1620.1436,526.8685},21032},
    {{-2528.2793,-1025.5176,102.1070},18076},
    {{-2528.2793,-1025.5176,102.1070},18076},
    {{-8.2656,-266.3369,11.9437},16921},
    {{-2120.4558,-1300.9391,77.9728},22053},
    {{-1956.4731,764.5522,55.7254},13998},
    {{-1963.7705,487.2920,31.9687},16098},
    {{-2542.7930,-353.2107,37.0313},15666},
    {{-1509.4563,1370.2919,3.0108},18223},
    {{-2189.1086,-269.0943,40.7195},24012},
    {{-1074.6843,-1234.5952,129.2188},25112},
    {{-2807.5503,1162.7417,20.3125},19729},
    {{-2268.7791,2664.1946,73.5156},14309},
    {{-1205.4790,-2349.8513,2.0340},39112},
    {{-1933.9781,211.7276,25.3226},16908},
    {{-2576.5107,1187.6368,41.8775},21087},
    {{2667.6277,2307.3535,24.0614},29872},
    {{-743.1037,-1933.7535,7.9191},14098},
    {{2146.2021,94.8287,27.1627},17609},
    {{2634.9646,263.1964,54.3462},15489},
    {{2581.4714,-1473.8392,24.0000},13062},
    {{2438.9673,-1901.5713,13.5534},17822},
    {{1248.5995,-1229.8175,13.6797},11021},
    {{-92.1334,-1560.6532,2.6107},11021},
    {{-349.9793,-1036.1240,59.6641},11021},
    {{-85.7244,-102.0955,6.4844},11021},
    {{319.2642,21.8955,4.3809},11021},
    {{742.3448,272.3130,27.1395},11021},
    {{1305.4237,340.6125,25.6946},11021},
    {{1417.9177,222.2229,19.5547},11021},
    {{2252.4656,67.7325,26.4844},11021},
    {{-32.1546,-1117.8408,1.0781},11021},
    {{2314.9888,41.4295,26.4844},11021},
    {{2598.3906,227.4479,59.2353},11021},
    {{2476.8198,-1972.9170,16.6281},15809},
    {{2545.9392,-2248.8154,13.5469},23091},
    {{836.7835,-1856.7886,8.3893},8092},
    {{664.9876,-1380.3512,21.8417},19872},
    {{588.3129,-1555.4790,15.6424},20112},
    {{459.0752,-1276.6705,15.4114},19221},
    {{471.4406,-269.6804,7.3002},41022},
    {{1271.9558,295.4855,20.6563},21011},
    {{2626.3064,2417.3677,10.8132},10921},
    {{2879.5156,1595.7340,10.8203},11092},
    {{2819.0471,1670.2314,10.8203},11021},
    {{397.1421,-1924.0480,7.8359},11021},
    {{-575.3457,-1484.0999,14.3511},11021},
    {{2243.4036,1131.7672,10.8203},26822},
    {{-781.4629,2147.3931,60.3828},28711},
    {{-86.8024,2642.1128,58.6177},36081},
    {{384.6790,2435.0015,16.5000},22901},
    {{-1133.1697,-1084.2583,129.2188},11021},
    {{110.7553,1019.9230,13.6094},11021},
    {{2807.2952,-1760.1057,11.8478},11021},
    {{2826.1438,-1453.0588,16.2500},11021},
    {{1040.5138,-285.2617,73.9922},11021},
    {{1848.1530,-1593.6870,23.8835},11021},
    {{826.2070,2665.7825,28.9297},40921},
    {{1047.2354,2921.5979,48.3125},50982},
    {{2528.8271,-1704.7632,13.3849},11021},
    {{2309.4153,-1637.9360,18.5078},11021},
    {{1104.4827,-1333.9176,13.7878},11021},
    {{1294.8359,-1442.7338,14.9363},11021}
};

task UpdatePumpkinInfo[60000]() 
{
    Halloween_Minute++;

    if(Halloween_Minute >= 20)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            PlayAudioStreamForPlayer(i, "https://dl.sndup.net/xmhjk/awdas.mp3");
        }

        if(!pumpkinFounded)
        {
            pumpkinIndex = random(sizeof(PumpkinLocation));
            SendClientMessageToAllEx(X11_ORANGE, "[Halloween] Tidak ada yang menemukan pumpkin, selanjutnya pumpkin berada di "YELLOW"%s.", GetLocation(PumpkinLocation[pumpkinIndex][Pos][0], PumpkinLocation[pumpkinIndex][Pos][1], PumpkinLocation[pumpkinIndex][Pos][2]));
            SendClientMessageToAll(X11_ORANGE, "[Halloween] Cari pumpkin secepatnya, dapatkan uang dan koleksi pumpkin untuk ditukarkan menjadi hadiah.");

            if(DestroyDynamicPickup(pumpkinPickup))
                pumpkinPickup = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

            if(DestroyDynamic3DTextLabel(pumpkinLabel))
                pumpkinLabel = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            pumpkinPickup = CreateDynamicPickup(19320, 2, PumpkinLocation[pumpkinIndex][Pos][0], PumpkinLocation[pumpkinIndex][Pos][1], PumpkinLocation[pumpkinIndex][Pos][2], 0, 0, -1, 65.0, -1, 0);
            pumpkinLabel = CreateDynamic3DTextLabel("[Halloween Pumpkin]\n"YELLOW"Ambil pumpkin ini untuk mendapatkan hadiah!", X11_ORANGE,PumpkinLocation[pumpkinIndex][Pos][0], PumpkinLocation[pumpkinIndex][Pos][1], PumpkinLocation[pumpkinIndex][Pos][2]+0.45, 65.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 65.0, -1, 0);

            pumpkinFounded = false;
        }
        else
        {
            pumpkinIndex = random(sizeof(PumpkinLocation));
            SendClientMessageToAllEx(X11_ORANGE, "[Halloween] Pumpkin telah ditemukan seseorang, selanjutnya pumpkin berada di "YELLOW"%s.", GetLocation(PumpkinLocation[pumpkinIndex][Pos][0], PumpkinLocation[pumpkinIndex][Pos][1], PumpkinLocation[pumpkinIndex][Pos][2]));
            SendClientMessageToAll(X11_ORANGE, "[Halloween] Cari pumpkin secepatnya, dapatkan uang dan koleksi pumpkin untuk ditukarkan menjadi hadiah.");

            if(DestroyDynamicPickup(pumpkinPickup))
                pumpkinPickup = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

            if(DestroyDynamic3DTextLabel(pumpkinLabel))
                pumpkinLabel = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            pumpkinPickup = CreateDynamicPickup(19320, 2, PumpkinLocation[pumpkinIndex][Pos][0], PumpkinLocation[pumpkinIndex][Pos][1], PumpkinLocation[pumpkinIndex][Pos][2], 0, 0, -1, 65.0, -1, 0);
            pumpkinLabel = CreateDynamic3DTextLabel("[Halloween Pumpkin]\n"YELLOW"Ambil pumpkin ini untuk mendapatkan hadiah!", X11_ORANGE,PumpkinLocation[pumpkinIndex][Pos][0], PumpkinLocation[pumpkinIndex][Pos][1], PumpkinLocation[pumpkinIndex][Pos][2]+0.45, 65.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 65.0, -1, 0);

            pumpkinFounded = false;
        }
        Halloween_Minute = 0;
    }
    return 1;
}

hook OnGameModeInit()
{
    //pumpkin store
    static ppst;
    ppst = CreateDynamicObject(19527, 1273.776245, 297.699035, 18.548822, 0.000000, 0.000000, 184.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppst, 1, 18752, "volcano", "lavalake", 0x00000000);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CreateDynamicObject(19320, 1272.814331, 292.297729, 18.799268, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19320, 1272.084228, 292.297729, 18.799268, 0.000000, 0.000000, 46.599990, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19320, 1272.505004, 292.932006, 18.799268, 0.000000, 0.000000, 138.599990, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19320, 1272.909179, 297.425781, 18.759267, 0.000000, 0.000015, 22.999994, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19320, 1272.237182, 297.140502, 18.759267, 0.000011, 0.000010, 69.599983, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19320, 1272.376708, 297.888763, 18.759267, 0.000010, -0.000011, 161.599945, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19527, 1272.536376, 291.458312, 18.518821, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3524, 1267.499023, 293.203735, 19.325963, 0.000000, 0.000000, 103.599975, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3092, 1267.874877, 293.310668, 20.178924, 0.000000, 0.000000, 270.000000, 0, 0, -1, 200.00, 200.00); 

    CreateDynamicPickup(19320, 23, 1273.5792,294.3599,19.5547, 0, 0, -1, 30.00,-1, 0);
    CreateDynamic3DTextLabel("[Halloween Pumpkin Store]\n"WHITE"Gunakan "YELLOW"'/pumpkinstore' "WHITE"untuk akses menu", X11_ORANGE, 1273.5792,294.3599,19.5547+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.00, -1, 0);
    
    Halloween_Minute = 18;
    return 1;
}

hook OnPlayerPickUpDynPickup(playerid, STREAMER_TAG_PICKUP:pickupid)
{
    if(pickupid == pumpkinPickup)
    {
        if(DestroyDynamicPickup(pumpkinPickup))
            pumpkinPickup = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(pumpkinLabel))
            pumpkinLabel = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        SendClientMessageToAllEx(X11_ORANGE, "[Halloween] Pumpkin telah ditemukan oleh %s, selamat ya!", GetPlayerRoleplayName(playerid));
        GivePlayerMoneyEx(playerid, PumpkinLocation[pumpkinIndex][Cash]);
        
        new randpump = RandomEx(1, 8);
        AccountData[playerid][pPumpkins] += randpump;

        static string[144];
        format(string, sizeof(string), "~y~Cash ~g~+$%s~n~~y~%d Pumpkins", FormatMoney(PumpkinLocation[pumpkinIndex][Cash]), randpump);
        GameTextForPlayer(playerid, string, 5000, 3);
        
        static fileName[144];
		format(fileName, sizeof(fileName), "PlayerEvent/%d.ini", AccountData[playerid][pID]);
		if(!dini_Exists(fileName))
		{
            dini_Create(fileName);
			dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
		}
		else
		{
			dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
		}

        pumpkinFounded = true;
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            PlayAudioStreamForPlayer(i, "https://dl.sndup.net/xmhjk/awdas.mp3");
        }
        Halloween_Minute = 18;
        PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
    }
    return 1;
}

Dialog:PumpkinStoreCatalog(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    static fileName[144];
    format(fileName, sizeof(fileName), "PlayerEvent/%d.ini", AccountData[playerid][pID]);

    switch(listitem)
    {
        case 0: //refill health
        {
            if(AccountData[playerid][pPumpkins] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pumpkin anda tidak cukup!");

            AccountData[playerid][pPumpkins] -= 10;
            if(dini_Exists(fileName))
            {
                dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
            }
            SetPlayerHealthEx(playerid, 100.00);
        }
        case 1: //body armour
        {
            if(AccountData[playerid][pPumpkins] < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pumpkin anda tidak cukup!");
            
            AccountData[playerid][pPumpkins] -= 50;
            if(dini_Exists(fileName))
            {
                dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
            }
            SetPlayerArmourEx(playerid, 100.00);
        }
        case 2: //10x burger & energy drink
        {
            if(AccountData[playerid][pPumpkins] < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pumpkin anda tidak cukup!");

            AccountData[playerid][pPumpkins] -= 25;
            if(dini_Exists(fileName))
            {
                dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
            }
            Inventory_Add(playerid, "Chicken BBQ", 2355, 10);
            Inventory_Add(playerid, "Coconut Water", 19564, 10);
        }
        case 3: //3x Pil Stres
        {
            if(AccountData[playerid][pPumpkins] < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pumpkin anda tidak cukup!");

            AccountData[playerid][pPumpkins] -= 25;
            if(dini_Exists(fileName))
            {
                dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
            }
            Inventory_Add(playerid, "Pil Stres", 1241, 3);
        }
        case 4: //good mood
        {
            if(AccountData[playerid][pPumpkins] < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pumpkin anda tidak cukup!");
            
            AccountData[playerid][pPumpkins] -= 50;
            if(dini_Exists(fileName))
            {
                dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
            }
            AccountData[playerid][pHunger] = 100;
            AccountData[playerid][pThirst] = 100;
            AccountData[playerid][pStress] = 0;
        }
        case 5: //7x Perban
        {
            if(AccountData[playerid][pPumpkins] < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pumpkin anda tidak cukup!");
            
            AccountData[playerid][pPumpkins] -= 50;
            Inventory_Add(playerid, "Perban", 11736, 7);
        }
        case 6: //reset all delay job & sidejob
        {
            if(AccountData[playerid][pPumpkins] < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pumpkin anda tidak cukup!");
            
            AccountData[playerid][pPumpkins] -= 50;
            if(dini_Exists(fileName))
            {
                dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
            }
            AccountData[playerid][pMowingSidejobDelay] = 0;
            AccountData[playerid][pSweeperSidejobDelay] = 0;
            AccountData[playerid][pForkliftSidejobDelay] = 0;
            AccountData[playerid][pTrashCollectorDelay] = 0;
            AccountData[playerid][pPizzaSidejobDelay] = 0;
        }
        case 7: //Bullet
        {
            if(AccountData[playerid][pPumpkins] < 750) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pumpkin anda tidak cukup!");
            
            new counting = 0;
            foreach(new v : PvtVehicles)
            {
                if(PlayerVehicle[v][pVehOwnerID] == AccountData[playerid][pID])
                    counting++;
            }
            if(counting >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai batas slot maksimum kendaraan!");

            AccountData[playerid][pPumpkins] -= 750;
            if(dini_Exists(fileName))
            {
                dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
            }
            Vehicle_Create(playerid, 541, 1283.7992,325.4675,19.0313,246.1803, -1, -1, 0, 0);
        }
        case 8: //NRG-500
        {
            if(AccountData[playerid][pPumpkins] < 750) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pumpkin anda tidak cukup!");

            new counting = 0;
            foreach(new v : PvtVehicles)
            {
                if(PlayerVehicle[v][pVehOwnerID] == AccountData[playerid][pID])
                    counting++;
            }
            if(counting >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai batas slot maksimum kendaraan!");

            AccountData[playerid][pPumpkins] -= 750;
            if(dini_Exists(fileName))
            {
                dini_IntSet(fileName, "Pumpkin", AccountData[playerid][pPumpkins]);
            }
            Vehicle_Create(playerid, 522, 1283.7992,325.4675,19.0313,246.1803, -1, -1, 0, 0);
        }
    }
    return 1;
}

YCMD:pumpkininfo(playerid, params[], help)
{
    if(!pumpkinFounded)
    {
        SendClientMessageEx(playerid, X11_ORANGE, "[Halloween Pumpkin] "WHITE"Pumpkin telah spawn dan terlihat di sekitar "YELLOW"%s.", GetLocation(PumpkinLocation[pumpkinIndex][Pos][0], PumpkinLocation[pumpkinIndex][Pos][1], PumpkinLocation[pumpkinIndex][Pos][2]));
    }
    else
    {
        SendClientMessage(playerid, X11_ORANGE, "[Halloween] "WHITE"Pumpkin telah ditemukan oleh seseorang, semoga beruntung lain waktu!");
    }
    return 1;
}

YCMD:pumpkinstore(playerid, params[], help)
{
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1273.5792,294.3599,19.5547)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di toko pumpkin!");

    Dialog_Show(playerid, "PumpkinStoreCatalog", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Toko Pumpkin "YELLOW"(%d pumpkin anda)", AccountData[playerid][pPumpkins]), 
    "Prizes\tRequirements\n\
    Refill Health\t10 Pumpkins\n\
    "GRAY"Body Armour\t"GRAY"50 Pumpkins\n\
    10x Burger & 10x Energy Drink\t25 Pumpkins\n\
    "GRAY"3x Pil Stres\t"GRAY"25 Pumpkins\n\
    Good Mood (HBE Full & 0 Stress)\t50 Pumpkins\n\
    "GRAY"7x Perban\t"GRAY"50 Pumpkins\n\
    Reset All Delays (Job & Sidejob)\t50 Pumpkins\n\
    "GRAY"Bullet Vehicle\t"GRAY"750 Pumpkins\n\
    NRG-500 Vehicle\t750 Pumpkins", "Pilih", "Batal");
    return 1;
}