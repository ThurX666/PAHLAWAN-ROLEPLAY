enum e_clothesdetails
{
    clothesID, //clothes db ID
    clothesOwnerID, //clothes owner db ID
    clothesName[34],
    clothesSkinID,
    clothesToys[4],
    clothesBone[4],
    Float:clothesToysX[4],
    Float:clothesToysY[4],
    Float:clothesToysZ[4],
    Float:clothesToysRX[4],
    Float:clothesToysRY[4],
    Float:clothesToysRZ[4],
    Float:clothesToysSX[4],
    Float:clothesToysSY[4],
    Float:clothesToysSZ[4],

    //stuff
    clothesTotal
};
new ClothesData[MAX_PLAYERS][e_clothesdetails];

forward OnPlayerSaveClothes(playerid);
public OnPlayerSaveClothes(playerid)
{
    ClothesData[playerid][clothesTotal]++;
    SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berhasil menyimpan pakaian dengan nama "CMDEA"%s", ClothesData[playerid][clothesName]);
    return 1;
}

SetDefaultAppearance(playerid)
{
    SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
    AttachPlayerToys(playerid);
}

forward SetPlayerClothes(playerid, slot);
public SetPlayerClothes(playerid, slot)
{
    new tstr[128];
	mysql_format(g_SQL, tstr, sizeof(tstr), "SELECT * FROM `player_clothes` WHERE `ID`=%d AND `Owner`=%d", slot, AccountData[playerid][pID]);
    mysql_query(g_SQL, tstr);
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(0, "Skin", ClothesData[playerid][clothesSkinID]);
        cache_get_value_name_int(0, "Bone0", ClothesData[playerid][clothesBone][0]);
        cache_get_value_name_int(0, "Bone1", ClothesData[playerid][clothesBone][1]);
        cache_get_value_name_int(0, "Bone2", ClothesData[playerid][clothesBone][2]);
        cache_get_value_name_int(0, "Bone3", ClothesData[playerid][clothesBone][3]);

        cache_get_value_name_int(0, "Toys0", ClothesData[playerid][clothesToys][0]);
        cache_get_value_name_int(0, "Toys1", ClothesData[playerid][clothesToys][1]);
        cache_get_value_name_int(0, "Toys2", ClothesData[playerid][clothesToys][2]);
        cache_get_value_name_int(0, "Toys3", ClothesData[playerid][clothesToys][3]);

        cache_get_value_name_float(0, "ToysX_0", ClothesData[playerid][clothesToysX][0]);
        cache_get_value_name_float(0, "ToysY_0", ClothesData[playerid][clothesToysY][0]);
        cache_get_value_name_float(0, "ToysZ_0", ClothesData[playerid][clothesToysZ][0]);
        cache_get_value_name_float(0, "ToysRX_0", ClothesData[playerid][clothesToysRX][0]);
        cache_get_value_name_float(0, "ToysRY_0", ClothesData[playerid][clothesToysRY][0]);
        cache_get_value_name_float(0, "ToysRZ_0", ClothesData[playerid][clothesToysRZ][0]);
        cache_get_value_name_float(0, "ToysSX_0", ClothesData[playerid][clothesToysSX][0]);
        cache_get_value_name_float(0, "ToysSY_0", ClothesData[playerid][clothesToysSY][0]);
        cache_get_value_name_float(0, "ToysSZ_0", ClothesData[playerid][clothesToysSZ][0]);

        cache_get_value_name_float(0, "ToysX_1", ClothesData[playerid][clothesToysX][1]);
        cache_get_value_name_float(0, "ToysY_1", ClothesData[playerid][clothesToysY][1]);
        cache_get_value_name_float(0, "ToysZ_1", ClothesData[playerid][clothesToysZ][1]);
        cache_get_value_name_float(0, "ToysRX_1", ClothesData[playerid][clothesToysRX][1]);
        cache_get_value_name_float(0, "ToysRY_1", ClothesData[playerid][clothesToysRY][1]);
        cache_get_value_name_float(0, "ToysRZ_1", ClothesData[playerid][clothesToysRZ][1]);
        cache_get_value_name_float(0, "ToysSX_1", ClothesData[playerid][clothesToysSX][1]);
        cache_get_value_name_float(0, "ToysSY_1", ClothesData[playerid][clothesToysSY][1]);
        cache_get_value_name_float(0, "ToysSZ_1", ClothesData[playerid][clothesToysSZ][1]);

        cache_get_value_name_float(0, "ToysX_2", ClothesData[playerid][clothesToysX][2]);
        cache_get_value_name_float(0, "ToysY_2", ClothesData[playerid][clothesToysY][2]);
        cache_get_value_name_float(0, "ToysZ_2", ClothesData[playerid][clothesToysZ][2]);
        cache_get_value_name_float(0, "ToysRX_2", ClothesData[playerid][clothesToysRX][2]);
        cache_get_value_name_float(0, "ToysRY_2", ClothesData[playerid][clothesToysRY][2]);
        cache_get_value_name_float(0, "ToysRZ_2", ClothesData[playerid][clothesToysRZ][2]);
        cache_get_value_name_float(0, "ToysSX_2", ClothesData[playerid][clothesToysSX][2]);
        cache_get_value_name_float(0, "ToysSY_2", ClothesData[playerid][clothesToysSY][2]);
        cache_get_value_name_float(0, "ToysSZ_2", ClothesData[playerid][clothesToysSZ][2]);

        cache_get_value_name_float(0, "ToysX_3", ClothesData[playerid][clothesToysX][3]);
        cache_get_value_name_float(0, "ToysY_3", ClothesData[playerid][clothesToysY][3]);
        cache_get_value_name_float(0, "ToysZ_3", ClothesData[playerid][clothesToysZ][3]);
        cache_get_value_name_float(0, "ToysRX_3", ClothesData[playerid][clothesToysRX][3]);
        cache_get_value_name_float(0, "ToysRY_3", ClothesData[playerid][clothesToysRY][3]);
        cache_get_value_name_float(0, "ToysRZ_3", ClothesData[playerid][clothesToysRZ][3]);
        cache_get_value_name_float(0, "ToysSX_3", ClothesData[playerid][clothesToysSX][3]);
        cache_get_value_name_float(0, "ToysSY_3", ClothesData[playerid][clothesToysSY][3]);
        cache_get_value_name_float(0, "ToysSZ_3", ClothesData[playerid][clothesToysSZ][3]);

        AccountData[playerid][pSkin] = ClothesData[playerid][clothesSkinID];
        SetPlayerSkin(playerid, ClothesData[playerid][clothesSkinID]);

        if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
            RemovePlayerAttachedObject(playerid, 0);

        if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
            RemovePlayerAttachedObject(playerid, 1);

        if(IsPlayerAttachedObjectSlotUsed(playerid, 2))
            RemovePlayerAttachedObject(playerid, 2);

        if(IsPlayerAttachedObjectSlotUsed(playerid, 3))
            RemovePlayerAttachedObject(playerid, 3);

        if(ClothesData[playerid][clothesToys][0] != 0) //hat / helmet bone = 2
        {
            SetPlayerAttachedObject(playerid,
            0,
            ClothesData[playerid][clothesToys][0],
            ClothesData[playerid][clothesBone][0],
            ClothesData[playerid][clothesToysX][0],
            ClothesData[playerid][clothesToysY][0],
            ClothesData[playerid][clothesToysZ][0],
            ClothesData[playerid][clothesToysRX][0],
            ClothesData[playerid][clothesToysRY][0],
            ClothesData[playerid][clothesToysRZ][0],
            ClothesData[playerid][clothesToysSX][0],
            ClothesData[playerid][clothesToysSY][0],
            ClothesData[playerid][clothesToysSZ][0]);
        }
        if(ClothesData[playerid][clothesToys][1] != 0) //kacamata bone = 2
        {
            SetPlayerAttachedObject(playerid,
            1,
            ClothesData[playerid][clothesToys][1],
            ClothesData[playerid][clothesBone][1],
            ClothesData[playerid][clothesToysX][1],
            ClothesData[playerid][clothesToysY][1],
            ClothesData[playerid][clothesToysZ][1],
            ClothesData[playerid][clothesToysRX][1],
            ClothesData[playerid][clothesToysRY][1],
            ClothesData[playerid][clothesToysRZ][1],
            ClothesData[playerid][clothesToysSX][1],
            ClothesData[playerid][clothesToysSY][1],
            ClothesData[playerid][clothesToysSZ][1]);
        }
        if(ClothesData[playerid][clothesToys][2] != 0) //aksesoris bone = 1
        {
            SetPlayerAttachedObject(playerid,
            2,
            ClothesData[playerid][clothesToys][2],
            ClothesData[playerid][clothesBone][2],
            ClothesData[playerid][clothesToysX][2],
            ClothesData[playerid][clothesToysY][2],
            ClothesData[playerid][clothesToysZ][2],
            ClothesData[playerid][clothesToysRX][2],
            ClothesData[playerid][clothesToysRY][2],
            ClothesData[playerid][clothesToysRZ][2],
            ClothesData[playerid][clothesToysSX][2],
            ClothesData[playerid][clothesToysSY][2],
            ClothesData[playerid][clothesToysSZ][2]);
        }
        if(ClothesData[playerid][clothesToys][3] != 0) //tas bone = 1
        {
            SetPlayerAttachedObject(playerid,
            3,
            ClothesData[playerid][clothesToys][3],
            ClothesData[playerid][clothesBone][3],
            ClothesData[playerid][clothesToysX][3],
            ClothesData[playerid][clothesToysY][3],
            ClothesData[playerid][clothesToysZ][3],
            ClothesData[playerid][clothesToysRX][3],
            ClothesData[playerid][clothesToysRY][3],
            ClothesData[playerid][clothesToysRZ][3],
            ClothesData[playerid][clothesToysSX][3],
            ClothesData[playerid][clothesToysSY][3],
            ClothesData[playerid][clothesToysSZ][3]);
        }

        pToys[playerid][0][toy_model] = ClothesData[playerid][clothesToys][0];
        pToys[playerid][0][toy_bone] = ClothesData[playerid][clothesBone][0];
        pToys[playerid][0][toy_x] = ClothesData[playerid][clothesToysX][0];
        pToys[playerid][0][toy_y] = ClothesData[playerid][clothesToysY][0];
        pToys[playerid][0][toy_z] = ClothesData[playerid][clothesToysZ][0];
        pToys[playerid][0][toy_rx] = ClothesData[playerid][clothesToysRX][0];
        pToys[playerid][0][toy_ry] = ClothesData[playerid][clothesToysRY][0];
        pToys[playerid][0][toy_rz] = ClothesData[playerid][clothesToysRZ][0];
        pToys[playerid][0][toy_sx] = ClothesData[playerid][clothesToysSX][0];
        pToys[playerid][0][toy_sy] = ClothesData[playerid][clothesToysSY][0];
        pToys[playerid][0][toy_sz] = ClothesData[playerid][clothesToysSZ][0];

        pToys[playerid][1][toy_model] = ClothesData[playerid][clothesToys][1];
        pToys[playerid][1][toy_bone] = ClothesData[playerid][clothesBone][1];
        pToys[playerid][1][toy_x] = ClothesData[playerid][clothesToysX][1];
        pToys[playerid][1][toy_y] = ClothesData[playerid][clothesToysY][1];
        pToys[playerid][1][toy_z] = ClothesData[playerid][clothesToysZ][1];
        pToys[playerid][1][toy_rx] = ClothesData[playerid][clothesToysRX][1];
        pToys[playerid][1][toy_ry] = ClothesData[playerid][clothesToysRY][1];
        pToys[playerid][1][toy_rz] = ClothesData[playerid][clothesToysRZ][1];
        pToys[playerid][1][toy_sx] = ClothesData[playerid][clothesToysSX][1];
        pToys[playerid][1][toy_sy] = ClothesData[playerid][clothesToysSY][1];
        pToys[playerid][1][toy_sz] = ClothesData[playerid][clothesToysSZ][1];

        pToys[playerid][2][toy_model] = ClothesData[playerid][clothesToys][2];
        pToys[playerid][2][toy_bone] = ClothesData[playerid][clothesBone][2];
        pToys[playerid][2][toy_x] = ClothesData[playerid][clothesToysX][2];
        pToys[playerid][2][toy_y] = ClothesData[playerid][clothesToysY][2];
        pToys[playerid][2][toy_z] = ClothesData[playerid][clothesToysZ][2];
        pToys[playerid][2][toy_rx] = ClothesData[playerid][clothesToysRX][2];
        pToys[playerid][2][toy_ry] = ClothesData[playerid][clothesToysRY][2];
        pToys[playerid][2][toy_rz] = ClothesData[playerid][clothesToysRZ][2];
        pToys[playerid][2][toy_sx] = ClothesData[playerid][clothesToysSX][2];
        pToys[playerid][2][toy_sy] = ClothesData[playerid][clothesToysSY][2];
        pToys[playerid][2][toy_sz] = ClothesData[playerid][clothesToysSZ][2];

        pToys[playerid][3][toy_model] = ClothesData[playerid][clothesToys][3];
        pToys[playerid][3][toy_bone] = ClothesData[playerid][clothesBone][3];
        pToys[playerid][3][toy_x] = ClothesData[playerid][clothesToysX][3];
        pToys[playerid][3][toy_y] = ClothesData[playerid][clothesToysY][3];
        pToys[playerid][3][toy_z] = ClothesData[playerid][clothesToysZ][3];
        pToys[playerid][3][toy_rx] = ClothesData[playerid][clothesToysRX][3];
        pToys[playerid][3][toy_ry] = ClothesData[playerid][clothesToysRY][3];
        pToys[playerid][3][toy_rz] = ClothesData[playerid][clothesToysRZ][3];
        pToys[playerid][3][toy_sx] = ClothesData[playerid][clothesToysSX][3];
        pToys[playerid][3][toy_sy] = ClothesData[playerid][clothesToysSY][3];
        pToys[playerid][3][toy_sz] = ClothesData[playerid][clothesToysSZ][3];
    }
    return 1;
}

