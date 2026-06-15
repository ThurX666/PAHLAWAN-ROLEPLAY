new Text:LCTD[36],
	Text:KTATD[5],
	Text:IDCTD[18],
	Text:BPJSTD[18],
	PlayerText:PKTATD[MAX_PLAYERS][3],
	PlayerText:PLCTD[MAX_PLAYERS][17],
	PlayerText:PIDCTD[MAX_PLAYERS][9],
	PlayerText: PBPJSTD[MAX_PLAYERS][5];

CreateBPJSTD()
{
	BPJSTD[0] = TextDrawCreate(400.000, 150.000, "LD_BEAT:chit");
	TextDrawTextSize(BPJSTD[0], 20.000, 20.000);
	TextDrawAlignment(BPJSTD[0], 1);
	TextDrawColor(BPJSTD[0], 579543807);
	TextDrawSetShadow(BPJSTD[0], 0);
	TextDrawSetOutline(BPJSTD[0], 0);
	TextDrawBackgroundColor(BPJSTD[0], 255);
	TextDrawFont(BPJSTD[0], 4);
	TextDrawSetProportional(BPJSTD[0], 1);

	BPJSTD[1] = TextDrawCreate(410.000, 153.000, "LD_SPAC:white");
	TextDrawTextSize(BPJSTD[1], 130.000, 35.000);
	TextDrawAlignment(BPJSTD[1], 1);
	TextDrawColor(BPJSTD[1], 579543807);
	TextDrawSetShadow(BPJSTD[1], 0);
	TextDrawSetOutline(BPJSTD[1], 0);
	TextDrawBackgroundColor(BPJSTD[1], 255);
	TextDrawFont(BPJSTD[1], 4);
	TextDrawSetProportional(BPJSTD[1], 1);

	BPJSTD[2] = TextDrawCreate(530.000, 150.000, "LD_BEAT:chit");
	TextDrawTextSize(BPJSTD[2], 20.000, 20.000);
	TextDrawAlignment(BPJSTD[2], 1);
	TextDrawColor(BPJSTD[2], 579543807);
	TextDrawSetShadow(BPJSTD[2], 0);
	TextDrawSetOutline(BPJSTD[2], 0);
	TextDrawBackgroundColor(BPJSTD[2], 255);
	TextDrawFont(BPJSTD[2], 4);
	TextDrawSetProportional(BPJSTD[2], 1);

	BPJSTD[3] = TextDrawCreate(403.000, 160.000, "LD_SPAC:white");
	TextDrawTextSize(BPJSTD[3], 144.000, 35.000);
	TextDrawAlignment(BPJSTD[3], 1);
	TextDrawColor(BPJSTD[3], 579543807);
	TextDrawSetShadow(BPJSTD[3], 0);
	TextDrawSetOutline(BPJSTD[3], 0);
	TextDrawBackgroundColor(BPJSTD[3], 255);
	TextDrawFont(BPJSTD[3], 4);
	TextDrawSetProportional(BPJSTD[3], 1);

	BPJSTD[4] = TextDrawCreate(403.000, 190.000, "LD_SPAC:white");
	TextDrawTextSize(BPJSTD[4], 144.000, 100.000);
	TextDrawAlignment(BPJSTD[4], 1);
	TextDrawColor(BPJSTD[4], -1);
	TextDrawSetShadow(BPJSTD[4], 0);
	TextDrawSetOutline(BPJSTD[4], 0);
	TextDrawBackgroundColor(BPJSTD[4], 255);
	TextDrawFont(BPJSTD[4], 4);
	TextDrawSetProportional(BPJSTD[4], 1);

	BPJSTD[5] = TextDrawCreate(399.500, 280.000, "LD_BEAT:chit");
	TextDrawTextSize(BPJSTD[5], 20.000, 20.000);
	TextDrawAlignment(BPJSTD[5], 1);
	TextDrawColor(BPJSTD[5], -1);
	TextDrawSetShadow(BPJSTD[5], 0);
	TextDrawSetOutline(BPJSTD[5], 0);
	TextDrawBackgroundColor(BPJSTD[5], 255);
	TextDrawFont(BPJSTD[5], 4);
	TextDrawSetProportional(BPJSTD[5], 1);

	BPJSTD[6] = TextDrawCreate(530.500, 280.000, "LD_BEAT:chit");
	TextDrawTextSize(BPJSTD[6], 20.000, 20.000);
	TextDrawAlignment(BPJSTD[6], 1);
	TextDrawColor(BPJSTD[6], -1);
	TextDrawSetShadow(BPJSTD[6], 0);
	TextDrawSetOutline(BPJSTD[6], 0);
	TextDrawBackgroundColor(BPJSTD[6], 255);
	TextDrawFont(BPJSTD[6], 4);
	TextDrawSetProportional(BPJSTD[6], 1);

	BPJSTD[7] = TextDrawCreate(410.000, 197.000, "LD_SPAC:white");
	TextDrawTextSize(BPJSTD[7], 130.000, 100.000);
	TextDrawAlignment(BPJSTD[7], 1);
	TextDrawColor(BPJSTD[7], -1);
	TextDrawSetShadow(BPJSTD[7], 0);
	TextDrawSetOutline(BPJSTD[7], 0);
	TextDrawBackgroundColor(BPJSTD[7], 255);
	TextDrawFont(BPJSTD[7], 4);
	TextDrawSetProportional(BPJSTD[7], 1);

	BPJSTD[8] = TextDrawCreate(435.000, 167.500, "KARTU INDONESIA SEHAT");
	TextDrawLetterSize(BPJSTD[8], 0.200, 1.000);
	TextDrawAlignment(BPJSTD[8], 1);
	TextDrawColor(BPJSTD[8], -1);
	TextDrawSetShadow(BPJSTD[8], 0);
	TextDrawSetOutline(BPJSTD[8], 0);
	TextDrawBackgroundColor(BPJSTD[8], 150);
	TextDrawFont(BPJSTD[8], 1);
	TextDrawSetProportional(BPJSTD[8], 1);

	BPJSTD[9] = TextDrawCreate(410.000, 195.000, "Nomor Kartu :");
	TextDrawLetterSize(BPJSTD[9], 0.200, 1.000);
	TextDrawAlignment(BPJSTD[9], 1);
	TextDrawColor(BPJSTD[9], 255);
	TextDrawSetShadow(BPJSTD[9], 0);
	TextDrawSetOutline(BPJSTD[9], 0);
	TextDrawBackgroundColor(BPJSTD[9], 150);
	TextDrawFont(BPJSTD[9], 1);
	TextDrawSetProportional(BPJSTD[9], 1);

	BPJSTD[10] = TextDrawCreate(410.000, 205.000, "Nama :");
	TextDrawLetterSize(BPJSTD[10], 0.200, 1.000);
	TextDrawAlignment(BPJSTD[10], 1);
	TextDrawColor(BPJSTD[10], 255);
	TextDrawSetShadow(BPJSTD[10], 0);
	TextDrawSetOutline(BPJSTD[10], 0);
	TextDrawBackgroundColor(BPJSTD[10], 150);
	TextDrawFont(BPJSTD[10], 1);
	TextDrawSetProportional(BPJSTD[10], 1);

	BPJSTD[11] = TextDrawCreate(410.000, 215.000, "Kelas :");
	TextDrawLetterSize(BPJSTD[11], 0.200, 1.000);
	TextDrawAlignment(BPJSTD[11], 1);
	TextDrawColor(BPJSTD[11], 255);
	TextDrawSetShadow(BPJSTD[11], 0);
	TextDrawSetOutline(BPJSTD[11], 0);
	TextDrawBackgroundColor(BPJSTD[11], 150);
	TextDrawFont(BPJSTD[11], 1);
	TextDrawSetProportional(BPJSTD[11], 1);

	BPJSTD[12] = TextDrawCreate(410.000, 225.000, "Tanggal Lahir :");
	TextDrawLetterSize(BPJSTD[12], 0.200, 1.000);
	TextDrawAlignment(BPJSTD[12], 1);
	TextDrawColor(BPJSTD[12], 255);
	TextDrawSetShadow(BPJSTD[12], 0);
	TextDrawSetOutline(BPJSTD[12], 0);
	TextDrawBackgroundColor(BPJSTD[12], 150);
	TextDrawFont(BPJSTD[12], 1);
	TextDrawSetProportional(BPJSTD[12], 1);

	BPJSTD[13] = TextDrawCreate(410.000, 235.000, "NIK :");
	TextDrawLetterSize(BPJSTD[13], 0.200, 1.000);
	TextDrawAlignment(BPJSTD[13], 1);
	TextDrawColor(BPJSTD[13], 255);
	TextDrawSetShadow(BPJSTD[13], 0);
	TextDrawSetOutline(BPJSTD[13], 0);
	TextDrawBackgroundColor(BPJSTD[13], 150);
	TextDrawFont(BPJSTD[13], 1);
	TextDrawSetProportional(BPJSTD[13], 1);

	BPJSTD[14] = TextDrawCreate(410.000, 246.000, "Syarat dan Ketentuan");
	TextDrawLetterSize(BPJSTD[14], 0.150, 0.898);
	TextDrawAlignment(BPJSTD[14], 1);
	TextDrawColor(BPJSTD[14], 1768516095);
	TextDrawSetShadow(BPJSTD[14], 0);
	TextDrawSetOutline(BPJSTD[14], 0);
	TextDrawBackgroundColor(BPJSTD[14], 150);
	TextDrawFont(BPJSTD[14], 1);
	TextDrawSetProportional(BPJSTD[14], 1);

	BPJSTD[15] = TextDrawCreate(410.000, 256.000, "1. Bawa kartu ketika berobat");
	TextDrawLetterSize(BPJSTD[15], 0.150, 0.898);
	TextDrawAlignment(BPJSTD[15], 1);
	TextDrawColor(BPJSTD[15], 1768516095);
	TextDrawSetShadow(BPJSTD[15], 0);
	TextDrawSetOutline(BPJSTD[15], 0);
	TextDrawBackgroundColor(BPJSTD[15], 150);
	TextDrawFont(BPJSTD[15], 1);
	TextDrawSetProportional(BPJSTD[15], 1);

	BPJSTD[16] = TextDrawCreate(410.000, 266.000, "2. Jangan salah gunakan kartu");
	TextDrawLetterSize(BPJSTD[16], 0.150, 0.898);
	TextDrawAlignment(BPJSTD[16], 1);
	TextDrawColor(BPJSTD[16], 1768516095);
	TextDrawSetShadow(BPJSTD[16], 0);
	TextDrawSetOutline(BPJSTD[16], 0);
	TextDrawBackgroundColor(BPJSTD[16], 150);
	TextDrawFont(BPJSTD[16], 1);
	TextDrawSetProportional(BPJSTD[16], 1);

	BPJSTD[17] = TextDrawCreate(410.000, 276.000, "3. Jika kartu hilang segera melapor");
	TextDrawLetterSize(BPJSTD[17], 0.150, 0.898);
	TextDrawAlignment(BPJSTD[17], 1);
	TextDrawColor(BPJSTD[17], 1768516095);
	TextDrawSetShadow(BPJSTD[17], 0);
	TextDrawSetOutline(BPJSTD[17], 0);
	TextDrawBackgroundColor(BPJSTD[17], 150);
	TextDrawFont(BPJSTD[17], 1);
	TextDrawSetProportional(BPJSTD[17], 1);
}

