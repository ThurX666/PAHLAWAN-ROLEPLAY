#include <YSI_Coding\y_hooks>

enum e_toy_data
{
	toy_model,
	toy_bone,
	Float:toy_x,
	Float:toy_y,
	Float:toy_z,
	Float:toy_rx,
	Float:toy_ry,
	Float:toy_rz,
	Float:toy_sx,
	Float:toy_sy,
	Float:toy_sz,
    matcolor1[5],
    matcolor2[5],
    bool:toy_hidden
}
new pToys[MAX_PLAYERS][5][e_toy_data];

AttachPlayerToys(playerid)
{
	if(!AccountData[playerid][pIsToyInsertedOnMysql]) return 1;

    if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
        RemovePlayerAttachedObject(playerid, 0);

    if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
        RemovePlayerAttachedObject(playerid, 1);

    if(IsPlayerAttachedObjectSlotUsed(playerid, 2))
        RemovePlayerAttachedObject(playerid, 2);

    if(IsPlayerAttachedObjectSlotUsed(playerid, 3))
        RemovePlayerAttachedObject(playerid, 3);
	
	if(pToys[playerid][0][toy_model] != 0)
	{
		SetPlayerAttachedObject(playerid,
		0,
		pToys[playerid][0][toy_model],
		pToys[playerid][0][toy_bone],
		pToys[playerid][0][toy_x],
		pToys[playerid][0][toy_y],
		pToys[playerid][0][toy_z],
		pToys[playerid][0][toy_rx],
		pToys[playerid][0][toy_ry],
		pToys[playerid][0][toy_rz],
		pToys[playerid][0][toy_sx],
		pToys[playerid][0][toy_sy],
		pToys[playerid][0][toy_sz],
        pToys[playerid][0][matcolor1][4],
        pToys[playerid][0][matcolor2][4]);
	}
	
	if(pToys[playerid][1][toy_model] != 0)
	{
		SetPlayerAttachedObject(playerid,
		1,
		pToys[playerid][1][toy_model],
		pToys[playerid][1][toy_bone],
		pToys[playerid][1][toy_x],
		pToys[playerid][1][toy_y],
		pToys[playerid][1][toy_z],
		pToys[playerid][1][toy_rx],
		pToys[playerid][1][toy_ry],
		pToys[playerid][1][toy_rz],
		pToys[playerid][1][toy_sx],
		pToys[playerid][1][toy_sy],
		pToys[playerid][1][toy_sz],
        pToys[playerid][1][matcolor1][4],
        pToys[playerid][1][matcolor2][4]);
	}
	
	if(pToys[playerid][2][toy_model] != 0)
	{
		SetPlayerAttachedObject(playerid,
		2,
		pToys[playerid][2][toy_model],
		pToys[playerid][2][toy_bone],
		pToys[playerid][2][toy_x],
		pToys[playerid][2][toy_y],
		pToys[playerid][2][toy_z],
		pToys[playerid][2][toy_rx],
		pToys[playerid][2][toy_ry],
		pToys[playerid][2][toy_rz],
		pToys[playerid][2][toy_sx],
		pToys[playerid][2][toy_sy],
		pToys[playerid][2][toy_sz],
        pToys[playerid][2][matcolor1][4],
        pToys[playerid][2][matcolor2][4]);
	}
	
	if(pToys[playerid][3][toy_model] != 0)
	{
		SetPlayerAttachedObject(playerid,
		3,
		pToys[playerid][3][toy_model],
		pToys[playerid][3][toy_bone],
		pToys[playerid][3][toy_x],
		pToys[playerid][3][toy_y],
		pToys[playerid][3][toy_z],
		pToys[playerid][3][toy_rx],
		pToys[playerid][3][toy_ry],
		pToys[playerid][3][toy_rz],
		pToys[playerid][3][toy_sx],
		pToys[playerid][3][toy_sy],
		pToys[playerid][3][toy_sz],
        pToys[playerid][3][matcolor1][4],
        pToys[playerid][3][matcolor2][4]);
	}
	
	return 1;
}

