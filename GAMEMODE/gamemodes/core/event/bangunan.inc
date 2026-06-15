#include <YSI_Coding\y_hooks>

new STREAMER_TAG_3D_TEXT_LABEL:bangunanLabel,
    STREAMER_TAG_CP:bangunanCP[MAX_PLAYERS],
    Float:bangunanProgress,
    pBangunanStep[MAX_PLAYERS],
    bool:pBangunanWorked[MAX_PLAYERS];

new Float:BangunanCoordinates[][3] =
{
    {-165.2475,2768.2332,62.6875}, //job point
    {-155.5368,2751.3264,63.7286}, //krikil
    {-154.2193,2743.0608,64.0407}, //pasir
    {-143.2367,2720.0464,62.8968}, //semen
    {-148.1358,2685.2878,62.2615}, //air
    {-166.9367,2678.6497,62.6836} //mixer
};

new Float:CorCoordinates[][3] =
{
    {-165.0650,2705.9705,67.8251},
    {-156.7011,2706.5967,67.8251},
    {-146.7511,2706.4509,67.8199},
    {-147.4178,2713.9160,67.8199},
    {-147.3879,2720.6123,67.8251},
    {-155.0750,2720.4951,67.8251},
    {-164.6533,2720.1250,67.8251},
    {-164.6026,2715.1262,67.8251},
    {-165.0802,2706.0610,62.9032},
    {-164.7987,2713.3789,62.9032},
    {-164.6726,2720.2039,62.9032},
    {-156.0766,2720.3728,62.9032},
    {-147.7529,2720.1975,62.9032},
    {-147.3586,2714.2124,62.8968},
    {-156.0920,2712.7075,62.4740}
};

forward StopMissPassed(playerid);
public StopMissPassed(playerid)
{
    PlayerPlaySound(playerid, 1188, 0.0, 0.0, 0.0);
    PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
    return 1;
}

