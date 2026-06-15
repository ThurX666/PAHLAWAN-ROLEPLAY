#include <YSI_Coding\y_hooks>

#define NUM_FERRIS_CAGES        10
#define FERRIS_WHEEL_ID         18877
#define FERRIS_CAGE_ID          18879
#define FERRIS_BASE_ID          18878
#define FERRIS_DRAW_DISTANCE    300.0
#define FERRIS_WHEEL_SPEED      0.0015

#define FERRIS_WHEEL_Z_ANGLE  	-54.0 // This is the heading the entire ferris wheel is at (beware of gimbal lock)

new Float:gFerrisOrigin[3] = {420.263671, -1958.554687, 21.994705};

// Cage offsets for attaching to the main wheel
new Float:gFerrisCageOffsets[NUM_FERRIS_CAGES][3] = {
{0.0699, 0.0600, -11.7500},
{-6.9100, -0.0899, -9.5000},
{11.1600, 0.0000, -3.6300},
{-11.1600, -0.0399, 3.6499},
{-6.9100, -0.0899, 9.4799},
{0.0699, 0.0600, 11.7500},
{6.9599, 0.0100, -9.5000},
{-11.1600, -0.0399, -3.6300},
{11.1600, 0.0000, 3.6499},
{7.0399, -0.0200, 9.3600}
};

// SA-MP objects
new gFerrisWheel;
new gFerrisCages[NUM_FERRIS_CAGES];

new Float:gCurrentTargetYAngle = 0.0; // Angle of the Y axis of the wheel to rotate to.
new gWheelTransAlternate = 0; // Since MoveObject requires some translation target to intepolate
						    // rotation, the world pos target is alternated by a small amount.

UpdateWheelTarget()
{
    gCurrentTargetYAngle += 90.0; // There are 10 carts, so 360 / 10
    if(gCurrentTargetYAngle >= 360.0) {
		gCurrentTargetYAngle = 0.0;
    }
	if(gWheelTransAlternate) gWheelTransAlternate = 0;
	else gWheelTransAlternate = 1;
}

forward RotateWheel();
public RotateWheel()
{
    UpdateWheelTarget();
    
    new Float:fModifyWheelZPos = 0.0;
    if(gWheelTransAlternate) fModifyWheelZPos = 0.05;
    
	MoveObject(gFerrisWheel, gFerrisOrigin[0], gFerrisOrigin[1], gFerrisOrigin[2]+fModifyWheelZPos, FERRIS_WHEEL_SPEED, 0.0, gCurrentTargetYAngle, FERRIS_WHEEL_Z_ANGLE);
    
    foreach(new i : Player) if(AccountData[i][pSpawned])
    {
        if(IsPlayerInDynamicArea(i, CarnavalZone))
        {
            PlayerPlaySound(i, 1076, 0.0, 0.0, 0.0);
        }
    }
    return 1;
}

hook OnGameModeInit()
{
    gFerrisWheel = CreateObject(FERRIS_WHEEL_ID, gFerrisOrigin[0], gFerrisOrigin[1], gFerrisOrigin[2], 0.0, 0.0, FERRIS_WHEEL_Z_ANGLE, 200.00);
	CreateObject(FERRIS_BASE_ID, gFerrisOrigin[0], gFerrisOrigin[1], gFerrisOrigin[2], 0.0, 0.0, FERRIS_WHEEL_Z_ANGLE, 200.00); //base
	  							 
	for(new x; x < NUM_FERRIS_CAGES; x++)
    {
        gFerrisCages[x] = CreateObject(FERRIS_CAGE_ID, gFerrisOrigin[0], gFerrisOrigin[1], gFerrisOrigin[2], 0.0, 0.0, FERRIS_WHEEL_Z_ANGLE, 200.00);
		
        AttachObjectToObject(gFerrisCages[x], gFerrisWheel, gFerrisCageOffsets[x][0], gFerrisCageOffsets[x][1], gFerrisCageOffsets[x][2], 0.0, 0.0, FERRIS_WHEEL_Z_ANGLE, false);
	}

    SetTimer("RotateWheel",5555,false);
    return 1;
}

hook OnObjectMoved(objectid)
{
    if(objectid == gFerrisWheel)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            if(IsPlayerInDynamicArea(i, CarnavalZone))
            {
                PlayerPlaySound(i, 1188, 0.0, 0.0, 0.0);
                PlayerPlaySound(i, 0, 0.0, 0.0, 0.0);
            }
        }
        SetTimer("RotateWheel",5555,false);
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == CarnavalZone)
    {
        PlayerPlaySound(playerid, 1188, 0.0, 0.0, 0.0);
        PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
    }
    return 1;
}