SavePlayerFashionToMysql(playerid)
{
	if(!AccountData[playerid][pIsToyInsertedOnMysql]) return true;
	if(!GetPVarInt(playerid, "UpdatedToy")) return true;

	new lstr[1418];

    mysql_format(g_SQL, lstr, sizeof(lstr), 
    "UPDATE \
    `player_toys` \
    SET \
    `Slot0_Model` = %d, \
    `Slot0_Bone` = %d, \
    `Slot0_XPos` = '%.3f', \
    `Slot0_YPos` = '%.3f', \
    `Slot0_ZPos` = '%.3f', \
    `Slot0_XRot` = '%.3f', \
    `Slot0_YRot` = '%.3f', \
    `Slot0_ZRot` = '%.3f', \
    `Slot0_XScale` = '%.3f', \
    `Slot0_YScale` = '%.3f', \
    `Slot0_ZScale` = '%.3f', \
    `Slot0_Color1` = '%d|%d|%d|%d', \
    `Slot0_Color2` = '%d|%d|%d|%d', \
    `Slot1_Model` = %d, \
    `Slot1_Bone` = %d, \
    `Slot1_XPos` = '%.3f', \
    `Slot1_YPos` = '%.3f', \
    `Slot1_ZPos` = '%.3f', \
    `Slot1_XRot` = '%.3f', \
    `Slot1_YRot` = '%.3f', \
    `Slot1_ZRot` = '%.3f', \
    `Slot1_XScale` = '%.3f', \
    `Slot1_YScale` = '%.3f', \
    `Slot1_ZScale` = '%.3f',\
    `Slot1_Color1` = '%d|%d|%d|%d', \
    `Slot1_Color2` = '%d|%d|%d|%d', \
    `Slot2_Model` = %d, \
    `Slot2_Bone` = %d, \
    `Slot2_XPos` = '%.3f', \
    `Slot2_YPos` = '%.3f', \
    `Slot2_ZPos` = '%.3f', \
    `Slot2_XRot` = '%.3f', \
    `Slot2_YRot` = '%.3f', \
    `Slot2_ZRot` = '%.3f', \
    `Slot2_XScale` = '%.3f', \
    `Slot2_YScale` = '%.3f', \
    `Slot2_ZScale` = '%.3f', \
    `Slot2_Color1` = '%d|%d|%d|%d', \
    `Slot2_Color2` = '%d|%d|%d|%d', \
    `Slot3_Model` = %d, \
    `Slot3_Bone` = %d, \
    `Slot3_XPos` = '%.3f', \
    `Slot3_YPos` = '%.3f', \
    `Slot3_ZPos` = '%.3f', \
    `Slot3_XRot` = '%.3f', \
    `Slot3_YRot` = '%.3f', \
    `Slot3_ZRot` = '%.3f', \
    `Slot3_XScale` = '%.3f', \
    `Slot3_YScale` = '%.3f', \
    `Slot3_ZScale` = '%.3f', \
    `Slot3_Color1` = '%d|%d|%d|%d', \
    `Slot3_Color2` = '%d|%d|%d|%d' WHERE `Owner` = '%e'",
    pToys[playerid][0][toy_model],
    pToys[playerid][0][toy_bone],
    pToys[playerid][0][toy_x],
    pToys[playerid][0][toy_y],
    pToys[playerid][0][toy_z],
    pToys[playerid][0][toy_rx],
    pToys[playerid][0][toy_ry],
    pToys[playerid][0][toy_rz],
    pToys[playerid][0][toy_sx],
    pToys[playerid][0][toy_sy],
    pToys[playerid][0][toy_sz],
    pToys[playerid][0][matcolor1][0], pToys[playerid][0][matcolor1][1], pToys[playerid][0][matcolor1][2], pToys[playerid][0][matcolor1][3],
    pToys[playerid][0][matcolor2][0], pToys[playerid][0][matcolor2][1], pToys[playerid][0][matcolor2][2], pToys[playerid][0][matcolor2][3],
    pToys[playerid][1][toy_model],
    pToys[playerid][1][toy_bone],
    pToys[playerid][1][toy_x],
    pToys[playerid][1][toy_y],
    pToys[playerid][1][toy_z],
    pToys[playerid][1][toy_rx],
    pToys[playerid][1][toy_ry],
    pToys[playerid][1][toy_rz],
    pToys[playerid][1][toy_sx],
    pToys[playerid][1][toy_sy],
    pToys[playerid][1][toy_sz],
    pToys[playerid][1][matcolor1][0], pToys[playerid][1][matcolor1][1], pToys[playerid][1][matcolor1][2], pToys[playerid][1][matcolor1][3],
    pToys[playerid][1][matcolor2][0], pToys[playerid][1][matcolor2][1], pToys[playerid][1][matcolor2][2], pToys[playerid][1][matcolor2][3],
    pToys[playerid][2][toy_model],
    pToys[playerid][2][toy_bone],
    pToys[playerid][2][toy_x],
    pToys[playerid][2][toy_y],
    pToys[playerid][2][toy_z],
    pToys[playerid][2][toy_rx],
    pToys[playerid][2][toy_ry],
    pToys[playerid][2][toy_rz],
    pToys[playerid][2][toy_sx],
    pToys[playerid][2][toy_sy],
    pToys[playerid][2][toy_sz],
    pToys[playerid][2][matcolor1][0], pToys[playerid][2][matcolor1][1], pToys[playerid][2][matcolor1][2], pToys[playerid][2][matcolor1][3],
    pToys[playerid][2][matcolor2][0], pToys[playerid][2][matcolor2][1], pToys[playerid][2][matcolor2][2], pToys[playerid][2][matcolor2][3],
    pToys[playerid][3][toy_model],
    pToys[playerid][3][toy_bone],
    pToys[playerid][3][toy_x],
    pToys[playerid][3][toy_y],
    pToys[playerid][3][toy_z],
    pToys[playerid][3][toy_rx],
    pToys[playerid][3][toy_ry],
    pToys[playerid][3][toy_rz],
    pToys[playerid][3][toy_sx],
    pToys[playerid][3][toy_sy],
    pToys[playerid][3][toy_sz],
    pToys[playerid][3][matcolor1][0], pToys[playerid][3][matcolor1][1], pToys[playerid][3][matcolor1][2], pToys[playerid][3][matcolor1][3],
    pToys[playerid][3][matcolor2][0], pToys[playerid][3][matcolor2][1], pToys[playerid][3][matcolor2][2], pToys[playerid][3][matcolor2][3],
    AccountData[playerid][pName]);
    mysql_pquery(g_SQL, lstr);

    DeletePVar(playerid, "UpdatedToy");
    return 1;
}