CreatePBPJSTD(playerid)
{
	PBPJSTD[playerid][0] = CreatePlayerTextDraw(playerid, 455.000, 196.000, "007929301");
	PlayerTextDrawLetterSize(playerid, PBPJSTD[playerid][0], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, PBPJSTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, PBPJSTD[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, PBPJSTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, PBPJSTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PBPJSTD[playerid][0], 150);
	PlayerTextDrawFont(playerid, PBPJSTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, PBPJSTD[playerid][0], 1);

	PBPJSTD[playerid][1] = CreatePlayerTextDraw(playerid, 435.000, 206.000, "Bryan_Margareth");
	PlayerTextDrawLetterSize(playerid, PBPJSTD[playerid][1], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, PBPJSTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, PBPJSTD[playerid][1], 255);
	PlayerTextDrawSetShadow(playerid, PBPJSTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, PBPJSTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PBPJSTD[playerid][1], 150);
	PlayerTextDrawFont(playerid, PBPJSTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, PBPJSTD[playerid][1], 1);

	PBPJSTD[playerid][2] = CreatePlayerTextDraw(playerid, 435.000, 216.000, "III");
	PlayerTextDrawLetterSize(playerid, PBPJSTD[playerid][2], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, PBPJSTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, PBPJSTD[playerid][2], 255);
	PlayerTextDrawSetShadow(playerid, PBPJSTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, PBPJSTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PBPJSTD[playerid][2], 150);
	PlayerTextDrawFont(playerid, PBPJSTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PBPJSTD[playerid][2], 1);

	PBPJSTD[playerid][3] = CreatePlayerTextDraw(playerid, 455.000, 226.000, "07/01/1998");
	PlayerTextDrawLetterSize(playerid, PBPJSTD[playerid][3], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, PBPJSTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, PBPJSTD[playerid][3], 255);
	PlayerTextDrawSetShadow(playerid, PBPJSTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, PBPJSTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PBPJSTD[playerid][3], 150);
	PlayerTextDrawFont(playerid, PBPJSTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PBPJSTD[playerid][3], 1);

	PBPJSTD[playerid][4] = CreatePlayerTextDraw(playerid, 430.000, 236.000, "01891087");
	PlayerTextDrawLetterSize(playerid, PBPJSTD[playerid][4], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, PBPJSTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, PBPJSTD[playerid][4], 255);
	PlayerTextDrawSetShadow(playerid, PBPJSTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, PBPJSTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PBPJSTD[playerid][4], 150);
	PlayerTextDrawFont(playerid, PBPJSTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, PBPJSTD[playerid][4], 1);
}

CreateKTATD()
{
	KTATD[0] = TextDrawCreate(449.000000, 159.000000, "ld_dual:white");
	TextDrawFont(KTATD[0], 4);
	TextDrawLetterSize(KTATD[0], 0.600000, 2.000000);
	TextDrawTextSize(KTATD[0], 171.500000, 110.500000);
	TextDrawSetOutline(KTATD[0], 1);
	TextDrawSetShadow(KTATD[0], 0);
	TextDrawAlignment(KTATD[0], 1);
	TextDrawColor(KTATD[0], 1097458175);
	TextDrawBackgroundColor(KTATD[0], 255);
	TextDrawBoxColor(KTATD[0], 50);
	TextDrawUseBox(KTATD[0], 1);
	TextDrawSetProportional(KTATD[0], 1);
	TextDrawSetSelectable(KTATD[0], 0);

	KTATD[1] = TextDrawCreate(449.000000, 179.000000, "ld_dual:white");
	TextDrawFont(KTATD[1], 4);
	TextDrawLetterSize(KTATD[1], 0.600000, 2.000000);
	TextDrawTextSize(KTATD[1], 171.500000, 55.500000);
	TextDrawSetOutline(KTATD[1], 1);
	TextDrawSetShadow(KTATD[1], 0);
	TextDrawAlignment(KTATD[1], 1);
	TextDrawColor(KTATD[1], -741092353);
	TextDrawBackgroundColor(KTATD[1], 255);
	TextDrawBoxColor(KTATD[1], 50);
	TextDrawUseBox(KTATD[1], 1);
	TextDrawSetProportional(KTATD[1], 1);
	TextDrawSetSelectable(KTATD[1], 0);

	KTATD[2] = TextDrawCreate(477.000000, 163.000000, "KARTU TANDA ANGGOTA");
	TextDrawFont(KTATD[2], 1);
	TextDrawLetterSize(KTATD[2], 0.291666, 1.250000);
	TextDrawTextSize(KTATD[2], 625.000000, 17.000000);
	TextDrawSetOutline(KTATD[2], 0);
	TextDrawSetShadow(KTATD[2], 0);
	TextDrawAlignment(KTATD[2], 1);
	TextDrawColor(KTATD[2], -1);
	TextDrawBackgroundColor(KTATD[2], 255);
	TextDrawBoxColor(KTATD[2], 50);
	TextDrawUseBox(KTATD[2], 0);
	TextDrawSetProportional(KTATD[2], 1);
	TextDrawSetSelectable(KTATD[2], 0);

	KTATD[3] = TextDrawCreate(449.000000, 234.000000, "ld_dual:white");
	TextDrawFont(KTATD[3], 4);
	TextDrawLetterSize(KTATD[3], 0.600000, 2.000000);
	TextDrawTextSize(KTATD[3], 171.500000, 35.500000);
	TextDrawSetOutline(KTATD[3], 1);
	TextDrawSetShadow(KTATD[3], 0);
	TextDrawAlignment(KTATD[3], 1);
	TextDrawColor(KTATD[3], 1097458175);
	TextDrawBackgroundColor(KTATD[3], 255);
	TextDrawBoxColor(KTATD[3], 50);
	TextDrawUseBox(KTATD[3], 1);
	TextDrawSetProportional(KTATD[3], 1);
	TextDrawSetSelectable(KTATD[3], 0);

	KTATD[4] = TextDrawCreate(449.000000, 227.000000, "ld_dual:white");
	TextDrawFont(KTATD[4], 4);
	TextDrawLetterSize(KTATD[4], 0.600000, 2.000000);
	TextDrawTextSize(KTATD[4], 171.500000, 10.500000);
	TextDrawSetOutline(KTATD[4], 1);
	TextDrawSetShadow(KTATD[4], 0);
	TextDrawAlignment(KTATD[4], 1);
	TextDrawColor(KTATD[4], -741092353);
	TextDrawBackgroundColor(KTATD[4], 255);
	TextDrawBoxColor(KTATD[4], 50);
	TextDrawUseBox(KTATD[4], 1);
	TextDrawSetProportional(KTATD[4], 1);
	TextDrawSetSelectable(KTATD[4], 0);
}

CreatePlayerKTATD(playerid)
{
	PKTATD[playerid][0] = CreatePlayerTextDraw(playerid, 498.000000, 189.000000, "Nama: Pablo Estimao~n~Jabatan: Chief of Police~n~Nomor Induk: 1234567");
	PlayerTextDrawFont(playerid, PKTATD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, PKTATD[playerid][0], 0.229166, 1.250000);
	PlayerTextDrawTextSize(playerid, PKTATD[playerid][0], 625.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, PKTATD[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, PKTATD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, PKTATD[playerid][0], 1);
	PlayerTextDrawColor(playerid, PKTATD[playerid][0], 255);
	PlayerTextDrawBackgroundColor(playerid, PKTATD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, PKTATD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, PKTATD[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, PKTATD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, PKTATD[playerid][0], 0);

	PKTATD[playerid][1] = CreatePlayerTextDraw(playerid, 455.000000, 243.000000, "Adalah benar data di atas merupakan anggota Kepolisian Pahlawan Roleplay");
	PlayerTextDrawFont(playerid, PKTATD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, PKTATD[playerid][1], 0.195833, 1.000000);
	PlayerTextDrawTextSize(playerid, PKTATD[playerid][1], 618.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, PKTATD[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, PKTATD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, PKTATD[playerid][1], 1);
	PlayerTextDrawColor(playerid, PKTATD[playerid][1], 255);
	PlayerTextDrawBackgroundColor(playerid, PKTATD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, PKTATD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, PKTATD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, PKTATD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, PKTATD[playerid][1], 0);

	PKTATD[playerid][2] = CreatePlayerTextDraw(playerid, 422.000000, 182.000000, "Preview_Model");
	PlayerTextDrawFont(playerid, PKTATD[playerid][2], 5);
	PlayerTextDrawLetterSize(playerid, PKTATD[playerid][2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, PKTATD[playerid][2], 106.500000, 93.500000);
	PlayerTextDrawSetOutline(playerid, PKTATD[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, PKTATD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, PKTATD[playerid][2], 1);
	PlayerTextDrawColor(playerid, PKTATD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, PKTATD[playerid][2], 0);
	PlayerTextDrawBoxColor(playerid, PKTATD[playerid][2], 255);
	PlayerTextDrawUseBox(playerid, PKTATD[playerid][2], 0);
	PlayerTextDrawSetProportional(playerid, PKTATD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, PKTATD[playerid][2], 0);
	PlayerTextDrawSetPreviewModel(playerid, PKTATD[playerid][2], 23);
	PlayerTextDrawSetPreviewRot(playerid, PKTATD[playerid][2], -10.000000, 0.000000, 0.000000, 0.990000);
	PlayerTextDrawSetPreviewVehCol(playerid, PKTATD[playerid][2], 1, 1);
}

CreateLCTD()
{
    LCTD[0] = TextDrawCreate(442.000, 127.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[0], 195.000, 211.000);
	TextDrawAlignment(LCTD[0], 1);
	TextDrawColor(LCTD[0], -186588929);
	TextDrawSetShadow(LCTD[0], 0);
	TextDrawSetOutline(LCTD[0], 0);
	TextDrawBackgroundColor(LCTD[0], 255);
	TextDrawFont(LCTD[0], 4);
	TextDrawSetProportional(LCTD[0], 1);

	LCTD[1] = TextDrawCreate(553.000, 135.000, "PAHLAWAN");
	TextDrawLetterSize(LCTD[1], 0.399, 1.800);
	TextDrawAlignment(LCTD[1], 1);
	TextDrawColor(LCTD[1], 1701078527);
	TextDrawSetShadow(LCTD[1], 0);
	TextDrawSetOutline(LCTD[1], 0);
	TextDrawBackgroundColor(LCTD[1], 150);
	TextDrawFont(LCTD[1], 1);
	TextDrawSetProportional(LCTD[1], 1);

	LCTD[2] = TextDrawCreate(557.000, 150.000, "LISENSI / SIM");
	TextDrawLetterSize(LCTD[2], 0.260, 1.299);
	TextDrawAlignment(LCTD[2], 1);
	TextDrawColor(LCTD[2], 1701078527);
	TextDrawSetShadow(LCTD[2], 0);
	TextDrawSetOutline(LCTD[2], 0);
	TextDrawBackgroundColor(LCTD[2], 150);
	TextDrawFont(LCTD[2], 1);
	TextDrawSetProportional(LCTD[2], 1);

	LCTD[3] = TextDrawCreate(447.000, 138.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[3], 29.000, 41.000);
	TextDrawAlignment(LCTD[3], 1);
	TextDrawColor(LCTD[3], 1701078527);
	TextDrawSetShadow(LCTD[3], 0);
	TextDrawSetOutline(LCTD[3], 0);
	TextDrawBackgroundColor(LCTD[3], 255);
	TextDrawFont(LCTD[3], 4);
	TextDrawSetProportional(LCTD[3], 1);

	LCTD[4] = TextDrawCreate(448.000, 139.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[4], 27.000, 39.000);
	TextDrawAlignment(LCTD[4], 1);
	TextDrawColor(LCTD[4], -438576129);
	TextDrawSetShadow(LCTD[4], 0);
	TextDrawSetOutline(LCTD[4], 0);
	TextDrawBackgroundColor(LCTD[4], 255);
	TextDrawFont(LCTD[4], 4);
	TextDrawSetProportional(LCTD[4], 1);

	LCTD[5] = TextDrawCreate(436.000, 133.000, "_");
	TextDrawTextSize(LCTD[5], 51.000, 51.000);
	TextDrawAlignment(LCTD[5], 1);
	TextDrawColor(LCTD[5], -1);
	TextDrawSetShadow(LCTD[5], 0);
	TextDrawSetOutline(LCTD[5], 0);
	TextDrawBackgroundColor(LCTD[5], 0);
	TextDrawFont(LCTD[5], 5);
	TextDrawSetProportional(LCTD[5], 0);
	TextDrawSetPreviewModel(LCTD[5], 2050);
	TextDrawSetPreviewRot(LCTD[5], 0.000, 0.000, 0.000, 1.000);
	TextDrawSetPreviewVehCol(LCTD[5], 0, 0);

	LCTD[6] = TextDrawCreate(507.000, 124.000, "LD_BEAT:chit");
	TextDrawTextSize(LCTD[6], 51.000, 58.000);
	TextDrawAlignment(LCTD[6], 1);
	TextDrawColor(LCTD[6], -743806721);
	TextDrawSetShadow(LCTD[6], 0);
	TextDrawSetOutline(LCTD[6], 0);
	TextDrawBackgroundColor(LCTD[6], 255);
	TextDrawFont(LCTD[6], 4);
	TextDrawSetProportional(LCTD[6], 1);

	LCTD[7] = TextDrawCreate(517.000, 136.000, "LD_DRV:silboat");
	TextDrawTextSize(LCTD[7], 31.000, 34.000);
	TextDrawAlignment(LCTD[7], 1);
	TextDrawColor(LCTD[7], -1);
	TextDrawSetShadow(LCTD[7], 0);
	TextDrawSetOutline(LCTD[7], 0);
	TextDrawBackgroundColor(LCTD[7], 255);
	TextDrawFont(LCTD[7], 4);
	TextDrawSetProportional(LCTD[7], 1);

	LCTD[8] = TextDrawCreate(443.000, 250.000, "_");
	TextDrawTextSize(LCTD[8], 110.000, 108.000);
	TextDrawAlignment(LCTD[8], 1);
	TextDrawColor(LCTD[8], -206);
	TextDrawSetShadow(LCTD[8], 0);
	TextDrawSetOutline(LCTD[8], 0);
	TextDrawBackgroundColor(LCTD[8], 0);
	TextDrawFont(LCTD[8], 5);
	TextDrawSetProportional(LCTD[8], 0);
	TextDrawSetPreviewModel(LCTD[8], 2614);
	TextDrawSetPreviewRot(LCTD[8], 0.000, 0.000, 0.000, 0.899);
	TextDrawSetPreviewVehCol(LCTD[8], 0, 0);

	LCTD[9] = TextDrawCreate(545.000, 169.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[9], 1.000, 136.000);
	TextDrawAlignment(LCTD[9], 1);
	TextDrawColor(LCTD[9], 1701078527);
	TextDrawSetShadow(LCTD[9], 0);
	TextDrawSetOutline(LCTD[9], 0);
	TextDrawBackgroundColor(LCTD[9], 255);
	TextDrawFont(LCTD[9], 4);
	TextDrawSetProportional(LCTD[9], 1);

	LCTD[10] = TextDrawCreate(570.000, 169.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[10], 1.000, 136.000);
	TextDrawAlignment(LCTD[10], 1);
	TextDrawColor(LCTD[10], 1701078527);
	TextDrawSetShadow(LCTD[10], 0);
	TextDrawSetOutline(LCTD[10], 0);
	TextDrawBackgroundColor(LCTD[10], 255);
	TextDrawFont(LCTD[10], 4);
	TextDrawSetProportional(LCTD[10], 1);

	LCTD[11] = TextDrawCreate(598.000, 169.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[11], 1.000, 136.000);
	TextDrawAlignment(LCTD[11], 1);
	TextDrawColor(LCTD[11], 1701078527);
	TextDrawSetShadow(LCTD[11], 0);
	TextDrawSetOutline(LCTD[11], 0);
	TextDrawBackgroundColor(LCTD[11], 255);
	TextDrawFont(LCTD[11], 4);
	TextDrawSetProportional(LCTD[11], 1);

	LCTD[12] = TextDrawCreate(514.000, 183.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[12], 119.000, 1.000);
	TextDrawAlignment(LCTD[12], 1);
	TextDrawColor(LCTD[12], 1701078527);
	TextDrawSetShadow(LCTD[12], 0);
	TextDrawSetOutline(LCTD[12], 0);
	TextDrawBackgroundColor(LCTD[12], 255);
	TextDrawFont(LCTD[12], 4);
	TextDrawSetProportional(LCTD[12], 1);

	LCTD[13] = TextDrawCreate(576.000, 171.000, "VALID");
	TextDrawLetterSize(LCTD[13], 0.160, 0.899);
	TextDrawAlignment(LCTD[13], 1);
	TextDrawColor(LCTD[13], 1701078527);
	TextDrawSetShadow(LCTD[13], 0);
	TextDrawSetOutline(LCTD[13], 0);
	TextDrawBackgroundColor(LCTD[13], 150);
	TextDrawFont(LCTD[13], 1);
	TextDrawSetProportional(LCTD[13], 1);

	LCTD[14] = TextDrawCreate(604.000, 171.000, "EXP DATE");
	TextDrawLetterSize(LCTD[14], 0.160, 0.899);
	TextDrawAlignment(LCTD[14], 1);
	TextDrawColor(LCTD[14], 1701078527);
	TextDrawSetShadow(LCTD[14], 0);
	TextDrawSetOutline(LCTD[14], 0);
	TextDrawBackgroundColor(LCTD[14], 150);
	TextDrawFont(LCTD[14], 1);
	TextDrawSetProportional(LCTD[14], 1);

	LCTD[15] = TextDrawCreate(528.000, 190.000, "GVL-1");
	TextDrawLetterSize(LCTD[15], 0.160, 0.899);
	TextDrawAlignment(LCTD[15], 1);
	TextDrawColor(LCTD[15], 1701078527);
	TextDrawSetShadow(LCTD[15], 0);
	TextDrawSetOutline(LCTD[15], 0);
	TextDrawBackgroundColor(LCTD[15], 150);
	TextDrawFont(LCTD[15], 1);
	TextDrawSetProportional(LCTD[15], 1);

	LCTD[16] = TextDrawCreate(547.000, 177.000, "_");
	TextDrawTextSize(LCTD[16], 22.000, 35.000);
	TextDrawAlignment(LCTD[16], 1);
	TextDrawColor(LCTD[16], -1);
	TextDrawSetShadow(LCTD[16], 0);
	TextDrawSetOutline(LCTD[16], 0);
	TextDrawBackgroundColor(LCTD[16], 0);
	TextDrawFont(LCTD[16], 5);
	TextDrawSetProportional(LCTD[16], 0);
	TextDrawSetPreviewModel(LCTD[16], 551);
	TextDrawSetPreviewRot(LCTD[16], -3.000, 0.000, 81.000, 0.899);
	TextDrawSetPreviewVehCol(LCTD[16], 0, 0);

	LCTD[17] = TextDrawCreate(514.000, 204.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[17], 119.000, 1.000);
	TextDrawAlignment(LCTD[17], 1);
	TextDrawColor(LCTD[17], 1701078527);
	TextDrawSetShadow(LCTD[17], 0);
	TextDrawSetOutline(LCTD[17], 0);
	TextDrawBackgroundColor(LCTD[17], 255);
	TextDrawFont(LCTD[17], 4);
	TextDrawSetProportional(LCTD[17], 1);

	LCTD[18] = TextDrawCreate(550.000, 205.000, "_");
	TextDrawTextSize(LCTD[18], 19.000, 29.000);
	TextDrawAlignment(LCTD[18], 1);
	TextDrawColor(LCTD[18], -1);
	TextDrawSetShadow(LCTD[18], 0);
	TextDrawSetOutline(LCTD[18], 0);
	TextDrawBackgroundColor(LCTD[18], 0);
	TextDrawFont(LCTD[18], 5);
	TextDrawSetProportional(LCTD[18], 0);
	TextDrawSetPreviewModel(LCTD[18], 499);
	TextDrawSetPreviewRot(LCTD[18], -3.000, 0.000, 81.000, 0.899);
	TextDrawSetPreviewVehCol(LCTD[18], 0, 0);

	LCTD[19] = TextDrawCreate(528.000, 214.000, "GVL-2");
	TextDrawLetterSize(LCTD[19], 0.160, 0.899);
	TextDrawAlignment(LCTD[19], 1);
	TextDrawColor(LCTD[19], 1701078527);
	TextDrawSetShadow(LCTD[19], 0);
	TextDrawSetOutline(LCTD[19], 0);
	TextDrawBackgroundColor(LCTD[19], 150);
	TextDrawFont(LCTD[19], 1);
	TextDrawSetProportional(LCTD[19], 1);

	LCTD[20] = TextDrawCreate(514.000, 227.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[20], 119.000, 1.000);
	TextDrawAlignment(LCTD[20], 1);
	TextDrawColor(LCTD[20], 1701078527);
	TextDrawSetShadow(LCTD[20], 0);
	TextDrawSetOutline(LCTD[20], 0);
	TextDrawBackgroundColor(LCTD[20], 255);
	TextDrawFont(LCTD[20], 4);
	TextDrawSetProportional(LCTD[20], 1);

	LCTD[21] = TextDrawCreate(547.000, 224.000, "_");
	TextDrawTextSize(LCTD[21], 24.000, 32.000);
	TextDrawAlignment(LCTD[21], 1);
	TextDrawColor(LCTD[21], -1);
	TextDrawSetShadow(LCTD[21], 0);
	TextDrawSetOutline(LCTD[21], 0);
	TextDrawBackgroundColor(LCTD[21], 0);
	TextDrawFont(LCTD[21], 5);
	TextDrawSetProportional(LCTD[21], 0);
	TextDrawSetPreviewModel(LCTD[21], 581);
	TextDrawSetPreviewRot(LCTD[21], -3.000, 0.000, 81.000, 0.899);
	TextDrawSetPreviewVehCol(LCTD[21], 0, 0);

	LCTD[22] = TextDrawCreate(515.000, 235.000, "MOTORBIKE");
	TextDrawLetterSize(LCTD[22], 0.150, 0.899);
	TextDrawAlignment(LCTD[22], 1);
	TextDrawColor(LCTD[22], 1701078527);
	TextDrawSetShadow(LCTD[22], 0);
	TextDrawSetOutline(LCTD[22], 0);
	TextDrawBackgroundColor(LCTD[22], 150);
	TextDrawFont(LCTD[22], 1);
	TextDrawSetProportional(LCTD[22], 1);

	LCTD[23] = TextDrawCreate(514.000, 250.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[23], 119.000, 1.000);
	TextDrawAlignment(LCTD[23], 1);
	TextDrawColor(LCTD[23], 1701078527);
	TextDrawSetShadow(LCTD[23], 0);
	TextDrawSetOutline(LCTD[23], 0);
	TextDrawBackgroundColor(LCTD[23], 255);
	TextDrawFont(LCTD[23], 4);
	TextDrawSetProportional(LCTD[23], 1);

	LCTD[24] = TextDrawCreate(545.000, 239.000, "_");
	TextDrawTextSize(LCTD[24], 23.000, 43.000);
	TextDrawAlignment(LCTD[24], 1);
	TextDrawColor(LCTD[24], -1);
	TextDrawSetShadow(LCTD[24], 0);
	TextDrawSetOutline(LCTD[24], 0);
	TextDrawBackgroundColor(LCTD[24], 0);
	TextDrawFont(LCTD[24], 5);
	TextDrawSetProportional(LCTD[24], 0);
	TextDrawSetPreviewModel(LCTD[24], 446);
	TextDrawSetPreviewRot(LCTD[24], -3.000, 0.000, 81.000, 0.899);
	TextDrawSetPreviewVehCol(LCTD[24], 0, 0);

	LCTD[25] = TextDrawCreate(531.000, 254.000, "BOAT");
	TextDrawLetterSize(LCTD[25], 0.150, 0.899);
	TextDrawAlignment(LCTD[25], 1);
	TextDrawColor(LCTD[25], 1701078527);
	TextDrawSetShadow(LCTD[25], 0);
	TextDrawSetOutline(LCTD[25], 0);
	TextDrawBackgroundColor(LCTD[25], 150);
	TextDrawFont(LCTD[25], 1);
	TextDrawSetProportional(LCTD[25], 1);

	LCTD[26] = TextDrawCreate(514.000, 267.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[26], 119.000, 1.000);
	TextDrawAlignment(LCTD[26], 1);
	TextDrawColor(LCTD[26], 1701078527);
	TextDrawSetShadow(LCTD[26], 0);
	TextDrawSetOutline(LCTD[26], 0);
	TextDrawBackgroundColor(LCTD[26], 255);
	TextDrawFont(LCTD[26], 4);
	TextDrawSetProportional(LCTD[26], 1);

	LCTD[27] = TextDrawCreate(548.000, 258.000, "_");
	TextDrawTextSize(LCTD[27], 24.000, 39.000);
	TextDrawAlignment(LCTD[27], 1);
	TextDrawColor(LCTD[27], -1);
	TextDrawSetShadow(LCTD[27], 0);
	TextDrawSetOutline(LCTD[27], 0);
	TextDrawBackgroundColor(LCTD[27], 0);
	TextDrawFont(LCTD[27], 5);
	TextDrawSetProportional(LCTD[27], 0);
	TextDrawSetPreviewModel(LCTD[27], 487);
	TextDrawSetPreviewRot(LCTD[27], -3.000, 0.000, 81.000, 0.899);
	TextDrawSetPreviewVehCol(LCTD[27], 0, 0);

	LCTD[28] = TextDrawCreate(515.000, 272.000, "HELICOPTER");
	TextDrawLetterSize(LCTD[28], 0.150, 0.899);
	TextDrawAlignment(LCTD[28], 1);
	TextDrawColor(LCTD[28], 1701078527);
	TextDrawSetShadow(LCTD[28], 0);
	TextDrawSetOutline(LCTD[28], 0);
	TextDrawBackgroundColor(LCTD[28], 150);
	TextDrawFont(LCTD[28], 1);
	TextDrawSetProportional(LCTD[28], 1);

	LCTD[29] = TextDrawCreate(514.000, 284.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[29], 119.000, 1.000);
	TextDrawAlignment(LCTD[29], 1);
	TextDrawColor(LCTD[29], 1701078527);
	TextDrawSetShadow(LCTD[29], 0);
	TextDrawSetOutline(LCTD[29], 0);
	TextDrawBackgroundColor(LCTD[29], 255);
	TextDrawFont(LCTD[29], 4);
	TextDrawSetProportional(LCTD[29], 1);

	LCTD[30] = TextDrawCreate(547.000, 275.000, "_");
	TextDrawTextSize(LCTD[30], 24.000, 39.000);
	TextDrawAlignment(LCTD[30], 1);
	TextDrawColor(LCTD[30], -1);
	TextDrawSetShadow(LCTD[30], 0);
	TextDrawSetOutline(LCTD[30], 0);
	TextDrawBackgroundColor(LCTD[30], 0);
	TextDrawFont(LCTD[30], 5);
	TextDrawSetProportional(LCTD[30], 0);
	TextDrawSetPreviewModel(LCTD[30], 577);
	TextDrawSetPreviewRot(LCTD[30], -3.000, 0.000, 81.000, 0.899);
	TextDrawSetPreviewVehCol(LCTD[30], 0, 0);

	LCTD[31] = TextDrawCreate(528.000, 287.000, "PLANE");
	TextDrawLetterSize(LCTD[31], 0.150, 0.899);
	TextDrawAlignment(LCTD[31], 1);
	TextDrawColor(LCTD[31], 1701078527);
	TextDrawSetShadow(LCTD[31], 0);
	TextDrawSetOutline(LCTD[31], 0);
	TextDrawBackgroundColor(LCTD[31], 150);
	TextDrawFont(LCTD[31], 1);
	TextDrawSetProportional(LCTD[31], 1);

	LCTD[32] = TextDrawCreate(514.000, 298.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[32], 119.000, 1.000);
	TextDrawAlignment(LCTD[32], 1);
	TextDrawColor(LCTD[32], 1701078527);
	TextDrawSetShadow(LCTD[32], 0);
	TextDrawSetOutline(LCTD[32], 0);
	TextDrawBackgroundColor(LCTD[32], 255);
	TextDrawFont(LCTD[32], 4);
	TextDrawSetProportional(LCTD[32], 1);

	LCTD[33] = TextDrawCreate(544.000, 311.000, "LD_BUM:blkdot");
	TextDrawTextSize(LCTD[33], 89.000, 18.000);
	TextDrawAlignment(LCTD[33], 1);
	TextDrawColor(LCTD[33], -1);
	TextDrawSetShadow(LCTD[33], 0);
	TextDrawSetOutline(LCTD[33], 0);
	TextDrawBackgroundColor(LCTD[33], 255);
	TextDrawFont(LCTD[33], 4);
	TextDrawSetProportional(LCTD[33], 1);

	LCTD[34] = TextDrawCreate(544.000, 307.000, "IIIIIIIIIIIIIIIIIIIIIIIIII");
	TextDrawLetterSize(LCTD[34], 0.310, 2.599);
	TextDrawAlignment(LCTD[34], 1);
	TextDrawColor(LCTD[34], 255);
	TextDrawSetShadow(LCTD[34], 0);
	TextDrawSetOutline(LCTD[34], 0);
	TextDrawBackgroundColor(LCTD[34], 150);
	TextDrawFont(LCTD[34], 1);
	TextDrawSetProportional(LCTD[34], 1);

	LCTD[35] = TextDrawCreate(453.000, 320.000, "SAN ANDREAS");
	TextDrawLetterSize(LCTD[35], 0.140, 0.999);
	TextDrawAlignment(LCTD[35], 1);
	TextDrawColor(LCTD[35], 1701078348);
	TextDrawSetShadow(LCTD[35], 0);
	TextDrawSetOutline(LCTD[35], 0);
	TextDrawBackgroundColor(LCTD[35], 150);
	TextDrawFont(LCTD[35], 1);
	TextDrawSetProportional(LCTD[35], 1);
}

CreatePlayerLCTD(playerid)
{
	PLCTD[playerid][0] = CreatePlayerTextDraw(playerid, 444.000, 183.000, "1. Juee");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][0], 0.220, 1.099);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][0], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][0], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][0], 1);

	PLCTD[playerid][1] = CreatePlayerTextDraw(playerid, 444.000, 196.000, "2. Seeong");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][1], 0.220, 1.099);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][1], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][1], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][1], 1);

	PLCTD[playerid][2] = CreatePlayerTextDraw(playerid, 444.000, 209.000, "3. 2002-02-22");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][2], 0.210, 1.099);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][2], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][2], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][2], 1);

	PLCTD[playerid][3] = CreatePlayerTextDraw(playerid, 444.000, 222.000, "4. Male");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][3], 0.210, 1.099);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][3], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][3], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][3], 1);

	PLCTD[playerid][4] = CreatePlayerTextDraw(playerid, 444.000, 235.000, "5. N/A");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][4], 0.210, 1.099);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][4], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][4], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][4], 1);

	PLCTD[playerid][5] = CreatePlayerTextDraw(playerid, 585.000, 189.000, "NO");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][5], 0.200, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][5], 2);
	PlayerTextDrawColor(playerid, PLCTD[playerid][5], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][5], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][5], 1);

	PLCTD[playerid][6] = CreatePlayerTextDraw(playerid, 585.000, 212.000, "YES");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][6], 0.200, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][6], 2);
	PlayerTextDrawColor(playerid, PLCTD[playerid][6], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][6], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][6], 1);

	PLCTD[playerid][7] = CreatePlayerTextDraw(playerid, 585.000, 234.000, "NO");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][7], 0.200, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][7], 2);
	PlayerTextDrawColor(playerid, PLCTD[playerid][7], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][7], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][7], 1);

	PLCTD[playerid][8] = CreatePlayerTextDraw(playerid, 585.000, 254.000, "NO");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][8], 0.200, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][8], 2);
	PlayerTextDrawColor(playerid, PLCTD[playerid][8], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][8], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][8], 1);

	PLCTD[playerid][9] = CreatePlayerTextDraw(playerid, 585.000, 271.000, "NO");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][9], 0.200, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][9], 2);
	PlayerTextDrawColor(playerid, PLCTD[playerid][9], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][9], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][9], 1);

	PLCTD[playerid][10] = CreatePlayerTextDraw(playerid, 585.000, 287.000, "NO");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][10], 0.200, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][10], 2);
	PlayerTextDrawColor(playerid, PLCTD[playerid][10], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][10], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][10], 1);

	PLCTD[playerid][11] = CreatePlayerTextDraw(playerid, 601.000, 189.000, "2000-03-22");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][11], 0.150, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][11], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][11], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][11], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][11], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][11], 1);

	PLCTD[playerid][12] = CreatePlayerTextDraw(playerid, 601.000, 212.000, "2000-03-22");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][12], 0.150, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][12], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][12], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][12], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][12], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][12], 1);

	PLCTD[playerid][13] = CreatePlayerTextDraw(playerid, 601.000, 234.000, "2000-03-22");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][13], 0.150, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][13], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][13], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][13], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][13], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][13], 1);

	PLCTD[playerid][14] = CreatePlayerTextDraw(playerid, 601.000, 254.000, "2000-03-22");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][14], 0.150, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][14], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][14], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][14], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][14], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][14], 1);

	PLCTD[playerid][15] = CreatePlayerTextDraw(playerid, 601.000, 271.000, "2000-03-22");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][15], 0.150, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][15], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][15], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][15], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][15], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][15], 1);

	PLCTD[playerid][16] = CreatePlayerTextDraw(playerid, 601.000, 287.000, "2000-03-22");
	PlayerTextDrawLetterSize(playerid, PLCTD[playerid][16], 0.150, 0.999);
	PlayerTextDrawAlignment(playerid, PLCTD[playerid][16], 1);
	PlayerTextDrawColor(playerid, PLCTD[playerid][16], 1701078527);
	PlayerTextDrawSetShadow(playerid, PLCTD[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, PLCTD[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, PLCTD[playerid][16], 150);
	PlayerTextDrawFont(playerid, PLCTD[playerid][16], 1);
	PlayerTextDrawSetProportional(playerid, PLCTD[playerid][16], 1);
}

ShowLCTD(playerid, targetid)
{
	static string[144];
	format(string, sizeof(string), "1. %s", GetPlayerPartName(playerid, 1));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][0], string);
	format(string, sizeof(string), "2. %s", GetPlayerPartName(playerid, 2));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][1], string);
	format(string, sizeof(string), "3. %d Tahun", AccountData[playerid][pAge]);
	PlayerTextDrawSetString(targetid, PLCTD[playerid][2], string);
	format(string, sizeof(string), "4. %s", (AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][3], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pGVL1LicTime]) ? ("NO") : ("YES"));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][5], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pGVL2LicTime]) ? ("NO") : ("YES"));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][6], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pMBLicTime]) ? ("NO") : ("YES"));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][7], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pBLicTime]) ? ("NO") : ("YES"));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][8], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pAir1LicTime]) ? ("NO") : ("YES"));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][9], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pAir2LicTime]) ? ("NO") : ("YES"));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][10], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pGVL1LicTime]) ? ("NO") : (sprintf("%s", ReturnSimpleDate(AccountData[playerid][pGVL1LicTime]))));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][11], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pGVL2LicTime]) ? ("NO") : (sprintf("%s", ReturnSimpleDate(AccountData[playerid][pGVL2LicTime]))));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][12], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pMBLicTime]) ? ("NO") : (sprintf("%s", ReturnSimpleDate(AccountData[playerid][pMBLicTime]))));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][13], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pBLicTime]) ? ("NO") : (sprintf("%s", ReturnSimpleDate(AccountData[playerid][pBLicTime]))));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][14], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pAir1LicTime]) ? ("NO") : (sprintf("%s", ReturnSimpleDate(AccountData[playerid][pAir1LicTime]))));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][15], string);
	format(string, sizeof(string), "%s", (gettime() > AccountData[playerid][pAir2LicTime]) ? ("NO") : (sprintf("%s", ReturnSimpleDate(AccountData[playerid][pAir2LicTime]))));
	PlayerTextDrawSetString(targetid, PLCTD[playerid][16], string);

	for(new x; x < 36; x++)
    {
        TextDrawShowForPlayer(targetid, LCTD[x]);
    }

	for(new x; x < 17; x++)
	{
		PlayerTextDrawShow(targetid, PLCTD[playerid][x]);
	}
	HideHBETD(targetid);

	SendClientMessage(targetid, Y_PAHLAWAN, "<!> "WHITE"Untuk menyembunyikan textdraw saat ini, gunakan "CMDEA"'/hidektd' "WHITE"sebagai CMD.");
}

