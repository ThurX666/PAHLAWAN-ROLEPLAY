// new __g_ServerWeather[] = {
//     4, 3, 2, 1, 0,
//     0, 1, 2, 3, 4,
//     4, 3, 2, 1, 0,
//     0, 1, 2, 3, 4,
//     9, 8, 0, 1, 2, 
//     0, 1, 2, 3, 4,
//     3, 4, 3, 2, 1,
//     0, 1, 2, 3, 4,
//     4, 3, 2, 1, 0,
//     4, 3, 2, 1, 0,
//     4, 3, 2, 1, 0,
//     0, 1, 2, 3, 4,
//     0, 1, 2, 3, 4,
//     0, 1, 2,
//     4, 3, 2, 1, 0,
//     3, 4, 3, 2, 1,
//     4, 3, 2, 1, 0,
//     0, 1, 2, 3, 4,
//     4, 3, 2, 1, 0,
//     0, 1, 2, 3, 4
// };

new __g_ServerWeather[] = {
    4, 3, 2, 1, 0, 10, 15, 11, 14,
    9, 8, 0, 1, 2, 11, 15, 10, 13,
    3, 4, 3, 2, 1, 12, 17, 14, 11, 8,
    0, 1, 2, 9, 13, 18, 13, 12,
    0, 8, 2, 3, 4, 14, 17, 12, 13
};

new datestring[64];
new av_hours, av_minutes, av_seconds, av_days, av_months, av_years;

