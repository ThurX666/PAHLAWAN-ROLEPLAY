new Text:ClothesShopTD[23],
    PlayerText:ClothesShopIndexTD[MAX_PLAYERS];

CreateClothesShopTD()
{
    ClothesShopTD[0] = TextDrawCreate(157.000000, 152.000000, "_");
    TextDrawFont(ClothesShopTD[0], true);
    TextDrawLetterSize(ClothesShopTD[0], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[0], 9.500000, 62.000000);
    TextDrawSetOutline(ClothesShopTD[0], true);
    TextDrawSetShadow(ClothesShopTD[0], false);
    TextDrawAlignment(ClothesShopTD[0], 2);
    TextDrawColor(ClothesShopTD[0], -1);
    TextDrawBackgroundColor(ClothesShopTD[0], 255);
    TextDrawBoxColor(ClothesShopTD[0], -7232312);
    TextDrawUseBox(ClothesShopTD[0], true);
    TextDrawSetProportional(ClothesShopTD[0], true);
    TextDrawSetSelectable(ClothesShopTD[0], false);

    ClothesShopTD[1] = TextDrawCreate(157.000000, 174.000000, "_");
    TextDrawFont(ClothesShopTD[1], true);
    TextDrawLetterSize(ClothesShopTD[1], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[1], 9.500000, 62.000000);
    TextDrawSetOutline(ClothesShopTD[1], true);
    TextDrawSetShadow(ClothesShopTD[1], false);
    TextDrawAlignment(ClothesShopTD[1], 2);
    TextDrawColor(ClothesShopTD[1], -1);
    TextDrawBackgroundColor(ClothesShopTD[1], 255);
    TextDrawBoxColor(ClothesShopTD[1], -7232312);
    TextDrawUseBox(ClothesShopTD[1], true);
    TextDrawSetProportional(ClothesShopTD[1], true);
    TextDrawSetSelectable(ClothesShopTD[1], false);

    ClothesShopTD[2] = TextDrawCreate(157.000000, 196.000000, "_");
    TextDrawFont(ClothesShopTD[2], true);
    TextDrawLetterSize(ClothesShopTD[2], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[2], 9.500000, 62.000000);
    TextDrawSetOutline(ClothesShopTD[2], true);
    TextDrawSetShadow(ClothesShopTD[2], false);
    TextDrawAlignment(ClothesShopTD[2], 2);
    TextDrawColor(ClothesShopTD[2], -1);
    TextDrawBackgroundColor(ClothesShopTD[2], 255);
    TextDrawBoxColor(ClothesShopTD[2], -7232312);
    TextDrawUseBox(ClothesShopTD[2], true);
    TextDrawSetProportional(ClothesShopTD[2], true);
    TextDrawSetSelectable(ClothesShopTD[2], false);

    ClothesShopTD[3] = TextDrawCreate(157.000000, 218.000000, "_");
    TextDrawFont(ClothesShopTD[3], true);
    TextDrawLetterSize(ClothesShopTD[3], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[3], 9.500000, 62.000000);
    TextDrawSetOutline(ClothesShopTD[3], true);
    TextDrawSetShadow(ClothesShopTD[3], false);
    TextDrawAlignment(ClothesShopTD[3], 2);
    TextDrawColor(ClothesShopTD[3], -1);
    TextDrawBackgroundColor(ClothesShopTD[3], 255);
    TextDrawBoxColor(ClothesShopTD[3], -7232312);
    TextDrawUseBox(ClothesShopTD[3], true);
    TextDrawSetProportional(ClothesShopTD[3], true);
    TextDrawSetSelectable(ClothesShopTD[3], false);

    ClothesShopTD[4] = TextDrawCreate(157.000000, 240.000000, "_");
    TextDrawFont(ClothesShopTD[4], true);
    TextDrawLetterSize(ClothesShopTD[4], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[4], 9.500000, 62.000000);
    TextDrawSetOutline(ClothesShopTD[4], true);
    TextDrawSetShadow(ClothesShopTD[4], false);
    TextDrawAlignment(ClothesShopTD[4], 2);
    TextDrawColor(ClothesShopTD[4], -1);
    TextDrawBackgroundColor(ClothesShopTD[4], 255);
    TextDrawBoxColor(ClothesShopTD[4], -7232312);
    TextDrawUseBox(ClothesShopTD[4], true);
    TextDrawSetProportional(ClothesShopTD[4], true);
    TextDrawSetSelectable(ClothesShopTD[4], false);

    ClothesShopTD[5] = TextDrawCreate(93.000000, 274.000000, "_");
    TextDrawFont(ClothesShopTD[5], true);
    TextDrawLetterSize(ClothesShopTD[5], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[5], 9.500000, 36.500000);
    TextDrawSetOutline(ClothesShopTD[5], true);
    TextDrawSetShadow(ClothesShopTD[5], false);
    TextDrawAlignment(ClothesShopTD[5], 2);
    TextDrawColor(ClothesShopTD[5], -1);
    TextDrawBackgroundColor(ClothesShopTD[5], 255);
    TextDrawBoxColor(ClothesShopTD[5], -7232312);
    TextDrawUseBox(ClothesShopTD[5], true);
    TextDrawSetProportional(ClothesShopTD[5], true);
    TextDrawSetSelectable(ClothesShopTD[5], false);

    ClothesShopTD[6] = TextDrawCreate(93.000000, 297.000000, "_");
    TextDrawFont(ClothesShopTD[6], true);
    TextDrawLetterSize(ClothesShopTD[6], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[6], 9.500000, 36.500000);
    TextDrawSetOutline(ClothesShopTD[6], true);
    TextDrawSetShadow(ClothesShopTD[6], false);
    TextDrawAlignment(ClothesShopTD[6], 2);
    TextDrawColor(ClothesShopTD[6], -1);
    TextDrawBackgroundColor(ClothesShopTD[6], 255);
    TextDrawBoxColor(ClothesShopTD[6], -7232312);
    TextDrawUseBox(ClothesShopTD[6], true);
    TextDrawSetProportional(ClothesShopTD[6], true);
    TextDrawSetSelectable(ClothesShopTD[6], false);

    ClothesShopTD[7] = TextDrawCreate(221.000000, 274.000000, "_");
    TextDrawFont(ClothesShopTD[7], true);
    TextDrawLetterSize(ClothesShopTD[7], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[7], 9.500000, 36.500000);
    TextDrawSetOutline(ClothesShopTD[7], true);
    TextDrawSetShadow(ClothesShopTD[7], false);
    TextDrawAlignment(ClothesShopTD[7], 2);
    TextDrawColor(ClothesShopTD[7], -1);
    TextDrawBackgroundColor(ClothesShopTD[7], 255);
    TextDrawBoxColor(ClothesShopTD[7], -7232312);
    TextDrawUseBox(ClothesShopTD[7], true);
    TextDrawSetProportional(ClothesShopTD[7], true);
    TextDrawSetSelectable(ClothesShopTD[7], false);

    ClothesShopTD[8] = TextDrawCreate(221.000000, 297.000000, "_");
    TextDrawFont(ClothesShopTD[8], true);
    TextDrawLetterSize(ClothesShopTD[8], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[8], 9.500000, 36.500000);
    TextDrawSetOutline(ClothesShopTD[8], true);
    TextDrawSetShadow(ClothesShopTD[8], false);
    TextDrawAlignment(ClothesShopTD[8], 2);
    TextDrawColor(ClothesShopTD[8], -1);
    TextDrawBackgroundColor(ClothesShopTD[8], 255);
    TextDrawBoxColor(ClothesShopTD[8], -7232312);
    TextDrawUseBox(ClothesShopTD[8], true);
    TextDrawSetProportional(ClothesShopTD[8], true);
    TextDrawSetSelectable(ClothesShopTD[8], false);

    ClothesShopTD[9] = TextDrawCreate(157.000000, 297.000000, "_");
    TextDrawFont(ClothesShopTD[9], true);
    TextDrawLetterSize(ClothesShopTD[9], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[9], 9.500000, 62.000000);
    TextDrawSetOutline(ClothesShopTD[9], true);
    TextDrawSetShadow(ClothesShopTD[9], false);
    TextDrawAlignment(ClothesShopTD[9], 2);
    TextDrawColor(ClothesShopTD[9], -1);
    TextDrawBackgroundColor(ClothesShopTD[9], 255);
    TextDrawBoxColor(ClothesShopTD[9], -7232312);
    TextDrawUseBox(ClothesShopTD[9], true);
    TextDrawSetProportional(ClothesShopTD[9], true);
    TextDrawSetSelectable(ClothesShopTD[9], false);

    ClothesShopTD[10] = TextDrawCreate(157.000000, 321.000000, "_");
    TextDrawFont(ClothesShopTD[10], true);
    TextDrawLetterSize(ClothesShopTD[10], 0.600000, 1.649000);
    TextDrawTextSize(ClothesShopTD[10], 9.500000, 62.000000);
    TextDrawSetOutline(ClothesShopTD[10], true);
    TextDrawSetShadow(ClothesShopTD[10], false);
    TextDrawAlignment(ClothesShopTD[10], 2);
    TextDrawColor(ClothesShopTD[10], -1);
    TextDrawBackgroundColor(ClothesShopTD[10], 255);
    TextDrawBoxColor(ClothesShopTD[10], -7232312);
    TextDrawUseBox(ClothesShopTD[10], true);
    TextDrawSetProportional(ClothesShopTD[10], true);
    TextDrawSetSelectable(ClothesShopTD[10], false);

    ClothesShopTD[11] = TextDrawCreate(143.000000, 152.000000, "Clothes");
    TextDrawFont(ClothesShopTD[11], true);
    TextDrawLetterSize(ClothesShopTD[11], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[11], 188.000000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[11], false);
    TextDrawSetShadow(ClothesShopTD[11], false);
    TextDrawAlignment(ClothesShopTD[11], true);
    TextDrawColor(ClothesShopTD[11], -1);
    TextDrawBackgroundColor(ClothesShopTD[11], 255);
    TextDrawBoxColor(ClothesShopTD[11], -7232312);
    TextDrawUseBox(ClothesShopTD[11], false);
    TextDrawSetProportional(ClothesShopTD[11], true);
    TextDrawSetSelectable(ClothesShopTD[11], true);

    ClothesShopTD[12] = TextDrawCreate(139.000000, 174.000000, "TOPI/HELM");
    TextDrawFont(ClothesShopTD[12], true);
    TextDrawLetterSize(ClothesShopTD[12], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[12], 188.000000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[12], false);
    TextDrawSetShadow(ClothesShopTD[12], false);
    TextDrawAlignment(ClothesShopTD[12], true);
    TextDrawColor(ClothesShopTD[12], -1);
    TextDrawBackgroundColor(ClothesShopTD[12], 255);
    TextDrawBoxColor(ClothesShopTD[12], -7232312);
    TextDrawUseBox(ClothesShopTD[12], false);
    TextDrawSetProportional(ClothesShopTD[12], true);
    TextDrawSetSelectable(ClothesShopTD[12], true);

    ClothesShopTD[13] = TextDrawCreate(139.000000, 196.000000, "KACAMATA");
    TextDrawFont(ClothesShopTD[13], true);
    TextDrawLetterSize(ClothesShopTD[13], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[13], 188.000000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[13], false);
    TextDrawSetShadow(ClothesShopTD[13], false);
    TextDrawAlignment(ClothesShopTD[13], true);
    TextDrawColor(ClothesShopTD[13], -1);
    TextDrawBackgroundColor(ClothesShopTD[13], 255);
    TextDrawBoxColor(ClothesShopTD[13], -7232312);
    TextDrawUseBox(ClothesShopTD[13], false);
    TextDrawSetProportional(ClothesShopTD[13], true);
    TextDrawSetSelectable(ClothesShopTD[13], true);

    ClothesShopTD[14] = TextDrawCreate(139.000000, 218.000000, "AKSESORIS");
    TextDrawFont(ClothesShopTD[14], true);
    TextDrawLetterSize(ClothesShopTD[14], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[14], 188.000000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[14], false);
    TextDrawSetShadow(ClothesShopTD[14], false);
    TextDrawAlignment(ClothesShopTD[14], true);
    TextDrawColor(ClothesShopTD[14], -1);
    TextDrawBackgroundColor(ClothesShopTD[14], 255);
    TextDrawBoxColor(ClothesShopTD[14], -7232312);
    TextDrawUseBox(ClothesShopTD[14], false);
    TextDrawSetProportional(ClothesShopTD[14], true);
    TextDrawSetSelectable(ClothesShopTD[14], true);

    ClothesShopTD[15] = TextDrawCreate(139.000000, 240.000000, "TAS/KOPER");
    TextDrawFont(ClothesShopTD[15], true);
    TextDrawLetterSize(ClothesShopTD[15], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[15], 188.000000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[15], false);
    TextDrawSetShadow(ClothesShopTD[15], false);
    TextDrawAlignment(ClothesShopTD[15], true);
    TextDrawColor(ClothesShopTD[15], -1);
    TextDrawBackgroundColor(ClothesShopTD[15], 255);
    TextDrawBoxColor(ClothesShopTD[15], -7232312);
    TextDrawUseBox(ClothesShopTD[15], false);
    TextDrawSetProportional(ClothesShopTD[15], true);
    TextDrawSetSelectable(ClothesShopTD[15], true);

    ClothesShopTD[16] = TextDrawCreate(217.000000, 297.000000, ">>");
    TextDrawFont(ClothesShopTD[16], true);
    TextDrawLetterSize(ClothesShopTD[16], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[16], 238.500000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[16], false);
    TextDrawSetShadow(ClothesShopTD[16], false);
    TextDrawAlignment(ClothesShopTD[16], true);
    TextDrawColor(ClothesShopTD[16], -1);
    TextDrawBackgroundColor(ClothesShopTD[16], 255);
    TextDrawBoxColor(ClothesShopTD[16], -7232312);
    TextDrawUseBox(ClothesShopTD[16], false);
    TextDrawSetProportional(ClothesShopTD[16], true);
    TextDrawSetSelectable(ClothesShopTD[16], true);

    ClothesShopTD[17] = TextDrawCreate(88.000000, 297.000000, "<<");
    TextDrawFont(ClothesShopTD[17], true);
    TextDrawLetterSize(ClothesShopTD[17], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[17], 110.000000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[17], false);
    TextDrawSetShadow(ClothesShopTD[17], false);
    TextDrawAlignment(ClothesShopTD[17], true);
    TextDrawColor(ClothesShopTD[17], -1);
    TextDrawBackgroundColor(ClothesShopTD[17], 255);
    TextDrawBoxColor(ClothesShopTD[17], -7232312);
    TextDrawUseBox(ClothesShopTD[17], false);
    TextDrawSetProportional(ClothesShopTD[17], true);
    TextDrawSetSelectable(ClothesShopTD[17], true);

    ClothesShopTD[18] = TextDrawCreate(149.000000, 297.000000, "BELI");
    TextDrawFont(ClothesShopTD[18], true);
    TextDrawLetterSize(ClothesShopTD[18], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[18], 188.000000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[18], false);
    TextDrawSetShadow(ClothesShopTD[18], false);
    TextDrawAlignment(ClothesShopTD[18], true);
    TextDrawColor(ClothesShopTD[18], -1);
    TextDrawBackgroundColor(ClothesShopTD[18], 255);
    TextDrawBoxColor(ClothesShopTD[18], -7232312);
    TextDrawUseBox(ClothesShopTD[18], false);
    TextDrawSetProportional(ClothesShopTD[18], true);
    TextDrawSetSelectable(ClothesShopTD[18], true);

    ClothesShopTD[19] = TextDrawCreate(146.500000, 321.000000, "Batal");
    TextDrawFont(ClothesShopTD[19], true);
    TextDrawLetterSize(ClothesShopTD[19], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[19], 188.000000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[19], false);
    TextDrawSetShadow(ClothesShopTD[19], false);
    TextDrawAlignment(ClothesShopTD[19], true);
    TextDrawColor(ClothesShopTD[19], -1);
    TextDrawBackgroundColor(ClothesShopTD[19], 255);
    TextDrawBoxColor(ClothesShopTD[19], -7232312);
    TextDrawUseBox(ClothesShopTD[19], false);
    TextDrawSetProportional(ClothesShopTD[19], true);
    TextDrawSetSelectable(ClothesShopTD[19], true);

    ClothesShopTD[20] = TextDrawCreate(212.000000, 274.000000, "ROT >");
    TextDrawFont(ClothesShopTD[20], true);
    TextDrawLetterSize(ClothesShopTD[20], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[20], 238.500000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[20], false);
    TextDrawSetShadow(ClothesShopTD[20], false);
    TextDrawAlignment(ClothesShopTD[20], true);
    TextDrawColor(ClothesShopTD[20], -1);
    TextDrawBackgroundColor(ClothesShopTD[20], 255);
    TextDrawBoxColor(ClothesShopTD[20], -7232312);
    TextDrawUseBox(ClothesShopTD[20], false);
    TextDrawSetProportional(ClothesShopTD[20], true);
    TextDrawSetSelectable(ClothesShopTD[20], true);

    ClothesShopTD[21] = TextDrawCreate(82.000000, 274.000000, "< ROT");
    TextDrawFont(ClothesShopTD[21], true);
    TextDrawLetterSize(ClothesShopTD[21], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[21], 111.000000, 10.000000);
    TextDrawSetOutline(ClothesShopTD[21], false);
    TextDrawSetShadow(ClothesShopTD[21], false);
    TextDrawAlignment(ClothesShopTD[21], true);
    TextDrawColor(ClothesShopTD[21], -1);
    TextDrawBackgroundColor(ClothesShopTD[21], 255);
    TextDrawBoxColor(ClothesShopTD[21], -7232312);
    TextDrawUseBox(ClothesShopTD[21], false);
    TextDrawSetProportional(ClothesShopTD[21], true);
    TextDrawSetSelectable(ClothesShopTD[21], true);

    ClothesShopTD[22] = TextDrawCreate(255.000000, 405.000000, "Kembali");
    TextDrawFont(ClothesShopTD[22], true);
    TextDrawLetterSize(ClothesShopTD[22], 0.204162, 1.649999);
    TextDrawTextSize(ClothesShopTD[22], 9.500000, 62.000000);
    TextDrawSetOutline(ClothesShopTD[22], false);
    TextDrawSetShadow(ClothesShopTD[22], false);
    TextDrawAlignment(ClothesShopTD[22], 2);
    TextDrawColor(ClothesShopTD[22], -1);
    TextDrawBackgroundColor(ClothesShopTD[22], 255);
    TextDrawBoxColor(ClothesShopTD[22], -7232312);
    TextDrawUseBox(ClothesShopTD[22], true);
    TextDrawSetProportional(ClothesShopTD[22], true);
    TextDrawSetSelectable(ClothesShopTD[22], true);
}

