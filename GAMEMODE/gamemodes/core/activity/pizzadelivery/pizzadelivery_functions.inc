#include <YSI_Coding\y_hooks>

new 
    pizzaRandom[MAX_PLAYERS],
    bool:pizzaHoldingBox[MAX_PLAYERS],
    pizzaDelivered[MAX_PLAYERS],
    STREAMER_TAG_CP:pizzaDeliveryCP[MAX_PLAYERS],
    STREAMER_TAG_ACTOR:pizzaDeliveryActor[MAX_PLAYERS],
    STREAMER_TAG_RACE_CP:pizzaDeliveryRCP[MAX_PLAYERS],
    Float:LastDeliveryPos[MAX_PLAYERS][3];

new Float:deliveryPizzaPos[][4] =
{
    {2066.7166,-1554.4839,13.4350,179.7448},
    {2067.3674,-1562.1831,13.4271,269.6723},
    {2165.4395,-1591.3445,14.3464,164.8878},
    {2144.0735,-1663.1464,15.0859,223.5632},
    {2380.1338,-1785.6791,13.5469,90.1361},
    {2465.2712,-2020.3114,14.1242,0.5121},
    {2524.0166,-1998.6398,13.7826,133.6760},
    {1895.4528,-2068.4399,15.6689,358.9366},
    {1871.2330,-2019.6190,13.5469,272.1851},
    {1888.3387,-1982.4719,13.5469,87.9433},
    {1851.7847,-2070.0181,15.4812,359.6451},
    {901.6682,-1515.2704,14.2706,182.7288},
    {875.3144,-1512.8068,14.0767,89.9813},
    {850.3485,-1520.0602,14.1548,266.7029},
    {841.2031,-1471.9012,14.0548,176.7754},
    {822.5012,-1504.5887,14.1036,355.0638},
    {898.3594,-1473.7689,14.0486,180.2455},
    {901.0463,-1447.4612,14.1325,271.4497},
    {699.8604,-1059.8367,49.4217,60.2611},
    {558.5953,-1160.5479,54.4223,28.3008},
    {416.4971,-1154.5746,76.6876,153.0086},
    {315.8352,-1769.9829,4.6369,178.9923},
    {305.3634,-1770.6270,4.5383,178.0523},
    {295.3319,-1765.2373,4.5468,180.8724},
    {280.8471,-1767.7390,4.5401,179.6191},
    {2148.6609,-1433.6676,25.5391,89.6681},
    {2147.7288,-1366.7965,25.6418,175.1854},
    {2230.4780,-1396.3513,24.0000,358.7771},
    {2388.3479,-1345.9991,24.6876,88.9944},
    {2469.7310,-1295.5570,29.9714,90.2477},
    {2467.5007,-1277.9868,29.9247,91.9828},
    {2109.9192,-1774.5371,13.3921,176.5834},
    {1667.4263,-2107.5388,14.0723,178.6776},
    {1674.1346,-2122.1038,14.1460,314.6656},
    {1695.6345,-2125.2014,13.8101,358.2193},
    {1711.6489,-2101.7578,14.0210,179.9544},
    {1734.7507,-2129.6951,14.0210,359.1592},
    {1734.0468,-2098.5535,14.0366,176.1942},
    {1804.2885,-2136.9043,13.5469,179.9776},
    {1894.1879,-2133.7681,15.4663,177.7843},
    {1851.8469,-2135.5281,15.3882,179.0377},
    {1932.2140,-1906.4768,15.0300,269.5920},
    {1913.3733,-1912.4474,15.2568,178.7245},
    {1872.2372,-1912.3772,15.2568,178.0979},
    {1973.2838,-1705.7667,15.9688,181.8579},
    {1981.5304,-1682.9026,17.0538,268.0253},
    {1969.4427,-1655.4490,15.9688,177.7845},
    {2017.4481,-1629.8541,13.7121,89.1338},
    {2015.9399,-1641.6246,13.7824,89.7605},
    {2012.6503,-1656.3591,13.5547,90.7005},
    {2065.7273,-1703.5770,14.1484,269.905},
    {2067.7620,-1731.5863,13.8762,270.218},
    {2128.8611,-1663.3694,15.0859,44.9534},
    {2141.2009,-1652.3282,15.0859,41.1933},
    {2158.1873,-1611.8651,14.3475,163.394},
    {2142.8372,-1605.2330,14.3516,159.634},
    {2178.5269,-1599.7531,14.3451,67.2002},
    {2192.6011,-1593.1652,14.3516,249.538},
    {2282.3071,-1641.7023,15.8898,180.314},
    {2306.9958,-1678.5311,14.0012,358.892},
    {2327.7195,-1682.0583,14.9297,270.532},
    {2308.9270,-1715.0629,14.6496,179.351},
    {2326.7124,-1717.5782,13.5469,179.351},
    {2385.2771,-1712.0605,14.2422,176.844},
    {2402.5349,-1715.7249,14.1078,180.291},
    {2454.8655,-1708.1819,13.6209,180.314},
    {2495.4290,-1690.6121,14.7656,0.1464},
    {2524.8943,-1703.0956,13.3791,230.1118},
    {2522.7361,-1679.3091,15.4970,90.0504},
    {2530.8010,-1664.4039,15.1665,180.9178},
    {2524.1802,-1658.5734,15.4935,91.9304},
    {2513.4116,-1650.5201,14.3557,135.1708},
    {2486.4006,-1645.0592,14.0772,179.3512},
    {2451.8220,-1642.2000,13.7357,180.6046},
    {2391.0476,-1633.2347,13.4644,359.8329},
    {2415.9077,-1631.1102,13.5106,359.8329},
    {2434.5171,-1303.4148,24.9393,272.0987},
    {2435.9478,-1289.3165,25.0860,269.5920},
    {2434.3909,-1275.1591,24.4948,269.5919},
    {2403.6619,-1281.6805,25.0497,269.2553},
    {2403.3547,-1330.4277,25.3881,269.2553},
    {2402.8472,-1344.0446,25.3146,269.5686},
    {2191.4695,-1276.2802,25.1563,178.0745},
    {2230.0696,-1280.8721,25.3672,180.8945},
    {2126.6846,-1320.4252,26.6241,358.2428},
    {2153.8528,-1243.2770,25.3672,358.8460},
    {2090.8423,-1234.7131,25.6887,0.0994},
    {2209.7507,-1239.6089,24.1496,0.0994},
    {167.3416,-1308.1852,70.3513,90.9364},
    {219.5085,-1250.2250,78.3342,216.247},
    {251.7240,-1220.6786,75.9573,217.814},
    {299.8893,-1154.7938,81.1706,136.973},
    {980.1644,-676.8047,121.9763,32.9926},
    {1045.0745,-642.4418,120.1172,10.432},
    {1094.9221,-647.2815,113.6484,2.2621},
    {1112.1053,-742.1914,100.1329,93.129},
    {1093.8243,-806.4581,107.4193,10.745},
    {1034.5642,-812.6117,101.8516,20.458},
    {989.5396,-828.3120,95.4686,29.2320},
    {937.6780,-848.3472,93.6363,28.9187},
    {910.0782,-817.1683,103.1260,33.6187},
    {827.9423,-858.5177,70.3308,198.7236},
    {836.4332,-894.2547,68.7689,325.9147},
    {808.6165,-759.1194,76.5314,288.0009},
    {1298.4907,-798.6265,84.1406,181.176},
    {1468.5754,-905.7679,54.8359,0.6951},
    {1536.1390,-885.0715,57.6575,317.4781},
    {1540.0237,-851.4211,64.3361,90.6225},
    {1534.4662,-800.2454,72.8495,91.2491},
    {1527.4900,-772.7943,80.5781,134.8028},
    {1496.9948,-688.5139,95.3861,181.4900},
    {1442.5594,-629.3320,95.7186,180.8634}
};