task ServerTimeClock[1000]()
{
    if(GM[GInsuTime] > 0)
    {
        GM[GInsuTime]--;
        
        ShowAsuransiTD(sprintf("Asuransi keliling %d menit %d detik", GM[GInsuTime]/60%60, GM[GInsuTime]%3600%60));

        if(GM[GInsuTime] <= 0)
        {
            GM[GInsuTime] = 0;

            TextDrawHideForAll(GInsurance[0]);
            TextDrawHideForAll(GInsurance[1]);
            TextDrawHideForAll(GInsurance[2]);

            SendClientMessageToAll(Y_LIGHTRED, "AdmCmd: Asuransi keliling telah dilaksanakan, selamat beraktivitas kembali.");

            new impstr[158];
            foreach (new pv : PvtVehicles)
            {
                if(Iter_Contains(Vehicle, PlayerVehicle[pv][pVehPhysic]))
                {
                    if(!IsVehicleOccupied(PlayerVehicle[pv][pVehPhysic]))
                    {
                        if (PlayerVehicle[pv][pVehRental] > -1 || PlayerVehicle[pv][pVehRentTime] > 0)
                        {
                            PlayerVehicle[pv][pVehRental] = -1;
                            PlayerVehicle[pv][pVehRentTime] = 0;

                            SetVehicleNeonLights(PlayerVehicle[pv][pVehPhysic], false, PlayerVehicle[pv][pVehNeon], 0);

                            DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);

                            PlayerVehicle[pv][pVehHandbraked] = false;

                            mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);
                            mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);
                            mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);
                            mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);

                            for(new x; x < MAX_BAGASI_ITEMS; x++)
                            {
                                VehicleBagasi[pv][x][vehicleBagasiExists] = false;
                                VehicleBagasi[pv][x][vehicleBagasiID] = 0;
                                VehicleBagasi[pv][x][vehicleBagasiVDBID] = 0;
                                VehicleBagasi[pv][x][vehicleBagasiTemp][0] = EOS;
                                VehicleBagasi[pv][x][vehicleBagasiModel] = 0;
                                VehicleBagasi[pv][x][vehicleBagasiQuant] = 0;
                            }

                            for(new z; z < 3; z++)
                            {
                                VehicleHolster[pv][vHolsterTaken][z] = false;
                                VehicleHolster[pv][vHolsterID][z] = -1;
                                VehicleHolster[pv][vHolsterWeaponID][z] = 0;
                                VehicleHolster[pv][vHolsterWeaponAmmo][z] = 0;
                            }

                            Iter_Remove(PvtVehicles, pv);
                        }
                        else
                        {
                            PlayerVehicle[pv][pVehHandbraked] = false;
                            PlayerVehicle[pv][pVehInsuranced] = true;
                            DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);

                            mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Insuranced` = 1 WHERE `id`=%d",PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);
                        }
                    }
                }
            }
        }
    }

	//Date and Time Textdraw
	getdate(av_years, av_months, av_days);
 	gettime(av_hours, av_minutes, av_seconds);

    format(datestring, sizeof(datestring), "%s", GetCalenderDate(av_days, av_months, av_years));
    TextDrawSetString(ServerClockTD[0], datestring);
    format(datestring, sizeof(datestring), "%02d:%02d:%02d", av_hours, av_minutes, av_seconds);
    TextDrawSetString(ServerClockTD[1], datestring);

    // Phone HBE Clock
    format(datestring, sizeof(datestring), "%01d:%02d", av_hours, av_minutes);
    TextDrawSetString(PHONE_HBE[18], datestring);

	if(av_minutes == 0 && av_seconds == 0) //tiap 1 jam atau menit 0 detik 0
	{
        new rand = __g_ServerWeather[random(sizeof(__g_ServerWeather))];
        WorldWeather = rand;
        WorldTime = av_hours;

        if (17 <= av_hours <= 20)
        {
            WorldWeather = 1;
            WorldTime += 3;
        }
        else if (21 <= av_hours <= 23)
        {
            WorldWeather = 1;
            WorldTime = 0;
        }
        else if(av_hours > 23)
        {
            WorldWeather = 1;
            WorldTime = 3;
        }
        
        if(!GM[HalloweenEvent])
        {
            SetWeather(WorldWeather);
            SetWorldTime(WorldTime);
        }
        else
        {
            SetWeather(WorldWeather);
            SetWorldTime(0);
        }
	}

    TextDrawSetString(LockScreenTD[6], sprintf("%02d:%02d", av_hours, av_minutes));
    TextDrawSetString(PhoneMainMenuClock, sprintf("%02d:%02d", av_hours, av_minutes));
    return 1;
}

task UpdateServerStock[60000]() 
{
    real_life_clock_minutes++;
    if(real_life_clock_minutes == 60)
    {
        real_life_clock_hours++;

        GM[g_ComponentPrice] = RandomEx(5, 10);

        static string[555];
        if(real_life_clock_hours == 2)
        {
            real_life_clock_hours = 0;

            OldChiliSalary = ChiliSalary;
            OldRiceSalary = RiceSalary;
            OldSugarSalary = SugarSalary;
            OldStrawberrySalary = StrawberrySalary;
            OldJerukSalary = JerukSalary;
            OldAnggurSalary = AnggurSalary;

            ChiliSalary = RandomEx(50, 65);
            RiceSalary = RandomEx(50, 65);
            SugarSalary = RandomEx(50, 65);
            StrawberrySalary = RandomEx(50, 65);
            JerukSalary = RandomEx(50, 65);
            AnggurSalary = RandomEx(50, 65);
        }

        if(GM[g_ComponentStock] < 100000)
        {
            GM[g_ComponentStock] += 10000;   
        }
        format(string, sizeof(string), "[Gudang Komponen]\n"WHITE"Harga: "GREEN"$%s/komponen\n"WHITE"Stock: "YELLOW"%d/100000\n"WHITE"Gunakan "YELLOW"'/buycomponent' "WHITE"untuk membeli komponen", FormatMoney(GM[g_ComponentPrice]), GM[g_ComponentStock]);
        UpdateDynamic3DTextLabelText(g_ComponentLabel, 0xc0c0c8A6, string);

        format(string, sizeof(string), "[Toko Bibit]\n"WHITE"Gunakan "GREEN"[Y] "WHITE"untuk beli bibit\n\nCabai: "RED"$%s"GRAY"/pcs => "GREEN"$%s"GRAY"/pcs\n"WHITE"Padi: "RED"$%s"GRAY"/pcs => "GREEN"$%s"GRAY"/pcs\n"WHITE"Tebu: "RED"$%s"GRAY"/pcs => "GREEN"$%s"GRAY"/pcs\n"WHITE"Strawberry: "RED"$%s"GRAY"/pcs => "GREEN"$%s"GRAY"/pcs\n"WHITE"Jeruk: "RED"$%s"GRAY"/pcs => "GREEN"$%s"GRAY"/pcs\n"WHITE"Anggur: "RED"$%s"GRAY"/pcs => "GREEN"$%s"GRAY"/pcs\n"WHITE"Drop tanaman hasil panen disini untuk dijual!", FormatMoney(OldChiliSalary), FormatMoney(ChiliSalary), FormatMoney(OldRiceSalary), FormatMoney(RiceSalary), FormatMoney(OldSugarSalary), FormatMoney(SugarSalary),
            FormatMoney(OldStrawberrySalary), FormatMoney(StrawberrySalary), FormatMoney(OldJerukSalary), FormatMoney(JerukSalary), FormatMoney(OldAnggurSalary), FormatMoney(AnggurSalary));
        UpdateDynamic3DTextLabelText(g_FarmerLabel, 0xc0c0c8A6, string);

        real_life_clock_minutes = 0;
    }
    return 1;
}

task ServerUpdateVoting[1500]() 
{
    if(VoteInfo[voteStarted])
    {
        if(VoteInfo[voteTime] != 0 && gettime() > VoteInfo[voteTime])
        {
            VoteInfo[voteStarted] = false;
            VoteInfo[voteTime] = 0;

            SendClientMessageToAllEx(Y_WHITE, "[Vote] "YELLOW"%s", VoteInfo[voteText]);
            SendClientMessageToAllEx(Y_WHITE, "~> Vote Yes: "YELLOW"%d "WHITE"// Vote No: "YELLOW"%d.", VoteInfo[voteYes], VoteInfo[voteNo]);

            VoteInfo[voteText][0] = EOS;
            VoteInfo[voteYes] = 0;
            VoteInfo[voteNo] = 0;

            foreach(new i : Player) if(AccountData[i][pSpawned])
            {
                AccountData[i][pVoted] = false;
            }
        }
    }

    foreach(new pv : PvtVehicles)
    {
        if(Iter_Contains(Vehicle, PlayerVehicle[pv][pVehPhysic]))
        {
            if(PlayerVehicle[pv][pVehHandbraked] || PlayerVehicle[pv][pVehTireLocked])
            {
                if(GetVehicleDistanceFromPoint(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehPos][0], PlayerVehicle[pv][pVehPos][1], PlayerVehicle[pv][pVehPos][2]) >= 3.0)
                {
                    if(!PlayerVehicle[pv][pVehInsuranced])
                    {
                        // masukin variable dari database player biar mobilnya gak spawn polosan
                        SetVehiclePos(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehPos][0], PlayerVehicle[pv][pVehPos][1], PlayerVehicle[pv][pVehPos][2]);
                        SetVehicleZAngle(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehPos][3]);
                        ChangeVehicleColor(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehColor1], PlayerVehicle[pv][pVehColor2]);
                        VehicleCore[PlayerVehicle[pv][pVehPhysic]][vCoreFuel] = PlayerVehicle[pv][pVehFuel];
                        VehicleCore[PlayerVehicle[pv][pVehPhysic]][vMaxHealth] = PlayerVehicle[pv][pVehMaxHealth];
                        VehicleCore[PlayerVehicle[pv][pVehPhysic]][vIsBodyUpgraded] = PlayerVehicle[pv][pVehBodyUpgraded];
                        VehicleCore[PlayerVehicle[pv][pVehPhysic]][vIsBodyBroken] = PlayerVehicle[pv][pVehBodyBroken];
                        SetVehicleNumberPlate(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehPlate]);
                        SetVehicleVirtualWorldEx(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehWorld]);
                        LinkVehicleToInteriorEx(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehInterior]);

                        if(PlayerVehicle[pv][pVehHealth] < 350.0)
                        {
                            SetValidVehicleHealth(PlayerVehicle[pv][pVehPhysic], 350.0);
                        }
                        else
                        {
                            SetValidVehicleHealth(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehHealth]);
                        }
                        UpdateVehicleDamageStatus(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehDamage][0], PlayerVehicle[pv][pVehDamage][1], PlayerVehicle[pv][pVehDamage][2], PlayerVehicle[pv][pVehDamage][3]);
                        if(PlayerVehicle[pv][pVehPaintjob] != -1)
                        {
                            ChangeVehiclePaintjob(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehPaintjob]);
                        }
                        
                        for(new z = 0; z < 17; z++)
                        {
                            if(PlayerVehicle[pv][pVehMod][z]) AddVehicleComponent(PlayerVehicle[pv][pVehPhysic], PlayerVehicle[pv][pVehMod][z]);
                        }

                        if(PlayerVehicle[pv][pVehLocked])
                        {
                            SwitchVehicleDoors(PlayerVehicle[pv][pVehPhysic], true);
                            VehicleCore[PlayerVehicle[pv][pVehPhysic]][vCoreLocked] = true;
                        }
                        else
                        {
                            SwitchVehicleDoors(PlayerVehicle[pv][pVehPhysic], false);
                            VehicleCore[PlayerVehicle[pv][pVehPhysic]][vCoreLocked] = false;
                        }

                        if(IsEngineVehicle(PlayerVehicle[pv][pVehPhysic]))
                        {
                            SwitchVehicleEngine(PlayerVehicle[pv][pVehPhysic], false);
                        }
                        else
                        {
                            SwitchVehicleEngine(PlayerVehicle[pv][pVehPhysic], true);
                        }
                    }
                    else
                    {
                        new impstr[158];
                        if(PlayerVehicle[pv][pVehRental] > -1 || PlayerVehicle[pv][pVehRentTime] > 0)
                        {
                            PlayerVehicle[pv][pVehRental] = -1;
                            PlayerVehicle[pv][pVehRentTime] = 0;

                            if(Iter_Contains(Vehicle, PlayerVehicle[pv][pVehPhysic]))
                            {
                                SetVehicleNeonLights(PlayerVehicle[pv][pVehPhysic], false, PlayerVehicle[pv][pVehNeon], 0);
                            }
                            DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);
                            PlayerVehicle[pv][pVehHandbraked] = false;
                            mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);
                            mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);
                            mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);
                            mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);

                            for(new x; x < MAX_BAGASI_ITEMS; x++)
                            {
                                VehicleBagasi[pv][x][vehicleBagasiExists] = false;
                                VehicleBagasi[pv][x][vehicleBagasiID] = 0;
                                VehicleBagasi[pv][x][vehicleBagasiVDBID] = 0;
                                VehicleBagasi[pv][x][vehicleBagasiTemp][0] = EOS;
                                VehicleBagasi[pv][x][vehicleBagasiModel] = 0;
                                VehicleBagasi[pv][x][vehicleBagasiQuant] = 0;
                            }

                            for(new z; z < 3; z++)
                            {
                                VehicleHolster[pv][vHolsterTaken][z] = false;
                                VehicleHolster[pv][vHolsterID][z] = -1;
                                VehicleHolster[pv][vHolsterWeaponID][z] = 0;
                                VehicleHolster[pv][vHolsterWeaponAmmo][z] = 0;
                            }

                            Iter_Remove(PvtVehicles, pv);
                        }
                        else
                        {
                            if(Iter_Contains(Vehicle, PlayerVehicle[pv][pVehPhysic]))
                            {
                                SetVehicleNeonLights(PlayerVehicle[pv][pVehPhysic], false, PlayerVehicle[pv][pVehNeon], 0);
                            }
                            DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);
                            PlayerVehicle[pv][pVehInsuranced] = true;
                            PlayerVehicle[pv][pVehHandbraked] = false;
                            mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Insuranced` = 1 WHERE `id`=%d", PlayerVehicle[pv][pVehID]);
                            mysql_pquery(g_SQL, impstr);
                        }
                    }
                }
            }
            else
            {
                Vehicle_GetStatus(pv);
            }
        }
    }

    foreach(new i : Player)
    {
        if(Iter_Contains(Vehicle, PlayerFactionVehicle[i][AccountData[i][pFaction]]))
        {
            VehicleFact_GetStatus(PlayerFactionVehicle[i][AccountData[i][pFaction]], i);
        }
    }
    return 1;
}

