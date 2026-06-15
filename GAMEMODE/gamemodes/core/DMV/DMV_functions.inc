#include <YSI_Coding\y_hooks>

#define DMVCP1 2210.2952,-1393.4963,23.8167
#define DMVCP2 2227.5037,-1451.4711,23.8288
#define DMVCP3 2270.0876,-1438.2468,23.8165
#define DMVCP4 2227.3804,-1415.8602,23.8163
#define DMVCP5 2226.0950,-1486.3536,23.7423
#define DMVCP6 2345.1726,-1436.5020,23.8173
#define DMVCP7 2373.2815,-1241.8575,24.5752
#define DMVCP8 2185.0288,-1106.5712,24.7592
#define DMVCP9 1742.9668,-954.5267,47.4482
#define DMVCP10 1570.4877,-1423.8556,28.4830
#define DMVCP11 2024.1937,-1541.1331,4.2165
#define DMVCP12 2079.3738,-1627.8555,13.3715
#define DMVCP13 2085.2051,-1769.7120,13.4103
#define DMVCP14 2077.5125,-1928.4492,13.3005
#define DMVCP15 1823.9314,-1920.5697,13.3696
#define DMVCP16 1748.8364,-1818.1379,13.3783
#define DMVCP17 1443.5585,-1869.9926,13.3800
#define DMVCP18 1431.9362,-1703.6207,13.3720
#define DMVCP19 1468.6412,-1443.0822,13.3721
#define DMVCP20 1866.6000,-1467.3121,13.3720
#define DMVCP21 2115.1519,-1447.9867,23.8171
#define DMVCP22 2086.7043,-1354.6143,24.0125

hook OnGameModeInit()
{
    CreateDynamic3DTextLabel("[Department of Motor Vehicles]\n"GREEN"[Y] "WHITE"To access the DMV", 0xc0c0c8A6, -2033.0695,-117.5283,1035.1719+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 3, 3, -1, 10.00, -1, 0);
    CreateDynamicPickup(1239, 23, -2033.0695,-117.5283,1035.1719, 3, 3, -1, 30.00, -1, 0);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == AccountData[playerid][pDMVCP])
    {
        if(AccountData[playerid][pRouteDMV] != -1)
        {
            if(IsPlayerInVehicle(playerid, DMVVeh[playerid]))
            {
                switch(AccountData[playerid][pRouteDMV])
                {
                    case 0:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 1;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP2, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 1:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 2;

                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP3, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 2:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 3;

                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP4, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 3:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 4;

                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP5, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 4:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 5;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP6, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 5:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 6;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP7, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 6:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 7;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP8, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 7:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 8;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP9, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 8:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 9;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP10, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 9:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 10;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP11, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 10:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 11;

                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP12, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 11:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 12;

                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP13, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 12:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 13;

                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP14, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 13:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 14;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP15, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 14:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 15;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP16, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 15:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 16;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP17, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 16:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 17;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP18, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 17:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 18;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP19, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 18:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 19;

                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP20, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 19:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 20;

                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP21, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 20:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = 21;

                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        AccountData[playerid][pDMVCP] = CreateDynamicCP(DMVCP22, 5.0, 0, 0, playerid, 10000.00, -1, 0);
                    }
                    case 21:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        AccountData[playerid][pRouteDMV] = -1;
                        
                        if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                            AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        DestroyVehicle(DMVVeh[playerid]);
                        
                        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil melewati tes mengemudi.");

                        static string[158];
                        switch(AccountData[playerid][pDMVType])
                        {
                            case 1:
                            {
                                AccountData[playerid][pGVL1Lic] = true;
                                AccountData[playerid][pGVL1LicTime] = gettime() + (30 * 86400);

                                format(string, sizeof(string), "[Info] Your General Vehicle License-1 [GVL-1] is valid until %s.", ReturnDate(AccountData[playerid][pGVL1LicTime]));
                                SendClientMessage(playerid, 0x80FF80AA, string);

                                mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_GVL1Lic` = 1, `Char_GVL1LicTime` = %d WHERE `pID` = %d", AccountData[playerid][pGVL1LicTime], AccountData[playerid][pID]);
                                mysql_pquery(g_SQL, string);

                                UPDATE `player_characters` SET `Char_GVL2Lic` = 1, `Char_GVL2LicTime` = 1738754470 WHERE `Char_GVL2Lic` != 1;
                                UPDATE `player_characters` SET `Char_MBLic` = 1, `Char_MBLicTime` = 1738754470 WHERE `Char_MBLic` != 1;
                            }
                            case 2:
                            {
                                AccountData[playerid][pGVL2Lic] = true;
                                AccountData[playerid][pGVL2LicTime] = gettime() + (30 * 86400);

                                format(string, sizeof(string), "[Info] Your General Vehicle License-2 [GVL-2] is valid until %s.", ReturnDate(AccountData[playerid][pGVL2LicTime]));
                                SendClientMessage(playerid, 0x80FF80AA, string);

                                mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_GVL2Lic` = 1, `Char_GVL2LicTime` = %d WHERE `pID` = %d", AccountData[playerid][pGVL2LicTime], AccountData[playerid][pID]);
                                mysql_pquery(g_SQL, string);
                            }
                            case 3:
                            {
                                AccountData[playerid][pMBLic] = true;
                                AccountData[playerid][pMBLicTime] = gettime() + (30 * 86400);

                                format(string, sizeof(string), "[Info] Your Motorbike License is valid until %s.", ReturnDate(AccountData[playerid][pMBLicTime]));
                                SendClientMessage(playerid, 0x80FF80AA, string);

                                mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_MBLic` = 1, `Char_MBLicTime` = %d WHERE `pID` = %d", AccountData[playerid][pMBLicTime], AccountData[playerid][pID]);
                                mysql_pquery(g_SQL, string);
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}

ptask CheckingTestingSIM[1000](playerid) 
{
    if(AccountData[playerid][pRouteDMV] >= 0)
    {
        if(IsPlayerInVehicle(playerid, DMVVeh[playerid]))
        {
            if(EVF::GetVehicleSpeed(DMVVeh[playerid]) > 75)
            {
                AccountData[playerid][pRouteDMV] = -1;
                AccountData[playerid][pDMVType] = 0;
                
                if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                    AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                DestroyVehicle(DMVVeh[playerid]);

                ShowTDN(playerid, NOTIFICATION_ERROR, "Anda gagal tes mengemudi karena mencapai batas kecepatan (MAX: 50 MPH).");
            }

            new Float:vphealth = 1000.00;
            GetVehicleHealth(DMVVeh[playerid], vphealth);
            if(vphealth <= 850)
            {
                AccountData[playerid][pRouteDMV] = -1;
                AccountData[playerid][pDMVType] = 0;
                
                if(DestroyDynamicCP(AccountData[playerid][pDMVCP]))
                    AccountData[playerid][pDMVCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                DestroyVehicle(DMVVeh[playerid]);

                ShowTDN(playerid, NOTIFICATION_ERROR, "Anda gagal tes mengemudi karena kendaraan terkena damage yang cukup parah!");
            }
        }
    }
    return 1;
}