new Float:pizzaOffset[][6] =
{
    {0.000, -1.040, 0.814, 270.000, 0.000, 0.000}, //1 / 0
    {0.000, -1.040, 0.764, 270.000, 0.000, 0.000}, //2
    {0.000, -1.040, 0.714, 270.000, 0.000, 0.000}, //3
    {0.000, -1.040, 0.664, 270.000, 0.000, 0.000}, //4
    {0.000, -1.040, 0.614, 270.000, 0.000, 0.000}, //5
    {0.000, -1.040, 0.564, 270.000, 0.000, 0.000}, //6
    {0.000, -1.040, 0.514, 270.000, 0.000, 0.000}, //7
    {0.000, -1.040, 0.464, 270.000, 0.000, 0.000}, //8
    {0.000, -1.040, 0.412, 270.000, 0.000, 0.000}, //9
    {0.000, -1.040, 0.360, 90.000, 0.000, 180.000} //10 / 9
};

hook OnGameModeInit()
{
    CreateDynamicPickup(1239, 23, 2119.4346,-1787.9850,13.5547, 0, 0, -1, 30.00, -1, 0);
    CreateDynamic3DTextLabel("[ Pizza Delivery Sidejob Point ]\n"WHITE"Press "GREEN"[Y] "WHITE"to start and cancel the delivery task", 0xFF99A4FF, 2119.4346,-1787.9850,13.5547+0.5, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.00, -1, 0);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pSideJob] == SIDEJOB_PIZZA && IsPlayerNearBoot(playerid, JobVehicle[playerid]))
        {
            if(pizzaHoldingBox[playerid])
            {
                if(pizzaDelivered[playerid] == 10) return 1;

                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                StopRunningAnimation(playerid);
                RemovePlayerAttachedObject(playerid, 9);
                pizzaHoldingBox[playerid] = false;

                PlayerPlaySound(playerid, SOUND_GET_ITEM, 0.0, 0.0, 0.0);

                VehicleCore[JobVehicle[playerid]][pizzaBox][pizzaDelivered[playerid]] = CreateDynamicObject(19571,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                AttachDynamicObjectToVehicle(VehicleCore[JobVehicle[playerid]][pizzaBox][pizzaDelivered[playerid]], JobVehicle[playerid], pizzaOffset[pizzaDelivered[playerid]][0], pizzaOffset[pizzaDelivered[playerid]][1], pizzaOffset[pizzaDelivered[playerid]][2], pizzaOffset[pizzaDelivered[playerid]][3], pizzaOffset[pizzaDelivered[playerid]][4], pizzaOffset[pizzaDelivered[playerid]][5]);

                Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

                ApplyAnimation(playerid, "CARRY", "putdwn105", 4.1, false, false, false, false, 0, true);
            }
            else
            {
                if(pizzaDelivered[playerid] == 10) return 1;

                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
                SetPlayerAttachedObject(playerid, 9, 2814, 1, 0.083000, 0.297000, -0.029000, -91.200042, 32.800014, 0.000000, 1.000000, 1.000000, 1.000000, 0, 0);
                pizzaHoldingBox[playerid] = true;

                PlayerPlaySound(playerid, SOUND_GET_ITEM, 0.0, 0.0, 0.0);

                if(DestroyDynamicObject(VehicleCore[JobVehicle[playerid]][pizzaBox][pizzaDelivered[playerid]]))
                    VehicleCore[JobVehicle[playerid]][pizzaBox][pizzaDelivered[playerid]] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                ApplyAnimation(playerid, "CARRY", "liftup105", 4.1, false, false, false, false, 0, true);
            }
        }

        if(IsPlayerInRangeOfPoint(playerid, 1.0, 2119.4346,-1787.9850,13.5547))
        {
            if(AccountData[playerid][pSideJob] == SIDEJOB_PIZZA)
            {
                DestroyVehicle(JobVehicle[playerid]);

                if(DestroyDynamicCP(pizzaDeliveryCP[playerid]))
                    pizzaDeliveryCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
                    pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

                if(DestroyDynamicRaceCP(pizzaDeliveryRCP[playerid]))
                    pizzaDeliveryRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                AccountData[playerid][pSideJob] = SIDEJOB_NONE;
                pizzaDelivered[playerid] = 0;
                pizzaRandom[playerid] = -1;
                pizzaHoldingBox[playerid] = false;

                AccountData[playerid][pPizzaSidejobDelay] = 1800;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pizza sidejob!");
            }
            else
            {
                if(AccountData[playerid][pPizzaSidejobDelay] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda masih memiliki delay %d menit.", AccountData[playerid][pPizzaSidejobDelay]/60));
                if(AccountData[playerid][pSideJob] != SIDEJOB_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang menjalankan sidejob lain, selesaikanlah!");
                if(AccountData[playerid][pMoney] < 250) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda butuh $250 sebagai biaya operasional!");

                TakePlayerMoneyEx(playerid, 250);
                DestroyVehicle(JobVehicle[playerid]);
                
                JobVehicle[playerid] = CreateVehicle(462, 2121.9526,-1784.0305,12.9850,359.4349, 6, 3, 60000, false);
                VehicleCore[JobVehicle[playerid]][vCoreFuel] = 35;
                SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
                VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
                VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
                PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
                SwitchVehicleEngine(JobVehicle[playerid], true);
                SwitchVehicleDoors(JobVehicle[playerid], false);

                for(new x; x < 10; x++)
                {
                    if(DestroyDynamicObject(VehicleCore[JobVehicle[playerid]][pizzaBox][x]))
                        VehicleCore[JobVehicle[playerid]][pizzaBox][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                    VehicleCore[JobVehicle[playerid]][pizzaBox][x] = CreateDynamicObject(19571,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                    AttachDynamicObjectToVehicle(VehicleCore[JobVehicle[playerid]][pizzaBox][x], JobVehicle[playerid], pizzaOffset[x][0], pizzaOffset[x][1], pizzaOffset[x][2], pizzaOffset[x][3], pizzaOffset[x][4], pizzaOffset[x][5]);
                }

                if(DestroyDynamicCP(pizzaDeliveryCP[playerid]))
                    pizzaDeliveryCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
                    pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

                if(DestroyDynamicRaceCP(pizzaDeliveryRCP[playerid]))
                    pizzaDeliveryRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                pizzaRandom[playerid] = random(sizeof(deliveryPizzaPos));
                pizzaDeliveryCP[playerid] = CreateDynamicCP(deliveryPizzaPos[pizzaRandom[playerid]][0], deliveryPizzaPos[pizzaRandom[playerid]][1], deliveryPizzaPos[pizzaRandom[playerid]][2], 2.0, 0, 0, playerid, 10000, -1, 0);

                LastDeliveryPos[playerid][0] = 2121.9526;
                LastDeliveryPos[playerid][1] = -1784.0305;
                LastDeliveryPos[playerid][2] = 12.9850;

                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memulai pizza sidejob!");

                ShowPlayerFooter(playerid, "~g~Sidejob Pizza Delivery: ~w~Antarkan ~y~10 pizza~n~~w~ke tempat yang telah ditandai dengan ~r~icon ~w~pada map anda!", 15000);

                ShowItemBox(playerid, "Cash", "Removed $250x", 1212, 5);
                SendClientMessage(playerid, -1, "You have paid a pizza operational fee of $250. Follow the "RED"checkpoint "WHITE"until completion!");

                AccountData[playerid][pSideJob] = SIDEJOB_PIZZA;
                pizzaDelivered[playerid] = 0;
                pizzaHoldingBox[playerid] = false;
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pSideJob] == SIDEJOB_PIZZA && checkpointid == pizzaDeliveryCP[playerid])
    {
        if(!pizzaHoldingBox[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus memegang pizza. Tekan 'Y' di dekat kendaraan pizza anda!");

        if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
            pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

        new randskin = RandomEx(1, 311);
        pizzaDeliveryActor[playerid] = CreateDynamicActor(randskin, deliveryPizzaPos[pizzaRandom[playerid]][0], deliveryPizzaPos[pizzaRandom[playerid]][1], deliveryPizzaPos[pizzaRandom[playerid]][2], deliveryPizzaPos[pizzaRandom[playerid]][3], true, 100.0, 0, 0, -1, 200.00, -1, 0);
        ApplyDynamicActorAnimation(pizzaDeliveryActor[playerid], "GANGS", "prtial_gngtlkF", 4.1, true, false, false, false, 0);

        AccountData[playerid][pActivityTime] = 1;
        pDeliveringPizzaTimer[playerid] = true;
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGIRIM");
        ShowProgressBar(playerid);

        Streamer_Update(playerid, STREAMER_TYPE_ACTOR);
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(AccountData[playerid][pSideJob] == SIDEJOB_PIZZA && checkpointid == pizzaDeliveryRCP[playerid])
    {
        DestroyVehicle(JobVehicle[playerid]);

        if(DestroyDynamicCP(pizzaDeliveryCP[playerid]))
            pizzaDeliveryCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

        if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
            pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

        if(DestroyDynamicRaceCP(pizzaDeliveryRCP[playerid]))
            pizzaDeliveryRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

        AccountData[playerid][pSideJob] = SIDEJOB_NONE;
        pizzaDelivered[playerid] = 0;
        pizzaRandom[playerid] = -1;
        pizzaHoldingBox[playerid] = false;
        
        AccountData[playerid][pPizzaSidejobDelay] = 1800;

        GivePlayerMoneyEx(playerid, 300);

        ShowItemBox(playerid, "Cash", "Received $300x", 1212, 5);

        PlayerPlaySound(playerid, 183, 0.0, 0.0, 0.0);
        GameTextForPlayer(playerid, "mission passed!~n~~w~$300", 8900, 0);
        SetTimerEx("StopMissPassed", 8000, false, "i", playerid);

        SendClientMessage(playerid, -1, "You have received a bonus for returning the vehicle!");
    }
    return 1;
}