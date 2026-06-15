
/*

		Spalvotų checkpoint kūrimo include/Coloured checkpoint include
		Autorius/Author "Bebras" 2014 ©
		v0.1

		Thanks to Vince from forum.sa-mp.com for the idea!
								
*/




/*

		native CreateColouredCheckpoint(Float:x,Float:y,Float:z,color);
		native DestroyColouredCheckpoint(cpid);
		native IsPlayerInAnyColouredCheckpoint(playerid);
		native IsPlayerInColouredCheckpoint(playerid,cpid);
		native ChangeColouredCheckpointColour(cpid,newcolor);
*/





#define CHECKPOINT_COLOUR_BLACK			1
#define CHECKPOINT_COLOUR_BLUE			2
#define CHECKPOINT_COLOUR_GREEN			3
#define CHECKPOINT_COLOUR_GREY			4
#define CHECKPOINT_COLOUR_ORANGE		5
#define CHECKPOINT_COLOUR_WHITE			6
#define CHECKPOINT_COLOUR_YELLOW		7

#define CHECKPOINT_COLOR_BLACK 			CHECKPOINT_COLOUR_BLACK
#define CHECKPOINT_COLOR_BLUE 			CHECKPOINT_COLOUR_BLUE
#define CHECKPOINT_COLOR_GREEN 			CHECKPOINT_COLOUR_GREEN
#define CHECKPOINT_COLOR_GREY 			CHECKPOINT_COLOUR_GREY
#define CHECKPOINT_COLOR_ORANGE 		CHECKPOINT_COLOUR_ORANGE
#define CHECKPOINT_COLOR_WHITE 			CHECKPOINT_COLOUR_WHITE 
#define CHECKPOINT_COLOR_YELLOW 		CHECKPOINT_COLOUR_YELLOW

#define COLOURED_CHECKPOINT_DIAMETER	1.0
#define COLOURED_CHECKPOINT_HEIGHT		2.0

#define MAX_COLOURED_CHECKPOINTS				40


forward OnPlayerExitColouredCheckpoint(playerid,cpid);
forward OnPlayerEnterColouredCheckpoint(playerid,cpid);

enum E_COLOURED_CHECKPOINTS {
	ObjectId,
	#if defined _inc_streamer
		AreaId
	#else 
		Float:PosX,
		Float:PosY,
		Float:PosZ
	#endif
};


static CCPData[MAX_COLOURED_CHECKPOINTS][E_COLOURED_CHECKPOINTS];

#if !defined _inc_streamer
	static bool:IsPlayerInCCP[MAX_PLAYERS][MAX_COLOURED_CHECKPOINTS];
#endif


stock CreateColouredCheckpoint(Float:x,Float:y,Float:z,color) 
{
	for(new i = 0; i < sizeof(CCPData); i++)
	{
		if(IsValidObject(CCPData[i][ObjectId])) continue;


		CCPData[i][ObjectId] = CreateObject(1317, x, y, z, 0.0, 0.0, 0.0);
		SetObjectMaterial(CCPData[i][ObjectId], 0, 18646, "matcolours", CCP_GetColourName(color), CCP_GetColourARGB(color)); 

		#if !defined _inc_streamer
			CCPData[i][PosX] = x;
			CCPData[i][PosY] = y;
			CCPData[i][PosZ] = z;
		#else 
			CCPData[i][AreaId] = CreateDynamicCylinder(x,y,z,z + COLOURED_CHECKPOINT_HEIGHT, COLOURED_CHECKPOINT_DIAMETER);
		#endif

		return i;
	}
	return -1;
}
stock DestroyColouredCheckpoint(cpid)
{
	if(-1 < cpid < MAX_COLOURED_CHECKPOINTS)
	{
		#if defined _inc_streamer
			DestroyDynamicArea(CCPData[cpid][AreaId]);
		#endif
		return DestroyObject(CCPData[cpid][ObjectId]);
	}
	return 0;
}

stock IsPlayerInAnyColouredCheckpoint(playerid)
{
	#if defined _inc_streamer
		for(new i = 0; i < sizeof(CCPData); i++)
		{
			if(!IsValidObject(CCPData[i][ObjectId])) continue;
			if(IsPlayerInDynamicArea(playerid, CCPData[i][AreaId]))
				return true;
		}
		return false;
	#else 
		for(new i = 0; i < sizeof(IsPlayerInCCP[]); i++)
		{
			if(IsPlayerInCCP[playerid][i]) 
				return true;
		}
		return false;

	#endif
}
stock IsPlayerInColouredCheckpoint(playerid,cpid)
{
	if(-1 > cpid > MAX_COLOURED_CHECKPOINTS) return false;
	#if defined _inc_streamer 
		if(!IsValidObject(CCPData[cpid][ObjectId])) return false;
		return IsPlayerInDynamicArea(playerid, CCPData[cpid][AreaId]);
	#else 
		return IsPlayerInCCP[playerid][cpid];
	#endif
}

stock ChangeColouredCheckpointColour(cpid,newcolor)
{
	if(-1 > cpid > MAX_COLOURED_CHECKPOINTS) return 0;
	SetObjectMaterial(CCPData[cpid][ObjectId], 0, 18646, "matcolours", CCP_GetColourName(newcolor), CCP_GetColourARGB(newcolor)); 
	return 1;
}	

//////////////////////////////////////////////////////////////////////////////////////////////////
////////////						Internal STUFF 								      ////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