forward LoadPlayerFashion(playerid);
public LoadPlayerFashion(playerid)
{
	new rows = cache_num_rows(), formatwarna[32];
	if(rows)
	{
		AccountData[playerid][pIsToyInsertedOnMysql] = true;
		cache_get_value_name_int(0, "Slot0_Model", pToys[playerid][0][toy_model]);
  		cache_get_value_name_int(0, "Slot0_Bone", pToys[playerid][0][toy_bone]);
  		cache_get_value_name_float(0, "Slot0_XPos", pToys[playerid][0][toy_x]);
  		cache_get_value_name_float(0, "Slot0_YPos", pToys[playerid][0][toy_y]);
  		cache_get_value_name_float(0, "Slot0_ZPos", pToys[playerid][0][toy_z]);
  		cache_get_value_name_float(0, "Slot0_XRot", pToys[playerid][0][toy_rx]);
  		cache_get_value_name_float(0, "Slot0_YRot", pToys[playerid][0][toy_ry]);
  		cache_get_value_name_float(0, "Slot0_ZRot", pToys[playerid][0][toy_rz]);
  		cache_get_value_name_float(0, "Slot0_XScale", pToys[playerid][0][toy_sx]);
  		cache_get_value_name_float(0, "Slot0_YScale", pToys[playerid][0][toy_sy]);
		cache_get_value_name_float(0, "Slot0_ZScale", pToys[playerid][0][toy_sz]);
		cache_get_value_name(0, "Slot0_Color1", formatwarna);
        sscanf(formatwarna, "p<|>a<i>[4]", pToys[playerid][0][matcolor1]);
        pToys[playerid][0][matcolor1][4] = RGBA(pToys[playerid][0][matcolor1][0], pToys[playerid][0][matcolor1][1], pToys[playerid][0][matcolor1][2], pToys[playerid][0][matcolor1][3]);

		cache_get_value_name(0, "Slot0_Color2", formatwarna);
        sscanf(formatwarna, "p<|>a<i>[4]", pToys[playerid][0][matcolor2]);
        pToys[playerid][0][matcolor2][4] = RGBA(pToys[playerid][0][matcolor2][0], pToys[playerid][0][matcolor2][1], pToys[playerid][0][matcolor2][2], pToys[playerid][0][matcolor2][3]);
		
		cache_get_value_name_int(0, "Slot1_Model", pToys[playerid][1][toy_model]);
  		cache_get_value_name_int(0, "Slot1_Bone", pToys[playerid][1][toy_bone]);
  		cache_get_value_name_float(0, "Slot1_XPos", pToys[playerid][1][toy_x]);
  		cache_get_value_name_float(0, "Slot1_YPos", pToys[playerid][1][toy_y]);
  		cache_get_value_name_float(0, "Slot1_ZPos", pToys[playerid][1][toy_z]);
  		cache_get_value_name_float(0, "Slot1_XRot", pToys[playerid][1][toy_rx]);
  		cache_get_value_name_float(0, "Slot1_YRot", pToys[playerid][1][toy_ry]);
  		cache_get_value_name_float(0, "Slot1_ZRot", pToys[playerid][1][toy_rz]);
  		cache_get_value_name_float(0, "Slot1_XScale", pToys[playerid][1][toy_sx]);
  		cache_get_value_name_float(0, "Slot1_YScale", pToys[playerid][1][toy_sy]);
		cache_get_value_name_float(0, "Slot1_ZScale", pToys[playerid][1][toy_sz]);
        cache_get_value_name(0, "Slot1_Color1", formatwarna);
        sscanf(formatwarna, "p<|>a<i>[4]", pToys[playerid][1][matcolor1]);
        pToys[playerid][1][matcolor1][4] = RGBA(pToys[playerid][1][matcolor1][0], pToys[playerid][1][matcolor1][1], pToys[playerid][1][matcolor1][2], pToys[playerid][1][matcolor1][3]);
		cache_get_value_name(0, "Slot1_Color2", formatwarna);
        sscanf(formatwarna, "p<|>a<i>[4]", pToys[playerid][1][matcolor2]);
        pToys[playerid][1][matcolor2][4] = RGBA(pToys[playerid][1][matcolor2][0], pToys[playerid][1][matcolor2][1], pToys[playerid][1][matcolor2][2], pToys[playerid][1][matcolor2][3]);
		
		cache_get_value_name_int(0, "Slot2_Model", pToys[playerid][2][toy_model]);
  		cache_get_value_name_int(0, "Slot2_Bone", pToys[playerid][2][toy_bone]);
  		cache_get_value_name_float(0, "Slot2_XPos", pToys[playerid][2][toy_x]);
  		cache_get_value_name_float(0, "Slot2_YPos", pToys[playerid][2][toy_y]);
  		cache_get_value_name_float(0, "Slot2_ZPos", pToys[playerid][2][toy_z]);
  		cache_get_value_name_float(0, "Slot2_XRot", pToys[playerid][2][toy_rx]);
  		cache_get_value_name_float(0, "Slot2_YRot", pToys[playerid][2][toy_ry]);
  		cache_get_value_name_float(0, "Slot2_ZRot", pToys[playerid][2][toy_rz]);
  		cache_get_value_name_float(0, "Slot2_XScale", pToys[playerid][2][toy_sx]);
  		cache_get_value_name_float(0, "Slot2_YScale", pToys[playerid][2][toy_sy]);
		cache_get_value_name_float(0, "Slot2_ZScale", pToys[playerid][2][toy_sz]);
        cache_get_value_name(0, "Slot2_Color1", formatwarna);
        sscanf(formatwarna, "p<|>a<i>[4]", pToys[playerid][2][matcolor1]);
        pToys[playerid][2][matcolor1][4] = RGBA(pToys[playerid][2][matcolor1][0], pToys[playerid][2][matcolor1][1], pToys[playerid][2][matcolor1][2], pToys[playerid][2][matcolor1][3]);
		cache_get_value_name(0, "Slot2_Color2", formatwarna);
        sscanf(formatwarna, "p<|>a<i>[4]", pToys[playerid][1][matcolor2]);
        pToys[playerid][2][matcolor2][4] = RGBA(pToys[playerid][2][matcolor2][0], pToys[playerid][2][matcolor2][1], pToys[playerid][2][matcolor2][2], pToys[playerid][2][matcolor2][3]);
		
		cache_get_value_name_int(0, "Slot3_Model", pToys[playerid][3][toy_model]);
  		cache_get_value_name_int(0, "Slot3_Bone", pToys[playerid][3][toy_bone]);
  		cache_get_value_name_float(0, "Slot3_XPos", pToys[playerid][3][toy_x]);
  		cache_get_value_name_float(0, "Slot3_YPos", pToys[playerid][3][toy_y]);
  		cache_get_value_name_float(0, "Slot3_ZPos", pToys[playerid][3][toy_z]);
  		cache_get_value_name_float(0, "Slot3_XRot", pToys[playerid][3][toy_rx]);
  		cache_get_value_name_float(0, "Slot3_YRot", pToys[playerid][3][toy_ry]);
  		cache_get_value_name_float(0, "Slot3_ZRot", pToys[playerid][3][toy_rz]);
  		cache_get_value_name_float(0, "Slot3_XScale", pToys[playerid][3][toy_sx]);
  		cache_get_value_name_float(0, "Slot3_YScale", pToys[playerid][3][toy_sy]);
		cache_get_value_name_float(0, "Slot3_ZScale", pToys[playerid][3][toy_sz]);
        cache_get_value_name(0, "Slot3_Color1", formatwarna);
        sscanf(formatwarna, "p<|>a<i>[4]", pToys[playerid][3][matcolor1]);
        pToys[playerid][3][matcolor1][4] = RGBA(pToys[playerid][3][matcolor1][0], pToys[playerid][3][matcolor1][1], pToys[playerid][3][matcolor1][2], pToys[playerid][3][matcolor1][3]);
		cache_get_value_name(0, "Slot3_Color2", formatwarna);
        sscanf(formatwarna, "p<|>a<i>[4]", pToys[playerid][3][matcolor2]);
        pToys[playerid][3][matcolor2][4] = RGBA(pToys[playerid][3][matcolor2][0], pToys[playerid][3][matcolor2][1], pToys[playerid][3][matcolor2][2], pToys[playerid][3][matcolor2][3]);

		printf("[Player Fashion] Jumlah total Fashion yang dimuat untuk %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], rows);
	}
	return 1;
}

Dialog:ToysEdit(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        HideServerNameTD(playerid);
        HideSpeedoTD(playerid);
        HideHBETD(playerid);
        ShowRadialFashionTD(playerid);
        return 1;
    }

    switch(listitem)
    {
        case 0: //edit posisi PC
        {
            EditAttachedObject(playerid, AccountData[playerid][pToySelected]);
        }
        case 1: //bone
        {
            Dialog_Show(playerid, "ToysEditBone", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Bone", 
            "Spine\n"GRAY"Head\nLeft upper arm\n"GRAY"Right upper arm\nLeft hand\n"GRAY"Right hand\nLeft thigh\n"GRAY"Right tigh\nLeft foot\n"GRAY"Right foot\nRight calf\n"GRAY"Left calf\nLeft forearm\n"GRAY"Right forearm\nLeft clavicle\n"GRAY"Right clavicle\nNeck\n"GRAY"Jaw", 
            "Pilih", "Batal");
        }
        case 2:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Sumbu X (saat ini): %f\n"YELLOW"(Masukkan Sumbu X yang baru):", pToys[playerid][AccountData[playerid][pToySelected]][toy_x]);
            Dialog_Show(playerid, "ToysEditX", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Sumbu X", mstr, "Set", "Batal");
        }
        case 3:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Sumbu Y (saat ini): %f\n"YELLOW"(Masukkan Sumbu Y yang baru):", pToys[playerid][AccountData[playerid][pToySelected]][toy_y]);
            Dialog_Show(playerid, "ToysEditY", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Sumbu Y", mstr, "Set", "Batal");
        }
        case 4:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Sumbu Z (saat ini): %f\n"YELLOW"(Masukkan Sumbu Z yang baru):", pToys[playerid][AccountData[playerid][pToySelected]][toy_z]);
            Dialog_Show(playerid, "ToysEditZ", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Sumbu Z", mstr, "Set", "Batal");
        }
        case 5:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Rotasi X (saat ini): %f\n"YELLOW"(Masukkan Rotasi X yang baru):", pToys[playerid][AccountData[playerid][pToySelected]][toy_rx]);
            Dialog_Show(playerid, "ToysEditRX", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Rotasi X", mstr, "Set", "Batal");
        }
        case 6:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Rotasi Y (saat ini): %f\n"YELLOW"(Masukkan Rotasi Y yang baru):", pToys[playerid][AccountData[playerid][pToySelected]][toy_ry]);
            Dialog_Show(playerid, "ToysEditRY", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Rotasi Y", mstr, "Set", "Batal");
        }
        case 7:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Rotasi Z (saat ini): %f\n"YELLOW"(Masukkan Rotasi Z yang baru):", pToys[playerid][AccountData[playerid][pToySelected]][toy_rz]);
            Dialog_Show(playerid, "ToysEditRZ", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Rotasi Z", mstr, "Set", "Batal");
        }
        case 8:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Skala X (saat ini): %f\n"YELLOW"(Masukkan Skala X yang baru):", pToys[playerid][AccountData[playerid][pToySelected]][toy_sx]);
            Dialog_Show(playerid, "ToysEditSX", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Skala X", mstr, "Set", "Batal");
        }
        case 9:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Skala Y (saat ini): %f\n"YELLOW"(Masukkan Skala Y yang baru):", pToys[playerid][AccountData[playerid][pToySelected]][toy_sy]);
            Dialog_Show(playerid, "ToysEditSY", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Skala Y", mstr, "Set", "Batal");
        }
        case 10:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Skala Z (saat ini): %f\n"YELLOW"(Masukkan Skala Z yang baru):", pToys[playerid][AccountData[playerid][pToySelected]][toy_sz]);
            Dialog_Show(playerid, "ToysEditSZ", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Skala Z", mstr, "Set", "Batal");
        }
        case 11:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Material Color 1 (saat ini): %08x\n"YELLOW"Masukkan Material Color 1 (Dalam format ARGB)\n"ORANGE"Contoh: 255 255 0 0 (Untuk warna merah)", pToys[playerid][AccountData[playerid][pToySelected]][matcolor1]);
            Dialog_Show(playerid, "ToysEditC1", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Color 1", mstr, "Set", "Batal");
        }
        case 12:
        {
            new mstr[128];
            format(mstr, sizeof(mstr), ""WHITE"Material Color 2 (saat ini): %08x\n"YELLOW"Masukkan Material Color 2 (Dalam format ARGB)\n"ORANGE"Contoh: 255 255 0 0 (Untuk warna merah)", pToys[playerid][AccountData[playerid][pToySelected]][matcolor2]);
            Dialog_Show(playerid, "ToysEditC2", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Color 2", mstr, "Set", "Batal");
        }
        case 13:
        {
            if(IsPlayerAttachedObjectSlotUsed(playerid, AccountData[playerid][pToySelected]))
            {
                RemovePlayerAttachedObject(playerid, AccountData[playerid][pToySelected]);
            }
            pToys[playerid][AccountData[playerid][pToySelected]][toy_model] = 0;
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Fashion tersebut berhasil dihapus!");
            SetPVarInt(playerid, "UpdatedToy", 1);
            SavePlayerFashionToMysql(playerid);
        }
        case 14:
        {
            switch(pToys[playerid][AccountData[playerid][pToySelected]][toy_hidden])
            {
                case true:
                {
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_hidden] = false;

                    SetPlayerAttachedObject(playerid,
                    AccountData[playerid][pToySelected],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
                    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
                    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
                    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

                    ApplyAnimation(playerid, "GOGGLES", "GOGGLES_PUT_ON", 4.1, false, false, false, false, 0, true); // masker

                    ShowTDN(playerid, NOTIFICATION_INFO, "Fashion tersebut telah ~g~ditampilkan!");
                }
                case false:
                {
                    if(IsPlayerAttachedObjectSlotUsed(playerid, AccountData[playerid][pToySelected]))
                        RemovePlayerAttachedObject(playerid, AccountData[playerid][pToySelected]);

                    ApplyAnimation(playerid, "GOGGLES", "GOGGLES_PUT_ON", 4.1, false, false, false, false, 0, true); // masker

                    pToys[playerid][AccountData[playerid][pToySelected]][toy_hidden] = true;
                    ShowTDN(playerid, NOTIFICATION_INFO, "Fashion tersebut telah ~r~disembunyikan!");
                }
            }
        }
        case 15:
        {
            SendNearbyMessage(playerid, 20.0, Y_HOTPINK4, "Fashion %s | X: %.3f - Y: %.3f - Z: %.3f - RX: %.3f - RY: %.3f - RZ: %.3f - SX: %.3f - SY: %.3f - SZ: %.3f", AccountData[playerid][pName], pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z], pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
		    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz]);
        }
    }
    return 1;
}
Dialog:ToysEditBone(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    listitem++;
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone] = listitem;

    if(IsPlayerAttachedObjectSlotUsed(playerid, AccountData[playerid][pToySelected]))
        RemovePlayerAttachedObject(playerid, AccountData[playerid][pToySelected]);

    listitem = AccountData[playerid][pToySelected];
    SetPlayerAttachedObject(playerid,
            listitem,
            pToys[playerid][listitem][toy_model],
            pToys[playerid][listitem][toy_bone],
            pToys[playerid][listitem][toy_x],
            pToys[playerid][listitem][toy_y],
            pToys[playerid][listitem][toy_z],
            pToys[playerid][listitem][toy_rx],
            pToys[playerid][listitem][toy_ry],
            pToys[playerid][listitem][toy_rz],
            pToys[playerid][listitem][toy_sx],
            pToys[playerid][listitem][toy_sy],
            pToys[playerid][listitem][toy_sz],
            pToys[playerid][listitem][matcolor1][4],
            pToys[playerid][listitem][matcolor2][4]);

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Posisi bone fashion tersebut berhasil diubah!");
    SetPVarInt(playerid, "UpdatedToy", 1);
    SavePlayerFashionToMysql(playerid);
    return 1;
}
Dialog:ToysEditX(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new Float:latestpos = floatstr(inputtext);

    if(latestpos > 1.0 && latestpos > -1.0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Coordinate tidak valid!");

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    latestpos,
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    pToys[playerid][AccountData[playerid][pToySelected]][toy_x] = latestpos;
    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditY(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new Float:latestpos = floatstr(inputtext);

    if(latestpos > 1.0 && latestpos > -1.0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Coordinate tidak valid!");

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    latestpos,
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    pToys[playerid][AccountData[playerid][pToySelected]][toy_y] = latestpos;
    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditZ(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new Float:latestpos = floatstr(inputtext);

    if(latestpos > 1.0 && latestpos > -1.0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Coordinate tidak valid!");

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    latestpos,
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    pToys[playerid][AccountData[playerid][pToySelected]][toy_z] = latestpos;
    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditRX(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new Float:latestpos = floatstr(inputtext);

    if(latestpos > 180.0 && latestpos > -180.0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Rotasi tidak valid!");

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    latestpos,
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx] = latestpos;
    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditRY(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new Float:latestpos = floatstr(inputtext);

    if(latestpos > 180.0 && latestpos > -180.0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Rotasi tidak valid!");

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    latestpos,
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry] = latestpos;
    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditRZ(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new Float:latestpos = floatstr(inputtext);

    if(latestpos > 180.0 && latestpos > -180.0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Rotasi tidak valid!");

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    latestpos,
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz] = latestpos;
    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditSX(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new Float:latestpos = floatstr(inputtext);

    if(latestpos > 2.0 && latestpos > -2.0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Scale tidak valid!");

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    latestpos,
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx] = latestpos;
    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditSY(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new Float:latestpos = floatstr(inputtext);

    if(latestpos > 2.0 && latestpos > -2.0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Scale tidak valid!");

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    latestpos,
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy] = latestpos;
    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditSZ(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new Float:latestpos = floatstr(inputtext);

    if(latestpos > 2.0 && latestpos > -2.0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Scale tidak valid!");

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    latestpos,
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz] = latestpos;
    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditC1(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new color[4], mstr[128];
    if(sscanf(inputtext, "p< >a<i>[4]", color))
    {
        format(mstr, sizeof(mstr), ""WHITE"Format warna salah!\nMaterial Color 1 (saat ini): %08x\n"YELLOW"Masukkan Material Color 1 (Dalam format ARGB)\n"ORANGE"Contoh: 255 255 0 0 (Untuk warna merah)", pToys[playerid][AccountData[playerid][pToySelected]][matcolor1]);
        Dialog_Show(playerid, "ToysEditC1", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Color 1", mstr, "Set", "Batal");
        return 1;
    }

    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][0] = color[0];
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][1] = color[1];
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][2] = color[2];
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][3] = color[3];

    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4] = RGBA(color[0], color[1], color[2], color[3]);
    
    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}
Dialog:ToysEditC2(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new color[4], mstr[128];
    if(sscanf(inputtext, "p< >a<i>[4]", color))
    {
        format(mstr, sizeof(mstr), ""WHITE"Format warna salah!\nMaterial Color 2 (saat ini): %08x\n"YELLOW"Masukkan Material Color 2 (Dalam format ARGB)\n"ORANGE"Contoh: 255 255 0 0 (Untuk warna merah)", pToys[playerid][AccountData[playerid][pToySelected]][matcolor2]);
        Dialog_Show(playerid, "ToysEditC2", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Color 2", mstr, "Set", "Batal");
        return 1;
    }

    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][0] = color[0];
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][1] = color[1];
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][2] = color[2];
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][3] = color[3];

    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4] = RGBA(color[0], color[1], color[2], color[3]);

    SetPlayerAttachedObject(playerid,
    AccountData[playerid][pToySelected],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_model],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_bone],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_y],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_ry],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sy],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);

    SetPVarInt(playerid, "UpdatedToy", 1);

    SavePlayerFashionToMysql(playerid);

    new string[666];
    format(string, sizeof(string), "Pengaturan\tParameter\n\
    Edit Posisi\t(Khusus PC)\n\
    "GRAY"Ubah Tulang (Bone)\n\
    Sumbu X:\t%f\n\
    "GRAY"Sumbu Y:\t"GRAY"%f\n\
    Sumbu Z:\t%f\n\
    "GRAY"Rotasi X:\t"GRAY"%f\n\
    Rotasi Y:\t%f\n\
    "GRAY"Rotasi Z:\t"GRAY"%f\n\
    Skala X:\t%f\n\
    "GRAY"Skala Y:\t"GRAY"%f\n\
    Skala Z:\t%f\n\
    "GRAY"Color 1:\t"GRAY"%08x\n\
    Color 2:\t%08x\n\
    "GRAY"Hapus\t"GRAY"(Pilih ini jika ingin menghapus permanen)\n\
    Sembunyikan\t(Jika ingin disembunyikan)\n\
    "GRAY"Bagikan Koordinat\t"GRAY"(Jika ingin membagikan koordinat)",
    pToys[playerid][AccountData[playerid][pToySelected]][toy_x], pToys[playerid][AccountData[playerid][pToySelected]][toy_y], pToys[playerid][AccountData[playerid][pToySelected]][toy_z],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_rx], pToys[playerid][AccountData[playerid][pToySelected]][toy_ry], pToys[playerid][AccountData[playerid][pToySelected]][toy_rz],
    pToys[playerid][AccountData[playerid][pToySelected]][toy_sx], pToys[playerid][AccountData[playerid][pToySelected]][toy_sy], pToys[playerid][AccountData[playerid][pToySelected]][toy_sz],
    pToys[playerid][AccountData[playerid][pToySelected]][matcolor1][4], pToys[playerid][AccountData[playerid][pToySelected]][matcolor2][4]);
    
    switch(AccountData[playerid][pToySelected])
    {
        case 0:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Hat/Helmet)", string, "Pilih", "Kembali");
        }
        case 1:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Kacamata)", string, "Pilih", "Kembali");
        }
        case 2:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Aksesoris)", string, "Pilih", "Kembali");
        }
        case 3:
        {
            Dialog_Show(playerid, "ToysEdit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Fashion (Tas/Koper)", string, "Pilih", "Kembali");
        }
    }
    return 1;
}