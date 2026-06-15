#include <YSI_Coding\y_hooks>

new MixerStep[MAX_PLAYERS],
    MixerSlump[MAX_PLAYERS],
    MixerPercent[MAX_PLAYERS],
    SemenInput[MAX_PLAYERS],
    PasirInput[MAX_PLAYERS],
    KrikilAInput[MAX_PLAYERS],
    KrikilBInput[MAX_PLAYERS],
    AirInput[MAX_PLAYERS],
    SemenDiAlat[MAX_PLAYERS],
    PasirDiAlat[MAX_PLAYERS],
    KrikilADiAlat[MAX_PLAYERS],
    KrikilBDiAlat[MAX_PLAYERS],
    AirDiAlat[MAX_PLAYERS];

StartMixerJob(playerid)
{
    if(DestroyDynamicRaceCP(JobCP[playerid]))
        JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
        
    MixerStep[playerid] = 0;

    TextDrawHideForPlayer(playerid, JobMixTD[10]);
    HidePlayerProgressBar(playerid, pSlumpMeter[playerid]);

    JobVehicle[playerid] = CreateVehicle(524,637.1105,1253.5585,12.5717,298.2655,1,8, 60000, false);
    VehicleCore[JobVehicle[playerid]][vCoreFuel] = 75;
    SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
    VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
    VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = false;
    VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
    VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
    PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
    SwitchVehicleEngine(JobVehicle[playerid], true);
    SwitchVehicleDoors(JobVehicle[playerid], false);

    ShowPlayerFooter(playerid, "Isi kendaraan ini dengan ~g~beton ~w~di belakang", 15000);
    return 1;
}

ShowJobMixTD(playerid)
{
    SemenDiAlat[playerid] = RandomEx(200, 1100);
    PasirDiAlat[playerid] = RandomEx(200, 1100);
    KrikilADiAlat[playerid] = RandomEx(200, 1100);
    KrikilBDiAlat[playerid] = RandomEx(200, 1100);
    AirDiAlat[playerid] = RandomEx(200, 1100);

    SemenInput[playerid] = 0;
    PasirInput[playerid] = 0;
    KrikilAInput[playerid] = 0;
    KrikilBInput[playerid] = 0;
    AirInput[playerid] = 0;
    
    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][0], sprintf("%d", SemenDiAlat[playerid]));
    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][1], sprintf("%d", PasirDiAlat[playerid]));
    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][2], sprintf("%d", KrikilADiAlat[playerid]));
    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][3], sprintf("%d", KrikilBDiAlat[playerid]));
    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][4], sprintf("%d", AirDiAlat[playerid]));

    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][5], sprintf("%d", SemenInput[playerid]));
    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][6], sprintf("%d", PasirInput[playerid]));
    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][7], sprintf("%d", KrikilAInput[playerid]));
    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][8], sprintf("%d", KrikilBInput[playerid]));
    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][9], sprintf("%d", AirInput[playerid]));

    for(new x; x < 10; x++)
    {
        TextDrawShowForPlayer(playerid, JobMixTD[x]);
    }
    for(new x; x < 10; x++)
    {
        PlayerTextDrawShow(playerid, pJobMixTD[playerid][x]);
    }

    SelectTextDraw(playerid, 0xb159ddcc);
    return 1;
}

HideJobMixTD(playerid)
{
    for(new x; x < 10; x++)
    {
        TextDrawHideForPlayer(playerid, JobMixTD[x]);
    }
    for(new x; x < 10; x++)
    {
        PlayerTextDrawHide(playerid, pJobMixTD[playerid][x]);
    }

    CancelSelectTextDraw(playerid);
    return 1;
}

Dialog:SetSemenValue(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan opsi!");

    if(!IsNumericEx(inputtext))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi angka!");
    
    if(strval(inputtext) < 1 || strval(inputtext) > 1200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat 1 - 1200!");

    SemenInput[playerid] = strval(inputtext);

    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][5], sprintf("%d", SemenInput[playerid]));

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menetapkan takaran semen!");
    return 1;
}

Dialog:SetPasirValue(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan opsi!");

    if(!IsNumericEx(inputtext))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi angka!");
    
    if(strval(inputtext) < 1 || strval(inputtext) > 1200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat 1 - 1200!");

    PasirInput[playerid] = strval(inputtext);

    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][6], sprintf("%d", PasirInput[playerid]));
    
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menetapkan takaran pasir!");
    return 1;
}

