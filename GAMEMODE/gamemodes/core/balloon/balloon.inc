#include <YSI_Coding\y_hooks>

new STREAMER_TAG_OBJECT:LS_Ballon,
    LS_BallonStep,
    bool:LS_BallonLanded;
hook OnGameModeInit()
{
    CreateDynamicObject(11496, 316.062469, -1842.562377, 5.804977, 0.000000, 0.000015, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(3361, 310.508209, -1833.670532, 3.917092, 0.000015, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(11496, 316.062469, -1842.572387, 5.794977, 0.000000, -0.000015, 179.999908, 0, 0, -1, 200.00, 200.00); 
    LS_Ballon = CreateDynamicObject(19336, 321.845611, -1842.355590, 5.669423, 0.000000, 0.000015, 0.000000, 0, 0, -1, 200.00, 200.00); // landing
    LS_BallonStep = 1;
    LS_BallonLanded = true;
    SetTimer("BalloonTakeOff", 300000, false);
    return 1;
}

hook OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid)
{
    if(objectid == LS_Ballon)
    {
        switch(LS_BallonStep)
        {
            case 1:
            {
                LS_BallonStep = 2;
                MoveDynamicObject(LS_Ballon, 615.645568, -1842.355590, 77.119392, 5.0, 0.0, 0.000015, 0.0); //ke point 1
            }
            case 2:
            {
                LS_BallonStep = 3;
                MoveDynamicObject(LS_Ballon, 842.606079, -1697.065795, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 3:
            {
                LS_BallonStep = 4;
                MoveDynamicObject(LS_Ballon, 1086.061035, -1409.525024, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 4:
            {
                LS_BallonStep = 5;
                MoveDynamicObject(LS_Ballon, 1086.061035, -1069.144042, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 5:
            {
                LS_BallonStep = 6;
                MoveDynamicObject(LS_Ballon, 1229.922241, -884.793945, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 6:
            {
                LS_BallonStep = 7;
                MoveDynamicObject(LS_Ballon, 1523.341674, -926.383850, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 7:
            {
                LS_BallonStep = 8;
                MoveDynamicObject(LS_Ballon, 1777.651489, -926.383850, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 8:
            {
                LS_BallonStep = 9;
                MoveDynamicObject(LS_Ballon, 1937.511962, -1053.913452, 77.119392, 5.0, 0.0, 0.000015, 0.0); //approach pos
            }
            case 9:
            {
                LS_BallonStep = 10;
                MoveDynamicObject(LS_Ballon, 1971.551635, -1353.333496, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 10:
            {
                LS_BallonStep = 11;
                MoveDynamicObject(LS_Ballon, 1971.551635, -1604.594116, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 11:
            {
                LS_BallonStep = 12;
                MoveDynamicObject(LS_Ballon, 2234.361328, -1846.283935, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 12:
            {
                LS_BallonStep = 13;
                MoveDynamicObject(LS_Ballon, 2234.361328, -2041.233642, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 13:
            {
                LS_BallonStep = 14;
                MoveDynamicObject(LS_Ballon, 1978.300537, -2093.554199, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 14:
            {
                LS_BallonStep = 15;
                MoveDynamicObject(LS_Ballon, 1417.810546, -2183.205078, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 15:
            {
                LS_BallonStep = 16;
                MoveDynamicObject(LS_Ballon, 1250.161376, -1907.783081, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 16:
            {
                LS_BallonStep = 17;
                MoveDynamicObject(LS_Ballon, 988.761108, -1775.382934, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 17:
            {
                LS_BallonStep = 18;
                MoveDynamicObject(LS_Ballon, 497.140777, -1775.382934, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 18:
            {
                LS_BallonStep = 19;
                MoveDynamicObject(LS_Ballon, 321.845611, -1842.355590, 77.119392, 5.0, 0.0, 0.000015, 0.0);
            }
            case 19:
            {
                LS_BallonStep = 20;
                LS_BallonLanded = true;
                MoveDynamicObject(LS_Ballon, 321.845611, -1842.355590, 5.669423, 5.0, 0.0, 0.000015, 0.0);
            }
            case 20:
            {
                LS_BallonStep = 1;
                LS_BallonLanded = true;
                SetTimer("BalloonTakeOff", 120000, false);
            }
        }
    }
    return 1;
}

forward BalloonTakeOff();
public BalloonTakeOff()
{
    if(!LS_BallonLanded) return 0;
    if(!IsValidDynamicObject(LS_Ballon)) return 0;

    LS_BallonLanded = false;
    MoveDynamicObject(LS_Ballon, 321.845611, -1842.355590, 77.119392, 5.0, 0.0, 0.000015, 0.0); //approach pos for takeoff
    return 1;
}