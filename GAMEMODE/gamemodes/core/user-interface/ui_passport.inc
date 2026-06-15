new Text:PassportCoverTD[5],
    PlayerText:PlayerPassportTD[MAX_PLAYERS][9],
    Text:PassportTD[27];

CreatePassportTextdraw()
{
    PassportTD[0] = TextDrawCreate(323.000000, 156.000000, "_");
    TextDrawFont(PassportTD[0], 1);
    TextDrawLetterSize(PassportTD[0], 0.600000, 27.299959);
    TextDrawTextSize(PassportTD[0], 298.500000, 302.500000);
    TextDrawSetOutline(PassportTD[0], 1);
    TextDrawSetShadow(PassportTD[0], 0);
    TextDrawAlignment(PassportTD[0], 2);
    TextDrawColor(PassportTD[0], -1);
    TextDrawBackgroundColor(PassportTD[0], 255);
    TextDrawBoxColor(PassportTD[0], 1296911871);
    TextDrawUseBox(PassportTD[0], 1);
    TextDrawSetProportional(PassportTD[0], 1);
    TextDrawSetSelectable(PassportTD[0], 0);

    PassportTD[1] = TextDrawCreate(323.000000, 158.000000, "_");
    TextDrawFont(PassportTD[1], 1);
    TextDrawLetterSize(PassportTD[1], 0.600000, 26.849966);
    TextDrawTextSize(PassportTD[1], 298.500000, 299.000000);
    TextDrawSetOutline(PassportTD[1], 1);
    TextDrawSetShadow(PassportTD[1], 0);
    TextDrawAlignment(PassportTD[1], 2);
    TextDrawColor(PassportTD[1], -1);
    TextDrawBackgroundColor(PassportTD[1], 255);
    TextDrawBoxColor(PassportTD[1], 52242943);
    TextDrawUseBox(PassportTD[1], 1);
    TextDrawSetProportional(PassportTD[1], 1);
    TextDrawSetSelectable(PassportTD[1], 0);

    PassportTD[2] = TextDrawCreate(266.000000, 169.000000, "PEMERINTAH KOTA PAHLAWAN");
    TextDrawFont(PassportTD[2], 1);
    TextDrawLetterSize(PassportTD[2], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[2], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[2], 0);
    TextDrawSetShadow(PassportTD[2], 0);
    TextDrawAlignment(PassportTD[2], 1);
    TextDrawColor(PassportTD[2], -625251585);
    TextDrawBackgroundColor(PassportTD[2], 255);
    TextDrawBoxColor(PassportTD[2], 50);
    TextDrawUseBox(PassportTD[2], 0);
    TextDrawSetProportional(PassportTD[2], 1);
    TextDrawSetSelectable(PassportTD[2], 0);

    PassportTD[3] = TextDrawCreate(272.000000, 185.000000, "PASSPORT INTERNATIONAL");
    TextDrawFont(PassportTD[3], 1);
    TextDrawLetterSize(PassportTD[3], 0.220832, 1.450000);
    TextDrawTextSize(PassportTD[3], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[3], 0);
    TextDrawSetShadow(PassportTD[3], 0);
    TextDrawAlignment(PassportTD[3], 1);
    TextDrawColor(PassportTD[3], -625251585);
    TextDrawBackgroundColor(PassportTD[3], 255);
    TextDrawBoxColor(PassportTD[3], 50);
    TextDrawUseBox(PassportTD[3], 0);
    TextDrawSetProportional(PassportTD[3], 1);
    TextDrawSetSelectable(PassportTD[3], 0);

    PassportTD[4] = TextDrawCreate(323.000000, 213.000000, "_");
    TextDrawFont(PassportTD[4], 1);
    TextDrawLetterSize(PassportTD[4], 0.600000, -0.200001);
    TextDrawTextSize(PassportTD[4], 298.500000, 299.000000);
    TextDrawSetOutline(PassportTD[4], 1);
    TextDrawSetShadow(PassportTD[4], 0);
    TextDrawAlignment(PassportTD[4], 2);
    TextDrawColor(PassportTD[4], -1);
    TextDrawBackgroundColor(PassportTD[4], 255);
    TextDrawBoxColor(PassportTD[4], 1296911871);
    TextDrawUseBox(PassportTD[4], 1);
    TextDrawSetProportional(PassportTD[4], 1);
    TextDrawSetSelectable(PassportTD[4], 0);

    PassportTD[5] = TextDrawCreate(323.000000, 214.500000, "_");
    TextDrawFont(PassportTD[5], 1);
    TextDrawLetterSize(PassportTD[5], 0.600000, 18.149963);
    TextDrawTextSize(PassportTD[5], 298.500000, 299.000000);
    TextDrawSetOutline(PassportTD[5], 1);
    TextDrawSetShadow(PassportTD[5], 0);
    TextDrawAlignment(PassportTD[5], 2);
    TextDrawColor(PassportTD[5], -1);
    TextDrawBackgroundColor(PassportTD[5], 255);
    TextDrawBoxColor(PassportTD[5], -625251585);
    TextDrawUseBox(PassportTD[5], 1);
    TextDrawSetProportional(PassportTD[5], 1);
    TextDrawSetSelectable(PassportTD[5], 0);

    PassportTD[6] = TextDrawCreate(189.000000, 218.000000, "Sex");
    TextDrawFont(PassportTD[6], 1);
    TextDrawLetterSize(PassportTD[6], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[6], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[6], 0);
    TextDrawSetShadow(PassportTD[6], 0);
    TextDrawAlignment(PassportTD[6], 1);
    TextDrawColor(PassportTD[6], 255);
    TextDrawBackgroundColor(PassportTD[6], 255);
    TextDrawBoxColor(PassportTD[6], 50);
    TextDrawUseBox(PassportTD[6], 0);
    TextDrawSetProportional(PassportTD[6], 1);
    TextDrawSetSelectable(PassportTD[6], 0);

    PassportTD[7] = TextDrawCreate(287.000000, 341.000000, "Tanggal lahir");
    TextDrawFont(PassportTD[7], 1);
    TextDrawLetterSize(PassportTD[7], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[7], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[7], 0);
    TextDrawSetShadow(PassportTD[7], 0);
    TextDrawAlignment(PassportTD[7], 1);
    TextDrawColor(PassportTD[7], 255);
    TextDrawBackgroundColor(PassportTD[7], 255);
    TextDrawBoxColor(PassportTD[7], 50);
    TextDrawUseBox(PassportTD[7], 0);
    TextDrawSetProportional(PassportTD[7], 1);
    TextDrawSetSelectable(PassportTD[7], 0);

    PassportTD[8] = TextDrawCreate(251.000000, 218.000000, "Type");
    TextDrawFont(PassportTD[8], 1);
    TextDrawLetterSize(PassportTD[8], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[8], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[8], 0);
    TextDrawSetShadow(PassportTD[8], 0);
    TextDrawAlignment(PassportTD[8], 1);
    TextDrawColor(PassportTD[8], 255);
    TextDrawBackgroundColor(PassportTD[8], 255);
    TextDrawBoxColor(PassportTD[8], 50);
    TextDrawUseBox(PassportTD[8], 0);
    TextDrawSetProportional(PassportTD[8], 1);
    TextDrawSetSelectable(PassportTD[8], 0);

    PassportTD[9] = TextDrawCreate(239.000000, 245.000000, "Permanent");
    TextDrawFont(PassportTD[9], 1);
    TextDrawLetterSize(PassportTD[9], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[9], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[9], 0);
    TextDrawSetShadow(PassportTD[9], 0);
    TextDrawAlignment(PassportTD[9], 1);
    TextDrawColor(PassportTD[9], 1296911871);
    TextDrawBackgroundColor(PassportTD[9], 255);
    TextDrawBoxColor(PassportTD[9], 50);
    TextDrawUseBox(PassportTD[9], 0);
    TextDrawSetProportional(PassportTD[9], 1);
    TextDrawSetSelectable(PassportTD[9], 0);

    PassportTD[10] = TextDrawCreate(308.000000, 230.000000, "Masukkan nama depan & belakang (3 - 20 karakter)");
    TextDrawFont(PassportTD[10], 1);
    TextDrawLetterSize(PassportTD[10], 0.162496, 1.100000);
    TextDrawTextSize(PassportTD[10], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[10], 0);
    TextDrawSetShadow(PassportTD[10], 0);
    TextDrawAlignment(PassportTD[10], 1);
    TextDrawColor(PassportTD[10], 255);
    TextDrawBackgroundColor(PassportTD[10], 255);
    TextDrawBoxColor(PassportTD[10], 50);
    TextDrawUseBox(PassportTD[10], 0);
    TextDrawSetProportional(PassportTD[10], 1);
    TextDrawSetSelectable(PassportTD[10], 0);

    PassportTD[11] = TextDrawCreate(308.000000, 242.000000, "Isi semua kolom yang diminta!");
    TextDrawFont(PassportTD[11], 1);
    TextDrawLetterSize(PassportTD[11], 0.162496, 1.100000);
    TextDrawTextSize(PassportTD[11], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[11], 0);
    TextDrawSetShadow(PassportTD[11], 0);
    TextDrawAlignment(PassportTD[11], 1);
    TextDrawColor(PassportTD[11], 255);
    TextDrawBackgroundColor(PassportTD[11], 255);
    TextDrawBoxColor(PassportTD[11], 50);
    TextDrawUseBox(PassportTD[11], 0);
    TextDrawSetProportional(PassportTD[11], 1);
    TextDrawSetSelectable(PassportTD[11], 0);

    PassportTD[12] = TextDrawCreate(287.000000, 281.000000, "Nama depan");
    TextDrawFont(PassportTD[12], 1);
    TextDrawLetterSize(PassportTD[12], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[12], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[12], 0);
    TextDrawSetShadow(PassportTD[12], 0);
    TextDrawAlignment(PassportTD[12], 1);
    TextDrawColor(PassportTD[12], 255);
    TextDrawBackgroundColor(PassportTD[12], 255);
    TextDrawBoxColor(PassportTD[12], 50);
    TextDrawUseBox(PassportTD[12], 0);
    TextDrawSetProportional(PassportTD[12], 1);
    TextDrawSetSelectable(PassportTD[12], 0);

    PassportTD[13] = TextDrawCreate(287.000000, 312.000000, "Nama belakang");
    TextDrawFont(PassportTD[13], 1);
    TextDrawLetterSize(PassportTD[13], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[13], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[13], 0);
    TextDrawSetShadow(PassportTD[13], 0);
    TextDrawAlignment(PassportTD[13], 1);
    TextDrawColor(PassportTD[13], 255);
    TextDrawBackgroundColor(PassportTD[13], 255);
    TextDrawBoxColor(PassportTD[13], 50);
    TextDrawUseBox(PassportTD[13], 0);
    TextDrawSetProportional(PassportTD[13], 1);
    TextDrawSetSelectable(PassportTD[13], 0);

    PassportTD[14] = TextDrawCreate(389.000000, 281.000000, "Origin");
    TextDrawFont(PassportTD[14], 1);
    TextDrawLetterSize(PassportTD[14], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[14], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[14], 0);
    TextDrawSetShadow(PassportTD[14], 0);
    TextDrawAlignment(PassportTD[14], 1);
    TextDrawColor(PassportTD[14], 255);
    TextDrawBackgroundColor(PassportTD[14], 255);
    TextDrawBoxColor(PassportTD[14], 50);
    TextDrawUseBox(PassportTD[14], 0);
    TextDrawSetProportional(PassportTD[14], 1);
    TextDrawSetSelectable(PassportTD[14], 0);

    PassportTD[15] = TextDrawCreate(389.000000, 312.000000, "Tinggi (cm)");
    TextDrawFont(PassportTD[15], 1);
    TextDrawLetterSize(PassportTD[15], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[15], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[15], 0);
    TextDrawSetShadow(PassportTD[15], 0);
    TextDrawAlignment(PassportTD[15], 1);
    TextDrawColor(PassportTD[15], 255);
    TextDrawBackgroundColor(PassportTD[15], 255);
    TextDrawBoxColor(PassportTD[15], 50);
    TextDrawUseBox(PassportTD[15], 0);
    TextDrawSetProportional(PassportTD[15], 1);
    TextDrawSetSelectable(PassportTD[15], 0);

    PassportTD[16] = TextDrawCreate(389.000000, 341.000000, "Berat (kg)");
    TextDrawFont(PassportTD[16], 1);
    TextDrawLetterSize(PassportTD[16], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[16], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[16], 0);
    TextDrawSetShadow(PassportTD[16], 0);
    TextDrawAlignment(PassportTD[16], 1);
    TextDrawColor(PassportTD[16], 255);
    TextDrawBackgroundColor(PassportTD[16], 255);
    TextDrawBoxColor(PassportTD[16], 50);
    TextDrawUseBox(PassportTD[16], 0);
    TextDrawSetProportional(PassportTD[16], 1);
    TextDrawSetSelectable(PassportTD[16], 0);

    PassportTD[17] = TextDrawCreate(323.000000, 271.000000, "_");
    TextDrawFont(PassportTD[17], 1);
    TextDrawLetterSize(PassportTD[17], 0.600000, -0.200001);
    TextDrawTextSize(PassportTD[17], 298.500000, 299.000000);
    TextDrawSetOutline(PassportTD[17], 1);
    TextDrawSetShadow(PassportTD[17], 0);
    TextDrawAlignment(PassportTD[17], 2);
    TextDrawColor(PassportTD[17], -1);
    TextDrawBackgroundColor(PassportTD[17], 255);
    TextDrawBoxColor(PassportTD[17], 1296911871);
    TextDrawUseBox(PassportTD[17], 1);
    TextDrawSetProportional(PassportTD[17], 1);
    TextDrawSetSelectable(PassportTD[17], 0);

    PassportTD[18] = TextDrawCreate(364.000000, 272.000000, "_");
    TextDrawFont(PassportTD[18], 1);
    TextDrawLetterSize(PassportTD[18], 0.600000, 11.750002);
    TextDrawTextSize(PassportTD[18], 298.500000, -1.500000);
    TextDrawSetOutline(PassportTD[18], 1);
    TextDrawSetShadow(PassportTD[18], 0);
    TextDrawAlignment(PassportTD[18], 2);
    TextDrawColor(PassportTD[18], -1);
    TextDrawBackgroundColor(PassportTD[18], 255);
    TextDrawBoxColor(PassportTD[18], 1296911871);
    TextDrawUseBox(PassportTD[18], 1);
    TextDrawSetProportional(PassportTD[18], 1);
    TextDrawSetSelectable(PassportTD[18], 0);

    PassportTD[19] = TextDrawCreate(323.000000, 380.000000, "_");
    TextDrawFont(PassportTD[19], 1);
    TextDrawLetterSize(PassportTD[19], 0.600000, -0.200001);
    TextDrawTextSize(PassportTD[19], 298.500000, 299.000000);
    TextDrawSetOutline(PassportTD[19], 1);
    TextDrawSetShadow(PassportTD[19], 0);
    TextDrawAlignment(PassportTD[19], 2);
    TextDrawColor(PassportTD[19], -1);
    TextDrawBackgroundColor(PassportTD[19], 255);
    TextDrawBoxColor(PassportTD[19], 1296911871);
    TextDrawUseBox(PassportTD[19], 1);
    TextDrawSetProportional(PassportTD[19], 1);
    TextDrawSetSelectable(PassportTD[19], 0);

    PassportTD[20] = TextDrawCreate(189.000000, 378.000000, "Tanda tangan");
    TextDrawFont(PassportTD[20], 1);
    TextDrawLetterSize(PassportTD[20], 0.233333, 1.399999);
    TextDrawTextSize(PassportTD[20], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[20], 0);
    TextDrawSetShadow(PassportTD[20], 0);
    TextDrawAlignment(PassportTD[20], 1);
    TextDrawColor(PassportTD[20], -625251585);
    TextDrawBackgroundColor(PassportTD[20], 255);
    TextDrawBoxColor(PassportTD[20], 50);
    TextDrawUseBox(PassportTD[20], 0);
    TextDrawSetProportional(PassportTD[20], 1);
    TextDrawSetSelectable(PassportTD[20], 0);

    PassportTD[21] = TextDrawCreate(261.000000, 272.000000, "_");
    TextDrawFont(PassportTD[21], 1);
    TextDrawLetterSize(PassportTD[21], 0.600000, 11.750002);
    TextDrawTextSize(PassportTD[21], 298.500000, -1.500000);
    TextDrawSetOutline(PassportTD[21], 1);
    TextDrawSetShadow(PassportTD[21], 0);
    TextDrawAlignment(PassportTD[21], 2);
    TextDrawColor(PassportTD[21], -1);
    TextDrawBackgroundColor(PassportTD[21], 255);
    TextDrawBoxColor(PassportTD[21], 1296911871);
    TextDrawUseBox(PassportTD[21], 1);
    TextDrawSetProportional(PassportTD[21], 1);
    TextDrawSetSelectable(PassportTD[21], 0);

    PassportTD[22] = TextDrawCreate(224.000000, 213.000000, "_");
    TextDrawFont(PassportTD[22], 1);
    TextDrawLetterSize(PassportTD[22], 0.600000, 6.100006);
    TextDrawTextSize(PassportTD[22], 298.500000, -1.500000);
    TextDrawSetOutline(PassportTD[22], 1);
    TextDrawSetShadow(PassportTD[22], 0);
    TextDrawAlignment(PassportTD[22], 2);
    TextDrawColor(PassportTD[22], -1);
    TextDrawBackgroundColor(PassportTD[22], 255);
    TextDrawBoxColor(PassportTD[22], 1296911871);
    TextDrawUseBox(PassportTD[22], 1);
    TextDrawSetProportional(PassportTD[22], 1);
    TextDrawSetSelectable(PassportTD[22], 0);

    PassportTD[23] = TextDrawCreate(296.000000, 213.000000, "_");
    TextDrawFont(PassportTD[23], 1);
    TextDrawLetterSize(PassportTD[23], 0.600000, 6.100006);
    TextDrawTextSize(PassportTD[23], 298.500000, -1.500000);
    TextDrawSetOutline(PassportTD[23], 1);
    TextDrawSetShadow(PassportTD[23], 0);
    TextDrawAlignment(PassportTD[23], 2);
    TextDrawColor(PassportTD[23], -1);
    TextDrawBackgroundColor(PassportTD[23], 255);
    TextDrawBoxColor(PassportTD[23], 1296911871);
    TextDrawUseBox(PassportTD[23], 1);
    TextDrawSetProportional(PassportTD[23], 1);
    TextDrawSetSelectable(PassportTD[23], 0);

    PassportTD[24] = TextDrawCreate(308.000000, 254.000000, "Nama karakter harus roleplay!");
    TextDrawFont(PassportTD[24], 1);
    TextDrawLetterSize(PassportTD[24], 0.162496, 1.100000);
    TextDrawTextSize(PassportTD[24], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[24], 0);
    TextDrawSetShadow(PassportTD[24], 0);
    TextDrawAlignment(PassportTD[24], 1);
    TextDrawColor(PassportTD[24], 255);
    TextDrawBackgroundColor(PassportTD[24], 255);
    TextDrawBoxColor(PassportTD[24], 50);
    TextDrawUseBox(PassportTD[24], 0);
    TextDrawSetProportional(PassportTD[24], 1);
    TextDrawSetSelectable(PassportTD[24], 0);

    PassportTD[25] = TextDrawCreate(308.000000, 214.000000, "Perhatian!");
    TextDrawFont(PassportTD[25], 1);
    TextDrawLetterSize(PassportTD[25], 0.200000, 1.450000);
    TextDrawTextSize(PassportTD[25], 598.000000, 12.500000);
    TextDrawSetOutline(PassportTD[25], 0);
    TextDrawSetShadow(PassportTD[25], 0);
    TextDrawAlignment(PassportTD[25], 1);
    TextDrawColor(PassportTD[25], -1962934017);
    TextDrawBackgroundColor(PassportTD[25], 255);
    TextDrawBoxColor(PassportTD[25], 50);
    TextDrawUseBox(PassportTD[25], 0);
    TextDrawSetProportional(PassportTD[25], 1);
    TextDrawSetSelectable(PassportTD[25], 0);

    PassportTD[26] = TextDrawCreate(426.000000, 382.500000, "SUBMIT");
    TextDrawFont(PassportTD[26], 2);
    TextDrawLetterSize(PassportTD[26], 0.258332, 1.750000);
    TextDrawTextSize(PassportTD[26], 16.500000, 90.500000);
    TextDrawSetOutline(PassportTD[26], 0);
    TextDrawSetShadow(PassportTD[26], 0);
    TextDrawAlignment(PassportTD[26], 2);
    TextDrawColor(PassportTD[26], 9109759);
    TextDrawBackgroundColor(PassportTD[26], 255);
    TextDrawBoxColor(PassportTD[26], -625251585);
    TextDrawUseBox(PassportTD[26], 1);
    TextDrawSetProportional(PassportTD[26], 1);
    TextDrawSetSelectable(PassportTD[26], 1);
}