CreateClothesShopIndexTD(playerid)
{
    ClothesShopIndexTD[playerid] = CreatePlayerTextDraw(playerid, 318.000000, 405.000000, "256/256");
    PlayerTextDrawFont(playerid, ClothesShopIndexTD[playerid], true);
    PlayerTextDrawLetterSize(playerid, ClothesShopIndexTD[playerid], 0.204164, 1.649999);
    PlayerTextDrawTextSize(playerid, ClothesShopIndexTD[playerid], 9.500000, 36.500000);
    PlayerTextDrawSetOutline(playerid, ClothesShopIndexTD[playerid], false);
    PlayerTextDrawSetShadow(playerid, ClothesShopIndexTD[playerid], false);
    PlayerTextDrawAlignment(playerid, ClothesShopIndexTD[playerid], 2);
    PlayerTextDrawColor(playerid, ClothesShopIndexTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ClothesShopIndexTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, ClothesShopIndexTD[playerid], -7232312);
    PlayerTextDrawUseBox(playerid, ClothesShopIndexTD[playerid], true);
    PlayerTextDrawSetProportional(playerid, ClothesShopIndexTD[playerid], true);
    PlayerTextDrawSetSelectable(playerid, ClothesShopIndexTD[playerid], false);
}

/*
UNTUK KAMERA BELI TOPI

static Float:buyx, Float:buyy, Float:buyz;
GetPlayerPos(playerid, buyx, buyy, buyz);

SetPlayerCameraPos(playerid,buyx,buyy+1.0,buyz+0.7);
SetPlayerCameraLookAt(playerid,buyx+0.2,buyy+0.2,buyz+0.7);
*/

