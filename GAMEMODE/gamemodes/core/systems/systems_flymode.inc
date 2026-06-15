// Default Move Speed
#define MOVE_SPEED              100.0
#define ACCEL_RATE              0.03
#define ACCEL_MODE              true

// Players Mode
#define CAMERA_MODE_NONE    	0
#define CAMERA_MODE_FLY     	1

// Key state definitions
#define MOVE_FORWARD    		1
#define MOVE_BACK       		2
#define MOVE_LEFT       		3
#define MOVE_RIGHT      		4
#define MOVE_FORWARD_LEFT       5
#define MOVE_FORWARD_RIGHT      6
#define MOVE_BACK_LEFT          7
#define MOVE_BACK_RIGHT         8

// Enumeration for storing data about the player
enum noclipenum
{
	cameramode,
	flyobject,
	mode,
	lrold,
	udold,
	lastmove,
	Float:accelmul,
    
    Float:accelrate,
    Float:maxspeed,
    bool:accel
}
new noclipdata[MAX_PLAYERS][noclipenum];

new bool:FlyMode[MAX_PLAYERS];

#define InFlyMode(%0) FlyMode[%0]

//--------------------------------------------------

forward IsFlyMode(playerid);
public IsFlyMode(playerid) { return noclipdata[playerid][cameramode]; }

YCMD:savecampos(playerid, arg[], help)
{
	if (AccountData[playerid][pAdmin] < 10)
		return PermissionError(playerid);

    new Float:camPosX, Float:camPosY, Float:camPosZ;
    new Float:lookPosX, Float:lookPosY, Float:lookPosZ;
    
    GetPlayerCameraPos(playerid, camPosX, camPosY, camPosZ);
    GetPlayerCameraFrontVector(playerid, lookPosX, lookPosY, lookPosZ);
    
    new File:file = fopen("camera_position.txt", io_append);

    if (file)
    {
        new string[2048];

        format(string, sizeof(string), "\n\n[%s]\nSetPlayerCameraPos(playerid, %f, %f, %f);\nSetPlayerCameraLookAt(playerid, %f, %f, %f);\n\n", ReturnTime(), camPosX, camPosY, camPosZ,camPosX + lookPosX, camPosY + lookPosY, camPosZ + lookPosZ);
        fwrite(file, string);
        fclose(file);
    }
    SendClientMessage(playerid, -1, "Posisi kamera telah disimpan ke dalam file.");
    return 1;
}

YCMD:flymode(playerid, arg[], help)
{
	if (AccountData[playerid][pAdmin] < 10)
		return PermissionError(playerid);

	if(help)
	{
		SendClientMessage(playerid, 0xFFFF00FF, "______________________________________________");
		SendClientMessage(playerid, 0x3BBD44FF, "Toggle flymode.");
		return 1;
	}

    // Place the player in and out of edit mode
	if(FlyMode[playerid]) CancelFlyMode(playerid);
	else StartFlyMode(playerid);
	return 1;
}

YCMD:fmspeed(playerid, arg[], help)
{
	if (AccountData[playerid][pAdmin] < 10)
		return PermissionError(playerid);

	if(help)
	{
		SendClientMessage(playerid, 0xFFFF00FF, "______________________________________________");
		SendClientMessage(playerid, 0x3BBD44FF, "Change flymode speed, must be 5-200.");
		return 1;
	}

    new Float:newspeed;
    sscanf(arg, "F(-1.0)", newspeed);
    
    if(newspeed == -1.0)
        newspeed = MOVE_SPEED;
    else if(newspeed < 5.0)
        newspeed = 5.0;
    else if(newspeed > 200.0)
        newspeed = 200.0;
	
	noclipdata[playerid][maxspeed] = newspeed;
    SendClientMessageEx(playerid, 0x3BBD44FF, "Flymode max speed set to %0.2f", newspeed);
	return 1;
}

