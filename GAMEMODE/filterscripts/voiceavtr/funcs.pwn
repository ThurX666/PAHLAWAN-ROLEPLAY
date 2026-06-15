#define MAX_FREQ 10000

#define WHITE	"{ffffff}"
#define RED		"{ff0000}"
#define YELLOW	"{ffff00}"
#define	PAHLAWAN "{DA9100}"
#define	CYAN	"{00FFFF}"

enum e_player_voice_stuff
{
    SV_BOOL:pHasRadio,
	SV_BOOL:pIsRadioOn,
    SV_BOOL:pIsRadioMicOn,
	SV_BOOL:pBroadcast,
	SV_BOOL:pInBroadcast,
	SV_BOOL:pIsCastMicOn,
	SV_BOOL:pTogBroadcast,
    VoiceModeDistance,
    pRadioFreq,
	SV_BOOL:pDuringPhoneConvers,
	pCallingWithPlayerID
};
new PlayerVoiceData[MAX_PLAYERS][e_player_voice_stuff];

new SV_GSTREAM:vdRadioStream[MAX_FREQ] = { SV_NULL, ... };
new SV_GSTREAM:vdPhoneStream[MAX_PLAYERS] = { SV_NULL, ... };
new SV_GSTREAM:vdBroadcastStream = SV_NULL;
new SV_LSTREAM:vdLocalStream[MAX_PLAYERS] = { SV_NULL, ... };

new STREAMER_TAG_3D_TEXT_LABEL:MouthStatusLabel[MAX_PLAYERS];

new SV_BOOL:BroadCastStatus;

GetName(playerid)
{
	new name[MAX_PLAYER_NAME];
 	GetPlayerName(playerid,name,sizeof(name));
	return name;
}

ResetVoiceVariables(playerid)
{
	if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
        MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		
	PlayerVoiceData[playerid][pHasRadio] = false;
	PlayerVoiceData[playerid][pIsRadioOn] = false;
	PlayerVoiceData[playerid][pIsRadioMicOn] = false;
	PlayerVoiceData[playerid][pBroadcast] = false;
	PlayerVoiceData[playerid][pInBroadcast] = false;
	PlayerVoiceData[playerid][pIsCastMicOn] = false;
	PlayerVoiceData[playerid][pTogBroadcast] = true;
	PlayerVoiceData[playerid][VoiceModeDistance] = 2;
	PlayerVoiceData[playerid][pRadioFreq] = 0;
	PlayerVoiceData[playerid][pDuringPhoneConvers] = false;
	PlayerVoiceData[playerid][pCallingWithPlayerID] = INVALID_PLAYER_ID;

	SvDetachListenerFromStream(vdBroadcastStream, playerid);
}

forward _KickPlayerDelayed(playerid);
public _KickPlayerDelayed(playerid)
{
	Kick(playerid);
	return 1;
}

forward UpdateVoiceMegaStatus(playerid, SV_BOOL:togmeg);
public UpdateVoiceMegaStatus(playerid, SV_BOOL:togmeg)
{
	switch(togmeg)
	{
		case SV_FALSE:
		{
			SvUpdateDistanceForLStream(vdLocalStream[playerid], 25.7);
		}
		case SV_TRUE:
		{
			SvUpdateDistanceForLStream(vdLocalStream[playerid], 150.7);
		}
	}
	return 1;
}

forward AssignFreqToFSVoice(playerid, SV_BOOL:hasradio, freq);
public AssignFreqToFSVoice(playerid, SV_BOOL:hasradio, freq)
{
	PlayerVoiceData[playerid][pHasRadio] = hasradio;
	SvDetachListenerFromStream(vdRadioStream[PlayerVoiceData[playerid][pRadioFreq]], playerid); //dikeluarkan dari mendengarkan freq lama
    SvAttachListenerToStream(vdRadioStream[freq], playerid); //dimasukkan ke freq baru sebagai pendengar
    PlayerVoiceData[playerid][pRadioFreq] = freq;
	return 1;
}

//sanews broadcast
forward UpdatePlayerBroadcast(playerid, SV_BOOL:isbroadcaston);
public UpdatePlayerBroadcast(playerid, SV_BOOL:isbroadcaston)
{
	//playerid == sanews
	PlayerVoiceData[playerid][pBroadcast] = isbroadcaston; //broadcast sanews diset status on/off
	BroadCastStatus = isbroadcaston;

	if(!PlayerVoiceData[playerid][pBroadcast])
	{
		//posisi mati, jika broadcast sanews off maka dikeluarkan dari pendengar
		for(new x; x < MAX_PLAYERS; x++) //untuk sluruh player di server
		{
			if(IsPlayerConnected(x))
			{
				SvDetachListenerFromStream(vdBroadcastStream, x);
			}
		}
	}
	return 1;
}