#if defined _inc_streamer
	
	public OnPlayerEnterDynamicArea(playerid, areaid)
	{
		for(new i = 0; i < sizeof(CCPData); i++)
		{
			if(!IsValidObject(CCPData[i][ObjectId])) continue;
			if(CCPData[i][AreaId] != areaid) continue;
			
			#if defined OnPlayerEnterColouredCheckpoint
				OnPlayerEnterColouredCheckpoint(playerid,i);
			#endif
		}
		#if defined CCP_OnPlayerEnterDynamicArea
			return CCP_OnPlayerEnterDynamicArea(playerid,areaid);
		#endif 
	}
	#if defined _ALS_OnPlayerEnterDynamicArea
		#undef OnPlayerEnterDynamicArea 
	#else 
		#define _ALS_OnPlayerEnterDynamicArea
	#endif
	#define OnPlayerEnterDynamicArea CCP_OnPlayerEnterDynamicArea
	#if defined CCP_OnPlayerEnterDynamicArea
		forward CCP_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif 

	public OnPlayerLeaveDynamicArea(playerid, areaid)
	{
		for(new i = 0; i < sizeof(CCPData); i++)
		{
			if(!IsValidObject(CCPData[i][ObjectId])) continue;
			if(CCPData[i][AreaId] != areaid) continue;

			#if defined OnPlayerExitColouredCheckpoint
				OnPlayerExitColouredCheckpoint(playerid,i);
			#endif
		}
		#if defined CCP_OnPlayerLeaveDynamicArea
			return CCP_OnPlayerLeaveDynamicArea(playerid,areaid);
		#endif 
	}
	#if defined CCP_OnPlayerLeaveDynamicArea
		#undef OnPlayerLeaveDynamicArea 
	#else 
		#define _ALS_OnPlayerLeaveDynamicArea
	#endif
	#define OnPlayerLeaveDynamicArea CCP_OnPlayerLeaveDynamicArea
	#if defined CCP_OnPlayerLeaveDynamicArea
		forward CCP_OnPlayerLeaveDynamicArea(playerid,areaid);
	#endif 

#else 

	// If streamer isn't used, we need our own timer :(
	// Also we need to monitor all player locations

	public OnGameModeInit()
	{
		SetTimer("CCP_CheckForEntries", 50, true);
		#if defined CCP_OnGameModeInit
			CCP_OnGameModeInit();
		#endif
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit 
	#else 
		#define _ALS_OnGameModeInit
	#endif 
	#define OnGameModeInit CCP_OnGameModeInit
	#if defined CCP_OnGameModeInit
		forward CCP_OnGameModeInit();
	#endif

	forward CCP_CheckForEntries();
	public CCP_CheckForEntries()
	{
		for(new j = 0; j < MAX_PLAYERS; j++)
		{
			if(!IsPlayerConnected(j)) continue;

			for(new i = 0; i < sizeof(CCPData); i++)
			{
				if(!IsValidObject(CCPData[i][ObjectId])) continue;

				// If the player is in range
				new Float:x,Float:y,Float:z;
				GetPlayerPos(j, x, y, z);
				if(floatabs(CCPData[i][PosX] - x) < COLOURED_CHECKPOINT_DIAMETER / 2 &&
					floatabs(CCPData[i][PosY] - y) < COLOURED_CHECKPOINT_DIAMETER / 2 &&
					floatabs(CCPData[i][PosZ] - z) < COLOURED_CHECKPOINT_HEIGHT)
				{
					// If he wasn't in checkpoint at previous check
					if(!IsPlayerInCCP[j][i])
					{
						IsPlayerInCCP[j][i] = true;
						#if defined OnPlayerEnterColouredCheckpoint
							OnPlayerEnterColouredCheckpoint(j,i);
						#endif
					}
				}
				// IF hes not in range but he WAS in checkpoint at previous check.
				else if(IsPlayerInCCP[j][i])
				{
					IsPlayerInCCP[j][i] = false;
					#if defined OnPlayerExitColouredCheckpoint
						OnPlayerExitColouredCheckpoint(j,i);
					#endif
				}
			}
		}
	}

#endif 




CCP_GetColourName(color)
{
	new s[7];
	switch(color)
	{
		case CHECKPOINT_COLOUR_BLACK: 		s = "black";
		case CHECKPOINT_COLOUR_BLUE: 		s = "blue";
		case CHECKPOINT_COLOUR_GREEN:		s = "green";
		case CHECKPOINT_COLOUR_GREY:		s = "grey";
		case CHECKPOINT_COLOUR_ORANGE:		s = "orange";
		case CHECKPOINT_COLOUR_WHITE:		s = "white";
		case CHECKPOINT_COLOUR_YELLOW:		s = "yellow";
	}
	return s;
}
CCP_GetColourARGB(color)
{
	switch(color)
	{
		case CHECKPOINT_COLOUR_BLACK: 		return 0xAA000000;
		case CHECKPOINT_COLOUR_BLUE: 		return 0xAA0000FF;
		case CHECKPOINT_COLOUR_GREEN:		return 0xAA00FF00;
		case CHECKPOINT_COLOUR_GREY:		return 0xAAC0C0C0;
		case CHECKPOINT_COLOUR_ORANGE:		return 0xAAFF8000;
		case CHECKPOINT_COLOUR_WHITE:		return 0xAAFFFFFF;
		case CHECKPOINT_COLOUR_YELLOW:		return 0xAAFFFF00;
	}
	return 0;
}