HideLCTD(playerid)
{
	for(new x; x < 36; x++)
    {
        TextDrawHideForPlayer(playerid, LCTD[x]);
    }

	for(new x; x < 17; x++)
	{
		PlayerTextDrawHide(playerid, PLCTD[playerid][x]);
	}
	ShowHBETD(playerid);
}

ShowBPJSTD(playerid, showtoID)
{
	HideHBETD(showtoID);

	for(new x; x < 18; x++)
	{
		TextDrawShowForPlayer(showtoID, BPJSTD[x]);
	}

	new string[144];
	format(string, sizeof(string), "%d", AccountData[playerid][pID]);
	PlayerTextDrawSetString(showtoID, PBPJSTD[playerid][0], string);
	format(string, sizeof(string), "%s", AccountData[playerid][pName]);
	PlayerTextDrawSetString(showtoID, PBPJSTD[playerid][1], string);

	if(DocumentInfo[playerid][BPJSClass] == 1)
	{
		PlayerTextDrawSetString(showtoID, PBPJSTD[playerid][2], "I");
	}
	else if(DocumentInfo[playerid][BPJSClass] == 2)
	{
		PlayerTextDrawSetString(showtoID, PBPJSTD[playerid][2], "II");
	}
	else if(DocumentInfo[playerid][BPJSClass] == 3)
	{
		PlayerTextDrawSetString(showtoID, PBPJSTD[playerid][2], "III");
	}
	format(string, sizeof(string), "%d Tahun", AccountData[playerid][pAge]);
	PlayerTextDrawSetString(showtoID, PBPJSTD[playerid][3], string);
	format(string, sizeof(string), "%d", AccountData[playerid][pSSN]);
	PlayerTextDrawSetString(showtoID, PBPJSTD[playerid][4], string);

	for(new x; x < 5; x++)
	{
		PlayerTextDrawShow(showtoID, PBPJSTD[playerid][x]);
	}
	return 1;
}