task ServerGMXMTUpdate[60000]()
{
    if(GM[Maintenance])
    {
        if(GM[MTTime] != 0 && gettime() > GM[MTTime])
        {
            GM[Maintenance] = false;
            GM[MTTime] = 0;

            //SendRconCommand("password awkakawkw");
            //SendRconCommand("hostname Arivena | Under Maintenance");

            foreach(new i : Player) if(AccountData[i][pSpawned])
            {
                TogglePlayerControllable(i, false);
                GameTextForPlayer(i, "~r~SERVER MAINTENANCE", 15000, 3);
                SendClientMessage(i, X11_YELLOW, "[Maintenance] Seluruh data telah tersimpan. Progress apapun setelah ini tidak akan tersimpan!");

                UpdateAccountData(i);
			    RemovePlayerVehicle(i);

                KickEx(i, 15000);
            }
        }
        else
        {
            static string[144];
            format(string, sizeof(string), "[Maintenance] Server telah dijadwalkan maintenance pada "YELLOW"%s", ReturnDate(GM[MTTime]));
            SendClientMessageToAll(X11_LIGHTBLUE, string);
        }
    }
    return 1;
}

task VehicleUpdate[25000]()
{
	foreach(new i : Vehicle) if(IsValidVehicle(i) && IsEngineVehicle(i) && GetEngineStatus(i))
    {
        if(VehicleCore[i][vCoreFuel] > 0)
        {
            VehicleCore[i][vCoreFuel]--;

            if(VehicleCore[i][vCoreFuel] >= 1 && VehicleCore[i][vCoreFuel] <= 45)
            {
                new driverid = GetVehicleDriver(i);
                if(driverid != INVALID_PLAYER_ID)
                    PlayerPlaySound(driverid, SOUND_FUEL_DECREASE, 0.0, 0.0, 0.0);
            }
        }
        if(VehicleCore[i][vCoreFuel] <= 0)
        {
            VehicleCore[i][vCoreFuel] = 0;
            SwitchVehicleEngine(i, false);
            new driverid = GetVehicleDriver(i);
            if(driverid != INVALID_PLAYER_ID)
                PlayerPlaySound(driverid, SOUND_FUEL_DECREASE, 0.0, 0.0, 0.0);
        }
	}
}