forward UpdatePlayerInviteBC(playerid, SV_BOOL:isinbc); //pembicara status izin ngomong / diundang
public UpdatePlayerInviteBC(playerid, SV_BOOL:isinbc)
{
	PlayerVoiceData[playerid][pInBroadcast] = isinbc;
}

forward UpdatePlayerCastToggle(playerid, SV_BOOL:togglemic); //pembicara mic
public UpdatePlayerCastToggle(playerid, SV_BOOL:togglemic)
{
	PlayerVoiceData[playerid][pIsCastMicOn] = togglemic;
	return 1;
}

forward UpdatePlayerListeningCast(playerid, SV_BOOL:caststatus);
public UpdatePlayerListeningCast(playerid, SV_BOOL:caststatus)
{
	PlayerVoiceData[playerid][pTogBroadcast] = caststatus;

	switch(caststatus)
	{
		case SV_FALSE:
		{
			SvDetachListenerFromStream(vdBroadcastStream, playerid);
		}
		case SV_TRUE:
		{
			if(IsPlayerInAnyVehicle(playerid))
			{
				SvAttachListenerToStream(vdBroadcastStream, playerid);
			}
		}
	}
	return 1;
}
//end of sanews broadcast

forward UpdatePlayerVoiceKey(playerid, dkey);
public UpdatePlayerVoiceKey(playerid, dkey)
{
	switch(dkey)
	{
		case 0: //Z
		{
			SvRemoveAllKeys(playerid);
			SvAddKey(playerid, 0x5A);
		}
		case 1: //M
		{
			SvRemoveAllKeys(playerid);
			SvAddKey(playerid, 0x4D);
		}
		case 2: //L
		{
			SvRemoveAllKeys(playerid);
			SvAddKey(playerid, 0x4C);
		}
		case 3: //B
		{
			SvRemoveAllKeys(playerid);
			SvAddKey(playerid, 0x42);
		}
		case 4: //X
		{
			SvRemoveAllKeys(playerid);
			SvAddKey(playerid, 0x58);
		}
		case 5: //R
		{
			SvRemoveAllKeys(playerid);
			SvAddKey(playerid, 0x52);
		}
		case 6: //P
		{
			SvRemoveAllKeys(playerid);
			SvAddKey(playerid, 0x50);
		}
		default: //B
		{
			SvRemoveAllKeys(playerid);
			SvAddKey(playerid, 0x42);
		}
	}
	return 1;
}

forward UpdatePlayerVoiceDistance(playerid, SV_FLOAT:lstreamdistance);
public UpdatePlayerVoiceDistance(playerid, SV_FLOAT:lstreamdistance)
{
	SvUpdateDistanceForLStream(vdLocalStream[playerid], lstreamdistance);
	return 1;
}

forward UpdatePlayerVoiceMicToggle(playerid, SV_BOOL:togglemic);
public UpdatePlayerVoiceMicToggle(playerid, SV_BOOL:togglemic)
{
	PlayerVoiceData[playerid][pIsRadioMicOn] = togglemic;
	return 1;
}

forward UpdatePlayerVoiceRadioToggle(playerid, SV_BOOL:togradio);
public UpdatePlayerVoiceRadioToggle(playerid, SV_BOOL:togradio)
{
	PlayerVoiceData[playerid][pIsRadioOn] = togradio;

	switch(PlayerVoiceData[playerid][pIsRadioOn])
	{
		case SV_FALSE: //posisi mati tidak bisa mendengar percakapan radio
		{
			SvDetachListenerFromStream(vdRadioStream[PlayerVoiceData[playerid][pRadioFreq]], playerid);
		}
		case SV_TRUE: //posisi hidup bisa dengar
		{
			SvAttachListenerToStream(vdRadioStream[PlayerVoiceData[playerid][pRadioFreq]], playerid);
		}
	}
	return 1;
}