ShowClothesMainMenuTD(playerid)
{
    for(new x; x < 23; x++)
    {
        switch(x)
        {
            case 5, 6.. 9, 16.. 18, 20.. 23: 
            {
                continue;
            }
        }
        TextDrawShowForPlayer(playerid, ClothesShopTD[x]);
    }
    SelectTextDraw(playerid, 0xff91a4cc);

    static Float:buyx, Float:buyy, Float:buyz;
    GetPlayerPos(playerid, buyx, buyy, buyz);

    SetPlayerCameraPos(playerid,buyx,buyy+2.5,buyz);
    SetPlayerCameraLookAt(playerid,buyx+0.60,buyy+0.2,buyz);
    SetPlayerFacingAngle(playerid, buyy+2.5);

    SetPVarInt(playerid, "ClothesShopChoosenID", -1);
    SetPVarInt(playerid, "IsPlayerPurchasedToys", -1);

    SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Gunakan "CMDEA"'/cursor' "WHITE"jika mouse hilang dari layar/textdraw tidak bisa ditekan!");
}

ShowClothesBuyClothesTD(playerid) //beli baju
{
    for(new x; x < 23; x++)
    {
        TextDrawShowForPlayer(playerid, ClothesShopTD[x]);

        switch(x)
        {
            case 1.. 4, 10, 12.. 15, 19: 
            {
                TextDrawHideForPlayer(playerid, ClothesShopTD[x]);
            }
        }
    }
    PlayerTextDrawShow(playerid, ClothesShopIndexTD[playerid]);

    static Float:buyx, Float:buyy, Float:buyz;
    GetPlayerPos(playerid, buyx, buyy, buyz);

    SetPlayerCameraPos(playerid,buyx,buyy+1.85,buyz+0.5);
    SetPlayerCameraLookAt(playerid,buyx+0.55,buyy+0.2,buyz+0.5);
}

