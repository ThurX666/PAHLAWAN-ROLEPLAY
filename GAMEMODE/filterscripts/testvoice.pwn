#define FILTERSCRIPT

#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS	500

#include <core>
#include <float>
#include <streamer>
#include <sampvoice>
#include <sscanf2>
#include <easyDialog>
#include "./voiceavtr/funcs.pwn"
//#include "./voiceavtr/cmds.pwn"

public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid) 
{
    if (keyid == 0x42 && PlayerVoiceData[playerid][pHasRadio] == SV_TRUE && PlayerVoiceData[playerid][pIsRadioOn] == SV_TRUE && PlayerVoiceData[playerid][pIsRadioMicOn] == SV_TRUE && PlayerVoiceData[playerid][pRadioFreq] > 0)
    {
        for(new i; i < 800; i++)
        {
            if(IsPlayerConnected(i) && PlayerVoiceData[i][pRadioFreq] == PlayerVoiceData[playerid][pRadioFreq] && PlayerVoiceData[i][pIsRadioOn] == SV_TRUE)
            {
                PlayerPlaySound(i, 21000, 0.0, 0.0, 0.0);
            }
        }
        ApplyAnimation(playerid, "ped", "phone_talk", 4.1, true, true, true, true, 1, true);
        SetPlayerAttachedObject(playerid, 9, 19942, 6, 0.078999, 0.047999, 0.023999, 0.000000, 0.000000, 179.099899, 1.000000, 1.000000, 1.000000);
        SvAttachSpeakerToStream(vdRadioStream[PlayerVoiceData[playerid][pRadioFreq]], playerid);
        
        if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
            MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        MouthStatusLabel[playerid] = CreateDynamic3DTextLabel("[Radio]", 0x7fffd4d9, 0.0, 0.0, 0.6, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 20.0, -1, 0);
    }

    if(keyid == 0x42 && (PlayerVoiceData[playerid][pBroadcast] == SV_TRUE || PlayerVoiceData[playerid][pInBroadcast] == SV_TRUE) && PlayerVoiceData[playerid][pIsCastMicOn] == SV_TRUE)
    {
        SvAttachSpeakerToStream(vdBroadcastStream, playerid);
        
        if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
            MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        MouthStatusLabel[playerid] = CreateDynamic3DTextLabel("[Broadcast]", 0x7fffd4d9, 0.0, 0.0, 0.6, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 20.0, -1, 0);
    }

    if (keyid == 0x42 && PlayerVoiceData[playerid][pDuringPhoneConvers] == SV_TRUE)
    {
        if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
            MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        MouthStatusLabel[playerid] = CreateDynamic3DTextLabel("[Telepon]", 0xff91a4d9, 0.0, 0.0, 0.6, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 20.0, -1, 0);
    }

    if (keyid == 0x42 && vdLocalStream[playerid]) 
    {
        SvAttachSpeakerToStream(vdLocalStream[playerid], playerid);
        SvStreamParameterSet(vdLocalStream[playerid], SV_PARAMETER_VOLUME, 1.0);

        if(PlayerVoiceData[playerid][pIsRadioMicOn] == SV_FALSE && PlayerVoiceData[playerid][pDuringPhoneConvers] == SV_FALSE)
        {
            if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
                MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
            MouthStatusLabel[playerid] = CreateDynamic3DTextLabel("Berbicara...", 0x00ff00d9, 0.0, 0.0, 0.6, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 20.0, -1, 0);

            // if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerWeapon(playerid) == 0 && (GetPlayerAnimationIndex(playerid) == 1189 || GetPlayerAnimationIndex(playerid) == 1275 || GetPlayerAnimationIndex(playerid) == 1182))
            // {
            //     ApplyAnimation(playerid, "PED","IDLE_CHAT",4.0,true,false,false,1,true);
            // }
        }
    }
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    if (keyid == 0x42 && PlayerVoiceData[playerid][pHasRadio] == SV_TRUE && PlayerVoiceData[playerid][pIsRadioOn] == SV_TRUE && PlayerVoiceData[playerid][pIsRadioMicOn] == SV_TRUE && PlayerVoiceData[playerid][pRadioFreq] > 0)
    {
        for(new i; i < 800; i++)
        {
            if(IsPlayerConnected(i) && PlayerVoiceData[i][pRadioFreq] == PlayerVoiceData[playerid][pRadioFreq])
            {
                PlayerPlaySound(i, 21001, 0.0, 0.0, 0.0);
            }
        }
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, false, false, false, false, 0, true);
        SvDetachSpeakerFromStream(vdRadioStream[PlayerVoiceData[playerid][pRadioFreq]], playerid);
        RemovePlayerAttachedObject(playerid, 9);

        if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
            MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    if(keyid == 0x42 && (PlayerVoiceData[playerid][pBroadcast] == SV_TRUE || PlayerVoiceData[playerid][pInBroadcast] == SV_TRUE) && PlayerVoiceData[playerid][pIsCastMicOn] == SV_TRUE)
    {
        SvDetachSpeakerFromStream(vdBroadcastStream, playerid);

        if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
            MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    if (keyid == 0x42 && PlayerVoiceData[playerid][pDuringPhoneConvers] == SV_TRUE)
    {
        if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
            MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }
    
    if (keyid == 0x42 && vdLocalStream[playerid] && PlayerVoiceData[playerid][pIsRadioMicOn] == SV_FALSE && PlayerVoiceData[playerid][pDuringPhoneConvers] == SV_FALSE)  
    {
        SvDetachSpeakerFromStream(vdLocalStream[playerid], playerid);

        if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
            MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        // if((GetPlayerAnimationIndex(playerid) == 1189 || GetPlayerAnimationIndex(playerid) == 1275 || GetPlayerAnimationIndex(playerid) == 1275 || GetPlayerAnimationIndex(playerid) == 1182))
        //     ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, false, false, false, false, 0, true);
    }
}

public OnPlayerConnect(playerid)
{
    ResetVoiceVariables(playerid);

    if (SvGetVersion(playerid) == SV_NULL)
    {
        new lstring[512];
		format(lstring, sizeof(lstring), ""WHITE"Mohon baca pesan ini sebelum melanjutkan, "RED"%s\n\n"WHITE"Sebelum bermain maka anda harus memenuhi salah satu syarat yaitu memasang plugin voice.\nLink Discord: "YELLOW"bit.ly/pahlawan-rp", GetName(playerid));
		Dialog_Show(playerid, "DialogNotUsed", DIALOG_STYLE_MSGBOX, "Pahlawan Roleplay "WHITE"- Plugin Tidak Terdeteksi", lstring, "Quit", "");

        SendClientMessage(playerid, 0xFFFF00FF, "[i] Anda telah ditendang dari server karena "RED"Plugin Voice "YELLOW"tidak terdeteksi!");
        return KickEx(playerid);
    }
    else if (SvHasMicro(playerid) == SV_FALSE)
    {
        new lstring[512];
		format(lstring, sizeof(lstring), ""WHITE"Mohon baca pesan ini sebelum melanjutkan, "RED"%s\n\n"WHITE"Sebelum bermain maka anda harus memenuhi salah satu syarat yaitu menggunakan mic/headset.\nLink Discord: "YELLOW"bit.ly/pahlawan-rp", GetName(playerid));
		Dialog_Show(playerid, "DialogNotUsed", DIALOG_STYLE_MSGBOX, "Pahlawan Roleplay "WHITE"- Mic Tidak Terdeteksi", lstring, "Quit", "");

        SendClientMessage(playerid, 0xFFFF00FF, "[i] Anda telah ditendang dari server karena "RED"Microphone/Headset "YELLOW"tidak terdeteksi!");
        return KickEx(playerid);
    }

    else if ((vdLocalStream[playerid] = SvCreateDLStreamAtPlayer(25.7, SV_INFINITY, playerid, 0xffff0000, "")))
    {
        SvAddKey(playerid, 0x42);

        if(DestroyDynamic3DTextLabel(MouthStatusLabel[playerid]))
		    MouthStatusLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    if(vdLocalStream[playerid])
    {
        SvDeleteStream(vdLocalStream[playerid]);
        vdLocalStream[playerid] = SV_NULL;
    }

    if(vdPhoneStream[playerid])
    {
        SvDeleteStream(vdPhoneStream[playerid]);
        vdPhoneStream[playerid] = SV_NULL;
    }
    ResetVoiceVariables(playerid);
    return 1;
}

public OnFilterScriptInit()
{
    //SvDebug(SV_TRUE);
    //SvInit(384000);
    //SvEffectCreateReverb(2, 2.5, 24.4, 4.33, 2.53);
    for(new x; x < MAX_FREQ; ++x)
    {
        vdRadioStream[x] = SvCreateGStream(0xffffff00, "");
    }
    
    vdBroadcastStream = SvCreateGStream(0xffffff00, "");

    print("-------------------- [Pahlawan Voice Chat System] --------------------\n\
    ===>> Berhasil dimuat dengan baik!\n\
    ===>> by: ThurX\n\
    ===>> dipersembahkan untuk Pahlawan Roleplay\n\
    -------------------------------------------------------------------");
    return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate) //naik-turun berita
{
    if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
    {
        if(BroadCastStatus == SV_TRUE && PlayerVoiceData[playerid][pTogBroadcast] == SV_TRUE)
        {
            SendClientMessage(playerid, 0x00FF00FF, "(Server) "WHITE"Anda sedang mendengarkan pewarta berita yang sedang siaran langsung!");
            SendClientMessage(playerid, 0x00FF00FF, "(Server) "WHITE"Gunakan CMD "CYAN"'/toggle' "WHITE"untuk berhenti mendengarkannya!");

            SvAttachListenerToStream(vdBroadcastStream, playerid); //dimasukkan ke stream broadcast
        }
    }

    if(newstate == PLAYER_STATE_ONFOOT)
    {
        SvDetachListenerFromStream(vdBroadcastStream, playerid);
    }
    return 1;
}

public OnFilterScriptExit()
{
    for(new x; x < MAX_FREQ; x++)
    {
        SvDeleteStream(vdRadioStream[x]);
    }
    return 1;
}