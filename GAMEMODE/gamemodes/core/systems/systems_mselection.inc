//Model Selection 
public OnPlayerModelSelection(playerid, response, listid, modelid)
{
	/*
	new setsqlisnt[512];
	if(listid == BuyMale)
    {
		if(!response) return 1;

		if(AccountData[playerid][pMoney] < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

		AccountData[playerid][pSkin] = modelid;
		mysql_format(g_SQL, setsqlisnt, sizeof(setsqlisnt), "UPDATE `player_characters` SET `Char_Skin` = %d WHERE `pID` = %d", AccountData[playerid][pSkin], AccountData[playerid][pID]);
		mysql_pquery(g_SQL, setsqlisnt);
		
		SetPlayerSkin(playerid, modelid);
		TakePlayerMoneyEx(playerid, 75);

		SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You've purchased a clothes for "RED4"$75");
    }
	else if(listid == BuyFemale)
    {
		if(!response) return 1;

		if(AccountData[playerid][pMoney] < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

		AccountData[playerid][pSkin] = modelid;
		mysql_format(g_SQL, setsqlisnt, sizeof(setsqlisnt), "UPDATE `player_characters` SET `Char_Skin` = %d WHERE `pID` = %d", AccountData[playerid][pSkin], AccountData[playerid][pID]);
		mysql_pquery(g_SQL, setsqlisnt);
		
		SetPlayerSkin(playerid, modelid);
		TakePlayerMoneyEx(playerid, 75);

		SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You've purchased a clothes for "RED4"$75");
    }
	*/
	if(listid == ModshopModel)
    {
		if(response)
        {
            new v = GetPlayerVehicleID(playerid);
            new iterid = Vehicle_GetIterID(v);
			if(iterid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan jenis kendaraan pribadi!");
			if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			new vehid = PlayerVehicle[iterid][pVehPhysic];

			for(new x; x < 6; x++)
			{
				if(vtData[iterid][x][vtoy_modelid] != 0) continue;

				vtData[iterid][x][vtoy_modelid] = modelid;
				
				if(DestroyDynamicObject(vtData[iterid][x][vtoy_model]))
					vtData[iterid][x][vtoy_model] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

				static Float:vx, Float:vy, Float:vz;
				GetVehiclePos(v, vx, vy, vz);
				vtData[iterid][x][vtoy_model] = CreateDynamicObject(vtData[iterid][x][vtoy_modelid], vx, vy, vz, 0.0, 0.0, 0.0, 0, 0, -1, 200.00, 200.00, -1);
				AttachDynamicObjectToVehicle(vtData[iterid][x][vtoy_model], vehid, vtData[iterid][x][vtoy_x], vtData[iterid][x][vtoy_y], vtData[iterid][x][vtoy_z], vtData[iterid][x][vtoy_rx], vtData[iterid][x][vtoy_ry], vtData[iterid][x][vtoy_rz]);
				SendClientMessage(playerid, X11_LIGHTBLUE, "MODSHOP: "WHITE"Anda berhasil membeli modifikasi tersebut seharga "RED"$16,500.");

				MySQL_CreateVehicleToy(iterid, x);
				TakePlayerMoneyEx(playerid, 5000);

				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				break;
			}
        }
        else return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pembelian modifikasi!");
	}
    return 1;
}