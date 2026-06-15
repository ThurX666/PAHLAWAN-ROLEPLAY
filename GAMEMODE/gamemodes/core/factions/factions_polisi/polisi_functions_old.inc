#include <YSI_Coding\y_hooks>

enum e_PoliceDetails
{
    //duty
    STREAMER_TAG_AREA:LSPDDutyArea[2],
    STREAMER_TAG_OBJECT:LSPDDutyObjid[2],

    //locker
    STREAMER_TAG_AREA:PoliceLockerArea[2],
    STREAMER_TAG_OBJECT:PoliceLockerObjid[2],

    //bos desk
    STREAMER_TAG_AREA:PoliceBosDeskArea[2],
    STREAMER_TAG_OBJECT:PoliceBosDeskObjid[2],

    //brankas
    STREAMER_TAG_AREA:PoliceBrankasArea[2],
    STREAMER_TAG_OBJECT:PoliceBrankasObjid[2],

    //garage
    STREAMER_TAG_AREA:PoliceArmouryArea[2],
    STREAMER_TAG_OBJECT:PoliceArmouryObjid[2],

    //garage
    STREAMER_TAG_AREA:PoliceGarageArea[2],
    STREAMER_TAG_OBJECT:PoliceGarageObjid[2],

    //impound
    STREAMER_TAG_CP:PoliceImpoundCP,

    //helipad
    STREAMER_TAG_CP:PoliceHeliCP[2],

    //spike trap, roadblock
    STREAMER_TAG_OBJECT:PoliceConeObjid,

    STREAMER_TAG_OBJECT:PoliceSpikeObjid,
    STREAMER_TAG_AREA:PoliceSpikeArea,

    STREAMER_TAG_OBJECT:PoliceRoadblockObjid,
};
new PlayerFactionPoliceVars[MAX_PLAYERS][e_PoliceDetails];

enum _Police_Details
{
    Float:LSPDDutyPos[3],
    Float:policeLockerPos[3],
    Float:policeBosDeskPos[3],
    Float:policeBrankasPos[3],
    Float:policeArmouryPos[3],
    Float:policeGaragePos[3],
    Float:policeGarageSpawnPos[4],
    Float:policeHeliPos[3],
    Float:policeHeliSpawnPos[4],
    policeVWID,
    policeIntID
};

new Police_Stuff[2][_Police_Details] =
{
    //on duty, locker, bos desk, brankas, armoury, garage pos, garage spawn pos, helipad, helipad spawn pos
    {{225.1268,2444.5994,-14.6972}, {205.7915,2423.3843,-14.6972}, {205.6617,2409.7437,-14.6972}, {220.3018,2445.0837,-14.6972}, {208.4825,2424.1873,-14.6972}, {-2024.6140,-121.3482,35.1803}, {-2028.9132,-126.3957,35.3595,90.1056}, {-2023.3123,-104.2537,38.9219}, {-2029.7664,-113.5740,39.0972,269.5508}, 21, 5}, //polantas
    {{242.4911,1858.9694,14.0840}, {247.6900,1859.0685,14.0840}, {222.1598,1822.8408,6.4141}, {266.8814,1854.3435,8.7578}, {213.6717,1825.7717,6.4141}, {250.1871,1828.4573,17.6406}, {257.0557,1832.1956,17.6325,179.5680}, {283.3804,2039.5138,17.6406}, {280.8697,2057.4221,19.2365,90.1010}, 69, 0} //federal
};

new Float: RandomJailSpawn[][5] = {
    {325.3861,1833.6582,8.0064,90.0492},
    {313.5565,1833.5442,8.0064,90.6759},
    {303.3396,1833.7335,8.0199,268.9408},
    {302.7939,1829.9690,8.0199,359.8083},
    {325.8369,1829.5742,8.0064,357.5190}
};

static const CopRank[20][] = 
{
	"N/A",

    "Recruit", //1
    "Police Officer I", //2
    "Police Officer II", //3
    "Police Officer III", //4
    "Police Officer III+1", //5
    "Detective I", //6
    "Sergeant I", //7
    "Detective II", //8
    "Sergeant II", //9
    "Detective III", //10
    "Lieutenant I", //11
    "Lieutenant II", //12
    "Captain I", //13
    "Captain II", //14
    "Captain III", //15
	"Commander", //16
	"Deputy Chief of Police", //17
    "Assistant Chief of Police", //18
	"Chief of Police" //19
};

static const CopSat[4][] = 
{
	"N/A",

    "SATLANTAS", //1
    "SABHARA", //2
    "BRIMOB" //3
};

GetPlayerNearestPoldaGarage(playerid)
{
    for(new x; x < 2; x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, Police_Stuff[x][policeGaragePos][0], Police_Stuff[x][policeGaragePos][1], Police_Stuff[x][policeGaragePos][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
        {
            return x;
        }
    }
    return -1;
}

IsPlayerNearPoldaGarage(playerid)
{
    for(new x; x < 2; x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, Police_Stuff[x][policeGaragePos][0], Police_Stuff[x][policeGaragePos][1], Police_Stuff[x][policeGaragePos][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
        {
            return true;
        }
    }
    return false;
}

AssignPoliceUniform(playerid)
{
    AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (311) : (309);
    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
    AccountData[playerid][pIsUsingUniform] = true;

    //lepas armor
    SetPlayerArmour(playerid, 0.0);
    AccountData[playerid][pArmor] = 0.0;
    AccountData[playerid][pHasArmor] = false;
    AccountData[playerid][pArmorEmpty] = true;

    RemovePlayerAttachedObject(playerid, 5);

    //lepas topi
    RemovePlayerAttachedObject(playerid, 6);
}

AssignPoliceLightVest(playerid)
{
    if(AccountData[playerid][pGender] == 1)
    {
        SetPlayerAttachedObject(playerid, 5, 19904, 1, 0.124999, 0.050000, -0.002000, 4.599998, 88.700027, 176.900009, 1.180999, 1.154000, 0.779999, -16711936, -16711936);
    }
    else
    {
        SetPlayerAttachedObject(playerid, 5, 19904, 1, 0.148999, 0.053999, 0.003000, 0.000000, 89.399993, 173.500000, 0.945000, 1.000000, 0.779999, -16711936, -16711936);
    }
    SetPlayerArmourEx(playerid, 200.0);
    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil mengenakan Light Vest dari locker.");
}

AssignPoliceHeavyVest(playerid)
{
    if(AccountData[playerid][pGender] == 1)
    {
        SetPlayerAttachedObject(playerid, 5, 19904, 1, 0.124999, 0.050000, -0.002000, 4.599998, 88.700027, 176.900009, 1.180999, 1.154000, 0.779999, -16711936, -16711936);
    }
    else
    {
        SetPlayerAttachedObject(playerid, 5, 19904, 1, 0.148999, 0.053999, 0.003000, 0.000000, 89.399993, 173.500000, 0.945000, 1.000000, 0.779999, -16711936, -16711936);
    }
    SetPlayerArmourEx(playerid, 254.0);
    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil mengenakan Heavy Vest dari locker.");
}

SendPlayerToFederal(playerid)
{
    new rand = random(sizeof(RandomJailSpawn));
    SetPlayerPositionEx(playerid, RandomJailSpawn[rand][0], RandomJailSpawn[rand][1], RandomJailSpawn[rand][2], RandomJailSpawn[rand][3]);
    SetPlayerVirtualWorldEx(playerid, 0);
    SetPlayerInteriorEx(playerid, 10);
    PlayerVoiceData[targetid][pHasRadio] = false;
}

Polda_ShowBrankas(playerid)
{
    new counted, jljs[1218];
    format(jljs, sizeof(jljs), "Nama Item\tJumlah\n");
    for(new i; i < MAX_FACTIONS_ITEMS; i++)
    {
        if(FactionBrankas[i][factionBrankasExists] && FactionBrankas[i][factionBrankasFID] == FACTION_LSPD)
        {
            if (i % 2 == 0) {
                format(jljs, sizeof(jljs), "%s%s\t%d\t-\n", jljs, FactionBrankas[i][factionBrankasTemp], FactionBrankas[i][factionBrankasQuant]);
            }
            else {
                format(jljs, sizeof(jljs), "%s"GRAY"%s\t"GRAY"%d\t"GRAY"-\n", jljs, FactionBrankas[i][factionBrankasTemp], FactionBrankas[i][factionBrankasQuant]);
            }
            PlayerListitem[playerid][counted++] = i;
        }
    }

    if(counted == 0)
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
        "Lemari ini isinya kosong!", "Tutup", "");
    }
    else
    {
        Dialog_Show(playerid, DIALOG_POLDAVLT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
        jljs, "Pilih", "Batal");
    }
    return 1;
}

forward OnTaserShoot(playerid);
public OnTaserShoot(playerid)
{
	return SetPlayerArmedWeapon(playerid, WEAPON_SILENCED);
}

