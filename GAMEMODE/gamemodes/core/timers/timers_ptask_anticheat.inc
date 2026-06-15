#include <YSI_Coding\y_hooks>

hook OnPlayerUpdate(playerid)
{
    if(!AccountData[playerid][pSpawned] || !AccountData[playerid][IsLoggedIn])
    {
        if(GetPlayerWeapon(playerid) != 0)
        {
            SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack "YELLOW"[%s].", ReturnWeaponName(GetPlayerWeapon(playerid)));
            KickEx(playerid);
            return 0;
        }
    }

    if(GetPlayerWeapon(playerid) == 40)
    {
        Kick(playerid);
        return 0;
    }
    return 1;
}

task AntiCheatVehSlap[1000]() 
{
    foreach(new v : Vehicle)
    {
        if(IsValidVehicle(v) && v != INVALID_VEHICLE_ID)
        {
            new Float:vlx[3], impstr[158];
            GetVehicleVelocity(v, vlx[0], vlx[1], vlx[2]);
            if(vlx[0] > 1.7 || vlx[1] > 1.7 || vlx[2] > 1.7)
            {
                if(!IsAPlane(v))
                {
                    foreach(new i : Player)
                    {
                        if(v == JobVehicle[i])
                        {
                            DestroyVehicle(JobVehicle[i]);
                        }
                        
                        if(v == TrailerVehicle[i])
                        {
                            DestroyVehicle(TrailerVehicle[i]);
                        }

                        if(v == FactionHeliVeh[i])
                        {
                            DestroyVehicle(FactionHeliVeh[i]);
                        }

                        if(v == ShowroomVeh[i])
                        {
                            DestroyVehicle(ShowroomVeh[i]);
                        }

                        if(v == DMVVeh[i])
                        {
                            DestroyVehicle(DMVVeh[i]);
                        }

                        if(v == PlayerFactionVehicle[i][AccountData[i][pFaction]])
                        {
                            if(VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vIsDeath])
                            {
                                DestroyVehicle(PlayerFactionVehicle[i][AccountData[i][pFaction]]);
                                FactionVehHasCallsign[PlayerFactionVehicle[i][AccountData[i][pFaction]]] = false;

                                LSPDPlayerCallsign[i][0] = EOS;

                                static string[168];
                                mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", AccountData[i][pID]);
                                mysql_pquery(g_SQL, string);
                            }
                            else
                            {
                                SetVehiclePos(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehPos][0], PlayerFactionVehStats[i][pFactVehPos][1], PlayerFactionVehStats[i][pFactVehPos][2]);
                                SetVehicleZAngle(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehPos][3]);
                                ChangeVehicleColor(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehColor1], PlayerFactionVehStats[i][pFactVehColor2]);
                                VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vCoreFuel] = PlayerFactionVehStats[i][pFactVehFuel];
                                VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vMaxHealth] = PlayerFactionVehStats[i][pFactVehMaxHealth];
                                VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vIsBodyUpgraded] = PlayerFactionVehStats[i][pFactVehBodyUpgraded];
                                VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vIsBodyBroken] = PlayerFactionVehStats[i][pFactVehBodyBroken];
                                SetVehicleVirtualWorldEx(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehWorld]);

                                if(PlayerFactionVehStats[i][pFactVehHealth] < 350.0)
                                {
                                    SetValidVehicleHealth(PlayerFactionVehicle[i][AccountData[i][pFaction]], 350.0);
                                }
                                else
                                {
                                    SetValidVehicleHealth(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehHealth]);
                                }
                                UpdateVehicleDamageStatus(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehDamage][0], PlayerFactionVehStats[i][pFactVehDamage][1], PlayerFactionVehStats[i][pFactVehDamage][2], PlayerFactionVehStats[i][pFactVehDamage][3]);
                                SwitchVehicleEngine(PlayerFactionVehicle[i][AccountData[i][pFaction]], false);
                                SwitchVehicleDoors(PlayerFactionVehicle[i][AccountData[i][pFaction]], PlayerFactionVehStats[i][pFactVehLocked]);
                                VehicleCore[PlayerFactionVehicle[i][AccountData[i][pFaction]]][vCoreLocked] = PlayerFactionVehStats[i][pFactVehLocked];
                            }
                        }
                            
                        if(v == EventVehicle[i])
                        {
                            DestroyVehicle(EventVehicle[i]);
                        }

                        if((pInSpecMode[i] == 2 || pInSpecMode[i] == 3) && SavingVehID[i] == v)
                        {
                            GetVehicleBoot(v, AccountData[i][pPos][0], AccountData[i][pPos][1], AccountData[i][pPos][2]);

                            AccountData[i][pInterior] = GetVehicleInterior(v);
                            AccountData[i][pWorld] = GetVehicleVirtualWorld(v);

                            SetSpawnInfo(i, NO_TEAM, AccountData[i][pSkin], AccountData[i][pPos][0], AccountData[i][pPos][1], AccountData[i][pPos][2], 180.0, 0, 0, 0, 0, 0, 0);
                            TogglePlayerSpectating(i, false);

                            PlayerSpectatePlayer(i, INVALID_PLAYER_ID);
                            PlayerSpectateVehicle(i, INVALID_VEHICLE_ID);
                            
                            SavingVehID[i] = INVALID_VEHICLE_ID;
                            pInSpecMode[i] = 0;

                            ShowTDN(i, NOTIFICATION_INFO, "Anda telah keluar dari trunk kendaraan.");

                            PlayerPlaySound(i, 12200, 0, 0, 0);
                        }

                        if(AccountData[i][pDuringCarsteal])
                        {
                            if(v == g_CarstealCarPhysic[i])
                            {
                                DestroyVehicle(g_CarstealCarPhysic[i]);

                                g_CarstealCountdown = 0;
                                AccountData[i][pDuringCarsteal] = false;
                                g_IsCarstealStarted = false;
                                g_CarstealCarFound[i] = false;
                                g_CarstealCooldown = gettime() + 1800;

                                ResetAllRaceCP(i);
                                
                                foreach(new x : LSPDDuty)
                                {
                                    if(DestroyDynamicMapIcon(AccountData[i][g_CarstealIcon][x]))
                                        AccountData[i][g_CarstealIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
                                }

                                ShowFivemNotify(i, "Pahlawan Roleplay~n~CAR STEAL", "Kendaraan carsteal telah hancur, misi dinyatakan gagal!", "hud:radar_qmark", 25);
                            }
                        }
                    }
                    
                    foreach(new vid : PvtVehicles)
                    {
                        if(v == PlayerVehicle[vid][pVehPhysic])
                        {
                            if(!PlayerVehicle[vid][pVehInsuranced])
                            {
                                // masukin variable dari database player biar mobilnya gak spawn polosan
                                SetVehiclePos(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehPos][0], PlayerVehicle[vid][pVehPos][1], PlayerVehicle[vid][pVehPos][2]);
                                SetVehicleZAngle(v, PlayerVehicle[vid][pVehPos][3]);
                                ChangeVehicleColor(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehColor1], PlayerVehicle[vid][pVehColor2]);
                                VehicleCore[PlayerVehicle[vid][pVehPhysic]][vCoreFuel] = PlayerVehicle[vid][pVehFuel];
                                SetVehicleNumberPlate(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehPlate]);
                                SetVehicleVirtualWorldEx(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehWorld]);
                                LinkVehicleToInteriorEx(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehInterior]);

                                if(PlayerVehicle[vid][pVehHealth] < 350.0)
                                {
                                    SetValidVehicleHealth(PlayerVehicle[vid][pVehPhysic], 350.0);
                                }
                                else
                                {
                                    SetValidVehicleHealth(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehHealth]);
                                    VehicleCore[PlayerVehicle[vid][pVehPhysic]][vMaxHealth] = PlayerVehicle[vid][pVehMaxHealth];
                                    VehicleCore[PlayerVehicle[vid][pVehPhysic]][vIsBodyUpgraded] = PlayerVehicle[vid][pVehBodyUpgraded];
                                    VehicleCore[PlayerVehicle[vid][pVehPhysic]][vIsBodyBroken] = PlayerVehicle[vid][pVehBodyBroken];
                                }
                                UpdateVehicleDamageStatus(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehDamage][0], PlayerVehicle[vid][pVehDamage][1], PlayerVehicle[vid][pVehDamage][2], PlayerVehicle[vid][pVehDamage][3]);
                                if(PlayerVehicle[vid][pVehPaintjob] != -1)
                                {
                                    ChangeVehiclePaintjob(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehPaintjob]);
                                }
                                
                                for(new z = 0; z < 17; z++)
                                {
                                    if(PlayerVehicle[vid][pVehMod][z]) AddVehicleComponent(PlayerVehicle[vid][pVehPhysic], PlayerVehicle[vid][pVehMod][z]);
                                }

                                if(PlayerVehicle[vid][pVehLocked])
                                {
                                    SwitchVehicleDoors(PlayerVehicle[vid][pVehPhysic], true);
                                    VehicleCore[PlayerVehicle[vid][pVehPhysic]][vCoreLocked] = true;
                                }
                                else
                                {
                                    SwitchVehicleDoors(PlayerVehicle[vid][pVehPhysic], false);
                                    VehicleCore[PlayerVehicle[vid][pVehPhysic]][vCoreLocked] = false;
                                }

                                if(IsEngineVehicle(PlayerVehicle[vid][pVehPhysic]))
                                {
                                    SwitchVehicleEngine(PlayerVehicle[vid][pVehPhysic], false);
                                }
                                else
                                {
                                    SwitchVehicleEngine(PlayerVehicle[vid][pVehPhysic], true);
                                }
                            }
                            else
                            {
                                if(PlayerVehicle[vid][pVehRental] > -1 || PlayerVehicle[vid][pVehRentTime] > 0) //jika rental
                                {
                                    PlayerVehicle[vid][pVehRental] = -1;
                                    PlayerVehicle[vid][pVehRentTime] = 0;

                                    if(IsValidVehicle(PlayerVehicle[vid][pVehPhysic]))
                                    {
                                        SetVehicleNeonLights(PlayerVehicle[vid][pVehPhysic], false, PlayerVehicle[vid][pVehNeon], 0);

                                    }
                                    DestroyVehicle(PlayerVehicle[vid][pVehPhysic]);
                                    PlayerVehicle[vid][pVehHandbraked] = false;
                                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
                                    mysql_pquery(g_SQL, impstr);
                                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
                                    mysql_pquery(g_SQL, impstr);
                                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[vid][pVehID]);
                                    mysql_pquery(g_SQL, impstr);
                                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
                                    mysql_pquery(g_SQL, impstr);

                                    for(new x; x < MAX_BAGASI_ITEMS; x++)
                                    {
                                        VehicleBagasi[vid][x][vehicleBagasiExists] = false;
                                        VehicleBagasi[vid][x][vehicleBagasiID] = 0;
                                        VehicleBagasi[vid][x][vehicleBagasiVDBID] = 0;
                                        VehicleBagasi[vid][x][vehicleBagasiTemp][0] = EOS;
                                        VehicleBagasi[vid][x][vehicleBagasiModel] = 0;
                                        VehicleBagasi[vid][x][vehicleBagasiQuant] = 0;
                                    }

                                    for(new z; z < 3; z++)
                                    {
                                        VehicleHolster[vid][vHolsterTaken][z] = false;
                                        VehicleHolster[vid][vHolsterID][z] = -1;
                                        VehicleHolster[vid][vHolsterWeaponID][z] = 0;
                                        VehicleHolster[vid][vHolsterWeaponAmmo][z] = 0;
                                    }

                                    for(new x; x < 6; x++)
                                    {
                                        vtData[vid][x][vtoy_modelid] = 0;
                                        vtData[vid][x][vtoy_text][0] = EOS;
                                        strcopy(vtData[vid][x][vtoy_font], "Arial");
                                        vtData[vid][x][vtoy_fontsize] = 11;
                                        vtData[vid][x][vtoy_fontcolor][0] = 255;
                                        vtData[vid][x][vtoy_fontcolor][1] = 0;
                                        vtData[vid][x][vtoy_fontcolor][2] = 0;
                                        vtData[vid][x][vtoy_fontcolor][3] = 0;
                                        vtData[vid][x][vtoy_fontcolor][4] = 0;
                                        vtData[vid][x][vtoy_objectcolor][0] = 255;
                                        vtData[vid][x][vtoy_objectcolor][1] = 0;
                                        vtData[vid][x][vtoy_objectcolor][2] = 0;
                                        vtData[vid][x][vtoy_objectcolor][3] = 0;
                                        vtData[vid][x][vtoy_objectcolor][4] = 0;
                                        vtData[vid][x][vtoy_x] = 0.0;
                                        vtData[vid][x][vtoy_y] = 0.0;
                                        vtData[vid][x][vtoy_z] = 0.0;
                                        vtData[vid][x][vtoy_rx] = 0.0;
                                        vtData[vid][x][vtoy_ry] = 0.0;
                                        vtData[vid][x][vtoy_rz] = 0.0;
                                    }

                                    Iter_Remove(PvtVehicles, vid);
                                }
                                else //jika bukan rental
                                {
                                    if(IsValidVehicle(PlayerVehicle[vid][pVehPhysic]))
                                    {
                                        SetVehicleNeonLights(PlayerVehicle[vid][pVehPhysic], false, PlayerVehicle[vid][pVehNeon], 0);

                                    }
                                    DestroyVehicle(PlayerVehicle[vid][pVehPhysic]);
                                    PlayerVehicle[vid][pVehInsuranced] = true;
                                    PlayerVehicle[vid][pVehHandbraked] = false;
                                    mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Insuranced` = 1 WHERE `id`=%d", PlayerVehicle[vid][pVehID]);
                                    mysql_pquery(g_SQL, impstr);
                                    // mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
                                    // mysql_pquery(g_SQL, impstr);
                                    // mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[vid][pVehID]);
                                    // mysql_pquery(g_SQL, impstr);
                                }
                            }
                        }
                    }

                    for(new i; i < MAX_ADMIN_VEHICLES; i++)
                    {
                        if(v == GM[adminV][i])
                        {
                            DestroyVehicle(GM[adminV][i]);
                        }
                    }
                    VehicleCore[v][vIsDeath] = true;
                }
            }
        }
    }
    return 1;
}

ptask AntiCheatCheck[1000](playerid)
{
    foreach(new v : Vehicle) if(GetVehicleModel(v))
    {
        new Float:health;
        GetVehicleHealth(v, health);

        if(health > VehicleCore[v][vMaxHealth]) SetValidVehicleHealth(v, VehicleCore[v][vMaxHealth]);

        if((health > VehicleHealthSecurityData[v]) && VehicleHealthSecurity[v] == false) //jika health lebih dari 1000 dan health security false
        {
			if(GetPlayerVehicleID(playerid) == v)
			{
				new playerState = GetPlayerState(playerid);
				if(playerState == PLAYER_STATE_DRIVER)
				{
					SetValidVehicleHealth(v, VehicleHealthSecurityData[v]);
					SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Vehicle Health Hack!");
                    KickEx(playerid);
				}
			}
        }
        if(VehicleHealthSecurity[v] == true)
        {
            VehicleHealthSecurity[v] = false;
        }
        VehicleHealthSecurityData[v] = health;
    }
}

ptask AntiCheatWeapon[1000](playerid) 
{
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            if(!IsAPlane(GetPlayerVehicleID(playerid)))
            {
                if(GetPlayerSpeed(playerid) > 300)
                {
                    SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}ditendang dari server karena diduga Vehicle Speed Hack.", GetName(playerid), playerid);
                    SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Player Vehicle Speed Hack.");
                    KickEx(playerid);
                }
            }
        }
        else
        {
            if(GetPlayerSpeed(playerid) > 300)
            {
                SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}ditendang dari server karena diduga Player Speed Hack.", GetName(playerid), playerid);
                SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Player Speed Hack.");
                KickEx(playerid);
            }
        }
        
        if(GetPlayerWeapon(playerid) == 40)
        {
            static string[522];
		    mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_ucp` SET `Blocked`=1, `Block_Duration`=0, `Block_Reason`='Crasher', `Block_AdminName`='AV_AntiCheat', `Block_IssuedDate`=CURRENT_TIMESTAMP() WHERE `UCP`='%e'", AccountData[playerid][pUCP]);
		    mysql_pquery(g_SQL, string);

            SetWeapons(playerid);
            printf("[AntiCheat] %s(%i) ditendang dari server karena diduga Crasher.", GetName(playerid), playerid);
            KickEx(playerid, 1555);
        }

        if(IsPlayerInAnyVehicle(playerid))
        {
            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && GetPlayerState(playerid) != PLAYER_STATE_PASSENGER)
            {
                SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}ditendang dari server karena diduga Vehicle Troll.", GetName(playerid), playerid);
                SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Vehicle Troll.");
                KickEx(playerid);
            }
        }

        if(!AccountData[playerid][pInEvent])
        {
            if(IsAFireArm(GetPlayerWeapon(playerid)))
            {
                if(AccountData[playerid][pLevel] < 5)
                {
                    SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack "YELLOW"[%s].", ReturnWeaponName(GetPlayerWeapon(playerid)));
                    SetWeapons(playerid); //Reload old weapons
                    KickEx(playerid);
                }
            }
        }

        if(!AccountData[playerid][pInEvent]) //tidak event
		{
            static pwpid[MAX_PLAYERS];
            if(GetPlayerWeapon(playerid) != pwpid[playerid])
            {
                pwpid[playerid] = GetPlayerWeapon(playerid);

                if(pwpid[playerid] >= 1 && pwpid[playerid] <= 45)
                {
                    if(pwpid[playerid] != 40 && GunData[playerid][g_aWeaponSlots[pwpid[playerid]]][WeaponType] == WEAPON_TYPE_NONE)
                    {
                        SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack "YELLOW"[%s].", ReturnWeaponName(pwpid[playerid]));
                        SetWeapons(playerid); //Reload old weapons
                        KickEx(playerid);
                    }

                    if(!AccountData[playerid][pTaser] && !AccountData[playerid][pUseBeanbag])
                    {
                        if(pwpid[playerid] != 40 && GunData[playerid][g_aWeaponSlots[pwpid[playerid]]][WeaponID] != pwpid[playerid])
                        {
                            SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack "YELLOW"[%s].", ReturnWeaponName(pwpid[playerid]));
                            SetWeapons(playerid); //Reload old weapons
                            KickEx(playerid);
                        }
                    }
                }
            }
        }
        else //jika sedang di dalam event
        {
            static pwpid[MAX_PLAYERS];
            if(GetPlayerWeapon(playerid) != pwpid[playerid])
            {
                pwpid[playerid] = GetPlayerWeapon(playerid);

                if(Iter_Contains(EvRedTeam, playerid))
                {
                    if(pwpid[playerid] != 0 && pwpid[playerid] != EventInfo[redWeapon][0] && pwpid[playerid] != EventInfo[redWeapon][1] && pwpid[playerid] != EventInfo[redWeapon][2])
                    {
                        SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack "YELLOW"[%s].", ReturnWeaponName(pwpid[playerid]));
                        SetWeapons(playerid); //Reload old weapons
                        KickEx(playerid);
                    }
                }
                else if(Iter_Contains(EvBlueTeam, playerid))
                {
                    if(pwpid[playerid] != 0 && pwpid[playerid] != EventInfo[blueWeapon][0] && pwpid[playerid] != EventInfo[blueWeapon][1] && pwpid[playerid] != EventInfo[blueWeapon][2])
                    {
                        SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack "YELLOW"[%s].", ReturnWeaponName(pwpid[playerid]));
                        SetWeapons(playerid); //Reload old weapons
                        KickEx(playerid);
                    }
                }
            }
            if(!EventInfo[eventStarted] && !EventInfo[eventOpened])
            {
                ResetPlayerWeapons(playerid);
            }
        }
    }
    return 1;
}