forward ConnectPlayerCalling(playerid, inlinewithID);
public ConnectPlayerCalling(playerid, inlinewithID)
{
	//playerid adalah player yang ditelpon, inlinewithid adalah player yang menelepon

	PlayerVoiceData[playerid][pCallingWithPlayerID] = inlinewithID;
	PlayerVoiceData[inlinewithID][pCallingWithPlayerID] = playerid;

	vdPhoneStream[inlinewithID] = SvCreateGStream(0xFFA200FF, "Phone");

	PlayerVoiceData[playerid][pDuringPhoneConvers] = true;
	PlayerVoiceData[inlinewithID][pDuringPhoneConvers] = true;

    if (vdPhoneStream[inlinewithID]) {
        SvAttachListenerToStream(vdPhoneStream[inlinewithID], inlinewithID);
        SvAttachListenerToStream(vdPhoneStream[inlinewithID], playerid);
    }

    if (vdPhoneStream[inlinewithID] && PlayerVoiceData[playerid][pCallingWithPlayerID] != INVALID_PLAYER_ID) {
        SvAttachSpeakerToStream(vdPhoneStream[inlinewithID], playerid);
    }

    if(vdPhoneStream[inlinewithID] && PlayerVoiceData[inlinewithID][pCallingWithPlayerID] != INVALID_PLAYER_ID){
        SvAttachSpeakerToStream(vdPhoneStream[inlinewithID], inlinewithID);
    }

	if(DestroyDynamic3DTextLabel(MouthStatusLabel[inlinewithID]))
        MouthStatusLabel[inlinewithID] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	MouthStatusLabel[inlinewithID] = CreateDynamic3DTextLabel("[Telepon]", 0xff91a4d9, 0.0, 0.0, 0.6, 20.0, inlinewithID, INVALID_VEHICLE_ID, 1, -1, -1, -1, 20.0, -1, 0);

	if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
        MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	MouthStatusLabel[playerid] = CreateDynamic3DTextLabel("[Telepon]", 0xff91a4d9, 0.0, 0.0, 0.6, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 20.0, -1, 0);
	return 1;
}

forward DisconnectPlayerCalling(playerid, inlinewithID);
public DisconnectPlayerCalling(playerid, inlinewithID)
{
	//playerid adalah player yang ditelpon, inlinewithid adalah player yang menelepon

	if(IsPlayerConnected(inlinewithID))
	{
		if (vdPhoneStream[inlinewithID] && PlayerVoiceData[inlinewithID][pCallingWithPlayerID] != INVALID_PLAYER_ID) {
			SvDetachSpeakerFromStream(vdPhoneStream[inlinewithID], inlinewithID);
		}

		if(vdPhoneStream[inlinewithID] && PlayerVoiceData[playerid][pCallingWithPlayerID] != INVALID_PLAYER_ID){
			SvDetachSpeakerFromStream(vdPhoneStream[inlinewithID], playerid);
		}

		if(vdPhoneStream[inlinewithID]){
			SvDetachListenerFromStream(vdPhoneStream[inlinewithID], inlinewithID);
			SvDetachListenerFromStream(vdPhoneStream[inlinewithID], playerid);
			SvDeleteStream(vdPhoneStream[inlinewithID]);
			vdPhoneStream[inlinewithID] = SV_NULL;
		}

		if (vdPhoneStream[playerid] && PlayerVoiceData[inlinewithID][pCallingWithPlayerID] != INVALID_PLAYER_ID) {
			SvDetachSpeakerFromStream(vdPhoneStream[playerid], inlinewithID);
		}

		PlayerVoiceData[inlinewithID][pDuringPhoneConvers] = false;
		PlayerVoiceData[inlinewithID][pCallingWithPlayerID] = INVALID_PLAYER_ID;

		if(DestroyDynamic3DTextLabel(MouthStatusLabel[inlinewithID]))
        	MouthStatusLabel[inlinewithID] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
	}

	if(vdPhoneStream[playerid])
	{
		if(IsPlayerConnected(inlinewithID))
		{
			SvDetachListenerFromStream(vdPhoneStream[playerid], inlinewithID);
		}
		SvDetachListenerFromStream(vdPhoneStream[playerid], playerid);
		SvDeleteStream(vdPhoneStream[playerid]);
		vdPhoneStream[playerid] = SV_NULL;
	}

	if(vdPhoneStream[playerid] && PlayerVoiceData[playerid][pCallingWithPlayerID] != INVALID_PLAYER_ID){
		SvDetachSpeakerFromStream(vdPhoneStream[playerid], playerid);
	}

	PlayerVoiceData[playerid][pDuringPhoneConvers] = false;
	PlayerVoiceData[playerid][pCallingWithPlayerID] = INVALID_PLAYER_ID;

	if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
        MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
	return 1;
}

KickEx(playerid, time = 1000)
{
	SetTimerEx("_KickPlayerDelayed", time, false, "i", playerid);
	return 1;
}