CreatePassportCoverTextdraw()
{
    PassportCoverTD[0] = TextDrawCreate(320.000000, 144.000000, "_");
    TextDrawFont(PassportCoverTD[0], 1);
    TextDrawLetterSize(PassportCoverTD[0], 0.600000, 29.800003);
    TextDrawTextSize(PassportCoverTD[0], 298.500000, 160.000000);
    TextDrawSetOutline(PassportCoverTD[0], 1);
    TextDrawSetShadow(PassportCoverTD[0], 0);
    TextDrawAlignment(PassportCoverTD[0], 2);
    TextDrawColor(PassportCoverTD[0], -1);
    TextDrawBackgroundColor(PassportCoverTD[0], 255);
    TextDrawBoxColor(PassportCoverTD[0], 52242943);
    TextDrawUseBox(PassportCoverTD[0], 1);
    TextDrawSetProportional(PassportCoverTD[0], 1);
    TextDrawSetSelectable(PassportCoverTD[0], 0);

    PassportCoverTD[1] = TextDrawCreate(349.000000, 174.000000, "KOTA PAHLAWAN");
    TextDrawFont(PassportCoverTD[1], 2);
    TextDrawLetterSize(PassportCoverTD[1], 0.216665, 1.550001);
    TextDrawTextSize(PassportCoverTD[1], 400.000000, 237.000000);
    TextDrawSetOutline(PassportCoverTD[1], 0);
    TextDrawSetShadow(PassportCoverTD[1], 0);
    TextDrawAlignment(PassportCoverTD[1], 2);
    TextDrawColor(PassportCoverTD[1], -625251585);
    TextDrawBackgroundColor(PassportCoverTD[1], 255);
    TextDrawBoxColor(PassportCoverTD[1], 50);
    TextDrawUseBox(PassportCoverTD[1], 0);
    TextDrawSetProportional(PassportCoverTD[1], 1);
    TextDrawSetSelectable(PassportCoverTD[1], 0);

    PassportCoverTD[2] = TextDrawCreate(358.000000, 190.000000, "PASSPORT");
    TextDrawFont(PassportCoverTD[2], 2);
    TextDrawLetterSize(PassportCoverTD[2], 0.216665, 1.550001);
    TextDrawTextSize(PassportCoverTD[2], 400.000000, 237.000000);
    TextDrawSetOutline(PassportCoverTD[2], 0);
    TextDrawSetShadow(PassportCoverTD[2], 0);
    TextDrawAlignment(PassportCoverTD[2], 2);
    TextDrawColor(PassportCoverTD[2], -625251585);
    TextDrawBackgroundColor(PassportCoverTD[2], 255);
    TextDrawBoxColor(PassportCoverTD[2], 50);
    TextDrawUseBox(PassportCoverTD[2], 0);
    TextDrawSetProportional(PassportCoverTD[2], 1);
    TextDrawSetSelectable(PassportCoverTD[2], 0);

    PassportCoverTD[3] = TextDrawCreate(322.000000, 302.000000, "Klik tanda di bawah untuk mendaftarkan karakter!");
    TextDrawFont(PassportCoverTD[3], 1);
    TextDrawLetterSize(PassportCoverTD[3], 0.145833, 1.400001);
    TextDrawTextSize(PassportCoverTD[3], 400.000000, 97.500000);
    TextDrawSetOutline(PassportCoverTD[3], 0);
    TextDrawSetShadow(PassportCoverTD[3], 0);
    TextDrawAlignment(PassportCoverTD[3], 2);
    TextDrawColor(PassportCoverTD[3], -625251585);
    TextDrawBackgroundColor(PassportCoverTD[3], 255);
    TextDrawBoxColor(PassportCoverTD[3], 50);
    TextDrawUseBox(PassportCoverTD[3], 0);
    TextDrawSetProportional(PassportCoverTD[3], 1);
    TextDrawSetSelectable(PassportCoverTD[3], 0);

    PassportCoverTD[4] = TextDrawCreate(312.000000, 337.000000, "ld_dual:white");
    TextDrawFont(PassportCoverTD[4], 4);
    TextDrawLetterSize(PassportCoverTD[4], 0.600000, 2.000000);
    TextDrawTextSize(PassportCoverTD[4], 19.000000, 18.500000);
    TextDrawSetOutline(PassportCoverTD[4], 1);
    TextDrawSetShadow(PassportCoverTD[4], 0);
    TextDrawAlignment(PassportCoverTD[4], 1);
    TextDrawColor(PassportCoverTD[4], -625251670);
    TextDrawBackgroundColor(PassportCoverTD[4], 255);
    TextDrawBoxColor(PassportCoverTD[4], 50);
    TextDrawUseBox(PassportCoverTD[4], 1);
    TextDrawSetProportional(PassportCoverTD[4], 1);
    TextDrawSetSelectable(PassportCoverTD[4], 1);
}

