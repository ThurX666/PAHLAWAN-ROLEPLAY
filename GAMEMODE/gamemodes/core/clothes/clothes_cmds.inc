YCMD:sc(playerid, params[], help)
{
    new cname[34];
    if(sscanf(params, "s[34]", cname)) return SUM(playerid, "/sc [nama pakaian]");
    
    if(ClothesData[playerid][clothesTotal] >= 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pakaian yang tersimpan telah mencapai batas maksimum!");

    ClothesData[playerid][clothesOwnerID] = AccountData[playerid][pID];
    strcopy(ClothesData[playerid][clothesName], cname);
    ClothesData[playerid][clothesSkinID] = GetPlayerSkin(playerid);

    ClothesData[playerid][clothesToys][0] = pToys[playerid][0][toy_model];
    ClothesData[playerid][clothesBone][0] = pToys[playerid][0][toy_bone];
    ClothesData[playerid][clothesToysX][0] = pToys[playerid][0][toy_x];
    ClothesData[playerid][clothesToysY][0] = pToys[playerid][0][toy_y];
    ClothesData[playerid][clothesToysZ][0] = pToys[playerid][0][toy_z];
    ClothesData[playerid][clothesToysRX][0] = pToys[playerid][0][toy_rx];
    ClothesData[playerid][clothesToysRY][0] = pToys[playerid][0][toy_ry];
    ClothesData[playerid][clothesToysRZ][0] = pToys[playerid][0][toy_rz];
    ClothesData[playerid][clothesToysSX][0] = pToys[playerid][0][toy_sx];
    ClothesData[playerid][clothesToysSY][0] = pToys[playerid][0][toy_sy];
    ClothesData[playerid][clothesToysSZ][0] = pToys[playerid][0][toy_sz];

    ClothesData[playerid][clothesToys][1] = pToys[playerid][1][toy_model];
    ClothesData[playerid][clothesBone][1] = pToys[playerid][1][toy_bone];
    ClothesData[playerid][clothesToysX][1] = pToys[playerid][1][toy_x];
    ClothesData[playerid][clothesToysY][1] = pToys[playerid][1][toy_y];
    ClothesData[playerid][clothesToysZ][1] = pToys[playerid][1][toy_z];
    ClothesData[playerid][clothesToysRX][1] = pToys[playerid][1][toy_rx];
    ClothesData[playerid][clothesToysRY][1] = pToys[playerid][1][toy_ry];
    ClothesData[playerid][clothesToysRZ][1] = pToys[playerid][1][toy_rz];
    ClothesData[playerid][clothesToysSX][1] = pToys[playerid][1][toy_sx];
    ClothesData[playerid][clothesToysSY][1] = pToys[playerid][1][toy_sy];
    ClothesData[playerid][clothesToysSZ][1] = pToys[playerid][1][toy_sz];

    ClothesData[playerid][clothesToys][2] = pToys[playerid][2][toy_model];
    ClothesData[playerid][clothesBone][2] = pToys[playerid][2][toy_bone];
    ClothesData[playerid][clothesToysX][2] = pToys[playerid][2][toy_x];
    ClothesData[playerid][clothesToysY][2] = pToys[playerid][2][toy_y];
    ClothesData[playerid][clothesToysZ][2] = pToys[playerid][2][toy_z];
    ClothesData[playerid][clothesToysRX][2] = pToys[playerid][2][toy_rx];
    ClothesData[playerid][clothesToysRY][2] = pToys[playerid][2][toy_ry];
    ClothesData[playerid][clothesToysRZ][2] = pToys[playerid][2][toy_rz];
    ClothesData[playerid][clothesToysSX][2] = pToys[playerid][2][toy_sx];
    ClothesData[playerid][clothesToysSY][2] = pToys[playerid][2][toy_sy];
    ClothesData[playerid][clothesToysSZ][2] = pToys[playerid][2][toy_sz];

    ClothesData[playerid][clothesToys][3] = pToys[playerid][3][toy_model];
    ClothesData[playerid][clothesBone][3] = pToys[playerid][3][toy_bone];
    ClothesData[playerid][clothesToysX][3] = pToys[playerid][3][toy_x];
    ClothesData[playerid][clothesToysY][3] = pToys[playerid][3][toy_y];
    ClothesData[playerid][clothesToysZ][3] = pToys[playerid][3][toy_z];
    ClothesData[playerid][clothesToysRX][3] = pToys[playerid][3][toy_rx];
    ClothesData[playerid][clothesToysRY][3] = pToys[playerid][3][toy_ry];
    ClothesData[playerid][clothesToysRZ][3] = pToys[playerid][3][toy_rz];
    ClothesData[playerid][clothesToysSX][3] = pToys[playerid][3][toy_sx];
    ClothesData[playerid][clothesToysSY][3] = pToys[playerid][3][toy_sy];
    ClothesData[playerid][clothesToysSZ][3] = pToys[playerid][3][toy_sz];

    new sstrs[1218];
    mysql_format(g_SQL, sstrs, sizeof(sstrs), "INSERT INTO `player_clothes` SET \
    `Owner`=%d, \
    `Name`='%e', \
    `Skin`=%d, \
    `Toys0`=%d, \
    `Bone0`=%d, \
    `ToysX_0`='%.3f', \
    `ToysY_0`='%.3f', \
    `ToysZ_0`='%.3f', \
    `ToysRX_0`='%.3f', \
    `ToysRY_0`='%.3f', \
    `ToysRZ_0`='%.3f', \
    `ToysSX_0`='%.3f', \
    `ToysSY_0`='%.3f', \
    `ToysSZ_0`='%.3f', \
    `Toys1`=%d, \
    `Bone1`=%d, \
    `ToysX_1`='%.3f', \
    `ToysY_1`='%.3f', \
    `ToysZ_1`='%.3f', \
    `ToysRX_1`='%.3f', \
    `ToysRY_1`='%.3f', \
    `ToysRZ_1`='%.3f', \
    `ToysSX_1`='%.3f', \
    `ToysSY_1`='%.3f', \
    `ToysSZ_1`='%.3f', \
    `Toys2`=%d, \
    `Bone2`=%d, \
    `ToysX_2`='%.3f', \
    `ToysY_2`='%.3f', \
    `ToysZ_2`='%.3f', \
    `ToysRX_2`='%.3f', \
    `ToysRY_2`='%.3f', \
    `ToysRZ_2`='%.3f', \
    `ToysSX_2`='%.3f', \
    `ToysSY_2`='%.3f', \
    `ToysSZ_2`='%.3f', \
    `Toys3`=%d, \
    `Bone3`=%d, \
    `ToysX_3`='%.3f', \
    `ToysY_3`='%.3f', \
    `ToysZ_3`='%.3f', \
    `ToysRX_3`='%.3f', \
    `ToysRY_3`='%.3f', \
    `ToysRZ_3`='%.3f', \
    `ToysSX_3`='%.3f', \
    `ToysSY_3`='%.3f', \
    `ToysSZ_3`='%.3f'", AccountData[playerid][pID], ClothesData[playerid][clothesName], ClothesData[playerid][clothesSkinID], 
    ClothesData[playerid][clothesToys][0], ClothesData[playerid][clothesBone][0], ClothesData[playerid][clothesToysX][0], ClothesData[playerid][clothesToysY][0], 
    ClothesData[playerid][clothesToysZ][0],  ClothesData[playerid][clothesToysRX][0],  ClothesData[playerid][clothesToysRY][0],  
    ClothesData[playerid][clothesToysRZ][0],  ClothesData[playerid][clothesToysSX][0],  ClothesData[playerid][clothesToysSY][0], ClothesData[playerid][clothesToysSZ][0], 
    ClothesData[playerid][clothesToys][1], ClothesData[playerid][clothesBone][1], ClothesData[playerid][clothesToysX][1], ClothesData[playerid][clothesToysY][1], 
    ClothesData[playerid][clothesToysZ][1],  ClothesData[playerid][clothesToysRX][1],  ClothesData[playerid][clothesToysRY][1],  
    ClothesData[playerid][clothesToysRZ][1],  ClothesData[playerid][clothesToysSX][1],  ClothesData[playerid][clothesToysSY][1], ClothesData[playerid][clothesToysSZ][1], 
    ClothesData[playerid][clothesToys][2], ClothesData[playerid][clothesBone][2], ClothesData[playerid][clothesToysX][2], ClothesData[playerid][clothesToysY][2], 
    ClothesData[playerid][clothesToysZ][2],  ClothesData[playerid][clothesToysRX][2],  ClothesData[playerid][clothesToysRY][2],  
    ClothesData[playerid][clothesToysRZ][2],  ClothesData[playerid][clothesToysSX][2],  ClothesData[playerid][clothesToysSY][2], ClothesData[playerid][clothesToysSZ][2], 
    ClothesData[playerid][clothesToys][3], ClothesData[playerid][clothesBone][3], ClothesData[playerid][clothesToysX][3], ClothesData[playerid][clothesToysY][3], 
    ClothesData[playerid][clothesToysZ][3],  ClothesData[playerid][clothesToysRX][3],  ClothesData[playerid][clothesToysRY][3],  
    ClothesData[playerid][clothesToysRZ][3],  ClothesData[playerid][clothesToysSX][3],  ClothesData[playerid][clothesToysSY][3], ClothesData[playerid][clothesToysSZ][3]);
    mysql_pquery(g_SQL, sstrs, "OnPlayerSaveClothes", "i", playerid);
    return 1;
}