YCMD:fmaccel(playerid, arg[], help)
{
	if (AccountData[playerid][pAdmin] < 10)
		return PermissionError(playerid);

	if(help)
	{
		SendClientMessage(playerid, 0xFFFF00FF, "______________________________________________");
		SendClientMessage(playerid, 0x3BBD44FF, "Change flymode acceleration rate, must be 0.005 - 0.05");
		return 1;
	}

    new Float:newacc;
    sscanf(arg, "F(-1.0)", newacc);
    
    if(newacc == -1.0)
        newacc = ACCEL_RATE;
    else if(newacc < 0.005)
        newacc = 0.005;
    else if(newacc > 0.05)
        newacc = 0.05;
	
	noclipdata[playerid][accelrate] = newacc;
    SendClientMessageEx(playerid, 0x3BBD44FF, "Flymode max speed set to %0.3f", newacc);
	return 1;
}

YCMD:fmtoggle(playerid, arg[], help)
{
	if (AccountData[playerid][pAdmin] < 10)
		return PermissionError(playerid);
		
	if(help)
	{
		SendClientMessage(playerid, 0xFFFF00FF, "______________________________________________");
		SendClientMessage(playerid, 0x3BBD44FF, "Toggle flymode acceleration.");
		return 1;
	}

	noclipdata[playerid][accel] = !noclipdata[playerid][accel];
	SendClientMessageEx(playerid, 0x3BBD44FF, "Flymode acceleration toggled %s", noclipdata[playerid][accel] ? ("on") : ("off"));
	return 1;
}

//--------------------------------------------------

forward GetMoveDirectionFromKeys(ud, lr);
public GetMoveDirectionFromKeys(ud, lr)
{
	new direction = 0;
	
    if(lr < 0)
	{
		if(ud < 0) 		direction = MOVE_FORWARD_LEFT; 	// Up & Left key pressed
		else if(ud > 0) direction = MOVE_BACK_LEFT; 	// Back & Left key pressed
		else            direction = MOVE_LEFT;          // Left key pressed
	}
	else if(lr > 0) 	// Right pressed
	{
		if(ud < 0)      direction = MOVE_FORWARD_RIGHT;  // Up & Right key pressed
		else if(ud > 0) direction = MOVE_BACK_RIGHT;     // Back & Right key pressed
		else			direction = MOVE_RIGHT;          // Right key pressed
	}
	else if(ud < 0) 	direction = MOVE_FORWARD; 	// Up key pressed
	else if(ud > 0) 	direction = MOVE_BACK;		// Down key pressed
	
	return direction;
}

//--------------------------------------------------

forward MoveCamera(playerid);
public MoveCamera(playerid)
{
	new Float:FV[3], Float:CP[3];
	//GetPlayerCameraPos(playerid, CP[0], CP[1], CP[2]);          // 	Cameras position in space
	GetDynamicObjectPos(noclipdata[playerid][flyobject], CP[0], CP[1], CP[2]);          // 	Cameras position in space
    GetPlayerCameraFrontVector(playerid, FV[0], FV[1], FV[2]);  //  Where the camera is looking at

	// Increases the acceleration multiplier the longer the key is held
	if(noclipdata[playerid][accelmul] <= 1.0) noclipdata[playerid][accelmul] += noclipdata[playerid][accelrate];

	// Determine the speed to move the camera based on the acceleration multiplier
	new Float:speed = noclipdata[playerid][maxspeed] * (noclipdata[playerid][accel] ? noclipdata[playerid][accelmul] : 1.0);

	// Calculate the cameras next position based on their current position and the direction their camera is facing
	new Float:X, Float:Y, Float:Z;
	GetNextCameraPosition(noclipdata[playerid][mode], CP, FV, X, Y, Z);
	MoveDynamicObject(noclipdata[playerid][flyobject], X, Y, Z, speed, 0.0, 0.0, 0.0);

    //SendClientMessage(playerid, -1, sprintf("(%0.1f, %0.1f, %0.1f) - (%0.1f, %0.1f, %0.1f) - (%0.1f, %0.1f, %0.1f)", CP[0], CP[1], CP[2], FV[0], FV[1], FV[2], X, Y, Z));
    
	// Store the last time the camera was moved as now
	noclipdata[playerid][lastmove] = GetTickCount();
	return 1;
}

