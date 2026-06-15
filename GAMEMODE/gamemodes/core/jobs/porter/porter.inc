#include <YSI_Coding\y_hooks>

GetPorterDropIDX(playerid)
{
    for(new d; d < sizeof(PorterDropCoord); d++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, PorterDropCoord[d][0], PorterDropCoord[d][1], PorterDropCoord[d][2]))
        {
            return d;
        }
    }
    return -1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_PORTER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(areaid == Porter_StartArea)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~Angkut Barang");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == Porter_StartArea)
    {
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        HideNotifBox(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 2386.5820,563.6393,10.3691))
        {
            if(AccountData[playerid][pJob] != JOB_PORTER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Porter!");

            ShowLockerTD(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Porter_StartArea))
        {
            if(AccountData[playerid][pJob] != JOB_PORTER) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            if(pPorterCarrying[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang mengangkut barang, antarkan ke tempatnya!");

            pPorterCarrying[playerid] = true;
            pPorterDropIDX[playerid] = random(7);
            SetPlayerAttachedObject(playerid, 9, 1271, 1, 0.286000, 0.625999, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

            switch(pPorterDropIDX[playerid])
            {
                case 0:
                {
                    ShowPlayerFooter(playerid, "Letakkan barang ke ~r~B3A1C2", 5555);
                }
                case 1:
                {
                    ShowPlayerFooter(playerid, "Letakkan barang ke ~r~B2A3C1", 5555);
                }
                case 2:
                {
                    ShowPlayerFooter(playerid, "Letakkan barang ke ~r~B1A2C3", 5555);
                }
                case 3:
                {
                    ShowPlayerFooter(playerid, "Letakkan barang ke ~r~A2B1C3", 5555);
                }
                case 4:
                {
                    ShowPlayerFooter(playerid, "Letakkan barang ke ~r~A1B3C2", 5555);
                }
                case 5:
                {
                    ShowPlayerFooter(playerid, "Letakkan barang ke ~r~C1A3B2", 5555);
                }
                case 6:
                {
                    ShowPlayerFooter(playerid, "Letakkan barang ke ~r~C2A1B1", 5555);
                }
            }
            HideNotifBox(playerid);
        }

        if(GetPorterDropIDX(playerid) != -1)
        {
            if(AccountData[playerid][pJob] != JOB_PORTER) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            if(!pPorterCarrying[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang mengangkut barang apapun!");
            if(pPorterDropIDX[playerid] != GetPorterDropIDX(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tempat ini tidak sesuai dengan barang ini!");
            
            new ranweight = RandomEx(1, 20);
            new salary = 22*ranweight;
            
            GivePlayerMoneyEx(playerid, salary);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda mendapatkan ~g~$%s ~l~dari barang seberat ~r~%d kg", FormatMoney(salary), ranweight));
            ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(salary)), 1212, 5);

            ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            RemovePlayerAttachedObject(playerid, 9);

            pPorterDropIDX[playerid] = -1;
            pPorterCarrying[playerid] = false;
            
            HideNotifBox(playerid);
        }
    }
    return 1;
}