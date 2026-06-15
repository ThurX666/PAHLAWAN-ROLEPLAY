#include <YSI_Coding\y_hooks>

enum E_DONATOR
{
	pDTag[40 + 1]
};
new DonatorData[MAX_PLAYERS][E_DONATOR];

Dialog:VIPVehicleRadio(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	}

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dibiarkan kosong!");

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di kursi driver!");

	if(IsABike(SavingVehID[playerid]) || !IsEngineVehicle(SavingVehID[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Type kendaraan ini tidak valid!");

	PlayAudioStreamForPlayer(playerid, inputtext);

	foreach(new passid : VehicleOccupant(SavingVehID[playerid], true))
	{
		PlayAudioStreamForPlayer(passid, inputtext);
		ShowTDN(passid, NOTIFICATION_INFO, "Musik telah dimainkan di mobil, jika tidak ada periksa radio volume di setting GTA!");
	}
	ShowTDN(playerid, NOTIFICATION_INFO, "Musik telah dimainkan di mobil, jika tidak ada periksa radio volume di setting GTA!");
	return 1;
}

forward SetDTag(playerid, const dtagn[]);
public SetDTag(playerid, const dtagn[])
{
    if(cache_num_rows() > 0)
	{
	    ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Donator Tag '%s' telah digunakan!", dtagn));
        return 1;
	}
	else
	{
		new query[512];
	    format(query, sizeof(query), "UPDATE player_characters SET Char_DonatorTag='%e' WHERE pID=%d", dtagn, AccountData[playerid][pID]);
		mysql_pquery(g_SQL, query);
		strcopy(DonatorData[playerid][pDTag], ColouredText(dtagn));
		SendClientMessageEx(playerid, 0x80FF80AA, "[Info] You have successfully set donator tag become %s", dtagn);
	}
	return 1;
}