ptask PlayerJailCheck[1000](playerid)
{
    if(OJailData[playerid][jailed] && !AccountData[playerid][pIsAFK])
	{
		if(OJailData[playerid][jailTime] > 0)
		{
			OJailData[playerid][jailTime]--;
			new mstr[128];
			format(mstr, sizeof(mstr), "~w~%d", OJailData[playerid][jailTime]);
			GameTextForPlayer(playerid, mstr, 2000, 4);
		}
		else
		{
			OJailData[playerid][jailed] = false;
			OJailData[playerid][jailCell] = -1;
			OJailData[playerid][jailAdmin][0] = EOS;
			OJailData[playerid][jailTime] = 0;
			OJailData[playerid][jailDur] = 0;
			OJailData[playerid][jailReason][0] = EOS;
			OJailData[playerid][jailFine] = 0;

            SetPlayerInteriorEx(playerid, 0);
            SetPlayerVirtualWorldEx(playerid, 0);

            SetPlayerPositionEx(playerid, 1479.7563,-1709.2994,14.0469,178.8976);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		}
	}
	return 1;
}

ptask PlayerFederalCheck[1000](playerid)
{
    if(AccountData[playerid][pArrested] && !AccountData[playerid][pIsAFK])
	{
		if(AccountData[playerid][pArrestTime] > 0)
		{
			AccountData[playerid][pArrestTime]--;
			new mstr[128];
			format(mstr, sizeof(mstr), "~w~%d", AccountData[playerid][pArrestTime]);
			GameTextForPlayer(playerid, mstr, 2000, 4);

			if(!IsPlayerInRangeOfPoint(playerid, 500.00, 227.4145,110.6261,999.0162) && (GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 10))
			{
				SendPlayerToFederal(playerid);
			}
		}
		else
		{
			AccountData[playerid][pArrested] = false;
			AccountData[playerid][pArrestTime] = 0;

            SetPlayerInteriorEx(playerid, 0);
            SetPlayerVirtualWorldEx(playerid, 0);

            SetPlayerPositionEx(playerid, 1545.6486,-1675.5486,13.5608,88.6509);
            StopRunningAnimation(playerid);

			GameTextForPlayer(playerid, "You are free!~n~~g~Please be a good person", 8000, 1);
		}
	}
	return 1;
}