ptask TaxCutting[60000](playerid) 
{
    AccountData[playerid][pTaxMinute]++;
    if(AccountData[playerid][pTaxMinute] >= 1440)
    {
        if(AccountData[playerid][IsLoggedIn])
        {
            if(AccountData[playerid][pMoney] > 0 || AccountData[playerid][pBankMoney] > 0)
            {
                RumusPajakTabungan[playerid] = (AccountData[playerid][pMoney] + AccountData[playerid][pBankMoney] + AccountData[playerid][pSlipSalary] + AccountData[playerid][pCasinoChip]) * 0.008;
                AccountData[playerid][pBankMoney] -= RoundNegativeToPositive(RumusPajakTabungan[playerid]);
            }

            foreach(new pv : PvtVehicles)
            {
                if(PlayerVehicle[pv][pVehOwnerID] == AccountData[playerid][pID])
                {
                    if(PlayerVehicle[pv][pVehRentTime] == 0)
                    {
                        RumusPajakKendaraan[playerid] += GetVehiclePrice(PlayerVehicle[pv][pVehModelID]) * 0.005;
                    }
                }
            }

            if(RumusPajakKendaraan[playerid] > 0)
            {
                AccountData[playerid][pBankMoney] -= floatround(RumusPajakKendaraan[playerid]);
            }
        }
        static Float:GrandTotal;
        GrandTotal = RoundNegativeToPositive(RumusPajakTabungan[playerid]) + floatround(RumusPajakKendaraan[playerid]);
        SendClientMessage(playerid, X11_YELLOW, "========== [Pemerintah Pahlawan Roleplay] ==========");
        SendClientMessageEx(playerid, -1, "-> Pajak Tabungan: "RED"$%s", FormatMoney(floatround(RumusPajakTabungan[playerid])));
        SendClientMessageEx(playerid, -1, "-> Pajak Kendaraan: "RED"$%s", FormatMoney(floatround(RumusPajakKendaraan[playerid])));
        SendClientMessageEx(playerid, -1, "-> Total Pajak: "RED"$%s", FormatMoney(floatround(GrandTotal)));
        SendClientMessageEx(playerid, -1, "-> Sisa Saldo Bank: "GREEN"$%s", FormatMoney(AccountData[playerid][pBankMoney]));
        SendClientMessage(playerid, -1, "- Pajak telah dibayar melalui pemotongan saldo Bank anda -");
        SendClientMessage(playerid, X11_YELLOW, "=================================================");
        RumusPajakTabungan[playerid]  = 0;
        RumusPajakKendaraan[playerid] = 0;
        AccountData[playerid][pTaxMinute] = 0;
        GrandTotal = 0;
    }
}

