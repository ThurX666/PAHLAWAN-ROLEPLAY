#include <YSI_Coding\y_hooks>

new ShowroomIndex_ID[MAX_PLAYERS] = 0,
    ShowroomBuyType[MAX_PLAYERS];

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!AccountData[playerid][pKnockdown])
		{
            if(IsValidDynamicCP(CarDealerCP) && IsPlayerInDynamicCP(playerid, CarDealerCP))
            {
                AccountData[playerid][pTempValue2] = -1;

                Dialog_Show(playerid, "CardealerCatalog", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Cardealer", 
                "Light Truck & Vans\n\
                "GRAY"Heavy Truck\n\
                SUV & Wagon\n\
                "GRAY"Motorbike & Bike\n\
                Lowriders\n\
                "GRAY"2 Doors & Compact\n\
                4 Doors & Luxury\n\
                "RED"(Jual Kendaraan)", "Pilih", "Batal");
            }
        }
    }
    return 1;
}

Dialog:CardealerCatalog(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    switch(listitem)
    {
        case 0: //truk ringan
        {
            ShowroomIndex_ID[playerid] = 0;
            ShowroomBuyType[playerid] = listitem;

            TogglePlayerControllable(playerid, false);

            ShowCarDealerTD(playerid);
            SelectTextDraw(playerid, 0xff91a4cc);
            
            SetPlayerVirtualWorld(playerid, playerid+1);

            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Light_Truck)));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Light_Truck[ShowroomIndex_ID[playerid]][0]), FormatMoney(Light_Truck[ShowroomIndex_ID[playerid]][1])));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Light_Truck[ShowroomIndex_ID[playerid]][0])));

            ShowroomVeh[playerid] = CreateVehicle(Light_Truck[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
            VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
            VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
            VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
            SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
            SwitchVehicleEngine(ShowroomVeh[playerid], false);
            SwitchVehicleDoors(ShowroomVeh[playerid], false);

            PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

            SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
            SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
        }
        case 1: //truk berat
        {
            ShowroomIndex_ID[playerid] = 0;
            ShowroomBuyType[playerid] = listitem;

            TogglePlayerControllable(playerid, false);

            ShowCarDealerTD(playerid);
            SelectTextDraw(playerid, 0xff91a4cc);
            
            SetPlayerVirtualWorld(playerid, playerid+1);

            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Heavy_Truck)));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Heavy_Truck[ShowroomIndex_ID[playerid]][0]), FormatMoney(Heavy_Truck[ShowroomIndex_ID[playerid]][1])));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Heavy_Truck[ShowroomIndex_ID[playerid]][0])));

            ShowroomVeh[playerid] = CreateVehicle(Heavy_Truck[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
            VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
            VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
            VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
            SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
            SwitchVehicleEngine(ShowroomVeh[playerid], false);
            SwitchVehicleDoors(ShowroomVeh[playerid], false);

            PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);
            
            SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
            SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
        }
        case 2: //SUV
        {
            ShowroomIndex_ID[playerid] = 0;
            ShowroomBuyType[playerid] = listitem;

            TogglePlayerControllable(playerid, false);

            ShowCarDealerTD(playerid);
            SelectTextDraw(playerid, 0xff91a4cc);
            
            SetPlayerVirtualWorld(playerid, playerid+1);

            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(SUVWagon)));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(SUVWagon[ShowroomIndex_ID[playerid]][0]), FormatMoney(SUVWagon[ShowroomIndex_ID[playerid]][1])));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(SUVWagon[ShowroomIndex_ID[playerid]][0])));

            ShowroomVeh[playerid] = CreateVehicle(SUVWagon[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
            VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
            VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
            VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
            SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
            SwitchVehicleEngine(ShowroomVeh[playerid], false);
            SwitchVehicleDoors(ShowroomVeh[playerid], false);

            PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

            SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
            SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
        }
        case 3: //motor
        {
            ShowroomIndex_ID[playerid] = 0;
            ShowroomBuyType[playerid] = listitem;

            TogglePlayerControllable(playerid, false);

            ShowCarDealerTD(playerid);
            SelectTextDraw(playerid, 0xff91a4cc);
            
            SetPlayerVirtualWorld(playerid, playerid+1);

            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Motorbike)));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Motorbike[ShowroomIndex_ID[playerid]][0]), FormatMoney(Motorbike[ShowroomIndex_ID[playerid]][1])));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Motorbike[ShowroomIndex_ID[playerid]][0])));

            ShowroomVeh[playerid] = CreateVehicle(Motorbike[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
            VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
            VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
            VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
            SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
            SwitchVehicleEngine(ShowroomVeh[playerid], false);
            SwitchVehicleDoors(ShowroomVeh[playerid], false);

            PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

            SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
            SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
        }
        case 4: //lowrider
        {
            ShowroomIndex_ID[playerid] = 0;
            ShowroomBuyType[playerid] = listitem;

            TogglePlayerControllable(playerid, false);

            ShowCarDealerTD(playerid);
            SelectTextDraw(playerid, 0xff91a4cc);
            
            SetPlayerVirtualWorld(playerid, playerid+1);

            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Lowriders)));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Lowriders[ShowroomIndex_ID[playerid]][0]), FormatMoney(Lowriders[ShowroomIndex_ID[playerid]][1])));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Lowriders[ShowroomIndex_ID[playerid]][0])));

            ShowroomVeh[playerid] = CreateVehicle(Lowriders[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
            VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
            VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
            VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
            SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
            SwitchVehicleEngine(ShowroomVeh[playerid], false);
            SwitchVehicleDoors(ShowroomVeh[playerid], false);

            PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

            SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
            SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
        }
        case 5: //2 door
        {
            ShowroomIndex_ID[playerid] = 0;
            ShowroomBuyType[playerid] = listitem;

            TogglePlayerControllable(playerid, false);

            ShowCarDealerTD(playerid);
            SelectTextDraw(playerid, 0xff91a4cc);
            
            SetPlayerVirtualWorld(playerid, playerid+1);

            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(TwoDoor_Compact)));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(TwoDoor_Compact[ShowroomIndex_ID[playerid]][0]), FormatMoney(TwoDoor_Compact[ShowroomIndex_ID[playerid]][1])));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(TwoDoor_Compact[ShowroomIndex_ID[playerid]][0])));

            ShowroomVeh[playerid] = CreateVehicle(TwoDoor_Compact[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
            VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
            VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
            VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
            SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
            SwitchVehicleEngine(ShowroomVeh[playerid], false);
            SwitchVehicleDoors(ShowroomVeh[playerid], false);

            PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);
            
            SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
            SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
        }
        case 6: //4 door
        {
            ShowroomIndex_ID[playerid] = 0;
            ShowroomBuyType[playerid] = listitem;

            TogglePlayerControllable(playerid, false);

            ShowCarDealerTD(playerid);
            SelectTextDraw(playerid, 0xff91a4cc);
            
            SetPlayerVirtualWorld(playerid, playerid+1);

            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(FourDoor_Luxury)));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(FourDoor_Luxury[ShowroomIndex_ID[playerid]][0]), FormatMoney(FourDoor_Luxury[ShowroomIndex_ID[playerid]][1])));
            PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(FourDoor_Luxury[ShowroomIndex_ID[playerid]][0])));

            ShowroomVeh[playerid] = CreateVehicle(FourDoor_Luxury[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
            VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
            VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
            VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
            SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
            SwitchVehicleEngine(ShowroomVeh[playerid], false);
            SwitchVehicleDoors(ShowroomVeh[playerid], false);
            
            PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

            SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
            SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
        }
        case 7: //jual kendaraan
        {
            Dialog_Show(playerid, "VehicleSelling", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Jual Kendaraan", 
            "Mohon masukkan VID kendaraan yang ingin dijual:\n\
            Catatan: Gunakan '/myv' untuk melihat VID", "Jual", "Batal");
        }
    }
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == CarDealerTD[0]) //prev
    {
        PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

        if(ShowroomIndex_ID[playerid] > 0)
            ShowroomIndex_ID[playerid]--;
        
        EnteringVehID[playerid]= INVALID_VEHICLE_ID;
        DestroyVehicle(ShowroomVeh[playerid]);

        AccountData[playerid][pTempValue2] = 1;

        switch(ShowroomBuyType[playerid])
        {
            case 0: //Light Truck
            {
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Light_Truck)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Light_Truck[ShowroomIndex_ID[playerid]][0]), FormatMoney(Light_Truck[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Light_Truck[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(Light_Truck[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 1: //Heavy Truck
            {
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Heavy_Truck)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Heavy_Truck[ShowroomIndex_ID[playerid]][0]), FormatMoney(Heavy_Truck[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Heavy_Truck[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(Heavy_Truck[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 2: //SUV
            {
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(SUVWagon)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(SUVWagon[ShowroomIndex_ID[playerid]][0]), FormatMoney(SUVWagon[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(SUVWagon[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(SUVWagon[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 3: //motor
            {
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Motorbike)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Motorbike[ShowroomIndex_ID[playerid]][0]), FormatMoney(Motorbike[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Motorbike[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(Motorbike[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 4: //lowrider
            {
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Lowriders)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Lowriders[ShowroomIndex_ID[playerid]][0]), FormatMoney(Lowriders[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Lowriders[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(Lowriders[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 5: //2 door
            {
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(TwoDoor_Compact)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(TwoDoor_Compact[ShowroomIndex_ID[playerid]][0]), FormatMoney(TwoDoor_Compact[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(TwoDoor_Compact[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(TwoDoor_Compact[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 6: //4 door
            {
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(FourDoor_Luxury)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(FourDoor_Luxury[ShowroomIndex_ID[playerid]][0]), FormatMoney(FourDoor_Luxury[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(FourDoor_Luxury[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(FourDoor_Luxury[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
        }
    }
    else if(clickedid == CarDealerTD[5]) //next
    {
        PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
        
        EnteringVehID[playerid]= INVALID_VEHICLE_ID;
        DestroyVehicle(ShowroomVeh[playerid]);

        AccountData[playerid][pTempValue2] = 1;

        switch(ShowroomBuyType[playerid])
        {
            case 0: //Light Truck
            {
                if(ShowroomIndex_ID[playerid] < sizeof(Light_Truck) - 1)
                    ShowroomIndex_ID[playerid]++;

                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Light_Truck)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Light_Truck[ShowroomIndex_ID[playerid]][0]), FormatMoney(Light_Truck[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Light_Truck[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(Light_Truck[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 1: //Heavy Truck
            {
                if(ShowroomIndex_ID[playerid] < sizeof(Heavy_Truck) - 1)
                    ShowroomIndex_ID[playerid]++;

                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Heavy_Truck)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Heavy_Truck[ShowroomIndex_ID[playerid]][0]), FormatMoney(Heavy_Truck[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Heavy_Truck[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(Heavy_Truck[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 2: //SUV
            {
                if(ShowroomIndex_ID[playerid] < sizeof(SUVWagon) - 1)
                    ShowroomIndex_ID[playerid]++;

                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(SUVWagon)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(SUVWagon[ShowroomIndex_ID[playerid]][0]), FormatMoney(SUVWagon[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(SUVWagon[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(SUVWagon[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 3: //motor
            {
                if(ShowroomIndex_ID[playerid] < sizeof(Motorbike) - 1)
                    ShowroomIndex_ID[playerid]++;

                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Motorbike)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Motorbike[ShowroomIndex_ID[playerid]][0]), FormatMoney(Motorbike[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Motorbike[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(Motorbike[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 4: //lowrider
            {
                if(ShowroomIndex_ID[playerid] < sizeof(Lowriders) - 1)
                    ShowroomIndex_ID[playerid]++;

                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(Lowriders)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(Lowriders[ShowroomIndex_ID[playerid]][0]), FormatMoney(Lowriders[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(Lowriders[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(Lowriders[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 5: //2 door
            {
                if(ShowroomIndex_ID[playerid] < sizeof(TwoDoor_Compact) - 1)
                    ShowroomIndex_ID[playerid]++;

                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(TwoDoor_Compact)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(TwoDoor_Compact[ShowroomIndex_ID[playerid]][0]), FormatMoney(TwoDoor_Compact[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(TwoDoor_Compact[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(TwoDoor_Compact[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);

                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
            case 6: //4 door
            {
                if(ShowroomIndex_ID[playerid] < sizeof(FourDoor_Luxury) - 1)
                    ShowroomIndex_ID[playerid]++;

                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][0], sprintf("%02d/%02d", ShowroomIndex_ID[playerid] + 1, sizeof(FourDoor_Luxury)));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][1], sprintf("%s - $%s", GetVehicleModelName(FourDoor_Luxury[ShowroomIndex_ID[playerid]][0]), FormatMoney(FourDoor_Luxury[ShowroomIndex_ID[playerid]][1])));
                PlayerTextDrawSetString(playerid, CarDealerPTD[playerid][2], sprintf("%d Kg Trunk Capacity", GetVehicleWeight(FourDoor_Luxury[ShowroomIndex_ID[playerid]][0])));

                ShowroomVeh[playerid] = CreateVehicle(FourDoor_Luxury[ShowroomIndex_ID[playerid]][0], 378.8723,-1330.8447,15.4398,301.4344, 1, 1, 60000, false);
                VehicleCore[ShowroomVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0); 
                VehicleCore[ShowroomVeh[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyUpgraded] = false;
                VehicleCore[ShowroomVeh[playerid]][vIsBodyBroken] = false;
                VehicleCore[ShowroomVeh[playerid]][vCoreLocked] = false;
                SetVehicleVirtualWorldEx(ShowroomVeh[playerid], playerid+1);
                SwitchVehicleEngine(ShowroomVeh[playerid], false);
                SwitchVehicleDoors(ShowroomVeh[playerid], false);

                PutPlayerInVehicleEx(playerid, ShowroomVeh[playerid], 0);
                
                SetPlayerCameraPos(playerid,387.067169,-1320.811645,17.537054);
                SetPlayerCameraLookAt(playerid,381.067199,-1330.242065,14.817038);
            }
        }
    }
    else if(clickedid == CarDealerTD[24]) //batal
    {
        ShowroomIndex_ID[playerid] = 0;
        ShowroomBuyType[playerid] = -1;

        Streamer_Update(playerid, -1);
        
        SetPlayerPositionEx(playerid, 385.2523,-1326.3335,14.8170,250.5686);
        SetPlayerVirtualWorldEx(playerid, 0);
        SetPlayerInteriorEx(playerid, 0);
        SetCameraBehindPlayer(playerid);
        HideCarDealerTD(playerid);
        CancelSelectTextDraw(playerid);
        DestroyVehicle(ShowroomVeh[playerid]);
    }
    else if(clickedid == CarDealerTD[20]) //ungu
    {
        if(Iter_Contains(Vehicle, ShowroomVeh[playerid]))
        {
            ChangeVehicleColor(ShowroomVeh[playerid], 136, 136);
            AccountData[playerid][pTempValue2] = 136;
        }
    }
    else if(clickedid == CarDealerTD[19]) //abu
    {
        if(Iter_Contains(Vehicle, ShowroomVeh[playerid]))
        {
            ChangeVehicleColor(ShowroomVeh[playerid], 24, 24);
            AccountData[playerid][pTempValue2] = 24;
        }
    }
    else if(clickedid == CarDealerTD[18]) //hitam
    {
        if(Iter_Contains(Vehicle, ShowroomVeh[playerid]))
        {
            ChangeVehicleColor(ShowroomVeh[playerid], 0, 0);
            AccountData[playerid][pTempValue2] = 0;
        }
    }
    else if(clickedid == CarDealerTD[17]) //putih
    {
        if(Iter_Contains(Vehicle, ShowroomVeh[playerid]))
        {
            ChangeVehicleColor(ShowroomVeh[playerid], 1, 1);
            AccountData[playerid][pTempValue2] = 1;
        }
        
    }
    else if(clickedid == CarDealerTD[16]) //cyan
    {
        if(Iter_Contains(Vehicle, ShowroomVeh[playerid]))
        {
            ChangeVehicleColor(ShowroomVeh[playerid], 163, 163);
            AccountData[playerid][pTempValue2] = 163;
        }
    }
    else if(clickedid == CarDealerTD[15]) //biru
    {
        if(Iter_Contains(Vehicle, ShowroomVeh[playerid]))
        {
            ChangeVehicleColor(ShowroomVeh[playerid], 79, 79);
            AccountData[playerid][pTempValue2] = 79;
        }
    }
    else if(clickedid == CarDealerTD[14]) //hijau
    {
        if(Iter_Contains(Vehicle, ShowroomVeh[playerid]))
        {
            ChangeVehicleColor(ShowroomVeh[playerid], 229, 229);
            AccountData[playerid][pTempValue2] = 229;
        }
        
    }
    else if(clickedid == CarDealerTD[13]) //kuning
    {
        if(Iter_Contains(Vehicle, ShowroomVeh[playerid]))
        {
            ChangeVehicleColor(ShowroomVeh[playerid], 6, 6);
            AccountData[playerid][pTempValue2] = 6;
        }
    }
    else if(clickedid == CarDealerTD[12]) //merah
    {
        if(Iter_Contains(Vehicle, ShowroomVeh[playerid]))
        {
            ChangeVehicleColor(ShowroomVeh[playerid], 3, 3);
            AccountData[playerid][pTempValue2] = 3;
        }
        
    }
    else if(clickedid == CarDealerTD[21]) //beli
    {
        new counting = 0;

        foreach(new v : PvtVehicles)
        {
            if(PlayerVehicle[v][pVehOwnerID] == AccountData[playerid][pID])
                counting++;
        }

        if(counting >= GetPlayerVehicleLimit(playerid))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan pribadi anda telah penuh!");

        new color1 = AccountData[playerid][pTempValue2],
            color2 = AccountData[playerid][pTempValue2];
            
        switch(ShowroomBuyType[playerid])
        {
            case 0: //Light Truck
            {
                if(!TempFreeCar[playerid] && AccountData[playerid][pMoney] < Light_Truck[ShowroomIndex_ID[playerid]][1]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                if(!TempFreeCar[playerid])
                    TakePlayerMoneyEx(playerid, Light_Truck[ShowroomIndex_ID[playerid]][1]);
                VehicleBuy_Create(playerid, Light_Truck[ShowroomIndex_ID[playerid]][0], Light_Truck[ShowroomIndex_ID[playerid]][1], 399.8399,-1319.8287,15.2959,211.4821, color1, color2, 0, 0);
            }
            case 1: //Heavy Truck
            {
                if(!TempFreeCar[playerid] && AccountData[playerid][pMoney] < Heavy_Truck[ShowroomIndex_ID[playerid]][1]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                if(!TempFreeCar[playerid])
                    TakePlayerMoneyEx(playerid, Heavy_Truck[ShowroomIndex_ID[playerid]][1]);
                VehicleBuy_Create(playerid, Heavy_Truck[ShowroomIndex_ID[playerid]][0], Heavy_Truck[ShowroomIndex_ID[playerid]][1], 399.8399,-1319.8287,15.2959,211.4821, color1, color2, 0, 0);
            }
            case 2: //SUV
            {
                if(!TempFreeCar[playerid] && AccountData[playerid][pMoney] < SUVWagon[ShowroomIndex_ID[playerid]][1]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                if(!TempFreeCar[playerid])
                    TakePlayerMoneyEx(playerid, SUVWagon[ShowroomIndex_ID[playerid]][1]);
                VehicleBuy_Create(playerid, SUVWagon[ShowroomIndex_ID[playerid]][0], SUVWagon[ShowroomIndex_ID[playerid]][1], 399.8399,-1319.8287,15.2959,211.4821, color1, color2, 0, 0);
            }
            case 3: //motor
            {
                if(!TempFreeCar[playerid] && AccountData[playerid][pMoney] < Motorbike[ShowroomIndex_ID[playerid]][1]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                if(!TempFreeCar[playerid])
                    TakePlayerMoneyEx(playerid, Motorbike[ShowroomIndex_ID[playerid]][1]);
                VehicleBuy_Create(playerid, Motorbike[ShowroomIndex_ID[playerid]][0], Motorbike[ShowroomIndex_ID[playerid]][1], 399.8399,-1319.8287,15.2959,211.4821, color1, color2, 0, 0);
            }
            case 4: //lowrider
            {
                if(!TempFreeCar[playerid] && AccountData[playerid][pMoney] < Lowriders[ShowroomIndex_ID[playerid]][1]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                if(!TempFreeCar[playerid])
                    TakePlayerMoneyEx(playerid, Lowriders[ShowroomIndex_ID[playerid]][1]);
                VehicleBuy_Create(playerid, Lowriders[ShowroomIndex_ID[playerid]][0], Lowriders[ShowroomIndex_ID[playerid]][1], 399.8399,-1319.8287,15.2959,211.4821, color1, color2, 0, 0);
            }
            case 5: //2 door
            {
                if(!TempFreeCar[playerid] && AccountData[playerid][pMoney] < TwoDoor_Compact[ShowroomIndex_ID[playerid]][1]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                
                if(!TempFreeCar[playerid])
                    TakePlayerMoneyEx(playerid, TwoDoor_Compact[ShowroomIndex_ID[playerid]][1]);
                VehicleBuy_Create(playerid, TwoDoor_Compact[ShowroomIndex_ID[playerid]][0], TwoDoor_Compact[ShowroomIndex_ID[playerid]][1], 399.8399,-1319.8287,15.2959,211.4821, color1, color2, 0, 0);
            }
            case 6: //4 door
            {
                if(!TempFreeCar[playerid] && AccountData[playerid][pMoney] < FourDoor_Luxury[ShowroomIndex_ID[playerid]][1]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                if(!TempFreeCar[playerid])
                    TakePlayerMoneyEx(playerid, FourDoor_Luxury[ShowroomIndex_ID[playerid]][1]);
                VehicleBuy_Create(playerid, FourDoor_Luxury[ShowroomIndex_ID[playerid]][0], FourDoor_Luxury[ShowroomIndex_ID[playerid]][1], 399.8399,-1319.8287,15.2959,211.4821, color1, color2, 0, 0);
            }
        }
        ShowroomIndex_ID[playerid] = 0;
        ShowroomBuyType[playerid] = -1;

        AccountData[playerid][pInDoor] = -1;
        AccountData[playerid][pInHouse] = -1;
        AccountData[playerid][pInBiz] = -1;
        AccountData[playerid][pInRusun] = -1;
        AccountData[playerid][pInGudang] = -1;

        Streamer_Update(playerid, -1);

        SetPlayerPositionEx(playerid, 393.8368,-1310.6884,14.8257,211.7149, 1500);
        SetPlayerVirtualWorldEx(playerid, 0);
        SetPlayerInteriorEx(playerid, 0);
        SetCameraBehindPlayer(playerid);
        HideCarDealerTD(playerid);
        CancelSelectTextDraw(playerid);

        AccountData[playerid][pTempValue2] = -1;
        TempFreeCar[playerid] = false;

        new jjja[128];
        mysql_format(g_SQL, jjja, sizeof(jjja), "UPDATE `player_ucp` SET `FreeCar` = '0' WHERE `UCP` = '%e'", AccountData[playerid][pUCP]);
        mysql_pquery(g_SQL, jjja);
    }
    return 1;
}