forward LoadPlayerClothes(playerid);
public LoadPlayerClothes(playerid)
{
    new rows = cache_num_rows();
    if(rows)
    {
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", ClothesData[playerid][clothesID]);
            cache_get_value_name_int(i, "Owner", ClothesData[playerid][clothesOwnerID]);
            cache_get_value_name(i, "Name", ClothesData[playerid][clothesName]);
            cache_get_value_name_int(i, "Skin", ClothesData[playerid][clothesSkinID]);
            cache_get_value_name_int(i, "Bone0", ClothesData[playerid][clothesBone][0]);
            cache_get_value_name_int(i, "Bone1", ClothesData[playerid][clothesBone][1]);
            cache_get_value_name_int(i, "Bone2", ClothesData[playerid][clothesBone][2]);
            cache_get_value_name_int(i, "Bone3", ClothesData[playerid][clothesBone][3]);

            cache_get_value_name_int(i, "Toys0", ClothesData[playerid][clothesToys][0]);
            cache_get_value_name_int(i, "Toys1", ClothesData[playerid][clothesToys][1]);
            cache_get_value_name_int(i, "Toys2", ClothesData[playerid][clothesToys][2]);
            cache_get_value_name_int(i, "Toys3", ClothesData[playerid][clothesToys][3]);

            cache_get_value_name_float(i, "ToysX_0", ClothesData[playerid][clothesToysX][0]);
            cache_get_value_name_float(i, "ToysY_0", ClothesData[playerid][clothesToysY][0]);
            cache_get_value_name_float(i, "ToysZ_0", ClothesData[playerid][clothesToysZ][0]);
            cache_get_value_name_float(i, "ToysRX_0", ClothesData[playerid][clothesToysRX][0]);
            cache_get_value_name_float(i, "ToysRY_0", ClothesData[playerid][clothesToysRY][0]);
            cache_get_value_name_float(i, "ToysRZ_0", ClothesData[playerid][clothesToysRZ][0]);
            cache_get_value_name_float(i, "ToysSX_0", ClothesData[playerid][clothesToysSX][0]);
            cache_get_value_name_float(i, "ToysSY_0", ClothesData[playerid][clothesToysSY][0]);
            cache_get_value_name_float(i, "ToysSZ_0", ClothesData[playerid][clothesToysSZ][0]);

            cache_get_value_name_float(i, "ToysX_1", ClothesData[playerid][clothesToysX][1]);
            cache_get_value_name_float(i, "ToysY_1", ClothesData[playerid][clothesToysY][1]);
            cache_get_value_name_float(i, "ToysZ_1", ClothesData[playerid][clothesToysZ][1]);
            cache_get_value_name_float(i, "ToysRX_1", ClothesData[playerid][clothesToysRX][1]);
            cache_get_value_name_float(i, "ToysRY_1", ClothesData[playerid][clothesToysRY][1]);
            cache_get_value_name_float(i, "ToysRZ_1", ClothesData[playerid][clothesToysRZ][1]);
            cache_get_value_name_float(i, "ToysSX_1", ClothesData[playerid][clothesToysSX][1]);
            cache_get_value_name_float(i, "ToysSY_1", ClothesData[playerid][clothesToysSY][1]);
            cache_get_value_name_float(i, "ToysSZ_1", ClothesData[playerid][clothesToysSZ][1]);

            cache_get_value_name_float(i, "ToysX_2", ClothesData[playerid][clothesToysX][2]);
            cache_get_value_name_float(i, "ToysY_2", ClothesData[playerid][clothesToysY][2]);
            cache_get_value_name_float(i, "ToysZ_2", ClothesData[playerid][clothesToysZ][2]);
            cache_get_value_name_float(i, "ToysRX_2", ClothesData[playerid][clothesToysRX][2]);
            cache_get_value_name_float(i, "ToysRY_2", ClothesData[playerid][clothesToysRY][2]);
            cache_get_value_name_float(i, "ToysRZ_2", ClothesData[playerid][clothesToysRZ][2]);
            cache_get_value_name_float(i, "ToysSX_2", ClothesData[playerid][clothesToysSX][2]);
            cache_get_value_name_float(i, "ToysSY_2", ClothesData[playerid][clothesToysSY][2]);
            cache_get_value_name_float(i, "ToysSZ_2", ClothesData[playerid][clothesToysSZ][2]);

            cache_get_value_name_float(i, "ToysX_3", ClothesData[playerid][clothesToysX][3]);
            cache_get_value_name_float(i, "ToysY_3", ClothesData[playerid][clothesToysY][3]);
            cache_get_value_name_float(i, "ToysZ_3", ClothesData[playerid][clothesToysZ][3]);
            cache_get_value_name_float(i, "ToysRX_3", ClothesData[playerid][clothesToysRX][3]);
            cache_get_value_name_float(i, "ToysRY_3", ClothesData[playerid][clothesToysRY][3]);
            cache_get_value_name_float(i, "ToysRZ_3", ClothesData[playerid][clothesToysRZ][3]);
            cache_get_value_name_float(i, "ToysSX_3", ClothesData[playerid][clothesToysSX][3]);
            cache_get_value_name_float(i, "ToysSY_3", ClothesData[playerid][clothesToysSY][3]);
            cache_get_value_name_float(i, "ToysSZ_3", ClothesData[playerid][clothesToysSZ][3]);
        }
        ClothesData[playerid][clothesTotal] = rows;
        printf("[Player Clothes] Jumlah total Clothes yang dimuat untuk %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], rows);
    }
    return 1;
}