ptask AntiCheatCheckTwo[1000](playerid) 
{
    if(GetPlayerMoney(playerid) != AccountData[playerid][pMoney])
    {
        ResetPlayerMoney(playerid);
        GivePlayerMoney(playerid, AccountData[playerid][pMoney]);
    }

    //Anti Cheat Uang
    if(AccountData[playerid][IsLoggedIn])
    {
        //Anti Darah Hack
        new Float:Healthx;
        if(!AccountData[playerid][pAdminDuty])
        {
            GetPlayerHealth(playerid, Healthx);
            if(Healthx > 100)
            {
                SetPlayerHealthEx(playerid, 100.0);
            }
        }

        //anti cheat ammo
        if(GunData[playerid][0][WeaponAmmo] > 500)
        {
            GunData[playerid][0][WeaponAmmo] = 500;
            SetWeapons(playerid);
        }
        if(GunData[playerid][1][WeaponAmmo] > 500){
            GunData[playerid][1][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][2][WeaponAmmo] > 500){
            GunData[playerid][2][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][3][WeaponAmmo] > 500){
            GunData[playerid][3][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][4][WeaponAmmo] > 500){
            GunData[playerid][4][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][5][WeaponAmmo] > 500){
            GunData[playerid][5][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][6][WeaponAmmo] > 500){
            GunData[playerid][6][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][7][WeaponAmmo] > 500){
            GunData[playerid][7][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][8][WeaponAmmo] > 500){
            GunData[playerid][8][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][9][WeaponAmmo] > 500){
            GunData[playerid][9][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][10][WeaponAmmo] > 500){
            GunData[playerid][10][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][11][WeaponAmmo] > 500){
            GunData[playerid][11][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        if(GunData[playerid][12][WeaponAmmo] > 500){
            GunData[playerid][12][WeaponAmmo] = 500;
            SetWeapons(playerid);}
        
        if(AccountData[playerid][pAdmin] < 1 && !AccountData[playerid][pSteward])
        {
            //anti jetpack
            if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
            {
                SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Jetpack Hack.");
                KickEx(playerid);
            }
            
            //anti cit senjata terlarang
            if(IsProhibitedWeapon(GetPlayerWeapon(playerid)))
            {
                SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena memegang senjata terlarang.");
                KickEx(playerid);
            }
        }
        
        //anti-lag
        if(GetPlayerPing(playerid) >= 650)
        {
            SendClientMessageEx(playerid, Y_RED, "[Anti-Lag] {DBD7D2}Anda ditendang dari server karena high-ping "YELLOW"(%d/650).", GetPlayerPing(playerid));
            KickEx(playerid);
        }
        
        new formulas = NetStats_GetConnectedTime(playerid)/1000;
        if(GetPlayerPacketLoss(playerid) >= 10.00 && formulas >= 360)
        {
            SendClientMessageEx(playerid, Y_RED, "[Anti-Lag] {DBD7D2}Anda ditendang dari server karena packetloss tinggi "YELLOW"(%.2f/10.00).", GetPlayerPacketLoss(playerid));
            KickEx(playerid);
        }
    }
    return 1;
}

ptask AntiCheatCheckThree[1000](playerid) 
{   
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        //Anti Armour Hacks
        if(gettime() > Anticheat[playerid][acArmorTime])
        {
            if(!AccountData[playerid][pHasArmor] && !AccountData[playerid][pInEvent]) //jika player tidak sedang memakai valid armor
            {
                static Float:A[MAX_PLAYERS];
                GetPlayerArmour(playerid, A[playerid]);
                if(A[playerid] > 0.0) //tetapi memiliki armor di atas 0 persen maka itu armor cheat
                {
                    SetPlayerArmour(playerid, 0.0);
                    AccountData[playerid][pArmor] = 0.0;
                    AccountData[playerid][pHasArmor] = false;
                    AccountData[playerid][pArmorEmpty] = true;

                    SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Stop gunakan Armour Hacks atau anda akan dibanned!");
                    return KickEx(playerid);
                }
            }
        }

        // if(AccountData[playerid][pHasArmor]) //jika player memakai valid armor
        // {
        //     new Float:parmor;
        //     GetPlayerArmour(playerid, parmor);
        //     if(parmor <= 0.0) //jika armor di badan kurang atau sama dengan 0 persen
        //     {
        //         if(!AccountData[playerid][pArmorEmpty]) //jika armor tidak kosong
        //         {
        //             SetPlayerArmour(playerid, 0.0);
        //             AccountData[playerid][pArmor] = 0.0;
        //             AccountData[playerid][pHasArmor] = false;
        //             AccountData[playerid][pArmorEmpty] = true;
        //         }
        //     }
        // }
    }
    return 1;
}

ptask AntiFlyHack[1000](playerid) 
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        switch(GetPlayerAnimationIndex(playerid))
        {
            case 958, 1538, 1539, 1543:
            {
                new
                    Float:z,
                    Float:vx,
                    Float:vy,
                    Float:vz;

                GetPlayerPos(playerid, z, z, z);
                GetPlayerVelocity(playerid, vx, vy, vz);

                if((z > 20.0) && (0.9 <= floatsqroot((vx * vx) + (vy * vy) + (vz * vz)) <= 1.9) && (AccountData[playerid][pAdmin] < 1 || !AccountData[playerid][pSteward]))
                {
                    SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}ditendang dari server karena diduga Flyhacks.", GetName(playerid), playerid);
                    SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena Flyhacks.");
                    KickEx(playerid);
                }
            }
        }
    }

    if(AccountData[playerid][pSpawned])
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
        {
            if(pInSpecMode[playerid] == 0 && AccountData[playerid][pSpec] == INVALID_PLAYER_ID)
            {
                if(AccountData[playerid][pAdmin] < 1 && !AccountData[playerid][pSteward] && !AccountData[playerid][pApprentice])
                {
                    SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena Invalid State.");
                    KickEx(playerid);
                }
            }
        }

        if(!IsPlayerInAnyVehicle(playerid))
        {
            switch(GetPlayerAnimationIndex(playerid))
            {
                case 123, 1128:
                {
                    SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}ditendang dari server karena diduga slapper.", GetName(playerid), playerid);
                    SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena diduga slapper.");
                    KickEx(playerid);
                }
            }
        }
    }
    return 1;
}