forward SetFlyModePos(playerid, Float:x, Float:y, Float:z);
public SetFlyModePos(playerid, Float:x, Float:y, Float:z)
{
	if(FlyMode[playerid])
	{
		SetDynamicObjectPos(noclipdata[playerid][flyobject], x, y, z);
		noclipdata[playerid][lastmove] = GetTickCount();
		return 1;
	}
	return 0;
}

forward GetFlyModePos(playerid, &Float:x, &Float:y, &Float:z);
public GetFlyModePos(playerid, &Float:x, &Float:y, &Float:z)
{
	if(FlyMode[playerid])
	{
		GetDynamicObjectPos(noclipdata[playerid][flyobject], x, y, z);
		return 1;
	}
	return 0;
}


//--------------------------------------------------

forward GetNextCameraPosition(move_mode, Float:CP[3], Float:FV[3], &Float:X, &Float:Y, &Float:Z);
public GetNextCameraPosition(move_mode, Float:CP[3], Float:FV[3], &Float:X, &Float:Y, &Float:Z)
{
    // Calculate the cameras next position based on their current position and the direction their camera is facing
    #define OFFSET_X (FV[0]*6000.0)
	#define OFFSET_Y (FV[1]*6000.0)
	#define OFFSET_Z (FV[2]*6000.0)
	switch(move_mode)
	{
		case MOVE_FORWARD:
		{
			X = CP[0]+OFFSET_X;
			Y = CP[1]+OFFSET_Y;
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_BACK:
		{
			X = CP[0]-OFFSET_X;
			Y = CP[1]-OFFSET_Y;
			Z = CP[2]-OFFSET_Z;
		}
		case MOVE_LEFT:
		{
			X = CP[0]-OFFSET_Y;
			Y = CP[1]+OFFSET_X;
			Z = CP[2];
		}
		case MOVE_RIGHT:
		{
			X = CP[0]+OFFSET_Y;
			Y = CP[1]-OFFSET_X;
			Z = CP[2];
		}
		case MOVE_BACK_LEFT:
		{
			X = CP[0]+(-OFFSET_X - OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y + OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_BACK_RIGHT:
		{
			X = CP[0]+(-OFFSET_X + OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y - OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_FORWARD_LEFT:
		{
			X = CP[0]+(OFFSET_X  - OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  + OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_FORWARD_RIGHT:
		{
			X = CP[0]+(OFFSET_X  + OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  - OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
	}
}
//--------------------------------------------------

forward CancelFlyMode(playerid);
public CancelFlyMode(playerid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerCameraPos(playerid, x, y, z);
	
	AccountData[playerid][pInterior] = GetPlayerInterior(playerid);
    AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
    AccountData[playerid][pPos][0] = x;
	AccountData[playerid][pPos][1] = y;
	AccountData[playerid][pPos][2] = z;
    AccountData[playerid][pPos][3] = GetPlayerCameraFrontVector(playerid, x, y, z);

	FlyMode[playerid] = false;
	CancelEdit(playerid);
	TogglePlayerSpectating(playerid, false);

	DestroyDynamicObject(noclipdata[playerid][flyobject]);
	noclipdata[playerid][cameramode] = CAMERA_MODE_NONE;
	return 1;
}

//--------------------------------------------------

forward StartFlyMode(playerid);
public StartFlyMode(playerid)
{
	// Create an invisible object for the players camera to be attached to
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	noclipdata[playerid][flyobject] = CreateDynamicObject(19300, X, Y, Z, 0.0, 0.0, 0.0, .playerid = playerid, .streamdistance = 300.0, .drawdistance = 300.0);

	// Place the player in spectating mode so objects will be streamed based on camera location
	TogglePlayerSpectating(playerid, true);
	// Attach the players camera to the created object
	AttachCameraToDynamicObject(playerid, noclipdata[playerid][flyobject]);

	FlyMode[playerid] = true;
	noclipdata[playerid][cameramode] = CAMERA_MODE_FLY;
	return 1;
}

//--------------------------------------------------