HideBPJSTD(playerid)
{
	for(new x; x < 18; x++)
	{
		TextDrawHideForPlayer(playerid, BPJSTD[x]);
	}
	for(new x; x < 5; x++)
	{
		PlayerTextDrawHide(playerid, PBPJSTD[playerid][x]);
	}
	ShowHBETD(playerid);
	return 1;
}

ShowKTATD(playerid, showingID)
{
	HideHBETD(showingID);
	
	for(new x; x < 5; x++)
	{
		TextDrawShowForPlayer(showingID, KTATD[x]);
	}

	new string[144];
	if(AccountData[playerid][pFaction] == FACTION_LSPD || AccountData[playerid][pFaction] == FACTION_LSFD)
	{
		format(string, sizeof(string), "Nama: %s~n~Jabatan: %s~n~Nomor Induk: %d", AccountData[playerid][pName], GetRankName(playerid), AccountData[playerid][pBadge]);
	}
	else
	{
		format(string, sizeof(string), "Nama: %s~n~Jabatan: %s", AccountData[playerid][pName], GetRankName(playerid));
	}
	
	PlayerTextDrawSetString(showingID, PKTATD[playerid][0], string);
	PlayerTextDrawShow(showingID, PKTATD[playerid][0]);

	format(string, sizeof(string), "Adalah benar data di atas merupakan anggota %s", GetFactionName(playerid));
	PlayerTextDrawSetString(showingID, PKTATD[playerid][1], string);
	PlayerTextDrawShow(showingID, PKTATD[playerid][1]);

	PlayerTextDrawSetPreviewModel(showingID, PKTATD[playerid][2], GetPlayerSkin(playerid));
	PlayerTextDrawShow(showingID, PKTATD[playerid][2]);
	return 1;
}