forward OnPlayerTasered(playerid);
public OnPlayerTasered(playerid)
{
    if(!IsPlayerConnected(playerid)) return 0;
    if(!AccountData[playerid][pTazed]) return 0;
    
	SetPlayerDrunkLevel(playerid, 0);
	TogglePlayerControllable(playerid, true);
    AccountData[playerid][pTazed] = false;

	StopRunningAnimation(playerid);
	return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pFaction] == FACTION_LSPD)
    {
        for(new x; x < 2; x++)
        {
            if(areaid == PlayerFactionPoliceVars[playerid][LSPDDutyArea][x])
            {
                if(!AccountData[playerid][pOnDuty])
                {
                    ShowNotifBox(playerid, "[Y] ~g~On Duty");
                }
                else
                {
                    ShowNotifBox(playerid, "[Y] ~r~Off Duty");
                }
            }
        
            if(areaid == PlayerFactionPoliceVars[playerid][PoliceLockerArea][x])
            {
                ShowNotifBox(playerid, "[Y] Locker Polisi");
            }

            if(areaid == PlayerFactionPoliceVars[playerid][PoliceBosDeskArea][x])
            {
                ShowNotifBox(playerid, "[Y] Akses Bos Desk");
            }

            if(areaid == PlayerFactionPoliceVars[playerid][PoliceBrankasArea][x])
            {
                ShowNotifBox(playerid, "[Y] Akses Brankas");
            }

            if(areaid == PlayerFactionPoliceVars[playerid][PoliceArmouryArea][x])
            {
                ShowNotifBox(playerid, "[Y] Akses Brankas");
            }

            if(areaid == PlayerFactionPoliceVars[playerid][PoliceGarageArea][x])
            {
                ShowNotifBox(playerid, "[Y] Garasi Polisi");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    for(new x; x < 2; x++)
    {
        if(areaid == PlayerFactionPoliceVars[playerid][LSPDDutyArea][x])
        {
            HideNotifBox(playerid);
        }

        if(areaid == PlayerFactionPoliceVars[playerid][PoliceLockerArea][x])
        {
            HideNotifBox(playerid);
        }

        if(areaid == PlayerFactionPoliceVars[playerid][PoliceBosDeskArea][x])
        {
            HideNotifBox(playerid);
        }

        if(areaid == PlayerFactionPoliceVars[playerid][PoliceBrankasArea][x])
        {
            HideNotifBox(playerid);
        }

        if(areaid == PlayerFactionPoliceVars[playerid][PoliceArmouryArea][x])
        {
            HideNotifBox(playerid);
        }

        if(areaid == PlayerFactionPoliceVars[playerid][PoliceGarageArea][x])
        {
            HideNotifBox(playerid);
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == PlayerFactionPoliceVars[playerid][PoliceImpoundCP])
    {
        ShowNotifBox(playerid, "[Y] Akses Impound");
    }

    for(new x; x < 2; x++)
    {
        if(checkpointid == PlayerFactionPoliceVars[playerid][PoliceHeliCP][x])
        {
            if(IsValidVehicle(FactionHeliVeh[playerid]))
                ShowNotifBox(playerid, "[Y] Kembalikan Heli");
            else
                ShowNotifBox(playerid, "[Y] Keluarkan Heli");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == PlayerFactionPoliceVars[playerid][PoliceImpoundCP])
    {
        HideNotifBox(playerid);
    }

    for(new x; x < 2; x++)
    {
        if(checkpointid == PlayerFactionPoliceVars[playerid][PoliceHeliCP][x])
        {
            HideNotifBox(playerid);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && AccountData[playerid][pFaction] == FACTION_LSPD && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        for(new x; x < 2; x++)
        {
            if(IsPlayerInDynamicArea(playerid, PlayerFactionPoliceVars[playerid][LSPDDutyArea][x]))
            {
                if(!AccountData[playerid][pOnDuty])
                {
                    AccountData[playerid][pOnDuty] = true;
                    SendClienMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda sekarang "GREEN"On Duty.");
                    Iter_Add(LSPDDuty, playerid);

                    if(AccountData[playerid][pFactionSat] == 1)
                    {
                        Iter_Add(SatlantasDuty, playerid);
                    }
                    else if(AccountData[playerid][pFactionSat] == 2)
                    {
                        Iter_Add(SabharaDuty, playerid);
                    }
                    else if(AccountData[playerid][pFactionSat] == 3)
                    {
                        Iter_Add(BrimobDuty, playerid);
                    }

                    RefreshFactionMap(playerid);
                }
                else
                {
                    AccountData[playerid][pOnDuty] = false;
                    SendClienMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda sekarang "RED"Off Duty.");
                    Iter_Remove(LSPDDuty, playerid);

                    if(Iter_Contains(SatlantasDuty, playerid))
                        Iter_Remove(SatlantasDuty, playerid);

                    if(Iter_Contains(SabharaDuty, playerid))
                        Iter_Remove(SabharaDuty, playerid);

                    if(Iter_Contains(BrimobDuty, playerid))
                        Iter_Remove(BrimobDuty, playerid);
                        
                    RefreshFactionMap(playerid);
                }
                HideNotifBox(playerid);
            }

            if(IsValidDynamicCP(PlayerFactionPoliceVars[playerid][PoliceHeliCP][x]) && IsPlayerInDynamicCP(playerid, PlayerFactionPoliceVars[playerid][PoliceHeliCP][x]))
            {
                if(IsValidVehicle(FactionHeliVeh[playerid]))
                {
                    DestroyVehicle(FactionHeliVeh[playerid]);
                    FactionHeliVeh[playerid] = INVALID_VEHICLE_ID;
                }
                else
                {
                    if(IsPlayerInDynamicCP(playerid, PlayerFactionPoliceVars[playerid][PoliceHeliCP][0]))
                        FactionHeliVeh[playerid] = CreateVehicle(497,Police_Stuff[0][policeHeliSpawnPos][0],Police_Stuff[0][policeHeliSpawnPos][1], Police_Stuff[0][policeHeliSpawnPos][2],Police_Stuff[0][policeHeliSpawnPos][3], 152,1, 60000, false);
                    else if(IsPlayerInDynamicCP(playerid, PlayerFactionPoliceVars[playerid][PoliceHeliCP][1]))
                        FactionHeliVeh[playerid] = CreateVehicle(497,Police_Stuff[1][policeHeliSpawnPos][0],Police_Stuff[1][policeHeliSpawnPos][1], Police_Stuff[1][policeHeliSpawnPos][2],Police_Stuff[1][policeHeliSpawnPos][3], 152,1, 60000, false);
                    
                    VehicleCore[FactionHeliVeh[playerid]][vCoreFuel] = 100;
                    SetValidVehicleHealth(FactionHeliVeh[playerid], 1000.0); 
                    VehicleCore[FactionHeliVeh[playerid]][vCoreLocked] = false;
                    PutPlayerInVehicleEx(playerid, FactionHeliVeh[playerid], 0);
                    SwitchVehicleEngine(FactionHeliVeh[playerid], true);
                    SwitchVehicleDoors(FactionHeliVeh[playerid], false);
                }
                HideNotifBox(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionPoliceVars[playerid][PoliceLockerArea][x]))
            {
                HideNotifBox(playerid);
                Dialog_Show(playerid, DIALOG_LOCKER_POLISI, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Seragam", 
                "Baju Warga\n\
                "GRAY"Baju Polisi\n\
                Baju Abu\n\
                "GRAY"Baju Biru\n\
                Baju Brimob 1\n\
                "GRAY"Baju Brimob 2\n\
                Baju Polantas\n\
                "GRAY"Light Vest\n\
                Heavy Vest", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionPoliceVars[playerid][PoliceBosDeskArea][x]))
            {
                HideNotifBox(playerid);
                if(AccountData[playerid][pFactionRank] < 19) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses Bos Desk!");

                Dialog_Show(playerid, DIALOG_BOSDESK_POLDA, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Bos Desk", 
                "Invite\n\
                "GRAY"Kelola Jabatan\n\
                Kelola Divisi\n\
                "GRAY"Kick\n\
                Saldo Finansial\n\
                "GRAY"Deposit Saldo\n\
                Tarik Saldo", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionPoliceVars[playerid][PoliceBrankasArea][x]))
            {
                HideNotifBox(playerid);

                Dialog_Show(playerid, DIALOG_POLDA_BRANKAS, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Kepolisian", 
                "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Kembali");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionPoliceVars[playerid][PoliceArmouryArea][x]))
            {
                HideNotifBox(playerid);

                if(AccountData[playerid][pFactionRank] < 13)
                    return SEM(playerid, "Hanya perwira dapat akses!");

                Dialog_Show(playerid, DIALOG_ARMOURY_POLDA, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Senjata", 
                "Nama\tHarga\n\
                Desert Eagle\t$500\n\
                "GRAY"Shotgun\t"GRAY"$700\n\
                MP5\t$700\n\
                "GRAY"M4\t"GRAY"$1000\n\
                Combat Shotgun\t$1000\n\
                "RED"(Reset Senjata)", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionPoliceVars[playerid][PoliceGarageArea][x]))
            {
                HideNotifBox(playerid);
                Dialog_Show(playerid, DIALOG_GARAGE_POLDA, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Polda", 
                "Keluarkan Kendaraan\n\
                "GRAY"Simpan Kendaraan\n\
                Beli Kendaraan\n\
                "GRAY"Hapus Kendaraan", "Pilih", "Batal");
            }
        }

        if(IsValidDynamicCP(PlayerFactionPoliceVars[playerid][PoliceImpoundCP]) && IsPlayerInDynamicCP(playerid, PlayerFactionPoliceVars[playerid][PoliceImpoundCP]))
        {
            HideNotifBox(playerid);
            Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
            "Mohon masukkan player id/nomor kantong pemain tersebut:", "Pilih", "Batal");
        }
    }
    else if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFaction] == FACTION_LSPD && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pInEvent]) return 1;
        new count = 0, frmxt[522];
        foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
		{
			format(frmxt, sizeof(frmxt), "%sKantong - (%d)\n", frmxt, i);
			NearestUser[playerid][count++] = i;
		}

        if(count > 0) 
		{
            Dialog_Show(playerid, FactionPanel, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
            frmxt, "Pilih", "Batal");
		}
    }
    else if(newkeys & KEY_CROUCH && AccountData[playerid][pFaction] == FACTION_LSPD && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        // Check if the player is near the eastern A51 gate
	    if (IsPlayerInRangeOfPoint(playerid, 10.0, 287.12, 1821.51, 18.14))
	    {
            PlaySoundForPlayersInRange(1035, 50.0, 287.12, 1821.51, 18.14);

            if(!g_FederalEasternOpen)
            {
                MoveDynamicObject(A51EasternGate, 286.008666, 1833.744628, 20.010623, 2.5, 0.0, 0.0, 90.0);
                g_FederalEasternOpen = true;
            }
            else
            {
                MoveDynamicObject(A51EasternGate, 286.008666, 1822.744628, 20.010623, 2.5, 0.0, 0.0, 90.0);
                g_FederalEasternOpen = false;
            }
        }

        // Check if the player is near the northern A51 gate
	    else if (IsPlayerInRangeOfPoint(playerid, 10.0, 135.09, 1942.37, 19.82))
	    {
            PlaySoundForPlayersInRange(1035, 50.0, 287.12, 1821.51, 18.14);

            if(!g_FederalNorthernOpen)
            {
                MoveDynamicObject(A51NorthernGate, 121.545074, 1941.527709, 21.691408, 2.5, 0.0, 0.0, 180.0);
                g_FederalNorthernOpen = true;
            }
            else
            {
                MoveDynamicObject(A51NorthernGate, 134.545074, 1941.527709, 21.691408, 2.5, 0.0, 0.0, 180.0);
                g_FederalNorthernOpen = false;
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_LOCKER_POLISI:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the selection!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

            switch(listitem)
            {
                case 0: //baju warga
                {
                    //lepas armor
                    SetPlayerArmour(playerid, 0.0);
                    AccountData[playerid][pArmor] = 0.0;
                    AccountData[playerid][pHasArmor] = false;
                    AccountData[playerid][pArmorEmpty] = true;
                    
                    RemovePlayerAttachedObject(playerid, 5);

                    //lepas topi
                    RemovePlayerAttachedObject(playerid, 6);

                    SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                    AccountData[playerid][pIsUsingUniform] = false;
                    RefreshFactionMap(playerid);
                }
                case 1: //baju polisi
                {
                    AssignPoliceUniform(playerid);
                }
                case 2: //baju abu
                {
                    AssignPoliceTrainingUniform(playerid);
                }
                case 3: //baju biru
                {
                    AssignPoliceBlueUniform(playerid);
                }
                case 4: //baju brimob 1
                {
                    AssignPoliceBrimob1Uniform(playerid);
                }
                case 5: //baju brimob 2
                {
                    AssignPoliceBrimob2Uniform(playerid);
                }
                case 6: //baju polantas
                {
                    AssignPolicePolantasUniform(playerid);
                }
                case 7: //light vest
                {
                    if(!AccountData[playerid][pIsUsingUniform]) return SEM(playerid, "Anda belum mengenakan seragam polisi apapun!");
                    AssignPoliceLightVest(playerid);
                }
                case 8: //heavy vest
                {
                    if(!AccountData[playerid][pIsUsingUniform]) return SEM(playerid, "Anda belum mengenakan seragam polisi apapun!");
                    AssignPoliceHeavyVest(playerid);
                }
            }
        }
        case DIALOG_BOSDESK_POLDA:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
            if(AccountData[playerid][pFactionRank] < 19) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses Bos Desk!");

            switch(listitem)
            {
                case 0: //invite
                {
                    new frmxt[522], count = 0;

                    foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 1.5)) 
                    {
                        format(frmxt, sizeof(frmxt), "%sKantong - (%d)\n", frmxt, i);
                        NearestUser[playerid][count++] = i;
                    }

                    if(count == 0)
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", "Tidak ada pemain terdekat!", "Tutup", "");
                    }

                    Dialog_Show(playerid, DIALOG_INVITE_CONFIRM_POLDA, DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", frmxt, "Pilih", "Batal");
                }
                case 1: //kelola jabatan
                {
                    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 1 ORDER BY Char_FactionRank DESC");

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new fckname[64], fckrank, fcklastlogin[30];
                        
                        AddDialogListitem(playerid, "Nama\tRank\tLast Online");
                        for(new i; i < rows; ++i)
                        {
                            cache_get_value_name(i, "Char_Name", fckname);
                            cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                            cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

                            AddDialogListitem(playerid, "%s\t%s\t%s", fckname, CopRank[fckrank], fcklastlogin);

                        }
                        ShowPlayerDialogPages(playerid, "PoldaSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Pilih", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
                    }
                }
                case 2: //kelola divisi
                {
                    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 1 ORDER BY Char_FactionRank DESC");

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new fckname[64], fckrank, fckdiv, fcklastlogin[30];
                        
                        AddDialogListitem(playerid, "Nama\tRank\tDivisi");
                        for(new i; i < rows; ++i)
                        {
                            cache_get_value_name(i, "Char_Name", fckname);
                            cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                            cache_get_value_name_int(i, "Char_FactionSat", fckdiv);
                            cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

                            AddDialogListitem(playerid, "%s\t%s\t%s\t%s", fckname, CopRank[fckrank], CopSat[fckdiv], fcklastlogin);

                        }
                        ShowPlayerDialogPages(playerid, "PoldaSetSat", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kelola Satuan", "Pilih", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
                    }
                }
                case 3: //kick
                {
	                mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 1 ORDER BY Char_FactionRank DESC");

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new fckname[64], fckrank, fcklastlogin[30];
                        
                        AddDialogListitem(playerid, "Nama\tRank\tLast Online");
                        for(new i; i < rows; ++i)
                        {
                            cache_get_value_name(i, "Char_Name", fckname);
                            cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                            cache_get_value_name(i, "Char_LastLogin", fcklastlogin);
                            
                            AddDialogListitem(playerid, "%s\t%s\t%s", fckname, CopRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialogPages(playerid, "PoldaKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Pilih", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Faction ini tidak memiliki anggota!", "Tutup", "");
                    }
                }
            }
        }
        case DIALOG_INVITE_CONFIRM_POLDA:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
            if(AccountData[playerid][pFactionRank] < 19) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses Bos Desk!");

            new targetid = NearestUser[playerid][listitem], icsr[128];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            AccountData[targetid][pFaction] = FACTION_LSPD;
            AccountData[targetid][pFactionRank] = 1;
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 1, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
            mysql_pquery(g_SQL, icsr);
            RefreshFactionMap(targetid);
            SendClientMessageEx(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have successfully invited "YELLOW"%s "WHITE"to the faction.", AccountData[targetid][pName]);

            InsertFactionLog("Invite", sprintf("%s %s - %s %s", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP]), "Polda");
        }
        case DIALOG_RANK_SET_POLDA:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
            if(AccountData[playerid][pFactionRank] < 19) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses Bos Desk!");

            if(isnull(inputtext)) return Dialog_Show(playerid, DIALOG_RANK_SET_POLDA, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Error: Tidak dapat dikosongkan!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Tamtama - BHARADA\n\
            2. Tamtama - BHARATU\n\
            3. Tamtama - BHARAKA\n\
            4. Tammtama - ABRIPDA\n\
            5. Tamtama - ABRIPTU\n\
            6. Tamtama - ABRIGPOL\n\
            7. Bintara - BRIPDA\n\
            8. Bintara - BRIPTU\n\
            9. Bintara - BRIGPOL\n\
            10. Bintara - BRIPKA\n\
            11. Bintara - AIPDA\n\
            12. Bintara - AIPTU\n\
            13. Perwira - IPDA\n\
            14. Perwira - IPTU\n\
            15. Perwira - AKP\n\
            16. Perwira - KOMPOL\n\
            17. Perwira - AKBP\n\
            18. Perwira - KOMBESPOL\n\
            19. Perwira - BRIGJEN\n\
            20. Perwira - IRJEN\n\
            21. Perwira - KOMJEN\n\
            22. JENDERAL", "Set", "Batal");
            
            if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, DIALOG_RANK_SET_POLDA, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Error: Masukkan hanya angka!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Tamtama - BHARADA\n\
            2. Tamtama - BHARATU\n\
            3. Tamtama - BHARAKA\n\
            4. Tammtama - ABRIPDA\n\
            5. Tamtama - ABRIPTU\n\
            6. Tamtama - ABRIGPOL\n\
            7. Bintara - BRIPDA\n\
            8. Bintara - BRIPTU\n\
            9. Bintara - BRIGPOL\n\
            10. Bintara - BRIPKA\n\
            11. Bintara - AIPDA\n\
            12. Bintara - AIPTU\n\
            13. Perwira - IPDA\n\
            14. Perwira - IPTU\n\
            15. Perwira - AKP\n\
            16. Perwira - KOMPOL\n\
            17. Perwira - AKBP\n\
            18. Perwira - KOMBESPOL\n\
            19. Perwira - BRIGJEN\n\
            20. Perwira - IRJEN\n\
            21. Perwira - KOMJEN\n\
            22. JENDERAL", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return Dialog_Show(playerid, DIALOG_RANK_SET_POLDA, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Tamtama - BHARADA\n\
            2. Tamtama - BHARATU\n\
            3. Tamtama - BHARAKA\n\
            4. Tammtama - ABRIPDA\n\
            5. Tamtama - ABRIPTU\n\
            6. Tamtama - ABRIGPOL\n\
            7. Bintara - BRIPDA\n\
            8. Bintara - BRIPTU\n\
            9. Bintara - BRIGPOL\n\
            10. Bintara - BRIPKA\n\
            11. Bintara - AIPDA\n\
            12. Bintara - AIPTU\n\
            13. Perwira - IPDA\n\
            14. Perwira - IPTU\n\
            15. Perwira - AKP\n\
            16. Perwira - KOMPOL\n\
            17. Perwira - AKBP\n\
            18. Perwira - KOMBESPOL\n\
            19. Perwira - BRIGJEN\n\
            20. Perwira - IRJEN\n\
            21. Perwira - KOMJEN\n\
            22. JENDERAL", "Set", "Batal");

            new hjh[128];
            mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
            mysql_pquery(g_SQL, hjh);

            foreach(new i : Player)
            {
                if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
                {
                    AccountData[i][pFactionRank] = strval(inputtext);
                    SendClientMessage(i, X11_PALEGREEN4, "[Info] "WHITE"Jabatan anda di faction telah diperbarui.");
                    InsertFactionLog("Set Rank", sprintf("%s %s - %s %s LV %d", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[i][pName], AccountData[i][pUCP], strval(inputtext)), "Polda");
                }
            }

            SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah merubah jabatan faction pemain tersebut.");

        }
        case DIALOG_SAT_SET_POLDA:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
            if(AccountData[playerid][pFactionRank] < 19) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses Bos Desk!");

            if(isnull(inputtext)) return Dialog_Show(playerid, DIALOG_SAT_SET_POLDA, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kelola Satuan", 
            "Error: Tidak dapat dikosongkan!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. SATLANTAS\n\
            2. SABHARA\n\
            3. BRIMOB", "Set", "Batal");
            
            if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, DIALOG_SAT_SET_POLDA, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kelola Satuan", 
            "Error: Masukkan hanya angka!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. SATLANTAS\n\
            2. SABHARA\n\
            3. BRIMOB", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > 3) return Dialog_Show(playerid, DIALOG_SAT_SET_POLDA, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kelola Satuan", 
            "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari 3!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. SATLANTAS\n\
            2. SABHARA\n\
            3. BRIMOB", "Set", "Batal");

            new hjh[128];
            mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FactionSat`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
            mysql_pquery(g_SQL, hjh);

            foreach(new i : Player)
            {
                if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
                {
                    AccountData[i][pFactionSat] = strval(inputtext);

                    if(Iter_Contains(SatlantasDuty, i))
		                Iter_Remove(SatlantasDuty, i);

                    if(Iter_Contains(SabharaDuty, i))
		                Iter_Remove(SabharaDuty, i);

                    if(Iter_Contains(BrimobDuty, i))
		                Iter_Remove(BrimobDuty, i);

                    if(strval(inputtext) == 1)
                    {
                        Iter_Add(SatlantasDuty, i);
                    }
                    else if(strval(inputtext) == 2)
                    {
                        Iter_Add(SabharaDuty, i);
                    }
                    else if(strval(inputtext) == 3)
                    {
                        Iter_Add(BrimobDuty, i);
                    }

                    SIM(i, "Satuan baru anda di faction telah diubah");
                }
            }

            SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil mengubah satuan faction Pemain tersebut");
        }
        case DIALOG_POLDA_BRANKAS:
        {
            if(!response) return 1;

            switch(listitem)
            {
                case 0: //deposit
                {
                    new str[1218], count;
                    format(str, sizeof(str), "Nama Item\tJumlah\n");
                    for(new index; index < MAX_INVENTORY; index++)
                    {
                        if(InventoryData[playerid][index][invExists])
                        {
                            for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invItem], true))
                            {
                                format(str, sizeof(str), "%s%s\t%d\n", str, InventoryData[playerid][index][invItem], InventoryData[playerid][index][invQuantity]);
                                PlayerListitem[playerid][count++] = index;
                            }
                        }
                    }

                    if(count == 0)
                    {
                        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
                        "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
                    }
                    else
                    {
                        Dialog_Show(playerid, DIALOG_POLDAVLT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", str, "Pilih", "Batal");
                    }
                }
                case 1: //withdraw
                {
                    if(AccountData[playerid][pFactionRank] < 13)
                        return SEM(playerid, "Hanya perwira yang dapat akses!");
            
                    Polda_ShowBrankas(playerid);
                }
            }
        }

        case DIALOG_POLDAVLT_DEPOSIT:
        {
            if(!response) 
            {
                AccountData[playerid][pMenuShowed] = false;
                return 1;
            }

            if(listitem == -1) 
            {
                AccountData[playerid][pMenuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
            }

            AccountData[playerid][pTempValue] = listitem;

            new shstr[528];
            format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Mohon masukkan jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][listitem]][invItem], InventoryData[playerid][PlayerListitem[playerid][listitem]][invQuantity]);
            Dialog_Show(playerid, DIALOG_POLDAVLT_IN, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
            shstr, "Input", "Batal");
        }
        case DIALOG_POLDAVLT_IN:
        {
            if(!response) 
            {
                AccountData[playerid][pMenuShowed] = false;
                return 1;
            }

            if(AccountData[playerid][pTempValue] == -1)
            {
                AccountData[playerid][pMenuShowed] = false;
                ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
                return 1;
            }

            new shstr[512], id = AccountData[playerid][pTempValue];
            if(isnull(inputtext)) 
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat dikosongkan!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
                Dialog_Show(playerid, DIALOG_POLDAVLT_IN, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumericEx(inputtext))
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
                Dialog_Show(playerid, DIALOG_POLDAVLT_IN, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
                Dialog_Show(playerid, DIALOG_POLDAVLT_IN, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            new invstr[1028];
            mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `faction_brankas` WHERE `FID` = %d AND `Item` = '%e'", FACTION_LSPD, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
            mysql_query(g_SQL, shstr);

            new rows = cache_num_rows();
            if(rows > 0)
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `faction_brankas` SET `Quantity` = `Quantity` + %d WHERE `FID` = %d AND `Item` = '%e'", quantity, FACTION_LSPD, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                mysql_pquery(g_SQL, invstr);

                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

                for(new x; x < MAX_FACTIONS_ITEMS; ++x)
                {
                    if(FactionBrankas[x][factionBrankasExists]  && FactionBrankas[x][factionBrankasFID] == FACTION_LSPD && !strcmp(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
                    {
                        FactionBrankas[x][factionBrankasQuant] += quantity;
                    }
                }
            }
            else
            {
                for(new x; x < MAX_FACTIONS_ITEMS; ++x)
                {
                    if(!FactionBrankas[x][factionBrankasExists]) 
                    {
                        FactionBrankas[x][factionBrankasExists] = true;
                        FactionBrankas[x][factionBrankasFID] = FACTION_LSPD;
                        strcopy(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                        FactionBrankas[x][factionBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                        FactionBrankas[x][factionBrankasQuant] = quantity;

                        mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `faction_brankas` SET `FID` = %d, `Item`='%e', `Model`=%d, `Quantity`=%d", FACTION_LSPD, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
			            mysql_pquery(g_SQL, invstr, "OnFactionDeposit", "id", playerid, x);

                        break;
                    }
                }
            }
            ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
            Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
        }
        case DIALOG_POLDAVLT_WITHDRAW:
        {
            if(!response) 
            {
                AccountData[playerid][pMenuShowed] = false;
                return 1;
            }

            if(listitem == -1) 
            {
                AccountData[playerid][pMenuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
            }

            AccountData[playerid][pTempValue] = listitem;

            new shstr[528];
            format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][listitem]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][listitem]][factionBrankasQuant]);
            Dialog_Show(playerid, DIALOG_POLDAVLT_OUT, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
            shstr, "Input", "Batal");
        }
        case DIALOG_POLDAVLT_OUT:
        {
            if(!response) 
            {
                AccountData[playerid][pMenuShowed] = false;
                return 1;
            }

            if(AccountData[playerid][pTempValue] == -1)
            {
                AccountData[playerid][pMenuShowed] = false;
                ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
                return 1;
            }

            new shstr[512], id = AccountData[playerid][pTempValue];
            if(isnull(inputtext)) 
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Tidak dapat dikosongkan!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
                Dialog_Show(playerid, DIALOG_POLDAVLT_OUT, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumericEx(inputtext))
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
                Dialog_Show(playerid, DIALOG_POLDAVLT_OUT, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant])
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
                Dialog_Show(playerid, DIALOG_POLDAVLT_OUT, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari POLDA", 
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext), jts[150];
            new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp]))/1000;
    		if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            if(!strcmp(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], "Smartphone"))
            {
                mysql_format(g_SQL, jts, sizeof(jts), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
                mysql_pquery(g_SQL, jts, "OnPlayerBuySmartphone", "i", playerid);
            }
            else
            {
                Inventory_Add(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasModel], quantity);
            }
            ShowItemBox(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], sprintf("Received %dx", quantity), FactionBrankas[PlayerListitem[playerid][id]][factionBrankasModel], 5);

            InsertFactionVaultLog(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], quantity, "Polda");

            FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant] -= quantity;
            
            if(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant] > 0)
            {
                mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `faction_brankas` SET `Quantity`=%d WHERE `ID`=%d", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasID]);
                mysql_pquery(g_SQL, jts);
            }
            else
            {
                mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `faction_brankas` WHERE `ID`=%d", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasID]);
                mysql_pquery(g_SQL, jts);

                FactionBrankas[PlayerListitem[playerid][id]][factionBrankasExists] = false;
                FactionBrankas[PlayerListitem[playerid][id]][factionBrankasID] = 0;
                FactionBrankas[PlayerListitem[playerid][id]][factionBrankasFID] = FACTION_NONE;
                FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp][0] = EOS;
                FactionBrankas[PlayerListitem[playerid][id]][factionBrankasModel] = 0;
                FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant] = 0;
            }
            AccountData[playerid][pMenuShowed] = false;
        }
        case DIALOG_ARMOURY_POLDA:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

            switch(listitem)
            {
                case 0: //DE
                {
                    if(AccountData[playerid][pMoney] < 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 500);
                    GivePlayerWeaponEx(playerid, 24, 300);
                    ShowItemBox(playerid, "Cash", "Removed $500x", 1212, 4);
                    ShowItemBox(playerid, "Desert Eagle", "Received 1x", 348, 5);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil membeli Desert Eagle");
                }
                case 1: //SG
                {
                    if(AccountData[playerid][pMoney] < 700) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 700);
                    GivePlayerWeaponEx(playerid, 25, 350);
                    ShowItemBox(playerid, "Cash", "Removed $700x", 1212, 4);
                    ShowItemBox(playerid, "Shotgun", "Received 1x", 349, 5);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil membeli Shotgun");
                }
                case 2: //MP5
                {
                    if(AccountData[playerid][pMoney] < 700) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 700);
                    GivePlayerWeaponEx(playerid, 29, 650);
                    ShowItemBox(playerid, "Cash", "Removed $700x", 1212, 4);
                    ShowItemBox(playerid, "MP5", "Received 1x", 353, 5);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil membeli MP5");
                }
                case 3: //M4
                {   
                    if(AccountData[playerid][pMoney] < 1000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 1000);
                    GivePlayerWeaponEx(playerid, 31, 650);
                    ShowItemBox(playerid, "Cash", "Removed $1000x", 1212, 4);
                    ShowItemBox(playerid, "M4", "Received 1x", 356, 5);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil membeli M4");
                }
                case 4: //Combat shotgun
                {
                    if(AccountData[playerid][pMoney] < 1000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 1000);
                    GivePlayerWeaponEx(playerid, 27, 400);
                    ShowItemBox(playerid, "Cash", "Removed $1000x", 1212, 4);
                    ShowItemBox(playerid, "Combat Shotgun", "Received 1x", 351, 5);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil membeli Combat Shotgun");
                }
                case 5: //reset weapon
                {
                    ResetPlayerWeaponsEx(playerid);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil reset semua senjata");
                }
            }
        }
        case DIALOG_GARAGE_POLDA:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
            switch(listitem)
            {
                case 0: //keluarkan kendaraan
                {
                    if(CountPlayerFactVehInGarage(playerid, FACTION_LSPD) < 1) return SEM(playerid, "Anda tidak memiliki kendaraan faction yang tersimpan!");

                    new id, count = CountPlayerFactVehInGarage(playerid, FACTION_LSPD), lstr[596];
                    format(lstr,sizeof(lstr),"No\tModel Kendaraan\tNomor Plat\n");
                    for(new itt; itt < count; itt++)
                    {
                        id = GetVehicleIDStoredFactGarage(playerid, itt, FACTION_LSPD);
                        if(itt == count)
                        {
                            format(lstr,sizeof(lstr), "%s%d\t%s\t%s", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                        }
                        else format(lstr,sizeof(lstr), "%s%d\t%s\t%s\n", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    }
                    Dialog_Show(playerid, DIALOG_GARAGE_POLDA_TAKEOUT, DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", lstr, "Pilih","Batal");
                }
                case 1: //simpan kendaraan
                {
                    new carid = INVALID_VEHICLE_ID, foundnearby = 0;

                    if((carid = Vehicle_Nearest(playerid, 10.0)) != INVALID_VEHICLE_ID)
                    {
                        if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return SEM(playerid, "Kendaraan ini bukan milik anda!");
                        if(PlayerVehicle[carid][pVehRental] > -1 || PlayerVehicle[carid][pVehRentTime] > 0) return SEM(playerid, "Anda tidak dapat menyimpan kendaraan rental!");
                        if(PlayerVehicle[carid][pVehFaction] != FACTION_LSPD) return SEM(playerid, "Kendaraan tersebut bukan dari Polda Pahlawan Roleplay!");
                        Vehicle_GetStatus(carid);
                        PlayerVehicle[carid][pVehFactStored] = FACTION_LSPD;
                        
                        foundnearby++;
                        for(new x; x < 7; x++)
                        {
                            if(DestroyDynamicObject(FactionVehObject[PlayerVehicle[carid][pVehPhysic]][x]))
                                FactionVehObject[PlayerVehicle[carid][pVehPhysic]][x] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
                        }

                        DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                        SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                        DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                        PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                    if(!foundnearby)
                        return SEM(playerid, "Tidak ada kendaraan dari Polda Pahlawan Roleplay milik anda di sekitar!");
                }
                case 2: //beli kendaraan
                {
                    Dialog_Show(playerid, DIALOG_GARAGE_POLDA_BUY, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Beli Kendaraan", 
                    "Model\tHarga\n\
                    Cruiser LSPD\t$5,000\n\
                    "GRAY"Cruiser SFPD\t"GRAY"$5,000\n\
                    HPV1000\t$2,500\n\
                    "GRAY"Premier\t"GRAY"$5,000\n\
                    Mountain Bike\n\
                    Sultan\n\
                    FBI Rancher", "Pilih", "Batal");
                }
                case 3: //hapus kendaraan
                {
                    new frmtdel[151];
                    mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 1 AND `PVeh_Owner` = %d ORDER BY `id` ASC LIMIT 30", AccountData[playerid][pID]);
                    mysql_query(g_SQL, frmtdel);

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new list[522], hkvid, hkvmod;
                        
                        format(list, sizeof(list), "Database ID\tModel\n");
                        for(new i; i < rows; ++i)
                        {
                            cache_get_value_name_int(i, "id", hkvid);
                            cache_get_value_name_int(i, "PVeh_ModelID", hkvmod);

                            format(list, sizeof(list), "%s%d\t%s\n", list, hkvid, GetVehicleModelName(hkvmod));
                        }
                        Dialog_Show(playerid, DIALOG_GARAGE_POLDA_DELETE, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Hapus Kendaraan", list, "Pilih", "Batal");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, DIALOG_GARAGE_POLDA_DELETE, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan dari Polda Pahlawan Roleplay", "Tutup", "");
                    }
                }
            }
        }
        case DIALOG_GARAGE_POLDA_TAKEOUT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

            if(listitem == -1) return SEM(playerid, "You have not selected a vehicle to deploy!");
            new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_LSPD);
            if(id == -1) return SEM(playerid, "You have not selected a vehicle to deploy!");

            if(!IsPlayerNearPoldaGarage(playerid))
                return SEM(playerid, "Anda tidak dekat dengan garasi Polda Pahlawan Roleplay manapun!");

            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return SEM(playerid, "Kendaraan ini bukan milik anda!");
			PlayerVehicle[id][pVehParked] = -1;
            PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehFactStored] = FACTION_NONE;

            new garageid = GetPlayerNearestPoldaGarage(playerid);
            PlayerVehicle[id][pVehPos][0] = Police_Stuff[garageid][policeGarageSpawnPos][0];
            PlayerVehicle[id][pVehPos][1] = Police_Stuff[garageid][policeGarageSpawnPos][1];
            PlayerVehicle[id][pVehPos][2] = Police_Stuff[garageid][policeGarageSpawnPos][2];
            PlayerVehicle[id][pVehPos][3] = Police_Stuff[garageid][policeGarageSpawnPos][3];
            
            OnPlayerVehicleRespawn(id);

            SetTimerEx("ForcePlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_GARAGE_POLDA_BUY:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

            if(!IsPlayerNearPoldaGarage(playerid))
                return SEM(playerid, "Anda tidak dekat dengan garasi Polda Pahlawan Roleplay manapun!");

            new count = 0, garageid = GetPlayerNearestPoldaGarage(playerid);

            foreach(new carid : PvtVehicles)
            {
                if(PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
                    count++;
            }
            if(count >= GetPlayerVehicleLimit(playerid)) return SEM(playerid, "Slot kendaraan anda sudah mencapai batas maksimum!");

            switch(listitem)
            {
                case 0: //HPV1000
                {
                    if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 1500);
                    Vehicle_Create(playerid, 523, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 25, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 1: //Cruiser LSPD
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 596, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 25, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 2: //Police Ranger
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 599, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 25, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 3: //Enforcer
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 427, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 25, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 4: //Sanchez
                {
                    if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 1500);
                    Vehicle_Create(playerid, 468, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 25, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 5: //Sultan
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 560, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 25, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 6: //SWAT
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 601, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 25, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 7: //FBI Rancher
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 490, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 25, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 8: //Kura-Kura
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 528, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 25, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 9: //Bullet
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 541, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 0, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 10: //NRG-500
                {
                    if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 1500);
                    Vehicle_Create(playerid, 522, FACTION_LSPD, Police_Stuff[garageid][policeGarageSpawnPos][0], Police_Stuff[garageid][policeGarageSpawnPos][1], Police_Stuff[garageid][policeGarageSpawnPos][2], Police_Stuff[garageid][policeGarageSpawnPos][3], 25, 0, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
            }
        }
        case DIALOG_GARAGE_POLDA_DELETE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
            if(listitem == -1) return SEM(playerid, "Anda belum memilih kendaraan!");

            new frmtdel[158];
            mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 1 AND `PVeh_Owner` = %d ORDER BY `id` ASC LIMIT 30", AccountData[playerid][pID]);
            mysql_query(g_SQL, frmtdel);
            if(cache_num_rows())
            {
                new hapvid, hapmods, kckstr[225], strgbg[128];

                cache_get_value_name_int(listitem, "id", hapvid);
                cache_get_value_name_int(listitem, "PVeh_ModelID", hapmods);
                
                format(kckstr, sizeof(kckstr), "Anda berhasil menghapus kendaraan:\n\
                Database ID: %d\n\
                Model: %s", hapvid, GetVehicleModelName(hapmods));
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Hapus Kendaraan", kckstr, "Tutup", "");

                new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_LSPD);

                if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                {
                    for(new x; x < 7; x++)
                    {
                        if(DestroyDynamicObject(FactionVehObject[PlayerVehicle[pvid][pVehPhysic]][x]))
                            FactionVehObject[PlayerVehicle[pvid][pVehPhysic]][x] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
                    }

                    DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                    SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                    DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                    PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                }
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", hapvid);
                mysql_pquery(g_SQL, strgbg);
                
                Iter_SafeRemove(PvtVehicles, pvid, pvid);
            }
        }
        case PolisiPanel:
        {
            if(!response) return 1;

            new targetid = NearestSingle[playerid];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return SEM(playerid, "Pemain tersebut tidak dekat dengan anda!");
            if(AccountData[playerid][pKnockdown]) return SEM(playerid, "Karakter anda terluka parah saat ini!");
            switch(listitem)
            {
                case 0: //Periksa Lisensi
                {
                    if(!AccountData[targetid][pSimA] && !AccountData[targetid][pSimB] && !AccountData[targetid][pSimC] && !AccountData[targetid][pFirearmLic] && !AccountData[targetid][pHuntingLic])
                    {
                        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Periksa Lisensi", 
                        "Orang tersebut tidak memiliki lisensi.", "Tutup", "");
                        return 1;
                    }

                    static jhtkm[520];
					format(jhtkm, sizeof(jhtkm), ""WHITE"Pemerintah Kota Pahlawan Roleplay merilis kepemilikan lisensi dari "YELLOW"%s.\n\n\
					"GREEN"- [Lisensi Mengemudi] -\n\
					"WHITE"Surat Izin Mengemudi (SIM) A: %s\n\
					"WHITE"Surat Izin Mengemudi (SIM) B: %s\n\
					"WHITE"Surat Izin Mengemudi (SIM) C: %s\n\n\
					"GREEN"- [Lisensi Lainnya] -\n\
					"WHITE"Carry Concealed Weapon License: %s\n\
					"WHITE"Surat Izin Perburuan: %s",
					GetPlayerRoleplayName(targetid),
					(AccountData[targetid][pSimA]) ? (""DARKGREEN"Dimiliki") : (""RED"Tidak Dimiliki"),
					(AccountData[targetid][pSimB]) ? (""DARKGREEN"Dimiliki") : (""RED"Tidak Dimiliki"),
					(AccountData[targetid][pSimC]) ? (""DARKGREEN"Dimiliki") : (""RED"Tidak Dimiliki"),
					(AccountData[targetid][pFirearmLic]) ? (""DARKGREEN"Dimiliki") : (""RED"Tidak Dimiliki"),
					(AccountData[targetid][pHuntingLic]) ? (""DARKGREEN"Dimiliki") : (""RED"Tidak Dimiliki"));
                    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Periksa Lisensi", 
                    jhtkm, "Tutup", "");

                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 1: //Invoice Belum Terbayar
                {
                    new xjjs[600], count;
                    format(xjjs, sizeof(xjjs), "#\tNama Tagihan\tNominal Tagihan\n");
                    for(new id; id < MAX_INVOICES; ++id)
                    {
                        if(InvoiceData[targetid][id][invoiceExists] && InvoiceData[targetid][id][invoiceOwner] == AccountData[targetid][pID]) 
                        {
                            format(xjjs, sizeof(xjjs), "%s%d\t%s\t%s\n", xjjs, id + 1, InvoiceData[targetid][id][invoiceName], FormatMoney(InvoiceData[targetid][id][invoiceCost]));
                            count++;
                        }
                    }

                    if(count == 0)
                    {
                        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Unpaid Invoice", 
                        "This person has no invoices.", "Tutup", "");
                    }
                    else
                    {
                        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Unpaid Invoice", 
                        xjjs, "Tutup", "");
                    }
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 2: //Kartu Identitas
                {
                    SEM(playerid, "Coming soon!");
                }
                case 3: //Geledah
                {
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);

                    new str[1218], count;
                    format(str, sizeof(str), "Nama Item\tJumlah\n");
                    for(new index; index < MAX_INVENTORY; index++)
                    {
                        if(InventoryData[targetid][index][invExists])
                        {
                            for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[targetid][index][invItem], true))
                            {
                                if (i % 2 == 0) {
                                {
                                    format(str, sizeof(str), "%s%s\t%d\n", str, InventoryData[targetid][index][invItem], InventoryData[targetid][index][invQuantity]);
                                }
                                else {
                                    format(str, sizeof(str), "%s"GRAY"%s\t"GRAY"%d\n", str, InventoryData[targetid][index][invItem], InventoryData[targetid][index][invQuantity]);
                                }
                                PlayerListitem[playerid][count++] = index;
                            }
                        }
                    }

                    if(count == 0)
                    {
                        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Geledah", 
                        "Pemain tersebut tidak memiliki item apapun!", "Tutup", "");
                    }
                    else
                    {
                        Dialog_Show(playerid, DIALOG_POLDA_CONSFICATED, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Geledah", str, "Pilih", "Batal");
                    }
                }
                case 4: //Borgol
                {
                    AccountData[targetid][pCuffed] = true;
	                SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
                    SendClientMessage(targetid, X11_ORANGERED, "[Warning] "WHITE"You've been cuffed!");
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 5: //Buka Borgol
                {
                    AccountData[targetid][pCuffed] = false;
	                SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
                    SendClientMessage(targetid, X11_ORANGERED, "[Warning] "WHITE"You've been uncuffed!");
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 6: //Seret
                {
                    if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
                    {
                        AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
                        if(IsPlayerConnected(AccountData[playerid][DraggingID]))
                        {
                            AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
                        }
                        TogglePlayerControllable(targetid, true);
                        SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah berhenti menggendong seseorang.");
                        return 1;
                    }

                    foreach(new i: Player)
                    {
                        if(AccountData[i][DraggingID] == playerid) return SEM(playerid, "Anda tidak dapat menyeret seseorang yang sedang menyeret orang lain!");
                    }

                    AccountData[playerid][DraggingID] = targetid;
                    AccountData[targetid][pGetDraggedBy] = playerid;
                    TogglePlayerControllable(targetid, false);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"You have successfully carried someone.");
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 7: //Masukkan Mobil
                {
                    new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
                    if(vehid != INVALID_VEHICLE_ID)
                    {
                        if(GetEmptyBackSeat(vehid) == INVALID_SEAT_ID) return SEM(playerid, "Tidak ada kursi kosong di belakang!");
                        PutPlayerInVehicleEx(targetid, vehid, GetEmptyBackSeat(vehid));
                        TogglePlayerControllable(targetid, false);
                        AccountData[targetid][pDetained] = true;
                        SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have successfully detained someone.");
                    }
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 8: //Keluarkan Paksa
                {
                    if(!AccountData[targetid][pDetained]) return SEM(playerid, "Pemain tersebut tidak sedang di-detain!");
                    TogglePlayerControllable(targetid, true);
                    RemovePlayerFromVehicle(targetid);
                    AccountData[targetid][pDetained] = false;
                    SendClientMessage(playerid, X11_PALEGREEN4, "You have successfully ejected someone.");
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 9: //Invoice Manual
                {
                    Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
                    "Mohon masukkan nama dari invoice ini:", "Input", "Batal");
                }
                case 10: //penjarakan
                {
                    Dialog_Show(playerid, DIALOG_POLDA_ARREST, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penjarakan",
                    "Masukkan jumlah menit yang ingin diberikan:", "Input", "Batal");
                }
                case 11: //cek senjata
                {
                    new lstr[555], weaponid, ammo, count;
                    format(lstr, sizeof(lstr), "Slot #ID\tNama\tPeluru\n");
                    for(new i; i < 13; i ++)
                    {
                        GetPlayerWeaponData(targetid, i, weaponid, ammo);

                        if(weaponid > 0)
                        {
                            count++;
                            format(lstr, sizeof(lstr), "%s"RED"%d\t"RED"%s\t"RED"%d\n", lstr, i, ReturnWeaponName(weaponid), ammo);
                        }
                    }
                    if(count > 0)
                    {
                        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Senjata", lstr,"Tutup","");
                    }
                    else
                    {
                        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Senjata", "Pemain tersebut tidak memiliki senjata!","Tutup","");
                    }
                }
                case 12: //cek blacklist
                {
                    static jhtkm[1800];
					format(jhtkm, sizeof(jhtkm), ""WHITE"Blacklist records from "YELLOW"%s.\n\n\
					"WHITE"- [Kepolisian Pahlawan Roleplay] -\n\
                    Status: "CYAN"%s\n\
					"WHITE"Petugas: "GREEN"%s %s\n\
					"WHITE"Alasan: "ORANGE"%s\n\n\
                    "WHITE"- [Paramedis Pahlawan Roleplay] -\n\
                    Status: "CYAN"%s\n\
					"WHITE"Petugas: "GREEN"%s %s\n\
					"WHITE"Alasan: "ORANGE"%s\n\n\
                    "WHITE"- [Dinarbucks] -\n\
                    Status: "CYAN"%s\n\
					"WHITE"Petugas: "GREEN"%s %s\n\
					"WHITE"Alasan: "ORANGE"%s\n\n\
                    "WHITE"- [Pemerintah Pahlawan Roleplay] -\n\
                    Status: "CYAN"%s\n\
					"WHITE"Petugas: "GREEN"%s %s\n\
					"WHITE"Alasan: "ORANGE"%s\n\n\
                    "WHITE"- [Bengkel Bennys] -\n\
                    Status: "CYAN"%s\n\
					"WHITE"Petugas: "GREEN"%s %s\n\
					"WHITE"Alasan: "ORANGE"%s",
					GetPlayerRoleplayName(targetid),
					ReturnTimelapse(gettime(), BlackListInfo[targetid][LSPDDur], ""DARKRED"No"),
                    BlackListInfo[targetid][LSPDIssuerRank],
                    BlackListInfo[targetid][LSPDIssuer],
                    BlackListInfo[targetid][LSPDReason],
                    ReturnTimelapse(gettime(), BlackListInfo[targetid][LSFDDur], ""DARKRED"No"),
                    BlackListInfo[targetid][LSFDIssuerRank],
                    BlackListInfo[targetid][LSFDIssuer],
                    BlackListInfo[targetid][LSFDReason],
                    ReturnTimelapse(gettime(), BlackListInfo[targetid][DINARBUCKSDur], ""DARKRED"No"),
                    BlackListInfo[targetid][DINARBUCKSIssuerRank],
                    BlackListInfo[targetid][DINARBUCKSIssuer],
                    BlackListInfo[targetid][DINARBUCKSReason],
                    ReturnTimelapse(gettime(), BlackListInfo[targetid][PEMERDur], ""DARKRED"No"),
                    BlackListInfo[targetid][PEMERIssuerRank],
                    BlackListInfo[targetid][PEMERIssuer],
                    BlackListInfo[targetid][PEMERReason],
                    ReturnTimelapse(gettime(), BlackListInfo[targetid][BENNYSDur], ""DARKRED"No"),
                    BlackListInfo[targetid][BENNYSIssuerRank],
                    BlackListInfo[targetid][BENNYSIssuer],
                    BlackListInfo[targetid][BENNYSReason]);
                    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Cek Blacklist", 
                    jhtkm, "Tutup", "");

                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
            }
        }
        case DIALOG_POLDA_CONSFICATED:
        {
            if(!response) return 1;
            new targetid = NearestSingle[playerid];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return SEM(playerid, "Pemain tersebut tidak dekat dengan anda!");
            if(AccountData[targetid][pActivityTime] != 0) return SEM(playerid, "Pemain tersebut sedang melakukan sesuatu!");
            if(AccountData[targetid][pMenuShowed]) return SEM(playerid, "Pemain tersebut sedang ingin menyimpan/mengambil sesuatu!");
            
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(InventoryData[targetid][PlayerListitem[playerid][listitem]][invQuantity] * GetItemWeight(InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem]))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            SIM(targetid, "All your %s have been confiscated by %s [%s] (ID: %d).", InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem], AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);
            SIM(targetid, "Someone has confiscated all your %s.", InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem]);
            SIM(playerid, "You have successfully confiscated all %s.", InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem]);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
            SendRPMeAboveHead(playerid, sprintf("Consficated all %s from the person in front.", InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem]), X11_PLUM1);
            
            Inventory_Add(playerid, InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem], InventoryData[targetid][PlayerListitem[playerid][listitem]][invModel], InventoryData[targetid][PlayerListitem[playerid][listitem]][invQuantity]);
            Inventory_Remove(targetid, InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem], InventoryData[targetid][PlayerListitem[playerid][listitem]][invQuantity]);
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case DIALOG_POLDA_ARREST:
        {
            if(!response) return 1;
            
            new targetid = NearestSingle[playerid];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return SEM(playerid, "Pemain tersebut tidak dekat dengan anda!");

            if(isnull(inputtext)) return  Dialog_Show(playerid, DIALOG_POLDA_ARREST, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penjarakan",
            "Error: Tidak dapat dikosongkan!\n\
            Masukkan jumlah menit yang ingin diberikan:", "Input", "Batal");

            if(!IsNumericEx(inputtext)) return  Dialog_Show(playerid, DIALOG_POLDA_ARREST, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penjarakan",
            "Error: Masukkan hanya angka!\n\
            Masukkan jumlah menit yang ingin diberikan:", "Input", "Batal");

            AccountData[targetid][pArrestTime] = strval(inputtext) * 60;
            AccountData[targetid][pArrested] = true;

            PlayerVoiceData[targetid][pHasRadio] = false;
            Inventory_Remove(targetid, "Smartphone", -1);
            ResetPlayerWeaponsEx(targetid);
            SendClientMessageToAllEx(X11_CHOCOLATE, "LSSD: %s has been transported to the county jail, arrested by %s %s for %d month(s).", GetPlayerRoleplayName(targetid), GetRankName(playerid), GetPlayerRoleplayName(playerid), AccountData[targetid][pArrestTime]/60);
            SendPlayerToFederal(targetid);

            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case DIALOG_POLDA_MENU:
        {
            if(!response) return 1;
            
            switch(listitem)
            {
                case 0: //interaksi kendaraan
                {
                    new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
	                if(vehid == INVALID_VEHICLE_ID) return SEM(playerid, "There are no vehicles around!");

                    NearestVehicleID[playerid] = vehid;
                    Dialog_Show(playerid, DIALOG_POLDA_INTERACT_VEH, DIALOG_STYLE_LIST, 
                    "{DA9100}Pahlawan Roleplay "WHITE"- Interaksi Kendaraan", 
                    "Informasi Kendaraan\n\
                    "GRAY"Membobol Kendaraan\n\
                    Menyita Kendaraan ke Insurance\n\
                    "GRAY"Menyita Kendaraan ke Samsat", "Pilih", "Batal");
                }
                case 1: //mengeluarkan objek
                {
                    Dialog_Show(playerid, DIALOG_POLDA_OBJECT, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Object", 
                    "Kerucut\n\
                    "GRAY"Pembatas Jalan\n\
                    Ranjau Kendaraan", "Pilih", "Batal");
                }
                case 2: //list tahanan
                {
                    new hhh[1524], count;
                    format(hhh, sizeof(hhh), "Nama Tahanan\tLama Hukuman\n");
                    foreach(new i : Player) if(i != playerid)
                    {
                        if(AccountData[i][pArrested] && AccountData[i][pArrestTime] > 0)
                        {
                            format(hhh, sizeof(hhh), "%s%s\t%s\n", hhh, GetPlayerRoleplayName(i), GetFormatTime(AccountData[i][pArrestTime]));
                            ListedUser[playerid][count++] = i;
                        }
                    }
                    if(!count) 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- List Tahanan", "Tidak ada tahanan yang sedang dipenjara!", "Tutup", "");
                    }
                    Dialog_Show(playerid, PolisiListPrison, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- List Tahanan", hhh, "Lepas", "Batal");
                }
            }
        }
        case DIALOG_POLDA_INTERACT_VEH:
        {
            if(!response) return 1;
            new vehid = NearestVehicleID[playerid];
            if(!IsValidVehicle(vehid)) return SEM(playerid, "Kendaraan tersebut tidak ada di dalam server!");
            if(!IsPlayerNearVehicle(playerid, vehid, 3.5)) return SEM(playerid, "Kendaraan tersebut tidak dekat dengan anda!");

            switch(listitem)
            {
                case 0: //informasi kendaraan
                {
                    new hjh[512];
                    foreach(new pv : PvtVehicles)
                    {
                        if(IsValidVehicle(PlayerVehicle[pv][pVehPhysic] && PlayerVehicle[pv][pVehPhysic] == vehid))
                        {
                            format(hjh, sizeof(hjh), "Nama Kendaraan: %s\n\
                            Plat Kendaraan: %s\n\
                            Status Kendaraan: %s\n\
                            Nama Pemilik: %s", GetVehicleModelName(PlayerVehicle[pv][pVehModelID]), PlayerVehicle[pv][pVehPlate], (PlayerVehicle[pv][pVehRentTime] != 0) ? ("Rental") : ("Dimiliki"), GetVehicleOwnerName(pv));
                            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Info Kendaraan", 
                            hjh, "Tutup", "");

                            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
                            return 1;
                        }
                    }
                    SEM(playerid, "Kendaraan tersebut bukanlah kendaraan pribadi!");
                }
                case 1: //membobol kendaraaan
                {
                    if(!VehicleCore[vehid][vCoreLocked]) return SEM(playerid, "Kendaraan tersebut tidak sedang dikunci!");

                    ApplyAnimation(playerid, "AIRPORT", "thrw_barl_thrw", 2.00, 1, 0, 0, 0, 0, 1);

                    AccountData[playerid][pActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "LOADING");
                    ShowProgressBar(playerid);

                    AccountData[playerid][pTempVehID] = vehid;

                    pBreakingVehDoorTimer[playerid] = true;
                }
                case 2: //menyita ke asuransi
                {
                    foreach(new pv : PvtVehicles)
                    {
                        if(IsValidVehicle(PlayerVehicle[pv][pVehPhysic] && PlayerVehicle[pv][pVehPhysic] == vehid))
                        {
                            ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 2.33, 1, 0, 0, 0, 0, 1);

                            AccountData[playerid][pActivityTime] = 1;
                            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "IMPOUNDING");
                            ShowProgressBar(playerid);

                            AccountData[playerid][pTempVehIterID] = pv;
                            pImpoundingInsuTimer[playerid] = true;
                            return 1;
                        }
                    }
                    SEM(playerid, "Kendaraan tersebut bukanlah kendaraan pribadi!");
                }
                case 3: //menyita ke samsat
                {
                    foreach(new pv : PvtVehicles)
                    {
                        if(IsValidVehicle(PlayerVehicle[pv][pVehPhysic] && PlayerVehicle[pv][pVehPhysic] == vehid))
                        {
                            Dialog_Show(playerid, DIALOG_POLDA_IMPOUND, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
                            "Harap masukkan sesuai format yang ada di bawah ini!\n\
                            [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");
                            return 1;
                        }
                    }
                    SEM(playerid, "Kendaraan tersebut bukanlah kendaraan pribadi!");
                }
            }
        }
        case DIALOG_POLDA_IMPOUND:
        {
            if(!response) return 1;
            new vehid = NearestVehicleID[playerid];
            if(!IsValidVehicle(vehid)) return SEM(playerid, "Kendaraan tersebut tidak ada di dalam server!");
            if(!IsPlayerNearVehicle(playerid, vehid, 3.5)) return SEM(playerid, "Kendaraan tersebut tidak dekat dengan anda!");
            
            if(isnull(inputtext)) return Dialog_Show(playerid, DIALOG_POLDA_IMPOUND, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
            "Error: Tidak dapat dikosongkan!\n\
            Harap masukkan sesuai format yang ada di bawah ini!\n\
            [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");
            
            new durasi, duration, denda, reason[128];
            if(sscanf(inputtext, "dds[128]", duration, denda, reason))
            {
                return Dialog_Show(playerid, DIALOG_POLDA_IMPOUND, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
                "Error: Format salah!\n\
                Harap masukkan sesuai format yang ada di bawah ini!\n\
                [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");
            }

            if(duration < 1 || duration > 3) return Dialog_Show(playerid, DIALOG_POLDA_IMPOUND, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
            "Error: Durasi sita harus 1 - 3 hari saja!\n\
            Harap masukkan sesuai format yang ada di bawah ini!\n\
            [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");

            if(denda < 1) return Dialog_Show(playerid, DIALOG_POLDA_IMPOUND, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
            "Error: Denda tidak dapat kurang dari $1!\n\
            Harap masukkan sesuai format yang ada di bawah ini!\n\
            [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");

            foreach(new pv : PvtVehicles)
            {
                if(PlayerVehicle[pv][pVehExists])
                {
                    if(IsValidVehicle(PlayerVehicle[pv][pVehPhysic] && PlayerVehicle[pv][pVehPhysic] == vehid))
                    {
                        ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 2.33, 1, 0, 0, 0, 0, 1);

                        AccountData[playerid][pActivityTime] = 1;
                        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "IMPOUNDING");
                        ShowProgressBar(playerid);

                        durasi = gettime() + (duration * 86400);
                        strcopy(PlayerVehicle[pv][pVehImpoundReason], reason);

                        pImpoundingSamsatTimer[playerid] = SetTimerEx("ImpoundingSamsat", 1000, true, "iidd", playerid, pv, durasi, denda);
                        return 1;
                    }
                }
            }
            SEM(playerid, "Kendaraan tersebut bukanlah kendaraan pribadi!");
        }
        case DIALOG_POLDA_OBJECT:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0: //kerucut
                {
                    if(IsValidDynamicObject(AccountData[playerid][PoliceConeObjid]))
                    {
                        DestroyDynamicObject(AccountData[playerid][PoliceConeObjid]);
                        AccountData[playerid][PoliceConeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                        SendRPMeAboveHead(playerid, "Removed their cone.", X11_PLUM1);
                        return 1;
                    }

                    if(DestroyDynamicObject(AccountData[playerid][PoliceConeObjid]))
                        AccountData[playerid][PoliceConeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                    new Float:X, Float:Y, Float:Z, Float:Ang;
                    GetPlayerPos(playerid, X, Y, Z);
                    Ang = GetXYInFrontOfPlayer(playerid, X, Y, 5.0);
                    AccountData[playerid][PoliceConeObjid] = CreateDynamicObject(1238, X, Y, Z-0.9, 0.0, 0.0, Ang, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 300.0);

                    SendRPMeAboveHead(playerid, "Put down their cone.", X11_PLUM1);
                }
                case 1: //pembatas jalan
                {
                    if(IsValidDynamicObject(AccountData[playerid][PoliceRoadblockObjid]))
                    {
                        DestroyDynamicObject(AccountData[playerid][PoliceRoadblockObjid]);
                        AccountData[playerid][PoliceRoadblockObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                        SendRPMeAboveHead(playerid, "Removed their road block.", X11_PLUM1);
                        return 1;
                    }

                    if(DestroyDynamicObject(AccountData[playerid][PoliceRoadblockObjid]))
                        AccountData[playerid][PoliceRoadblockObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                    new Float:X, Float:Y, Float:Z, Float:Ang;
                    GetPlayerPos(playerid, X, Y, Z);
                    Ang = GetXYInFrontOfPlayer(playerid, X, Y, 5.0);
                    AccountData[playerid][PoliceRoadblockObjid] = CreateDynamicObject(1422, X, Y, Z-0.9, 0.0, 0.0, Ang, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 300.0);

                    SendRPMeAboveHead(playerid, "Put down their road block.", X11_PLUM1);
                }
                case 2: //ranjau kendaraan
                {
                    if(IsValidDynamicObject(AccountData[playerid][PoliceSpikeObjid]) || IsValidDynamicArea(AccountData[playerid][PoliceSpikeArea]))
                    {
                        DestroyDynamicObject(AccountData[playerid][PoliceSpikeObjid]);
                        AccountData[playerid][PoliceSpikeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                        DestroyDynamicArea(AccountData[playerid][PoliceSpikeArea]);
                        AccountData[playerid][PoliceSpikeArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

                        SendRPMeAboveHead(playerid, "Removed their spike.", X11_PLUM1);
                        return 1;
                    }

                    if(DestroyDynamicObject(AccountData[playerid][PoliceSpikeObjid]))
                        AccountData[playerid][PoliceSpikeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                    
                    if(DestroyDynamicArea(AccountData[playerid][PoliceSpikeArea]))
                        AccountData[playerid][PoliceSpikeArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

                    new Float:X, Float:Y, Float:Z, Float:Ang;
                    GetPlayerPos(playerid, X, Y, Z);
                    Ang = GetXYInFrontOfPlayer(playerid, X, Y, 5.0);
                    AccountData[playerid][PoliceSpikeObjid] = CreateDynamicObject(2892, X, Y, Z-1, 0.0, 0.0, Ang, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 300.0);
                    AccountData[playerid][PoliceSpikeArea] = CreateDynamicRectangle(X-2, Y-6, X+2, Y+6);

                    SendRPMeAboveHead(playerid, "Put down their spike.", X11_PLUM1);
                }
            }
        }
        case PolisiListPrison:
        {
            if(!response) return 1;
            
            Temptargetid[playerid] = ListedUser[playerid][listitem];
            Dialog_Show(playerid, PolisiPrisonFree, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- List Tahanan", 
            sprintf("Apakah anda yakin ingin membebaskan %s?", GetPlayerRoleplayName(Temptargetid[playerid])), "Ya", "No");
        }
        case PolisiPrisonFree:
        {
            if(!response) return 1;
            if(!IsPlayerConnected(Temptargetid[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

            AccountData[Temptargetid[playerid]][pArrested] = false;
			AccountData[Temptargetid[playerid]][pArrestTime] = 0;

            SetPlayerInteriorEx(Temptargetid[playerid], 0);
            SetPlayerVirtualWorldEx(Temptargetid[playerid], 0);

            SetPlayerPositionEx(Temptargetid[playerid], 143.7855,1945.5334,19.3505,356.1586);
            StopRunningAnimation(Temptargetid[playerid]);

            SendClientMessageToAllEx(X11_CHOCOLATE, "SACF Press Release: %s has been released from the prison by %s %s.", GetPlayerRoleplayName(Temptargetid[playerid]), GetRankName(playerid), GetPlayerRoleplayName(playerid));
        }
        case PolisiImpoundSearch:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
            "Error: Tidak dapat dikosongkan!\n\
            Mohon masukkan player id/nomor kantong pemain tersebut:", "Pilih", "Batal");
            if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
            "Error: Masukkan hanya angka!\n\
            Mohon masukkan player id/nomor kantong pemain tersebut:", "Pilih", "Batal");
            
            new mstr[128], hjstr[512], modelid, impduration, impfee;
            AccountData[playerid][pTempSQLImpoundID] = strval(inputtext);
            if(!IsPlayerConnected(AccountData[playerid][pTempSQLImpoundID])) return Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
            "Error: The player is not connected to the server!\n\
            Mohon masukkan player id/nomor kantong pemain tersebut:", "Pilih", "Batal");
            if(!IsPlayerNearPlayer(playerid, AccountData[playerid][pTempSQLImpoundID], 3.5)) return Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
            "Error: Pemain tersebut tidak dekat dengan anda!\n\
            Mohon masukkan player id/nomor kantong pemain tersebut:", "Pilih", "Batal");

            mysql_format(g_SQL, mstr, sizeof(mstr), "SELECT * FROM `player_vehicles` WHERE `PVeh_Impounded`=1 AND `PVeh_Owner`=%d", AccountData[AccountData[playerid][pTempSQLImpoundID]][pID]);
            mysql_query(g_SQL, mstr);
            if(cache_num_rows())
            {
                format(hjstr, sizeof(hjstr), "Model\tDurasi\tTagihan\n");
                for(new x; x < cache_num_rows(); x++)
                {
                    cache_get_value_name_int(x, "PVeh_ModelID", modelid);
                    cache_get_value_name_int(x, "PVeh_ImpoundDuration", impduration);
                    cache_get_value_name_int(x, "PVeh_ImpoundFee", impfee);

                    format(hjstr, sizeof(hjstr), "%s%s\t%s\t$%s\n", hjstr, GetVehicleModelName(modelid), ReturnTimelapse(gettime(), impduration, "Sudah Waktunya"), FormatMoney(impfee));
                }
                Dialog_Show(playerid, "PolisiImpoundSelect", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Impounded List", 
                hjstr, "Pilih", "Batal");
            }
            else
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Impounded List", "Tidak ada kendaraan impound dari pemain tersebut!", 
                "Tutup", "");
            }
        }
        case PolisiImpoundSelect:
        {
            if(!response) return 1;
            if(listitem == -1) return SEM(playerid, "Anda belum memilih kendaraan!");

            new mstr[128];
            mysql_format(g_SQL, mstr, sizeof(mstr), "SELECT * FROM `player_vehicles` WHERE `PVeh_Impounded`=1 AND `PVeh_Owner`=%d", AccountData[AccountData[playerid][pTempSQLImpoundID]][pID]);
            mysql_query(g_SQL, mstr);
            new modelid, impduration, impfee, impreason[128], jjj[512];
            if(cache_num_rows())
            {
                cache_get_value_name_int(listitem, "id", AccountData[playerid][pTempSQLImpoundVID]);
                cache_get_value_name_int(listitem, "PVeh_ModelID", modelid);
                cache_get_value_name_int(listitem, "PVeh_ImpoundDuration", impduration);
                cache_get_value_name_int(listitem, "PVeh_ImpoundFee", impfee);
                cache_get_value_name(listitem, "PVeh_ImpoundReason", impreason);

                format(jjj, sizeof(jjj), "Detail Impound SAMSAT:\n\
                Model: %s\n\
                Durasi: %s\n\
                Tagihan: $%s\n\
                Alasan: %s", GetVehicleModelName(modelid), ReturnTimelapse(gettime(), impduration, "Sudah Waktunya"), FormatMoney(impfee), impreason);
                Dialog_Show(playerid, PolisiImpoundConfirm, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Impounded List", 
                jjj, "Lepas", "Batal");
            }
        }
        case PolisiImpoundConfirm:
        {
            if(!response) return 1;
            foreach(new vid : PvtVehicles)
            {
                if(PlayerVehicle[vid][pVehExists] && PlayerVehicle[vid][pVehID] == AccountData[playerid][pTempSQLImpoundVID] && PlayerVehicle[vid][pVehImpounded] && PlayerVehicle[vid][pVehOwnerID] == AccountData[AccountData[playerid][pTempSQLImpoundID]][pID])
                {
                    if(gettime() < PlayerVehicle[vid][pVehImpoundDuration]) return SEM(playerid, "Belum saatnya melepaskan kendaraan tersebut!");
                    
                    PlayerVehicle[vid][pVehImpounded] = false;
                    PlayerVehicle[vid][pVehImpoundDuration] = 0;
                    PlayerVehicle[vid][pVehImpoundFee] = 0;
                    PlayerVehicle[vid][pVehImpoundReason][0] = EOS;
                    
                    PlayerVehicle[vid][pVehPos][0] = -2030.5951;
                    PlayerVehicle[vid][pVehPos][1] = -138.3298;
                    PlayerVehicle[vid][pVehPos][2] = 35.4300;
                    PlayerVehicle[vid][pVehPos][3] = 89.9642;
                    
                    OnPlayerVehicleRespawn(vid);
                }
            }
            new impstr[250];
            mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Impounded` = 0, `PVeh_ImpoundDuration`=0, `PVeh_ImpoundFee`=0, `PVeh_ImpoundReason`='' WHERE `id`=%d", AccountData[playerid][pTempSQLImpoundVID]);
            mysql_pquery(g_SQL, impstr);
        }
        case DIALOG_TEST_C1:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_C2, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM C", 
            "Mana yang bukan fungsi klakson?\n\
            A. Meminta kendaraan di depan untuk segera menyingkir.\n\
            "GRAY"B. Memberi tanda isyarat bahwa kita sedang melintas.\n\
            C. Sebagai alat untuk memarahi orang lain.\n\
            "GRAY"D. Sebagai alat atau sinyal darurat.", "Pilih", "Batal");
        }
        case DIALOG_TEST_C2:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_C3, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM C", 
            "Apa fungsi lampu tangan pada kendaraan?\n\
            A. Sebagai pemberi sinyal arah kemana kita akan berbelok.\n\
            "GRAY"B. Sebagai alat untuk berjabat tangan dengan kendaraan di sebelah.\n\
            C. Supaya kendaraan terlihat terang dan keren.\n\
            "GRAY"D. Sebagai hiasan bagi kecantikan kendaraan.", "Pilih", "Batal");
        }

        case DIALOG_TEST_C3:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 0) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_C4, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM C", 
            "Mana yang bukan termasuk SIM kendaraan roda 4?\n\
            A. SIM A.\n\
            "GRAY"B. SIM B.\n\
            C. SIM B1.\n\
            "GRAY"D. SIM C.", "Pilih", "Batal");
        }

        case DIALOG_TEST_C4:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_C5, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM C", 
            "Apa bahaya dari pengereman mendadak saat jalanan licin, kecuali?\n\
            A. Kendaraan akan tergelincir.\n\
            "GRAY"B. Membahayakan pengendara lain.\n\
            C. Kehilangan kendali.\n\
            "GRAY"D. Tidak berakibat apa-apa karena pengemudi mahir.", "Pilih", "Batal");
        }

        case DIALOG_TEST_C5:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_C6, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM C", 
            "Mana yang tidak termasuk syarat administratif untuk mendapatkan SIM adalah?\n\
            A. KTP.\n\
            "GRAY"B. Pengisian formulir permohonan.\n\
            C. Kartu keluarga.\n\
            "GRAY"D. Rumusan sidik jari.", "Pilih", "Batal");
        }

        case DIALOG_TEST_C6:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_C7, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM C", 
            "Penggunaan jalan selain jalur sebelah kiri hanya dapat dilakukan apabila?\n\
            A. Pengemudi bermaksud akan melewati kendaraan didepannya.\n\
            "GRAY"B. Ditunjuk atau ditetapkan oleh petugas yang berwenang.\n\
            C. Pilihan A dan B benar semua.\n\
            "GRAY"D. Butir A dan B salah semua.", "Pilih", "Batal");
        }

        case DIALOG_TEST_C7:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_C8, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM C", 
            "Apa kepanjangan dari STNK?\n\
            A. Surat Tanda Nomor Kendaraan.\n\
            "GRAY"B. Surat Tanda Nomor Keluarga.\n\
            C. Surat Tanda Nikah Kelurahan.\n\
            "GRAY"D. Surat Tanda Nomor Kantong.", "Pilih", "Batal");
        }

        case DIALOG_TEST_C8:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 0) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_C9, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM C", 
            "Golongan SIM untuk mengendarai motor 250 cc?\n\
            A. Golongan SIM C.\n\
            "GRAY"B. Golongan SIM C I.\n\
            C. Golongan SIM C II.\n\
            "GRAY"D. Golongan SIM C I dan C II benar.", "Pilih", "Batal");
        }

        case DIALOG_TEST_C9:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_C10, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM C", 
            "Fungsi dari lampu hazard adalah?\n\
            A. Menunjukkan bahwa kita akan berjalan lurus depan di suatu persimpangan.\n\
            "GRAY"B. Untuk tanda bahwa kendaraan kita sedang mundur.\n\
            C. Untuk memberi tanda bahwa kita sedang dalam keadaan darurat.\n\
            "GRAY"D. Untuk memberi tanda pada saat kendaraan akan berbelok.", "Pilih", "Batal");
        }

        case DIALOG_TEST_C10:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            SetPlayerVirtualWorldEx(playerid, 0);
            SetPlayerInteriorEx(playerid, 0);

            AccountData[playerid][pRouteSIM] = 0;
            SetPlayerCheckpoint(playerid, -2016.2024,-238.5945,34.9203, 1.5);
            DMVVehicle[playerid] = CreateVehicle(462, -2015.9913,-178.3730,34.9198,180.0578, 1, 1, 60000, false);
            VehicleCore[DMVVehicle[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(DMVVehicle[playerid], 1000.0); 
            VehicleCore[DMVVehicle[playerid]][vCoreLocked] = false;
            SetVehicleNumberPlate(DMVVehicle[playerid], ""BLUE"SIM");
            PutPlayerInVehicleEx(playerid, DMVVehicle[playerid], 0);
            SwitchVehicleEngine(DMVVehicle[playerid], true);
            SwitchVehicleDoors(DMVVehicle[playerid], false);

            Streamer_Update(playerid, -1);

            SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil lolos tahap uji teori, selesaikan uji praktek untuk mendapatkan SIM.");
        }

        case DIALOG_TEST_A1:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_A2, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM A", 
            "Kompetensi mengemudi dapat diperoleh dengan cara?\n\
            A. Pendidikan dan pelatihan mengemudi.\n\
            "GRAY"B. Percobaan mengemudi.\n\
            C. Belajar sendiri.\n\
            "GRAY"D. Pilihan A dan C benar.", "Pilih", "Batal");
        }

        case DIALOG_TEST_A2:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_A3, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM A", 
            "Dalam keadaan tertentu, polisi dapat melakukan tindakan:\n\
            A. Memberhentikan arus lalu lintas.\n\
            "GRAY"B. Memerintahkan pemakai jalan untuk jalan terus & mempercepat arus.\n\
            C. Memperlambat arus & mengubah arah arus.\n\
            "GRAY"D. Semuanya benar.", "Pilih", "Batal");
        }

        case DIALOG_TEST_A3:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_A4, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM A", 
            "Golongan rambu lalu lintas terdiri dari:\n\
            A. 2 golongan, rambu perintah & rambu larangan.\n\
            "GRAY"B. 3 golongan, rambu peringatan, larangan & perintah.\n\
            C. 3 golongan, rambu peringatan, larangan & petunjuk.\n\
            "GRAY"D. 4 golongan, rambu peringatan, larangan, perintah & petunjuk.", "Pilih", "Batal");
        }

        case DIALOG_TEST_A4:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_A5, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM A", 
            "Alat pengukur kecepatan kendaraan, secara umum menunjukkan:\n\
            A. Kecepatan rata-rata kendaraan kita.\n\
            "GRAY"B. Kecepatan maksimal kendaraan kita.\n\
            C. Kecepatan aktual kendaraan kita pada saat melihat alat tersebut.\n\
            "GRAY"D. Kecepatan yang diwajibkan sesuai kelas jalan yang dilalui.", "Pilih", "Batal");
        }

        case DIALOG_TEST_A5:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_A6, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM A", 
            "Apakah fungsi dari tuas transmisi?\n\
            A. Menambah kecepatan.\n\
            "GRAY"B. Memperlambat kecepatan.\n\
            C. Memindahkan gigi transmisi.\n\
            "GRAY"D. Memberi isyarat kendaraan saat akan berbelok.", "Pilih", "Batal");
        }

        case DIALOG_TEST_A6:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_A7, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM A", 
            "Di antara SIM berikut yang syarat usia minimumnya 20 tahun adalah:\n\
            A. SIM B1.\n\
            "GRAY"B. SIM A.\n\
            C. SIM C.\n\
            "GRAY"D. SIM D.", "Pilih", "Batal");
        }

        case DIALOG_TEST_A7:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 0) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_A8, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM A", 
            "Manakah syarat yang harus dipenuhi untuk mendapatkan SIM?\n\
            A. Usia.\n\
            "GRAY"B. Lulus tes teori dan praktek.\n\
            C. Persyaratan kesehatan.\n\
            "GRAY"D. Semuanya benar.", "Pilih", "Batal");
        }

        case DIALOG_TEST_A8:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_A9, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM A", 
            "Untuk mendepatkan SIM, calon pengemudi harus?\n\
            A. Memiliki kompetensi mengemudi.\n\
            "GRAY"B. Memiliki kendaraan bermotor.\n\
            C. Memiliki kompetensi permesinan.\n\
            "GRAY"D. Mengetahui jalan di lingkungannya.", "Pilih", "Batal");
        }

        case DIALOG_TEST_A9:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 0) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            Dialog_Show(playerid, DIALOG_TEST_A10, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ujian Teori SIM A", 
            "Berapa batas maksimal seseorang untuk mengikuti tes mendapatkan SIM?\n\
            A. 3 kali.\n\
            "GRAY"B. 1 kali.\n\
            C. 5 kali.\n\
            "GRAY"D. Tidak ada batasan yang penting memenuhi syarat.", "Pilih", "Batal");
        }

        case DIALOG_TEST_A10:
        {
            if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah membatalkan ujian teori SIM.");

            if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

            SetPlayerVirtualWorldEx(playerid, 0);
            SetPlayerInteriorEx(playerid, 0);

            AccountData[playerid][pRouteSIM] = 0;
            SetPlayerCheckpoint(playerid, -2044.7181,-84.6308,34.9431, 3.0);
            DMVVehicle[playerid] = CreateVehicle(401,-2087.2808,-272.9340,35.0997,359.0763, 1, 1, 60000, false);
            VehicleCore[DMVVehicle[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(DMVVehicle[playerid], 1000.0); 
            VehicleCore[DMVVehicle[playerid]][vCoreLocked] = false;
            SetVehicleNumberPlate(DMVVehicle[playerid], ""BLUE"SIM");
            PutPlayerInVehicleEx(playerid, DMVVehicle[playerid], 0);
            SwitchVehicleEngine(DMVVehicle[playerid], true);
            SwitchVehicleDoors(DMVVehicle[playerid], false);

            Streamer_Update(playerid, -1);

            SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil lolos tahap uji teori, selesaikan uji praktek untuk mendapatkan SIM.");
        }
    }
    return 0;
}