ShowClothesBuyHatTD(playerid) //beli topi
{
    for(new x; x < 23; x++)
    {
        TextDrawShowForPlayer(playerid, ClothesShopTD[x]);

        switch(x)
        {
            case 0, 11, 2.. 4, 10, 13.. 15, 19: 
            {
                TextDrawHideForPlayer(playerid, ClothesShopTD[x]);
            }
        }
    }
    PlayerTextDrawShow(playerid, ClothesShopIndexTD[playerid]);

    static Float:buyx, Float:buyy, Float:buyz;
    GetPlayerPos(playerid, buyx, buyy, buyz);

    SetPlayerCameraPos(playerid,buyx,buyy+1.5,buyz+0.7);
    SetPlayerCameraLookAt(playerid,buyx+0.37,buyy+0.2,buyz+0.7);
}

ShowClothesBuyGlasesTD(playerid) //beli kacamata
{
    for(new x; x < 23; x++)
    {
        TextDrawShowForPlayer(playerid, ClothesShopTD[x]);

        switch(x)
        {
            case 0, 1, 3, 4, 10, 11, 12, 14, 15, 19: 
            {
                TextDrawHideForPlayer(playerid, ClothesShopTD[x]);
            }
        }
    }
    PlayerTextDrawShow(playerid, ClothesShopIndexTD[playerid]);

    static Float:buyx, Float:buyy, Float:buyz;
    GetPlayerPos(playerid, buyx, buyy, buyz);

    SetPlayerCameraPos(playerid,buyx,buyy+1.0,buyz+0.8);
    SetPlayerCameraLookAt(playerid,buyx+0.37,buyy,buyz+0.8);
}