HideKTATD(playerid)
{
	for(new x; x < 5; x++)
	{
		TextDrawHideForPlayer(playerid, KTATD[x]);
	}
	PlayerTextDrawHide(playerid, PKTATD[playerid][0]);
	PlayerTextDrawHide(playerid, PKTATD[playerid][1]);
	PlayerTextDrawHide(playerid, PKTATD[playerid][2]);
	ShowHBETD(playerid);
	return 1;
}

CreateIDCTD()
{
	IDCTD[0] = TextDrawCreate(385.000, 163.000, "LD_BEAT:chit");
	TextDrawTextSize(IDCTD[0], 30.000, 35.000);
	TextDrawAlignment(IDCTD[0], 1);
	TextDrawColor(IDCTD[0], -1396573441);
	TextDrawSetShadow(IDCTD[0], 0);
	TextDrawSetOutline(IDCTD[0], 0);
	TextDrawBackgroundColor(IDCTD[0], 255);
	TextDrawFont(IDCTD[0], 4);
	TextDrawSetProportional(IDCTD[0], 1);

	IDCTD[1] = TextDrawCreate(537.000, 163.000, "LD_BEAT:chit");
	TextDrawTextSize(IDCTD[1], 30.000, 35.000);
	TextDrawAlignment(IDCTD[1], 1);
	TextDrawColor(IDCTD[1], -1396573441);
	TextDrawSetShadow(IDCTD[1], 0);
	TextDrawSetOutline(IDCTD[1], 0);
	TextDrawBackgroundColor(IDCTD[1], 255);
	TextDrawFont(IDCTD[1], 4);
	TextDrawSetProportional(IDCTD[1], 1);

	IDCTD[2] = TextDrawCreate(390.000, 181.000, "ld_bum:blkdot");
	TextDrawTextSize(IDCTD[2], 172.000, 100.500);
	TextDrawAlignment(IDCTD[2], 1);
	TextDrawColor(IDCTD[2], -1396573441);
	TextDrawSetShadow(IDCTD[2], 0);
	TextDrawSetOutline(IDCTD[2], 0);
	TextDrawBackgroundColor(IDCTD[2], 255);
	TextDrawFont(IDCTD[2], 4);
	TextDrawSetProportional(IDCTD[2], 1);

	IDCTD[3] = TextDrawCreate(400.000, 169.000, "ld_bum:blkdot");
	TextDrawTextSize(IDCTD[3], 153.000, 122.500);
	TextDrawAlignment(IDCTD[3], 1);
	TextDrawColor(IDCTD[3], -1396573441);
	TextDrawSetShadow(IDCTD[3], 0);
	TextDrawSetOutline(IDCTD[3], 0);
	TextDrawBackgroundColor(IDCTD[3], 255);
	TextDrawFont(IDCTD[3], 4);
	TextDrawSetProportional(IDCTD[3], 1);

	IDCTD[4] = TextDrawCreate(385.000, 262.399, "LD_BEAT:chit");
	TextDrawTextSize(IDCTD[4], 30.000, 35.000);
	TextDrawAlignment(IDCTD[4], 1);
	TextDrawColor(IDCTD[4], -1396573441);
	TextDrawSetShadow(IDCTD[4], 0);
	TextDrawSetOutline(IDCTD[4], 0);
	TextDrawBackgroundColor(IDCTD[4], 255);
	TextDrawFont(IDCTD[4], 4);
	TextDrawSetProportional(IDCTD[4], 1);

	IDCTD[5] = TextDrawCreate(537.000, 262.399, "LD_BEAT:chit");
	TextDrawTextSize(IDCTD[5], 30.000, 35.000);
	TextDrawAlignment(IDCTD[5], 1);
	TextDrawColor(IDCTD[5], -1396573441);
	TextDrawSetShadow(IDCTD[5], 0);
	TextDrawSetOutline(IDCTD[5], 0);
	TextDrawBackgroundColor(IDCTD[5], 255);
	TextDrawFont(IDCTD[5], 4);
	TextDrawSetProportional(IDCTD[5], 1);

	IDCTD[6] = TextDrawCreate(477.000, 175.000, "REPUBLIK INDONESIA");
	TextDrawLetterSize(IDCTD[6], 0.180, 0.999);
	TextDrawAlignment(IDCTD[6], 2);
	TextDrawColor(IDCTD[6], 255);
	TextDrawSetShadow(IDCTD[6], 1);
	TextDrawSetOutline(IDCTD[6], 1);
	TextDrawBackgroundColor(IDCTD[6], 0);
	TextDrawFont(IDCTD[6], 1);
	TextDrawSetProportional(IDCTD[6], 1);

	IDCTD[7] = TextDrawCreate(477.000, 184.000, "KOTA PAHLAWAN");
	TextDrawLetterSize(IDCTD[7], 0.180, 0.999);
	TextDrawAlignment(IDCTD[7], 2);
	TextDrawColor(IDCTD[7], 255);
	TextDrawSetShadow(IDCTD[7], 1);
	TextDrawSetOutline(IDCTD[7], 1);
	TextDrawBackgroundColor(IDCTD[7], 0);
	TextDrawFont(IDCTD[7], 1);
	TextDrawSetProportional(IDCTD[7], 1);

	IDCTD[8] = TextDrawCreate(396.000, 198.000, "NIK   :");
	TextDrawLetterSize(IDCTD[8], 0.250, 1.499);
	TextDrawAlignment(IDCTD[8], 1);
	TextDrawColor(IDCTD[8], 255);
	TextDrawSetShadow(IDCTD[8], 1);
	TextDrawSetOutline(IDCTD[8], 5);
	TextDrawBackgroundColor(IDCTD[8], 0);
	TextDrawFont(IDCTD[8], 1);
	TextDrawSetProportional(IDCTD[8], 1);

	IDCTD[9] = TextDrawCreate(516.000, 199.000, "LD_BUM:blkdot");
	TextDrawTextSize(IDCTD[9], 37.000, 56.000);
	TextDrawAlignment(IDCTD[9], 1);
	TextDrawColor(IDCTD[9], 33023);
	TextDrawSetShadow(IDCTD[9], 0);
	TextDrawSetOutline(IDCTD[9], 0);
	TextDrawBackgroundColor(IDCTD[9], 255);
	TextDrawFont(IDCTD[9], 4);
	TextDrawSetProportional(IDCTD[9], 1);

	IDCTD[10] = TextDrawCreate(516.000, 255.000, "LD_BUM:blkdot");
	TextDrawTextSize(IDCTD[10], 37.000, 32.000);
	TextDrawAlignment(IDCTD[10], 1);
	TextDrawColor(IDCTD[10], -1396573441);
	TextDrawSetShadow(IDCTD[10], 0);
	TextDrawSetOutline(IDCTD[10], 0);
	TextDrawBackgroundColor(IDCTD[10], 255);
	TextDrawFont(IDCTD[10], 4);
	TextDrawSetProportional(IDCTD[10], 1);

	IDCTD[11] = TextDrawCreate(396.000, 215.000, "Nama");
	TextDrawLetterSize(IDCTD[11], 0.129, 0.699);
	TextDrawAlignment(IDCTD[11], 1);
	TextDrawColor(IDCTD[11], 255);
	TextDrawSetShadow(IDCTD[11], 1);
	TextDrawSetOutline(IDCTD[11], 1);
	TextDrawBackgroundColor(IDCTD[11], 0);
	TextDrawFont(IDCTD[11], 1);
	TextDrawSetProportional(IDCTD[11], 1);

	IDCTD[12] = TextDrawCreate(396.000, 223.000, "Tanggal Lahir");
	TextDrawLetterSize(IDCTD[12], 0.129, 0.699);
	TextDrawAlignment(IDCTD[12], 1);
	TextDrawColor(IDCTD[12], 255);
	TextDrawSetShadow(IDCTD[12], 1);
	TextDrawSetOutline(IDCTD[12], 1);
	TextDrawBackgroundColor(IDCTD[12], 0);
	TextDrawFont(IDCTD[12], 1);
	TextDrawSetProportional(IDCTD[12], 1);

	IDCTD[13] = TextDrawCreate(396.000, 231.000, "Jenis Kelamin");
	TextDrawLetterSize(IDCTD[13], 0.129, 0.699);
	TextDrawAlignment(IDCTD[13], 1);
	TextDrawColor(IDCTD[13], 255);
	TextDrawSetShadow(IDCTD[13], 1);
	TextDrawSetOutline(IDCTD[13], 1);
	TextDrawBackgroundColor(IDCTD[13], 0);
	TextDrawFont(IDCTD[13], 1);
	TextDrawSetProportional(IDCTD[13], 1);

	IDCTD[14] = TextDrawCreate(396.000, 239.000, "Tinggi Badan");
	TextDrawLetterSize(IDCTD[14], 0.129, 0.699);
	TextDrawAlignment(IDCTD[14], 1);
	TextDrawColor(IDCTD[14], 255);
	TextDrawSetShadow(IDCTD[14], 1);
	TextDrawSetOutline(IDCTD[14], 1);
	TextDrawBackgroundColor(IDCTD[14], 0);
	TextDrawFont(IDCTD[14], 1);
	TextDrawSetProportional(IDCTD[14], 1);

	IDCTD[15] = TextDrawCreate(396.000, 247.000, "Pekerjaan");
	TextDrawLetterSize(IDCTD[15], 0.129, 0.699);
	TextDrawAlignment(IDCTD[15], 1);
	TextDrawColor(IDCTD[15], 255);
	TextDrawSetShadow(IDCTD[15], 1);
	TextDrawSetOutline(IDCTD[15], 1);
	TextDrawBackgroundColor(IDCTD[15], 0);
	TextDrawFont(IDCTD[15], 1);
	TextDrawSetProportional(IDCTD[15], 1);

	IDCTD[16] = TextDrawCreate(396.000, 256.000, "Berlaku Hingga");
	TextDrawLetterSize(IDCTD[16], 0.129, 0.699);
	TextDrawAlignment(IDCTD[16], 1);
	TextDrawColor(IDCTD[16], 255);
	TextDrawSetShadow(IDCTD[16], 1);
	TextDrawSetOutline(IDCTD[16], 1);
	TextDrawBackgroundColor(IDCTD[16], 0);
	TextDrawFont(IDCTD[16], 1);
	TextDrawSetProportional(IDCTD[16], 1);

	IDCTD[17] = TextDrawCreate(534.500, 257.000, "2025");
	TextDrawLetterSize(IDCTD[17], 0.129, 0.799);
	TextDrawAlignment(IDCTD[17], 2);
	TextDrawColor(IDCTD[17], 255);
	TextDrawSetShadow(IDCTD[17], 1);
	TextDrawSetOutline(IDCTD[17], 1);
	TextDrawBackgroundColor(IDCTD[17], 0);
	TextDrawFont(IDCTD[17], 1);
	TextDrawSetProportional(IDCTD[17], 1);
}

