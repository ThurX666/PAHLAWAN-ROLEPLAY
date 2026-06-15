YCMD:engine(playerid, params[], help)
{
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(!IsEngineVehicle(SavingVehID[playerid]))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan bermesin!");
		
		if(AccountData[playerid][pTurningEngine]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini masih mencoba menghidupkan mesin, mohon tunggu!");

		switch(GetEngineStatus(SavingVehID[playerid]))
		{
			case true: //dimatikan
			{
				SendRPMeAboveHead(playerid, "Mematikan mesin kendaraannya.");

				SwitchVehicleLight(SavingVehID[playerid], false);
				SwitchVehicleEngine(SavingVehID[playerid], false);

				AccountData[playerid][pTurningEngine] = false;
			}
			case false: //dihidupkan
			{
				AccountData[playerid][pTurningEngine] = true;
				SendRPMeAboveHead(playerid, "Mencoba menghidupkan mesin kendaraannya.");
				SetTimerEx("EngineStatus", 2000, false, "id", playerid, SavingVehID[playerid]);
			}
		}
	}
	else return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai kendaraan!");
	return 1;
}
YCMD:en(playerid, params[], help) = engine;

YCMD:sl(playerid, params[], help)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menyetir kendaraan!");
	
	new Float:speed, vid = GetPlayerVehicleID(playerid), Float:fHealth;
	GetVehicleHealth(vid, fHealth);
	if(fHealth <= 600.0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Mesin kendaraan ini tidak dalam kondisi prima!");

	if(IsASweeperSidejobVeh(vid) || IsAMowingSidejobVeh(vid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak dapat diberi speed limit!");

	switch(VehicleCore[vid][vUsedSL])
	{
		case false:
		{
			if(sscanf(params, "f", speed))
				return SUM(playerid, "/sl [speed]~n~Gunakan '/sl' kembali untuk menonaktifkan!");

			if(speed < 10 || speed > 70)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat 10 - 70!");
			
			VehicleCore[vid][vUsedSL] = true;
			SetVehicleSpeedCap(vid, speed);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil menetapkan speed limit %.0f.", speed));
		}
		case true:
		{
			VehicleCore[vid][vUsedSL] = false;
			DisableVehicleSpeedCap(vid);
			ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah menonaktifkan speed limit.");
		}
	}
	return 1;
}