ShowClothesBuyAccessoriesTD(playerid) //beli aksesoris
{
    for(new x; x < 23; x++)
    {
        TextDrawShowForPlayer(playerid, ClothesShopTD[x]);

        switch(x)
        {
            case 0.. 2, 4, 10, 11.. 13, 15, 19: 
            {
                TextDrawHideForPlayer(playerid, ClothesShopTD[x]);
            }
        }
    }
    PlayerTextDrawShow(playerid, ClothesShopIndexTD[playerid]);

    static Float:buyx, Float:buyy, Float:buyz;
    GetPlayerPos(playerid, buyx, buyy, buyz);

    SetPlayerCameraPos(playerid,buyx,buyy+1.85,buyz+0.5);
    SetPlayerCameraLookAt(playerid,buyx+0.55,buyy+0.2,buyz+0.5);
}

ShowClothesBuyBagTD(playerid) //beli tas/koper
{
    for(new x; x < 23; x++)
    {
        TextDrawShowForPlayer(playerid, ClothesShopTD[x]);

        switch(x)
        {
            case 0.. 3, 10, 11.. 14, 15, 19: 
            {
                TextDrawHideForPlayer(playerid, ClothesShopTD[x]);
            }
        }
    }
    PlayerTextDrawShow(playerid, ClothesShopIndexTD[playerid]);

    static Float:buyx, Float:buyy, Float:buyz;
    GetPlayerPos(playerid, buyx, buyy, buyz);

    SetPlayerCameraPos(playerid,buyx,buyy+1.85,buyz+0.5);
    SetPlayerCameraLookAt(playerid,buyx+0.55,buyy+0.2,buyz+0.5);
}

HideClothesShopTD(playerid)
{
    for(new x; x < 23; x++)
    {
        TextDrawHideForPlayer(playerid, ClothesShopTD[x]);
    }
    CancelSelectTextDraw(playerid);
    PlayerTextDrawHide(playerid, ClothesShopIndexTD[playerid]);
}