CreatePlayerPassportTD(playerid)
{
    PlayerPassportTD[playerid][0] = CreatePlayerTextDraw(playerid, 195.000000, 232.000000, "Klik"); //kelamin
    PlayerTextDrawFont(playerid, PlayerPassportTD[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPassportTD[playerid][0], 0.633333, 3.249998);
    PlayerTextDrawTextSize(playerid, PlayerPassportTD[playerid][0], 15.000000, 42.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPassportTD[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPassportTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PlayerPassportTD[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerPassportTD[playerid][0], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerPassportTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPassportTD[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, PlayerPassportTD[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPassportTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPassportTD[playerid][0], 1);

    PlayerPassportTD[playerid][1] = CreatePlayerTextDraw(playerid, 287.000000, 294.000000, "Klik disini!"); //firstname
    PlayerTextDrawFont(playerid, PlayerPassportTD[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPassportTD[playerid][1], 0.233333, 1.399999);
    PlayerTextDrawTextSize(playerid, PlayerPassportTD[playerid][1], 343.000000, 12.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPassportTD[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPassportTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PlayerPassportTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, PlayerPassportTD[playerid][1], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerPassportTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPassportTD[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, PlayerPassportTD[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPassportTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPassportTD[playerid][1], 1);

    PlayerPassportTD[playerid][2] = CreatePlayerTextDraw(playerid, 287.000000, 323.000000, "Klik disini!"); //lastname
    PlayerTextDrawFont(playerid, PlayerPassportTD[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPassportTD[playerid][2], 0.233333, 1.399999);
    PlayerTextDrawTextSize(playerid, PlayerPassportTD[playerid][2], 344.000000, 12.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPassportTD[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPassportTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PlayerPassportTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, PlayerPassportTD[playerid][2], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerPassportTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPassportTD[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, PlayerPassportTD[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPassportTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPassportTD[playerid][2], 1);

    PlayerPassportTD[playerid][3] = CreatePlayerTextDraw(playerid, 287.000000, 353.000000, "hh/bb/tttt"); //birthday
    PlayerTextDrawFont(playerid, PlayerPassportTD[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPassportTD[playerid][3], 0.233333, 1.399999);
    PlayerTextDrawTextSize(playerid, PlayerPassportTD[playerid][3], 343.500000, 12.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPassportTD[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPassportTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PlayerPassportTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, PlayerPassportTD[playerid][3], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerPassportTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPassportTD[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, PlayerPassportTD[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPassportTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPassportTD[playerid][3], 1);
    
    PlayerPassportTD[playerid][4] = CreatePlayerTextDraw(playerid, 389.000000, 294.000000, "Klik disini!"); //origin
    PlayerTextDrawFont(playerid, PlayerPassportTD[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPassportTD[playerid][4], 0.233333, 1.399999);
    PlayerTextDrawTextSize(playerid, PlayerPassportTD[playerid][4], 441.500000, 12.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPassportTD[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPassportTD[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PlayerPassportTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, PlayerPassportTD[playerid][4], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerPassportTD[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPassportTD[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, PlayerPassportTD[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPassportTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPassportTD[playerid][4], 1);
    
    PlayerPassportTD[playerid][5] = CreatePlayerTextDraw(playerid, 389.000000, 323.000000, "Klik disini!"); //tinggi
    PlayerTextDrawFont(playerid, PlayerPassportTD[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPassportTD[playerid][5], 0.233333, 1.399999);
    PlayerTextDrawTextSize(playerid, PlayerPassportTD[playerid][5], 441.500000, 12.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPassportTD[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPassportTD[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PlayerPassportTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, PlayerPassportTD[playerid][5], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerPassportTD[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPassportTD[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, PlayerPassportTD[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPassportTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPassportTD[playerid][5], 1);
    
    PlayerPassportTD[playerid][6] = CreatePlayerTextDraw(playerid, 389.000000, 353.000000, "Klik disini!"); //berat
    PlayerTextDrawFont(playerid, PlayerPassportTD[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, PlayerPassportTD[playerid][6], 0.233333, 1.399999);
    PlayerTextDrawTextSize(playerid, PlayerPassportTD[playerid][6], 428.500000, 12.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPassportTD[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPassportTD[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, PlayerPassportTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, PlayerPassportTD[playerid][6], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, PlayerPassportTD[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPassportTD[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, PlayerPassportTD[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPassportTD[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPassportTD[playerid][6], 1);

    PlayerPassportTD[playerid][7] = CreatePlayerTextDraw(playerid, 163.000000, 270.000000, "Preview_Model"); //skin
    PlayerTextDrawFont(playerid, PlayerPassportTD[playerid][7], 5);
    PlayerTextDrawLetterSize(playerid, PlayerPassportTD[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PlayerPassportTD[playerid][7], 81.500000, 107.000000);
    PlayerTextDrawSetOutline(playerid, PlayerPassportTD[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPassportTD[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, PlayerPassportTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, PlayerPassportTD[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPassportTD[playerid][7], 0);
    PlayerTextDrawBoxColor(playerid, PlayerPassportTD[playerid][7], 255);
    PlayerTextDrawUseBox(playerid, PlayerPassportTD[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPassportTD[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPassportTD[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, PlayerPassportTD[playerid][7], 230);
    PlayerTextDrawSetPreviewRot(playerid, PlayerPassportTD[playerid][7], 0.000000, 0.000000, 0.000000, 0.849999);
    PlayerTextDrawSetPreviewVehCol(playerid, PlayerPassportTD[playerid][7], 1, 1);

    PlayerPassportTD[playerid][8] = CreatePlayerTextDraw(playerid, 251.000000, 383.000000, "_"); //tanda tangan
    PlayerTextDrawFont(playerid, PlayerPassportTD[playerid][8], 0);
    PlayerTextDrawLetterSize(playerid, PlayerPassportTD[playerid][8], 0.529165, 1.549998);
    PlayerTextDrawTextSize(playerid, PlayerPassportTD[playerid][8], 375.500000, 12.500000);
    PlayerTextDrawSetOutline(playerid, PlayerPassportTD[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, PlayerPassportTD[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PlayerPassportTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, PlayerPassportTD[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerPassportTD[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, PlayerPassportTD[playerid][8], 50);
    PlayerTextDrawUseBox(playerid, PlayerPassportTD[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, PlayerPassportTD[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerPassportTD[playerid][8], 0);
}

ShowPassportTD(playerid)
{
    for(new x; x < 27; x++)
	{
        TextDrawShowForPlayer(playerid, PassportTD[x]);
    }

    for(new x; x < 9; x++)
    {
        PlayerTextDrawShow(playerid, PlayerPassportTD[playerid][x]);
    }
    SelectTextDraw(playerid, 0xff91a4cc);
    SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Gunakan "CMDEA"'/cursor' "WHITE"jika mouse hilang dari layar/textdraw tidak bisa ditekan!");
}

HidePassportTD(playerid)
{
    for(new x=0; x < 27; x++)
	{
        TextDrawHideForPlayer(playerid, PassportTD[x]);
    }

    for(new x; x < 9; x++)
    {
        PlayerTextDrawHide(playerid, PlayerPassportTD[playerid][x]);
    }
    CancelSelectTextDraw(playerid);
}

ShowPassportCoverTD(playerid)
{
    for(new x=0; x < 5; x++)
	{
        TextDrawShowForPlayer(playerid, PassportCoverTD[x]);
    }
    SelectTextDraw(playerid, 0xff91a4cc);
    SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Gunakan "CMDEA"'/cursor' "WHITE"jika mouse hilang dari layar/textdraw tidak bisa ditekan!");
    return 1;
}

HidePassportCoverTD(playerid)
{
    for(new x=0; x < 5; x++)
	{
        TextDrawHideForPlayer(playerid, PassportCoverTD[x]);
    }
    CancelSelectTextDraw(playerid);
}