Dialog:SetKrikilAValue(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan opsi!");

    if(!IsNumericEx(inputtext))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi angka!");
    
    if(strval(inputtext) < 1 || strval(inputtext) > 1200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat 1 - 1200!");

    KrikilAInput[playerid] = strval(inputtext);

    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][7], sprintf("%d", KrikilAInput[playerid]));
    
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menetapkan takaran krikil 1-2!");
    return 1;
}

Dialog:SetKrikilBValue(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan opsi!");

    if(!IsNumericEx(inputtext))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi angka!");
    
    if(strval(inputtext) < 1 || strval(inputtext) > 1200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat 1 - 1200!");

    KrikilBInput[playerid] = strval(inputtext);

    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][8], sprintf("%d", KrikilBInput[playerid]));
    
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menetapkan takaran krikil 2-3!");
    return 1;
}

Dialog:SetAirValue(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan opsi!");

    if(!IsNumericEx(inputtext))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi angka!");
    
    if(strval(inputtext) < 1 || strval(inputtext) > 1200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat 1 - 1200!");

    AirInput[playerid] = strval(inputtext);

    PlayerTextDrawSetString(playerid, pJobMixTD[playerid][9], sprintf("%d", AirInput[playerid]));
    
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menetapkan takaran air!");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 640.5365,1237.4777,11.6895))
        {
            if(AccountData[playerid][pJob] != JOB_MIXER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukanlah Supir Mixer!");

            if(!IsValidVehicle(JobVehicle[playerid]))
            {
                StartMixerJob(playerid);
            }
            else
            {
                DestroyVehicle(JobVehicle[playerid]);

                if(DestroyDynamicRaceCP(JobCP[playerid]))
                    JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                MixerStep[playerid] = -1;
                MixerSlump[playerid] = 0;
                MixerPercent[playerid] = 0;
                pMixerDumpTimer[playerid] = false;
                pMixBetonTimer[playerid] = false;
                pSlumpTimer[playerid] = false;
                SemenInput[playerid] = 0;
                PasirInput[playerid] = 0;
                KrikilAInput[playerid] = 0;
                KrikilBInput[playerid] = 0;
                AirInput[playerid] = 0;

                TextDrawHideForPlayer(playerid, JobMixTD[10]);
                HidePlayerProgressBar(playerid, pSlumpMeter[playerid]);

                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membatalkan pekerjaan dan mengembalikan kendaraannya.");
            }
        }
    }

    else if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        if(AccountData[playerid][pJob] == JOB_MIXER && IsPlayerInVehicle(playerid, JobVehicle[playerid]) && (IsPlayerInRangeOfPoint(playerid, 5.0, 589.4763,1245.1146,12.6529) || IsPlayerInRangeOfPoint(playerid, 5.0, 565.0966,1252.4762,12.6899)))
        {
            if(MixerStep[playerid] == 0)
            {
                ShowJobMixTD(playerid);
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_MIXER && Iter_Contains(Vehicle, JobVehicle[playerid]) && IsPlayerInVehicle(playerid, JobVehicle[playerid]))
    {
        if(checkpointid == JobCP[playerid])
        {
            if(MixerStep[playerid] == 1)
            {
                PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                pMixerDumpTimer[playerid] = true;
                AccountData[playerid][pActivityTime] = 1;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENUMPAHKAN");
                ShowProgressBar(playerid);
            }
            else if(MixerStep[playerid] == 2)
            {
                DestroyVehicle(JobVehicle[playerid]);
                
                if(DestroyDynamicRaceCP(JobCP[playerid]))
                    JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
                    
                MixerStep[playerid] = -1;
                MixerSlump[playerid] = 0;
                MixerPercent[playerid] = 0;
                pMixerDumpTimer[playerid] = false;
                pMixBetonTimer[playerid] = false;
                pSlumpTimer[playerid] = false;
                SemenInput[playerid] = 0;
                PasirInput[playerid] = 0;
                KrikilAInput[playerid] = 0;
                KrikilBInput[playerid] = 0;
                AirInput[playerid] = 0;

                TextDrawHideForPlayer(playerid, JobMixTD[10]);
                HidePlayerProgressBar(playerid, pSlumpMeter[playerid]);

                GivePlayerMoneyEx(playerid, 150);
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda mendapatkan bonus $150 karena menyelesaikan pekerjaan supir mixer!");
                ShowItemBox(playerid, "Cash", "Received $150x", 1212, 5);
            }
        }
    }
    return 1;
}