task UpdateAdvertTime[120000]() 
{
    if(AdvertisementEnum[GM[g_AdvertSentPublic]][adActive])
    {
        static string[164];
        if(strlen(AdvertisementEnum[GM[g_AdvertSentPublic]][adDetail]) > 64)
        {
            foreach(new i : Player) if(AccountData[i][pSpawned] && ToggleInfo[i][TogAdv])
            {
                format(string, sizeof(string), "%.64s...", AdvertisementEnum[GM[g_AdvertSentPublic]][adDetail]);
                SendClientMessage(i, 0x33AA33AA, string);
                format(string, sizeof(string), "... %s | CP: %s | Ph: [%s]", AdvertisementEnum[GM[g_AdvertSentPublic]][adDetail][64], AdvertisementEnum[GM[g_AdvertSentPublic]][adIssuer], AdvertisementEnum[GM[g_AdvertSentPublic]][adNumb]);
                SendClientMessage(i, 0x33AA33AA, string);
            }
        }
        else
        {
            format(string, sizeof(string), "%s | CP: %s | Ph: [%s]", AdvertisementEnum[GM[g_AdvertSentPublic]][adDetail], AdvertisementEnum[GM[g_AdvertSentPublic]][adIssuer], AdvertisementEnum[GM[g_AdvertSentPublic]][adNumb]);
            foreach(new i : Player) if(AccountData[i][pSpawned] && ToggleInfo[i][TogAdv])
            {
                SendClientMessage(i, 0x33AA33AA, string);
            }
        }
        AdvertisementEnum[GM[g_AdvertSentPublic]][adActive] = false;
        GM[g_AdvertSentPublic]++;
        if(GM[g_AdvertSentPublic] > 14)
        {
            GM[g_AdvertSentPublic] = 0;
            GM[g_TotalAdverts] = 0;

            for(new x; x < MAX_ADVERTISEMENT; x++)
            {
                AdvertisementEnum[x][adActive] = false;
                AdvertisementEnum[x][adSubmitted] = false;
                AdvertisementEnum[x][adNumb][0] = EOS;
                AdvertisementEnum[x][adIssuer][0] = EOS;
                AdvertisementEnum[x][adDetail][0] = EOS;
            }
            SendClientMessageToAll(Y_ORANGE, "Seluruh iklan telah ditayangkan, warga dapat membuat iklan baru kembali!");
        }
    }
    return 1;
}

