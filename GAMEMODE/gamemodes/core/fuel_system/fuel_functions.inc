#include <YSI_Coding\y_hooks>

GasPump_Nearest(playerid)
{
    for(new gp; gp < sizeof(__g_GasPumpLoc); gp++) if (IsPlayerInRangeOfPoint(playerid, 0.65, __g_GasPumpLoc[gp][0], __g_GasPumpLoc[gp][1], __g_GasPumpLoc[gp][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
	{
        return gp;
	}
	return -1;
}

ptask CheckingPlayerInArea[1111](playerid) 
{
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        if(!AccountData[playerid][pDuringRefueling])
        {
            new gp = GasPump_Nearest(playerid);
            if(gp != -1)
            {
                new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
                if(vehid != INVALID_VEHICLE_ID)
                {
                    UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][gp], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk mengisi bbm");
                }
                else
                {
                    UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][gp], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk membeli jerigen\nHarga: "GREEN"$1,200");
                }
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!AccountData[playerid][pKnockdown])
		{
            if(PlayerHasItem(playerid, "Jerigen") && AccountData[playerid][pHoldingFuelCan])
            {
                new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false), gplstr[128];
                if(vehid != INVALID_VEHICLE_ID)
                {
                    if(!AccountData[playerid][pDuringRefueling])
                    {
                        if(GetEngineStatus(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mematikan mesin terlebih dahulu!");

                        if(VehicleCore[vehid][vCoreFuel] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bahan bakar kendaraan anda masih penuh!");

                        AccountData[playerid][pDuringRefueling] = true;
                        ApplyAnimation(playerid, "CAMERA", "camstnd_lkabt", 4.33, true, false, false, false, 0, true);

                        format(gplstr, sizeof(gplstr), "%d persen", VehicleCore[vehid][vCoreFuel]);
                        UpdateDynamic3DTextLabelText(g_GasProgressLabel[playerid], Y_WHITE, gplstr);

                        Inventory_Remove(playerid, "Jerigen");
                        ShowItemBox(playerid, "Jerigen", "Removed 1x", 1650, 5);

                        AccountData[playerid][pTempVehID] = vehid;
                        pRefuelJerrycanTimer[playerid] = true;
                    }
                }
            }
            else
            {
                new gp = -1, gplstr[128];
                if((gp = GasPump_Nearest(playerid)) != -1)
                {
                    new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
                    if(vehid != INVALID_VEHICLE_ID)
                    {
                        if(!AccountData[playerid][pDuringRefueling])
                        {
                            if(GetEngineStatus(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mematikan mesin terlebih dahulu!");
                            if(AccountData[playerid][pHoldingFuelCan]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Simpan jerigen terlebih dahulu!");
                            if(AccountData[playerid][pMoney] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!"); 

                            if(VehicleCore[vehid][vCoreFuel] >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bahan bakar kendaraan anda masih penuh!");

                            AccountData[playerid][pDuringRefueling] = true;
                            ApplyAnimation(playerid, "CAMERA", "camstnd_lkabt", 4.33, true, false, false, false, 0, true);

                            format(gplstr, sizeof(gplstr), "Tekan "GREEN"Y "WHITE"untuk membatalkan mengisi bahan bakar\nHarga: "DARKGREEN"$%s", FormatMoney(AccountData[playerid][pRefuelingPrice]));
                            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][gp], Y_WHITE, gplstr);

                            format(gplstr, sizeof(gplstr), "%d persen", VehicleCore[vehid][vCoreFuel]);

                            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                                
                            g_GasProgressLabel[playerid] = CreateDynamic3DTextLabel(gplstr, Y_WHITE, 0.0, 0.0, 1.10, 5.0, INVALID_PLAYER_ID, vehid, 0, 0, 0, playerid, 5.0, -1, 0);

                            Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);

                            AccountData[playerid][pInGas] = gp;
                            AccountData[playerid][pTempVehID] = vehid;
                            pRefuelingTimer[playerid] = true;

                            PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                        }
                        else
                        {
                            pRefuelingTimer[playerid] = false;

                            AccountData[playerid][pDuringRefueling] = false;
                            StopRunningAnimation(playerid);

                            TakePlayerMoneyEx(playerid, AccountData[playerid][pRefuelingPrice]);
                            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(AccountData[playerid][pRefuelingPrice])), 1212, 5);
                            AccountData[playerid][pRefuelingPrice] = 0;

                            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][gp], Y_GREEN, "[Y] "WHITE"Untuk mengisi bahan bakar");

                            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                        }
                    }
                    else
                    {
                        if(AccountData[playerid][pMoney] < 1200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!"); 

                        TakePlayerMoneyEx(playerid, 1200);
                        Inventory_Add(playerid, "Jerigen", 1650);
                        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda telah berhasil membeli Jerigen.");
                    }
                }
            }
        }
    }
    return 1;
}