CreatePlayerIDCTD(playerid)
{
	PIDCTD[playerid][0] = CreatePlayerTextDraw(playerid, 498.000, 197.000, "_");
	PlayerTextDrawTextSize(playerid, PIDCTD[playerid][0], 72.000, 85.000);
	PlayerTextDrawAlignment(playerid, PIDCTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, PIDCTD[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, PIDCTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, PIDCTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PIDCTD[playerid][0], 0);
	PlayerTextDrawFont(playerid, PIDCTD[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, PIDCTD[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, PIDCTD[playerid][0], 264);
	PlayerTextDrawSetPreviewRot(playerid, PIDCTD[playerid][0], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, PIDCTD[playerid][0], 0, 0);

	PIDCTD[playerid][1] = CreatePlayerTextDraw(playerid, 438.000, 198.000, "1234567890");
	PlayerTextDrawLetterSize(playerid, PIDCTD[playerid][1], 0.190, 1.499);
	PlayerTextDrawAlignment(playerid, PIDCTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, PIDCTD[playerid][1], 255);
	PlayerTextDrawSetShadow(playerid, PIDCTD[playerid][1], 1);
	PlayerTextDrawSetOutline(playerid, PIDCTD[playerid][1], 10);
	PlayerTextDrawBackgroundColor(playerid, PIDCTD[playerid][1], 0);
	PlayerTextDrawFont(playerid, PIDCTD[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, PIDCTD[playerid][1], 1);

	PIDCTD[playerid][2] = CreatePlayerTextDraw(playerid, 442.000, 215.000, ": Ditzy Seruni");
	PlayerTextDrawLetterSize(playerid, PIDCTD[playerid][2], 0.129, 0.699);
	PlayerTextDrawAlignment(playerid, PIDCTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, PIDCTD[playerid][2], 255);
	PlayerTextDrawSetShadow(playerid, PIDCTD[playerid][2], 1);
	PlayerTextDrawSetOutline(playerid, PIDCTD[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, PIDCTD[playerid][2], 0);
	PlayerTextDrawFont(playerid, PIDCTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PIDCTD[playerid][2], 1);

	PIDCTD[playerid][3] = CreatePlayerTextDraw(playerid, 442.000, 223.000, ": 23/2/1999");
	PlayerTextDrawLetterSize(playerid, PIDCTD[playerid][3], 0.129, 0.699);
	PlayerTextDrawAlignment(playerid, PIDCTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, PIDCTD[playerid][3], 255);
	PlayerTextDrawSetShadow(playerid, PIDCTD[playerid][3], 1);
	PlayerTextDrawSetOutline(playerid, PIDCTD[playerid][3], 1);
	PlayerTextDrawBackgroundColor(playerid, PIDCTD[playerid][3], 0);
	PlayerTextDrawFont(playerid, PIDCTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PIDCTD[playerid][3], 1);

	PIDCTD[playerid][4] = CreatePlayerTextDraw(playerid, 442.000, 231.000, ": Laki-Laki");
	PlayerTextDrawLetterSize(playerid, PIDCTD[playerid][4], 0.129, 0.699);
	PlayerTextDrawAlignment(playerid, PIDCTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, PIDCTD[playerid][4], 255);
	PlayerTextDrawSetShadow(playerid, PIDCTD[playerid][4], 1);
	PlayerTextDrawSetOutline(playerid, PIDCTD[playerid][4], 1);
	PlayerTextDrawBackgroundColor(playerid, PIDCTD[playerid][4], 0);
	PlayerTextDrawFont(playerid, PIDCTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, PIDCTD[playerid][4], 1);

	PIDCTD[playerid][5] = CreatePlayerTextDraw(playerid, 442.000, 239.000, ": 180cm");
	PlayerTextDrawLetterSize(playerid, PIDCTD[playerid][5], 0.129, 0.699);
	PlayerTextDrawAlignment(playerid, PIDCTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, PIDCTD[playerid][5], 255);
	PlayerTextDrawSetShadow(playerid, PIDCTD[playerid][5], 1);
	PlayerTextDrawSetOutline(playerid, PIDCTD[playerid][5], 1);
	PlayerTextDrawBackgroundColor(playerid, PIDCTD[playerid][5], 0);
	PlayerTextDrawFont(playerid, PIDCTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, PIDCTD[playerid][5], 1);

	PIDCTD[playerid][6] = CreatePlayerTextDraw(playerid, 442.000, 247.000, ": Penambang");
	PlayerTextDrawLetterSize(playerid, PIDCTD[playerid][6], 0.129, 0.699);
	PlayerTextDrawAlignment(playerid, PIDCTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, PIDCTD[playerid][6], 255);
	PlayerTextDrawSetShadow(playerid, PIDCTD[playerid][6], 1);
	PlayerTextDrawSetOutline(playerid, PIDCTD[playerid][6], 1);
	PlayerTextDrawBackgroundColor(playerid, PIDCTD[playerid][6], 0);
	PlayerTextDrawFont(playerid, PIDCTD[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, PIDCTD[playerid][6], 1);

	PIDCTD[playerid][7] = CreatePlayerTextDraw(playerid, 515.000, 256.000, "LD_TATT:11ggift");
	PlayerTextDrawTextSize(playerid, PIDCTD[playerid][7], 38.000, 35.000);
	PlayerTextDrawAlignment(playerid, PIDCTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, PIDCTD[playerid][7], -1396573441);
	PlayerTextDrawSetShadow(playerid, PIDCTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, PIDCTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, PIDCTD[playerid][7], 255);
	PlayerTextDrawFont(playerid, PIDCTD[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, PIDCTD[playerid][7], 1);

	PIDCTD[playerid][8] = CreatePlayerTextDraw(playerid, 442.000, 256.000, ": Seumur Hidup");
	PlayerTextDrawLetterSize(playerid, PIDCTD[playerid][8], 0.129, 0.699);
	PlayerTextDrawAlignment(playerid, PIDCTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, PIDCTD[playerid][8], 255);
	PlayerTextDrawSetShadow(playerid, PIDCTD[playerid][8], 1);
	PlayerTextDrawSetOutline(playerid, PIDCTD[playerid][8], 1);
	PlayerTextDrawBackgroundColor(playerid, PIDCTD[playerid][8], 0);
	PlayerTextDrawFont(playerid, PIDCTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, PIDCTD[playerid][8], 1);
}

ShowIDCTD(playerid, targetid)
{
	PlayerTextDrawSetPreviewModel(targetid, PIDCTD[playerid][0], GetPlayerSkin(playerid));

	new string[144];

	format(string, sizeof(string), "%d", AccountData[playerid][pSSN]);
	PlayerTextDrawSetString(targetid, PIDCTD[playerid][1], string);
	format(string, sizeof(string), ": %s", AccountData[playerid][pName]);
	PlayerTextDrawSetString(targetid, PIDCTD[playerid][2], string);
	format(string, sizeof(string), ": %d Tahun", AccountData[playerid][pAge]);
	PlayerTextDrawSetString(targetid, PIDCTD[playerid][3], string);
	format(string, sizeof(string), ": %s", (AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"));
	PlayerTextDrawSetString(targetid, PIDCTD[playerid][4], string);
	format(string, sizeof(string), ": %d cm", AccountData[playerid][pBodyHeight]);
	PlayerTextDrawSetString(targetid, PIDCTD[playerid][5], string);
	format(string, sizeof(string), ": %s", GetJobName(playerid));
	PlayerTextDrawSetString(targetid, PIDCTD[playerid][6], string);
	format(string, sizeof(string), ": %s", ReturnSimpleDate(AccountData[playerid][pKTPTime]));
	PlayerTextDrawSetString(targetid, PIDCTD[playerid][8], string);

	for(new x; x < 18; x++)
    {
        TextDrawShowForPlayer(targetid, IDCTD[x]);
    }

	for(new x; x < 9; x++)
	{
		PlayerTextDrawShow(targetid, PIDCTD[playerid][x]);
	}
	HideHBETD(targetid);

	SendClientMessage(targetid, Y_PAHLAWAN, "<!> "WHITE"Untuk menyembunyikan textdraw saat ini, gunakan "CMDEA"'/hidektd' "WHITE"sebagai CMD.");
}

HideIDCTD(playerid)
{
	for(new x; x < 18; x++)
    {
        TextDrawHideForPlayer(playerid, IDCTD[x]);
    }

	for(new x; x < 9; x++)
	{
		PlayerTextDrawHide(playerid, PIDCTD[playerid][x]);
	}
	ShowHBETD(playerid);
}