forward AntiKnifeKill(playerid);
public AntiKnifeKill(playerid)
{
    GivePlayerWeaponEx(playerid, 4, 1, WEAPON_TYPE_PLAYER);
    return 1;
}

ptask UpdateSpecialAction[1000](playerid) 
{
    if(GetPlayerAnimationIndex(playerid) == 748)
    {
        ResetWeapon(playerid, 4);
        SetTimerEx("AntiKnifeKill", 2555, false, "i", playerid);
    }
    return 1;
}

ptask UpateAntiFConn[1000](playerid) 
{
    if(IsPlayerNPC(playerid))
    {
        return Ban(playerid);
    }

    if(!AccountData[playerid][pSpawned] || !AccountData[playerid][IsLoggedIn])
    {
        if(GetPlayerWeapon(playerid) != 0)
        {
            SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack "YELLOW"[%s].", ReturnWeaponName(GetPlayerWeapon(playerid)));
            KickEx(playerid);
            return 1;
        }
    }

    if(IsPlayerSpawned(playerid))
    {
        if(!AVC_PConnected[playerid] && !AccountData[playerid][IsLoggedIn] && !AccountData[playerid][pSpawned] && !InCharSelection[playerid] && !pLoginSpawnLoaded[playerid])
        {
            SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena terdeteksi Fake Connect.");
            return KickEx(playerid);
        }
        
        if(GetPlayerColor(playerid) == 0x7F7F83FF && !InCharSelection[playerid] && !pLoginSpawnLoaded[playerid])
        {
            SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena terdeteksi Fake Connect.");
            return KickEx(playerid);
        }
    }
    
    if(IsPlayerMoving(playerid))
    {
        if(!AVC_PConnected[playerid] && !AccountData[playerid][IsLoggedIn] && !AccountData[playerid][pSpawned] && !InCharSelection[playerid] && !pLoginSpawnLoaded[playerid])
        {
            SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena terdeteksi Fake Connect [IPM].");
            return KickEx(playerid);
        }
    }
    return 1;
}