task TaxFactionAndBadside[60000]() 
{
    if(gettime() > FactBadTaxTime)
    {
        FactBadTaxTime = gettime() + 604800;
        
        new fsrs[228], Float:rumuspajakbadside;
        foreach(new fmid : Fams) if(fmid != INVALID_ITERATOR_SLOT)
        {
            rumuspajakbadside = FamilyData[fmid][famMoney] * 0.05;
            FamilyData[fmid][famMoney] -= floatround(rumuspajakbadside);

            mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `families` SET `Money` = %d WHERE `ID` = %d", FamilyData[fmid][famMoney], fmid);
            mysql_pquery(g_SQL, fsrs);
        }

        PolisiMoneyVault -= floatround(PolisiMoneyVault * 0.07);
        EMSMoneyVault -= floatround(EMSMoneyVault * 0.07);
        PutrideliMoneyVault -= floatround(PutrideliMoneyVault * 0.07);
        PemerMoneyVault -= floatround(PemerMoneyVault * 0.07);
        BennysMoneyVault -= floatround(BennysMoneyVault * 0.07);
        UberMoneyVault -= floatround(UberMoneyVault * 0.07);
        DinarbucksMoneyVault -= floatround(DinarbucksMoneyVault * 0.07);
        Fox11MoneyVault -= floatround(Fox11MoneyVault * 0.07);
        AutomaxMoneyVault -= floatround(AutomaxMoneyVault * 0.07);

        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `polisimoneyvault`=%d WHERE `id`=0", PolisiMoneyVault);
        mysql_pquery(g_SQL, fsrs);
        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `emsmoneyvault`=%d WHERE `id`=0", EMSMoneyVault);
        mysql_pquery(g_SQL, fsrs);
        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `putridelimoneyvault`=%d WHERE `id`=0", PutrideliMoneyVault);
        mysql_pquery(g_SQL, fsrs);
        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `pemermoneyvault`=%d WHERE `id`=0", PemerMoneyVault);
        mysql_pquery(g_SQL, fsrs);
        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `bennysmoneyvault`=%d WHERE `id`=0", BennysMoneyVault);
        mysql_pquery(g_SQL, fsrs);
        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `ubermoneyvault`=%d WHERE `id`=0", UberMoneyVault);
        mysql_pquery(g_SQL, fsrs);
        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `dinarbucksmoneyvault`=%d WHERE `id`=0", DinarbucksMoneyVault);
        mysql_pquery(g_SQL, fsrs);
        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `fox11moneyvault`=%d WHERE `id`=0", Fox11MoneyVault);
        mysql_pquery(g_SQL, fsrs);
        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `automaxmoneyvault`=%d WHERE `id`=0", AutomaxMoneyVault);
        mysql_pquery(g_SQL, fsrs);

        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `taxtiming`=%d WHERE `id`=0", FactBadTaxTime);
        mysql_pquery(g_SQL, fsrs);
    }
    return 1;
}

task SendRandBotMessage[300000]()
{
    foreach(new i : Player) if(AccountData[i][pSpawned])
    {
        new string[144], randasmaul = random(sizeof(g_ServerHintTips));
        format(string, sizeof(string), "TIP: %s", g_ServerHintTips[randasmaul]);
        SendClientMessage(i, 0x077292FF, string);
    }
    return 1;
}

static hostnamestep = 0, gmtxt[128];
task updateHostname[5000]()
{
    switch(hostnamestep)
	{
		case 0:
		{
			hostnamestep = 1;

            SendRconCommand("hostname Pahlawan Roleplay | We Are Back!");
		}
		case 1:
		{
			hostnamestep = 2;

			SendRconCommand("hostname Pahlawan Roleplay | est. 1 November 2020");
		}
        case 2:
		{
			hostnamestep = 3;

            SendRconCommand("hostname Pahlawan Roleplay | Welcome Home!");
		}
        case 3:
		{
			hostnamestep = 0;

            SendRconCommand("hostname Pahlawan Roleplay | bit.ly/pahlawan-rp");
		}
	}
    return 1;
}