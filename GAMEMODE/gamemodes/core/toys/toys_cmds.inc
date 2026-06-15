/*
YCMD:fashion(playerid, params[], help)
{
	if(IsPlayerInAnyVehicle(playerid)) return SEM(playerid, "Anda harus turun dari kendaraan!");
	if(!AccountData[playerid][IsLoggedIn]) return SEM(playerid, "Anda belum login / spawn!");
	if(AccountData[playerid][pKnockdown]) return SEM(playerid, "You cannot do that at the moment!");
	Dialog_Show(playerid, DIALOG_FASHION, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion", "Hat/Helmet\n"GRAY"Kacamata\nAksesoris\n"GRAY"Tas/Koper", "Pilih", "Batal");
	return 1;
}
*/