forward BangunanTimer(playerid);
public BangunanTimer(playerid)
{
    if(!IsPlayerConnected(playerid)) 
    {
        KillTimer(p_BangunanTimer[playerid]);
        p_BangunanTimer[playerid] = -1;

        pBangunanWorked[playerid] = false;
        return 0;
    }

    if(!pBangunanWorked[playerid])
    {
        KillTimer(p_BangunanTimer[playerid]);
        p_BangunanTimer[playerid] = -1;
        return 0;
    }

    if(!IsValidDynamicCP(bangunanCP[playerid]))
    {
        KillTimer(p_BangunanTimer[playerid]);
        p_BangunanTimer[playerid] = -1;
        pBangunanWorked[playerid] = false;
        AccountData[playerid][pActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, true);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicCP(playerid, bangunanCP[playerid]))
    {
        KillTimer(p_BangunanTimer[playerid]);
        p_BangunanTimer[playerid] = -1;
        pBangunanWorked[playerid] = false;
        AccountData[playerid][pActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, true);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(pBangunanStep[playerid] > 0)
    {
        if(AccountData[playerid][pActivityTime] >= 6)
        {
            KillTimer(p_BangunanTimer[playerid]);
            p_BangunanTimer[playerid] = -1;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pThirst]--;

            if(DestroyDynamicCP(bangunanCP[playerid]))
                bangunanCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            pBangunanWorked[playerid] = false;

            if(pBangunanStep[playerid] == 9)
            {
                new randcash = RandomEx(150, 250);
                GivePlayerMoneyEx(playerid, randcash);

                LSFDMoneyVault -= randcash;
                
                new frmtmny[215];
                mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `emsmoneyvault` = %d WHERE `id` = 0", LSFDMoneyVault);
                mysql_pquery(g_SQL, frmtmny);

                pBangunanStep[playerid] = 0;

                bangunanProgress += 0.05;

                UpdateDynamic3DTextLabelText(bangunanLabel, -1, sprintf("[Pembangunan Puskesmas Pahlawan Roleplay]\n\nProgress: "GREEN"%.2f/100.00\n\n[Y] "WHITE"Bekerja", bangunanProgress));

                PlayerPlaySound(playerid, 183, 0.0, 0.0, 0.0);
                GameTextForPlayer(playerid, sprintf("mission passed!~n~~w~$%s",FormatMoney(randcash)), 8900, 0);
                SetTimerEx("StopMissPassed", 8000, false, "i", playerid);
                //ShowPlayerFooter(playerid, sprintf("Pekerjaan telah selesai, kamu mendapatkan ~g~$%s", FormatMoney(randcash)), 5000); 
            }
            else
            {
                pBangunanStep[playerid]++;

                switch(pBangunanStep[playerid])
                {
                    case 2:
                    {
                        bangunanCP[playerid] = CreateDynamicCP(BangunanCoordinates[5][0],BangunanCoordinates[5][1],BangunanCoordinates[5][2], 1.5, 0, 0, playerid, 100.0, -1, 0);
                        ShowPlayerFooter(playerid, "Letakkan ~g~krikil ~w~ke dalam ~y~mixer", 5000); 
                    }
                    case 4:
                    {
                        bangunanCP[playerid] = CreateDynamicCP(BangunanCoordinates[5][0],BangunanCoordinates[5][1],BangunanCoordinates[5][2], 1.5, 0, 0, playerid, 100.0, -1, 0);
                        ShowPlayerFooter(playerid, "Letakkan ~g~pasir ~w~ke dalam ~y~mixer", 5000); 
                    }
                    case 6:
                    {
                        bangunanCP[playerid] = CreateDynamicCP(BangunanCoordinates[5][0],BangunanCoordinates[5][1],BangunanCoordinates[5][2], 1.5, 0, 0, playerid, 100.0, -1, 0);
                        ShowPlayerFooter(playerid, "Letakkan ~g~semen ~w~ke dalam ~y~mixer", 5000); 
                    }
                    case 8:
                    {
                        bangunanCP[playerid] = CreateDynamicCP(BangunanCoordinates[5][0],BangunanCoordinates[5][1],BangunanCoordinates[5][2], 1.5, 0, 0, playerid, 100.0, -1, 0);
                        ShowPlayerFooter(playerid, "Letakkan ~g~air ~w~ke dalam ~y~mixer", 5000); 
                    }
                    case 9:
                    {
                        new randcp = random(sizeof(CorCoordinates));
                        bangunanCP[playerid] = CreateDynamicCP(CorCoordinates[randcp][0],CorCoordinates[randcp][1],CorCoordinates[randcp][2], 1.5, 0, 0, playerid, 100.0, -1, 0);
                        ShowPlayerFooter(playerid, "Anda harus segera ~y~mengecor ~w~bangunan dengan ~g~beton", 5000); 
                    }
                }
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    return 1;
}

hook OnGameModeInit()
{
    bangunanLabel = CreateDynamic3DTextLabel("[Pembangunan Puskesmas Pahlawan Roleplay]\n\nProgress: "GREEN"0.00/100.00\n\n[Y] "WHITE"Bekerja", -1, BangunanCoordinates[0][0],BangunanCoordinates[0][1],BangunanCoordinates[0][2], 15.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 15.0, -1, 0);
    
    //mapping
    static bngunxt;
    bngunxt = CreateDynamicObject(19911, -176.312576, 2687.981933, 64.682525, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2697.602294, 64.682525, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2707.212158, 64.682525, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2716.842285, 64.682525, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2726.461425, 64.682525, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2736.060791, 64.682525, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2752.141601, 64.682525, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2761.760742, 63.942474, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -172.939544, 2769.928466, 63.942474, 0.000000, 0.000000, 135.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -166.144256, 2776.723876, 63.942474, 0.000000, 0.000000, 135.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(16317, -152.255645, 2746.159423, 59.923427, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 10351, "beach_sfs", "ws_drysand", 0x00000000);
    bngunxt = CreateDynamicObject(16317, -152.255645, 2751.439208, 59.923427, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 12871, "ce_ground01", "sw_stones", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -171.472610, 2654.354248, 64.682525, 0.000000, 0.000007, 90.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2659.133544, 64.682525, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2668.743408, 64.682525, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -176.312576, 2678.373535, 64.682525, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -161.902587, 2654.354248, 65.702537, 0.000000, 0.000007, 90.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -152.322540, 2654.354248, 65.702537, 0.000000, 0.000007, 90.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -144.522460, 2654.274169, 65.972564, 0.000000, 0.000007, 90.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -139.692459, 2659.123046, 64.622482, 0.000000, 0.000000, 179.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -139.692459, 2668.762451, 64.622482, 0.000000, 0.000000, 179.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -139.692459, 2678.351806, 64.622482, 0.000000, 0.000000, 179.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -138.951080, 2687.826904, 64.622482, 0.000001, -0.000022, 170.699829, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -137.393341, 2697.339843, 64.332489, 0.000001, -0.000022, 170.699829, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -135.843673, 2706.803222, 64.162475, 0.000001, -0.000022, 170.699829, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -134.292343, 2716.277343, 64.002471, 0.000001, -0.000022, 170.699829, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    bngunxt = CreateDynamicObject(19911, -132.763595, 2725.614501, 64.002471, 0.000001, -0.000022, 170.699829, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(bngunxt, 0, 19071, "wssections", "wood1", 0x00000000);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CreateDynamicObject(5463, -155.982910, 2713.496826, 56.356369, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3361, -160.642669, 2701.210937, 63.525142, 0.000000, 0.000000, 180.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3502, -148.501602, 2733.709472, 64.325782, -0.099999, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3502, -148.265640, 2729.840576, 62.916156, -0.099999, 0.000000, 93.099952, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3502, -148.471038, 2733.784912, 58.206157, 269.899993, 90.000000, 93.099952, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -156.785873, 2701.916015, 65.704574, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -156.785873, 2701.916015, 65.874549, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -156.785873, 2701.445556, 65.704574, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -156.785873, 2701.916015, 66.104568, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3286, -145.007049, 2685.321777, 63.895614, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(13025, -166.158355, 2673.585693, 64.444549, 0.000000, 0.000000, 270.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2991, -148.695632, 2706.803466, 62.533374, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2991, -148.695632, 2708.824218, 62.533374, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2991, -165.965637, 2710.664062, 67.413391, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2991, -163.965652, 2710.664062, 67.413391, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3530, -148.364364, 2699.497070, 61.600021, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3530, -167.094436, 2699.497070, 61.600021, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3530, -148.364364, 2726.509521, 61.600021, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3530, -167.094436, 2726.509521, 61.600021, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1521, -141.698364, 2705.992431, 61.833473, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1521, -141.698364, 2708.592773, 63.913475, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1521, -141.698364, 2708.652832, 61.843513, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1521, -141.698242, 2713.943115, 61.833473, 0.000000, -0.000007, -90.000007, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1521, -141.698242, 2711.343017, 63.913475, 0.000000, -0.000007, -90.000007, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1521, -141.698242, 2711.282958, 61.843513, 0.000000, -0.000007, -90.000007, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(9618, -175.467346, 2719.970703, 71.224807, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1395, -147.805343, 2674.959716, 92.725646, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(18248, -145.409378, 2660.450927, 70.482063, 0.000000, 0.000000, 118.100006, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(7017, -176.183593, 2701.846679, 63.191005, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -143.812255, 2718.919677, 61.965106, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -143.812255, 2720.039062, 61.965106, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -143.812255, 2721.158447, 61.965106, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.312316, 2721.158447, 61.965106, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.312316, 2720.048339, 61.965106, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.312316, 2718.948730, 61.965106, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.812240, 2718.919677, 61.965106, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.812240, 2720.039062, 61.965106, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.812240, 2721.158447, 61.965106, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -145.312301, 2721.158447, 61.965106, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -145.312301, 2720.048339, 61.965106, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -145.312301, 2718.948730, 61.965106, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -143.812255, 2718.919677, 62.185104, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -143.812255, 2720.039062, 62.185104, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -143.812255, 2721.158447, 62.185104, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.312316, 2721.158447, 62.185104, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.312316, 2720.048339, 62.185104, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.312316, 2718.948730, 62.185104, 0.000007, 0.000000, 89.999977, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.812240, 2718.919677, 62.185104, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.812240, 2720.039062, 62.185104, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.812240, 2721.158447, 62.185104, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -145.312301, 2721.158447, 62.185104, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -145.312301, 2720.048339, 62.185104, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -145.312301, 2718.948730, 62.185104, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -143.812255, 2718.919677, 62.415081, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -143.812255, 2720.039062, 62.415081, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -143.812255, 2721.158447, 62.415081, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.312316, 2721.158447, 62.415081, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.312316, 2720.048339, 62.415081, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.312316, 2718.948730, 62.415081, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.812240, 2718.919677, 62.415081, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.812240, 2720.039062, 62.415081, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -144.812240, 2721.158447, 62.415081, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -145.312301, 2721.158447, 62.415081, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -145.312301, 2720.048339, 62.415081, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2060, -145.312301, 2718.948730, 62.415081, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3632, -147.334533, 2683.636962, 61.705860, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3632, -147.334533, 2683.026855, 61.705860, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    return 1;
}

hook OnPlayerConnect(playerid)
{
    RemoveBuildingForPlayer(playerid, 3241, -165.391, 2708.100, 62.226, 0.250);
    RemoveBuildingForPlayer(playerid, 3298, -165.391, 2708.100, 62.226, 0.250);
    RemoveBuildingForPlayer(playerid, 669, -155.093, 2711.229, 61.843, 0.250);
    RemoveBuildingForPlayer(playerid, 3242, -147.789, 2684.810, 63.218, 0.250);
    RemoveBuildingForPlayer(playerid, 3297, -147.789, 2684.810, 63.218, 0.250);
    RemoveBuildingForPlayer(playerid, 3285, -166.132, 2731.090, 63.070, 0.250);
    RemoveBuildingForPlayer(playerid, 3300, -166.132, 2731.090, 63.070, 0.250);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.5, BangunanCoordinates[0][0],BangunanCoordinates[0][1],BangunanCoordinates[0][2]))
        {
            if(bangunanProgress >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Proyek konstruksi ini telah mencapai progress 100 persen!");
            Dialog_Show(playerid, "JobBangunan", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Pembangunan Pahlawan Roleplay", ""WHITE"Saat ini kami sedang mengerjakan proyek konstruksi Puskesmas Pahlawan Roleplay\nApakah anda ingin mulai bekerja disini?", "Ya", "No");
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == bangunanCP[playerid] && pBangunanStep[playerid] > 0)
    {
        switch(pBangunanStep[playerid])
        {
            case 1, 3, 5, 7, 9:
            {
                ClearAnimations(playerid, true);

                pBangunanWorked[playerid] = true;
                AccountData[playerid][pActivityTime] = 1;
                p_BangunanTimer[playerid] = SetTimerEx("BangunanTimer", 1000, true, "i", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "BEKERJA");
                ShowProgressBar(playerid);

                ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);
            }
            case 2:
            {
                if(DestroyDynamicCP(bangunanCP[playerid]))
                    bangunanCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                bangunanCP[playerid] = CreateDynamicCP(BangunanCoordinates[2][0],BangunanCoordinates[2][1],BangunanCoordinates[2][2], 1.5, 0, 0, playerid, 100.0, -1, 0);
                ShowPlayerFooter(playerid, "Ambil ~g~pasir", 5000); 
                pBangunanStep[playerid]++;
            }
            case 4:
            {
                if(DestroyDynamicCP(bangunanCP[playerid]))
                    bangunanCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                bangunanCP[playerid] = CreateDynamicCP(BangunanCoordinates[3][0],BangunanCoordinates[3][1],BangunanCoordinates[3][2], 1.5, 0, 0, playerid, 100.0, -1, 0);
                ShowPlayerFooter(playerid, "Ambil ~g~semen", 5000); 
                pBangunanStep[playerid]++;
            }
            case 6:
            {
                if(DestroyDynamicCP(bangunanCP[playerid]))
                    bangunanCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                bangunanCP[playerid] = CreateDynamicCP(BangunanCoordinates[4][0],BangunanCoordinates[4][1],BangunanCoordinates[4][2], 1.5, 0, 0, playerid, 100.0, -1, 0);
                ShowPlayerFooter(playerid, "Ambil ~g~air", 5000); 
                pBangunanStep[playerid]++;
            }
            case 8:
            {
                ClearAnimations(playerid, true);
                
                pBangunanWorked[playerid] = true;
                AccountData[playerid][pActivityTime] = 1;
                p_BangunanTimer[playerid] = SetTimerEx("BangunanTimer", 1000, true, "i", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUAT BETON");
                ShowProgressBar(playerid);

                ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);
            }
        }
    }
    return 1;
}

Dialog:JobBangunan(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    if(bangunanProgress >= 100.00) return ShowTDN(playerid, NOTIFICATION_ERROR, "Proyek konstruksi ini telah mencapai progress 100 persen!");

    KillTimer(p_BangunanTimer[playerid]);
    p_BangunanTimer[playerid] = -1;

    pBangunanStep[playerid] = 1;
    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil memulai pekerjaan!");
    ShowPlayerFooter(playerid, "Ambil ~g~krikil", 5000); 

    if(DestroyDynamicCP(bangunanCP[playerid]))
        bangunanCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

    bangunanCP[playerid] = CreateDynamicCP(BangunanCoordinates[1][0],BangunanCoordinates[1][1],BangunanCoordinates[1][2], 1.5, 0, 0, playerid, 100.0, -1, 0);
    return 1;
}