ptask CheckingTestingSIM[1000](playerid) 
{
    if(AccountData[playerid][pRouteSIM] >= 1)
    {
        if(IsValidVehicle(DMVVehicle[playerid]))
        {
            if(IsPlayerInVehicle(playerid, DMVVehicle[playerid]))
            {
                if(AccountData[playerid][pSIMTimer] > 0) 
                {
                    AccountData[playerid][pSIMTimer]--;
                    GameTextForPlayer(playerid, sprintf("%d", AccountData[playerid][pSIMTimer]), 1000, 4);
                }
                else
                {
                    AccountData[playerid][pSIMTimer] = 0;
                    AccountData[playerid][pRouteSIM] = -1;
                    DisablePlayerCheckpoint(playerid);
                    DestroyVehicle(DMVVehicle[playerid]);
                    DMVVehicle[playerid] = INVALID_VEHICLE_ID;

                    SendClientMessage(playerid, -1, "[Praktek] Anda gagal tes praktek mengemudi karena kehabisan waktu!");
                    return 1;
                }

                static Float:vphealth;
                GetVehicleHealth(DMVVehicle[playerid], vphealth);
                if(vphealth != 1000.0)
                {
                    AccountData[playerid][pSIMTimer] = 0;
                    AccountData[playerid][pRouteSIM] = -1;
                    DisablePlayerCheckpoint(playerid);
                    DestroyVehicle(DMVVehicle[playerid]);
                    DMVVehicle[playerid] = INVALID_VEHICLE_ID;

                    SendClientMessage(playerid, -1, "[Praktek] Anda gagal tes praktek mengemudi karena kendaraan terkena damage!");
                    return 1;
                }

                if(!IsVehicleMoving(DMVVehicle[playerid]))
                {
                    AccountData[playerid][pSIMTimer] = 0;
                    AccountData[playerid][pRouteSIM] = -1;
                    DisablePlayerCheckpoint(playerid);
                    DestroyVehicle(DMVVehicle[playerid]);
                    DMVVehicle[playerid] = INVALID_VEHICLE_ID;

                    SendClientMessage(playerid, -1, "[Praktek] Anda gagal tes praktek mengemudi karena berhenti!");
                    return 1;
                }
            }
        }
    }
    return 1;
}

DialogPages:PoldaSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 19) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses Bos Desk!");
    if(listitem == -1) return SEM(playerid, "Anda belum memilih anggota!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 1 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return SEM(playerid, "Anda tidak dapat menetapkan rank anda sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return SEM(playerid, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
        Dialog_Show(playerid, DIALOG_RANK_SET_POLDA, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. Tamtama - BHARADA\n\
        2. Tamtama - BHARATU\n\
        3. Tamtama - BHARAKA\n\
        4. Tammtama - ABRIPDA\n\
        5. Tamtama - ABRIPTU\n\
        6. Tamtama - ABRIGPOL\n\
        7. Bintara - BRIPDA\n\
        8. Bintara - BRIPTU\n\
        9. Bintara - BRIGPOL\n\
        10. Bintara - BRIPKA\n\
        11. Bintara - AIPDA\n\
        12. Bintara - AIPTU\n\
        13. Perwira - IPDA\n\
        14. Perwira - IPTU\n\
        15. Perwira - AKP\n\
        16. Perwira - KOMPOL\n\
        17. Perwira - AKBP\n\
        18. Perwira - KOMBESPOL\n\
        19. Perwira - BRIGJEN\n\
        20. Perwira - IRJEN\n\
        21. Perwira - KOMJEN\n\
        22. JENDERAL", "Set", "Batal");
    }
    return 1;
}

DialogPages:PoldaSetSat(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 19) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses Bos Desk!");
    if(listitem == -1) return SEM(playerid, "Anda belum memilih anggota!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 1 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return SEM(playerid, "Anda tidak dapat menetapkan rank anda sendiri!");
        Dialog_Show(playerid, DIALOG_SAT_SET_POLDA, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kelola Satuan", 
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. SATLANTAS\n\
        2. SABHARA\n\
        3. BRIMOB", "Set", "Batal");
    }
    return 1;
}

DialogPages:PoldaKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 19) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses Bos Desk!");
    if(listitem == -1) return SEM(playerid, "Anda belum memilih anggota!");

    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 1 ORDER BY Char_FactionRank DESC");
    if(cache_num_rows())
    {
        new pidrow, fckname[64], fckrank, fcklastlogin[30], kckstr[225], icsr[128];

        cache_get_value_name_int(listitem, "pID", pidrow);
        cache_get_value_name(listitem, "Char_Name", fckname);
        cache_get_value_name_int(listitem, "Char_FactionRank", fckrank);
        cache_get_value_name(listitem, "Char_LastLogin", fcklastlogin);

        if(AccountData[playerid][pID] == pidrow) return SEM(playerid, "Anda tidak dapat kick diri sendiri!");
        if(fckrank >= AccountData[playerid][pFactionRank]) return SEM(playerid, "Anda tidak dapat kick pangkat yang lebih tinggi atau setara!");
        
        /* kendaraan pribadi yang milik faction dicek */
        new strgbg[158];
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_Owner` = %d AND `PVeh_Faction` = 1", pidrow);
        mysql_pquery(g_SQL, strgbg);

        foreach(new i : Player)
        {
            if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && pidrow == AccountData[i][pID])
            {
                AccountData[i][pFaction] = 0;
                AccountData[i][pFactionRank] = 0;

                RefreshFactionMap(i);

                //jika kendaraan pribadi ada di server dan player sedang online, maka kendaraan fisik dihapus
                foreach(new pvid : PvtVehicles)
                {
                    if(PlayerVehicle[pvid][pVehExists] && PlayerVehicle[pvid][pVehOwnerID] == AccountData[i][pID])
                    {
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_LSPD)
                        {
                            PlayerVehicle[pvid][pVehExists] = false;
                            if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                            {
                                for(new x; x < 7; x++)
                                {
                                    if(DestroyDynamicObject(FactionVehObject[PlayerVehicle[pvid][pVehPhysic]][x]))
                                        FactionVehObject[PlayerVehicle[pvid][pVehPhysic]][x] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
                                }

                                DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                                SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                                DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                                PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                            }
                            Iter_SafeRemove(PvtVehicles, pvid, pvid);
                        }
                    }
                }
                if(Iter_Contains(LSPDDuty, i))
		            Iter_Remove(LSPDDuty, i);

                if(Iter_Contains(SatlantasDuty, i))
                    Iter_Remove(SatlantasDuty, i);

                if(Iter_Contains(SabharaDuty, i))
                    Iter_Remove(SabharaDuty, i);

                if(Iter_Contains(BrimobDuty, i))
                    Iter_Remove(BrimobDuty, i);

                SendClientMessage(i, X11_ORANGERED, "[Warning] "WHITE"You have been removed from Polda Pahlawan Roleplay!");
            }
        }
        InsertFactionLog("Kick", sprintf("%s %s - %s", AccountData[playerid][pName], AccountData[playerid][pUCP], fckname), "Polda");

        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 0, `Char_FactionRank` = 0 WHERE `pID` = %d", pidrow);
        mysql_pquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
        Name: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, CopRank[fckrank], fcklastlogin);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", 
        kckstr, "Tutup", "");
    }
    return 1;
}