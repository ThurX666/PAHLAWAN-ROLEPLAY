#include <YSI_Coding\y_hooks>

enum ___g_StandDetails
{
    Float:StandPos[3],
    StandName[64],

    //external
    STREAMER_TAG_3D_TEXT_LABEL:g_StandInfoLabel
};

new STREAMER_TAG_AREA:RamadhanMusic;
new STREAMER_TAG_OBJECT:RamadhanObj;

new g_RamadhanStand[][___g_StandDetails] =
{
    {{724.1068,-1394.2528,13.5175}, "Kolak Pisang Berkah"},
    {{727.9531,-1394.2452,13.5176}, "Gorengan"},
    {{732.0241,-1394.2455,13.5176}, "Bubur Sumsum"},
    {{735.8853,-1394.2454,13.5176}, "Pancake Durian Ucok"},
    {{739.4830,-1394.2454,13.5176}, "Lontong Medan"},
    {{743.2866,-1394.2537,13.4975}, "Soto Medan"},
    {{747.3483,-1394.2440,13.5076}, "Ayam Geprek Mak Judes"},
    {{750.9348,-1394.2412,13.5076}, "Teh Poci"},
    {{750.6783,-1406.8920,13.4193}, "Vanilla Milkshake"},
    {{746.9667,-1406.8979,13.4192}, "Mie Ayam Jamur Haji Mahmud"},
    {{742.8489,-1406.8892,13.4093}, "Martabak Mesir"},
    {{739.0829,-1406.8894,13.4293}, "Sup Iga Ayahanda"},
    {{735.3596,-1406.8810,13.4294}, "Sate Padang Memeng"},
    {{731.6996,-1406.8809,13.4294}, "Pecel Lele"},
    {{727.5620,-1406.8732,13.4294}, "Seblak Jletet Neng Ayu"},
    {{723.8150,-1406.8942,13.4293}, "Bakso Bangjon"}
};

new const g_AsmaulHusnaMUI[][144] =
{
    "Ar-Rahman - Yang Maha Pengasih",
    "Ar-Rahim - Yang Maha Penyayang",
    "Al-Malik - Yang Maha Merajai",
    "Al-Quddus - Yang Maha Suci",
    "As-Salaam - Yang Maha Memberi Kesejahteraan",
    "Al-Mu'min - Yang Maha Memberi Keamanan",
    "Al-Muhaimin - Yang Maha Mengatur",
    "Al-Aziz - Yang Maha Perkasa",
    "Al-Jabbar - Yang Memiliki Mutlak Kegagahan",
    "Al-Mutakabbir - Yang Maha Megah",
    "Al-Khaliq - Yang Maha Pencipta",
    "Al-Bari - Yang Maha Melepaskan",
    "Al-Mushawwir - Yang Maha Membentuk Rupa",
    "Al-Ghaffaar - Yang Maha Pengampun",
    "Al-Qahhaar - Yang Maha Memaksa",
    "Al-Wahhaab - Yang Maha Pemberi Karunia",
    "Ar-Razzaaq - Yang Maha Pemberi Rezeki",
    "Al-Fattaah - Yang Maha Pembuka Rahmat",
    "Al-'Aliim - Yang Maha Mengetahui",
    "Al-Qaabidh - Yang Maha Menyempitkan",
    "Al-Baasith - Yang Maha Melapangkan",
    "Al-Khaafidh - Yang Maha Merendahkan",
    "Ar-Raafi - Yang Maha Meninggikan",
    "Al-Mu'izz - Yang Maha Memuliakan",
    "Al-Mudzil - Yang Maha Menghinakan",
    "As-Samii - Yang Maha Mendengar",
    "Al-Bashiir - Yang Maha Melihat",
    "Al-Hakam - Yang Maha Menetapkan",
    "Al-'Adl - Yang Maha Adil",
    "Al-Lathiif - Yang Maha Lembut",
    "Al-Khabiir - Yang Maha Mengenal",
    "Al-Haliim - Yang Maha Penyantun",
    "Al-'Azhiim - Yang Maha Agung",
    "Al-Ghafuur - Yang Maha Memberi Pengampunan",
    "Ash-Shakuur - Yang Maha Pembalas Budi",
    "Al-'Aliy - Yang Maha Tinggi",
    "Al-Kabiir - Yang Maha Besar",
    "Al-Hafizh - Yang Maha Memelihara",
    "Al-Muqiit - Yang Maha Pemberi Kecukupan",
    "Al-Hasiib - Yang Maha Membuat Perhitungan",
    "Al-Jaliil - Yang Maha Luhur",
    "Al-Kariim - Yang Maha Pemurah",
    "Ar-Raqiib - Yang Maha Mengawasi",
    "Al-Mujiib - Yang Maha Mengabulkan",
    "Al-Waasi' - Yang Maha Luas",
    "Al-Hakiim - Yang Maha Bijaksana",
    "Al-Waduud - Yang Maha Mengasihi",
    "Al-Majiid - Yang Maha Mulia",
    "Al-Baa'its - Yang Maha Membangkitkan",
    "Ash-Shahiid - Yang Maha Menyaksikan",
    "Al-Haqq - Yang Maha Benar",
    "Al-Wakiil - Yang Maha Memelihara",
    "Al-Qawiyyu - Yang Maha Kuat",
    "Al-Matiin - Yang Maha Kokoh",
    "Al-Waliyy - Yang Maha Melindungi",
    "Al-Hamiid - Yang Maha Terpuji",
    "Al-Muhshii - Yang Maha Menghitung",
    "Al-Mubdi - Yang Maha Memulai",
    "Al-Mu'iid - Yang Maha Mengembalikan Kehidupan",
    "Al-Muhyii - Yang Maha Menghidupkan",
    "Al-Mumiitu - Yang Maha Mematikan",
    "Al-Hayyu - Yang Maha Hidup",
    "Al-Qayyuum - Yang Maha Mandiri",
    "Al-Waajid - Yang Maha Penemu",
    "Al-Maajid - Yang Maha Mulia",
    "Al-Wahid - Yang Maha Tunggal",
    "Al-Ahad - Yang Maha Esa",
    "As-Shamad - Yang Maha Dibutuhkan",
    "Al-Qaadir - Yang Maha Menentukan",
    "Al-Muqtadir - Yang Maha Berkuasa",
    "Al-Muqaddim - Yang Maha Mendahulukan",
    "Al-Mu'akkhir - Yang Maha Mengakhirkan",
    "Al-Awwal - Yang Maha Awal",
    "Al-Aakhir - Yang Maha Akhir",
    "Az-Zhaahir - Yang Maha Nyata",
    "Al-Baathin - Yang Maha Ghaib",
    "Al-Waali - Yang Maha Memerintah",
    "Al-Muta'aalii - Yang Maha Tinggi",
    "Al-Barr - Yang Maha Penderma",
    "At-Tawwaab - Yang Maha Penerima Tobat",
    "Al-Muntaqim - Yang Maha Pemberi Balasan",
    "Al-Afuww - Yang Maha Pemaaf",
    "Ar-Ra'uuf - Yang Maha Pengasuh",
    "Malikul Mulk - Pemilik Kerajaan",
    "Dzul Jalaali Wal Ikraam - Yang Maha Pemilik Kebesaran dan Kemuliaan",
    "Al-Muqsith - Yang Maha Pemberi Keadilan",
    "Al-Jamii' - Yang Maha Mengumpulkan",
    "Al-Ghaniyy - Yang Maha Kaya",
    "Al-Mughnii - Yang Maha Pemberi Kekayaan",
    "Al-Maani - Yang Maha Mencegah",
    "Ad-Dhaar - Yang Maha Penimpa Kemudharatan",
    "An-Nafii - Yang Maha Memberi Manfaat",
    "An-Nuur - Yang Maha Bercahaya",
    "Al-Haadii - Yang Maha Pemberi Petunjuk",
    "Al-Badii' - Yang Maha Pencipta",
    "Al-Baaqii - Yang Maha Kekal",
    "Al-Waarits - Yang Maha Pewaris",
    "Ar-Rasyiid - Yang Maha Pandai",
    "As-Shabuur - Yang Maha Sabar"
};

Stand_Nearest(playerid)
{
    for(new i; i < sizeof(g_RamadhanStand); i++) if (IsPlayerInRangeOfPoint(playerid, 3.0, g_RamadhanStand[i][StandPos][0], g_RamadhanStand[i][StandPos][1], g_RamadhanStand[i][StandPos][2]))
	{
		if(GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0)
			return i;
	}
	return -1;
}

hook OnGameModeInit()
{
    RamadhanObj = CreateDynamicObject(18762, 768.109985, -1405.195556, 14.709830, -0.000852, -0.400950, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(18762, 768.110168, -1402.209472, 16.720726, -0.000852, 89.599052, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(18762, 768.102050, -1399.029174, 16.742929, -0.000852, 89.599052, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(18762, 768.110229, -1396.975219, 14.767215, -0.000852, -0.400950, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(975, 758.419250, -1401.921142, 21.652204, 59.599010, 0.001622, 179.996597, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 758.419372, -1399.189331, 21.744577, 60.400920, 179.998321, 0.000062, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 758.419433, -1396.441650, 20.186157, 60.400920, 179.998321, 0.000062, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 758.419250, -1404.620727, 20.068313, 59.599010, 0.001622, 179.996597, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 749.579528, -1401.920898, 21.652198, 59.599010, 0.001619, 179.996505, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 749.579528, -1399.189086, 21.744579, 60.400886, 179.998321, 0.000061, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 749.569396, -1396.441406, 20.186162, 60.400920, 179.998321, 0.000062, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 749.578979, -1404.620483, 20.068311, 59.599010, 0.001622, 179.996597, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 740.779479, -1401.920654, 21.652204, 59.599010, 0.001621, 179.996505, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 740.779541, -1399.188842, 21.744581, 60.400886, 179.998321, 0.000076, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 740.759582, -1396.441162, 20.186166, 60.400920, 179.998321, 0.000062, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 740.788269, -1404.620239, 20.068313, 59.599010, 0.001607, 179.996566, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 731.959167, -1401.920410, 21.652202, 59.599010, 0.001619, 179.996475, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 731.959167, -1399.188598, 21.744579, 60.400886, 179.998321, 0.000123, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 731.959350, -1396.440917, 20.186170, 60.400920, 179.998321, 0.000062, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 731.948059, -1404.619995, 20.068317, 59.599010, 0.001607, 179.996566, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(638, 760.807739, -1400.551391, 12.908705, -0.400950, 0.000844, 179.997909, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 801, "gta_proc_ferns", "veg_bush2", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 764.967407, -1390.507812, 12.498652, -0.400943, 0.000844, 179.997894, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 764.966918, -1410.542724, 12.358780, -0.400943, 0.000844, 179.997894, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 758.227416, -1390.507690, 12.498655, -0.400936, 0.000844, 179.997894, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 758.226928, -1410.542602, 12.358784, -0.400936, 0.000844, 179.997894, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 751.474609, -1390.507446, 12.498656, -0.400936, 0.000844, 179.997894, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 751.474121, -1410.542358, 12.358785, -0.400936, 0.000844, 179.997894, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 744.734558, -1390.507324, 12.498654, -0.400929, 0.000844, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 744.734069, -1410.542236, 12.358782, -0.400929, 0.000844, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 737.972534, -1390.507202, 12.498655, -0.400929, 0.000844, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 737.972045, -1410.542114, 12.358782, -0.400929, 0.000844, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 731.232238, -1390.506958, 12.498657, -0.400920, 0.000844, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 731.231750, -1410.541870, 12.358781, -0.400920, 0.000844, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 724.471801, -1390.506835, 12.498657, -0.400913, 0.000843, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 724.471313, -1410.541748, 12.358786, -0.400913, 0.000843, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 761.647460, -1410.478393, 13.349246, -0.400936, 90.000846, 179.997894, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 761.648010, -1390.713256, 13.487231, -0.400936, 90.000846, 179.997894, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 752.977172, -1410.478271, 13.349247, -0.400929, 90.000846, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 752.977661, -1390.713134, 13.487234, -0.400929, 90.000846, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 743.897705, -1410.478027, 13.349247, -0.400929, 90.000846, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 743.898193, -1390.712890, 13.487236, -0.400929, 90.000846, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 735.227294, -1410.477783, 13.349251, -0.400920, 90.000846, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 735.227783, -1390.712646, 13.487236, -0.400920, 90.000846, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 728.776672, -1410.477661, 13.349253, -0.400913, 90.000846, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(991, 728.777160, -1390.712524, 13.487236, -0.400913, 90.000846, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 11092, "burgalrystore_sfse", "ws_warehswin2", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(18981, 733.774536, -1401.788818, 11.944893, 0.399998, 90.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 11145, "carrierint_sfs", "ws_floor2", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 731.947875, -1407.336914, 18.474311, 59.599010, 0.001607, 179.996566, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 740.788146, -1407.337158, 18.474296, 59.599010, 0.001607, 179.996566, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 749.587646, -1407.337402, 18.474306, 59.599010, 0.001589, 179.996505, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 758.427978, -1407.337646, 18.474300, 59.599010, 0.001589, 179.996505, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 758.419494, -1393.720214, 18.640113, 60.400920, 179.998321, 0.000062, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 749.579467, -1393.719970, 18.640119, 60.400920, 179.998321, 0.000062, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 740.759338, -1393.719726, 18.640121, 60.400920, 179.998352, 0.000031, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 731.919372, -1393.719482, 18.640125, 60.400920, 179.998352, 0.000031, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 758.419494, -1390.946044, 17.064447, 60.400920, 179.998321, 0.000062, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 749.549499, -1390.945800, 17.064453, 60.400920, 179.998321, 0.000062, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 740.738891, -1390.945556, 17.064447, 60.400920, 179.998336, 0.000047, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 731.868896, -1390.945312, 17.064456, 60.400920, 179.998336, 0.000047, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 731.947814, -1410.053955, 16.880302, 59.599010, 0.001607, 179.996566, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 740.797973, -1410.054199, 16.880294, 59.599010, 0.001607, 179.996566, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(18764, 763.649536, -1400.548828, 10.398664, -0.000844, -0.400950, 89.998199, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF899D48);
    RamadhanObj = CreateDynamicObject(2790, 768.549865, -1400.999755, 16.367206, -0.002252, -0.400929, 90.198303, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 1, "KE XXI - 1445 H TAHUN 2024", 130, "Verdana", 25, 1, 0xFFBBBBBB, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(2790, 768.549865, -1401.003051, 16.827203, -0.002252, -0.400929, 90.198303, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 1, "RAMADHAN FAIR", 130, "Verdana", 50, 1, 0xFFB0AB4D, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(2695, 768.681396, -1396.958618, 14.113280, -0.000852, -0.400950, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 768.681457, -1396.967529, 15.403246, -0.000852, -0.400950, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 768.681518, -1396.950439, 12.953309, -0.000852, -0.400950, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 768.681213, -1405.219116, 14.055608, -0.000852, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 768.681213, -1405.228149, 15.345580, -0.000852, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 768.681213, -1405.211059, 12.895640, -0.000852, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 768.681274, -1404.885620, 16.508003, -0.000852, 89.599060, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 768.681213, -1404.317504, 16.821977, -0.000852, 89.599060, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 768.681457, -1397.767456, 16.867708, -0.000838, -90.400894, 89.998344, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 768.681457, -1397.214721, 16.561559, -0.000838, -90.400894, 89.998344, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 750.660095, -1393.178710, 13.512831, -0.000837, -0.400950, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 8618, "ceasersign", "ceaserssign01_128", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 2767, "cb_details", "cluckinbig_cb", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 2767, "cb_details", "pattern1_cb", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 750.909973, -1407.940063, 13.399783, 0.000850, 0.400950, -90.001060, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 2343, "cb_bar_bits", "CJ_POLISHED", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 2767, "cb_details", "wrapper_cb", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 2767, "cb_details", "fillet_cb", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 747.128845, -1393.178466, 13.512834, -0.000837, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 13363, "cephotoblockcs_t", "wallwashv128", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 5712, "cemetint_law", "pizzabox", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 13363, "cephotoblockcs_t", "BigS01_law", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 747.128601, -1407.940063, 13.409785, 0.000849, 0.400943, -90.001106, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 3335, "ceroadsigns", "sw_roadsign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 13364, "cetown3cs_t", "des_cafesign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 3335, "ceroadsigns", "sw_barberpole", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 743.049011, -1393.178222, 13.492835, -0.000837, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 8618, "ceasersign", "ceaserssign01_128", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 2767, "cb_details", "cluckinbig_cb", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 2767, "cb_details", "pattern1_cb", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 743.048645, -1407.939941, 13.409782, 0.000849, 0.400943, -90.001106, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 2343, "cb_bar_bits", "CJ_POLISHED", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 2767, "cb_details", "wrapper_cb", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 2767, "cb_details", "fillet_cb", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 739.267639, -1393.178100, 13.522831, -0.000837, -0.400936, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 13363, "cephotoblockcs_t", "wallwashv128", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 5712, "cemetint_law", "pizzabox", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 13363, "cephotoblockcs_t", "BigS01_law", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 739.267395, -1407.940185, 13.429784, 0.000849, 0.400934, -90.001144, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 3335, "ceroadsigns", "sw_roadsign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 13364, "cetown3cs_t", "des_cafesign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 3335, "ceroadsigns", "sw_barberpole", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 735.589050, -1393.178100, 13.522832, -0.000837, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 8618, "ceasersign", "ceaserssign01_128", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 2767, "cb_details", "cluckinbig_cb", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 2767, "cb_details", "pattern1_cb", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 735.588806, -1407.939819, 13.419784, 0.000849, 0.400943, -90.001106, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 2343, "cb_bar_bits", "CJ_POLISHED", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 2767, "cb_details", "wrapper_cb", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 2767, "cb_details", "fillet_cb", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 731.807678, -1393.178222, 13.522830, -0.000837, -0.400936, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 13363, "cephotoblockcs_t", "wallwashv128", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 5712, "cemetint_law", "pizzabox", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 13363, "cephotoblockcs_t", "BigS01_law", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 731.807312, -1407.939697, 13.419783, 0.000849, 0.400934, -90.001144, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 3335, "ceroadsigns", "sw_roadsign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 13364, "cetown3cs_t", "des_cafesign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 3335, "ceroadsigns", "sw_barberpole", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 727.727966, -1393.178100, 13.522833, -0.000837, -0.400936, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 8618, "ceasersign", "ceaserssign01_128", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 2767, "cb_details", "cluckinbig_cb", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 2767, "cb_details", "pattern1_cb", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 727.727539, -1407.939575, 13.409784, 0.000849, 0.400934, -90.001144, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 2343, "cb_bar_bits", "CJ_POLISHED", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 2767, "cb_details", "wrapper_cb", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 2767, "cb_details", "fillet_cb", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 723.946472, -1393.177978, 13.512833, -0.000837, -0.400929, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 13363, "cephotoblockcs_t", "wallwashv128", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 5712, "cemetint_law", "pizzabox", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 13363, "cephotoblockcs_t", "BigS01_law", 0x00000000);
    RamadhanObj = CreateDynamicObject(1342, 723.946228, -1407.939819, 13.429785, 0.000849, 0.400927, -90.001197, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 2, 3335, "ceroadsigns", "sw_roadsign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 5, 13364, "cetown3cs_t", "des_cafesign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 10, 3335, "ceroadsigns", "sw_barberpole", 0x00000000);
    RamadhanObj = CreateDynamicObject(19373, 766.129760, -1399.647583, 14.465052, -0.400950, 0.000844, 179.997909, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(19373, 766.121887, -1401.483154, 14.452239, -0.400950, 0.000844, 179.997909, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(19373, 766.111938, -1400.688964, 13.877762, -0.400943, 0.000844, 179.997909, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "RAMADHAN FAIR", 140, "Verdana", 60, 1, 0xFFB0AB4D, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19373, 766.111938, -1400.686767, 13.577775, -0.400943, 0.000844, 179.997909, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "KE XX1 - 1445 H TAHUN 2024", 140, "Verdana", 25, 1, 0xFFBBBBBB, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19373, 766.111999, -1400.485473, 14.829211, -0.400943, 0.000844, 179.997909, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "t", 140, "Wingdings", 199, 1, 0xFF899D48, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19373, 766.101867, -1400.754150, 14.607324, -0.400943, 0.000844, 179.997909, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "t", 140, "Wingdings", 199, 1, 0xFF3D5E49, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(2695, 765.991516, -1398.635864, 13.788142, 0.000849, 720.400939, -90.001083, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.991394, -1402.615966, 13.760353, 0.000849, 720.400939, -90.001083, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.991394, -1402.448486, 14.121526, 0.000849, 720.400939, -90.001083, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.991516, -1398.858520, 14.146590, 0.000849, 720.400939, -90.001083, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.991516, -1398.674438, 14.997901, 0.000849, 720.400939, -90.001083, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.991455, -1402.474243, 14.971372, 0.000849, 720.400939, -90.001083, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.990722, -1401.850219, 15.815748, 0.000849, 810.400939, -90.001083, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.990783, -1400.540039, 15.824892, 0.000849, 810.400939, -90.001083, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3red", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.990783, -1399.390258, 15.832921, 0.000849, 810.400939, -90.001083, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 754.405151, -1403.705932, 12.912844, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 754.405151, -1404.976074, 12.912844, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 757.655578, -1404.976074, 12.912844, 0.000000, -0.000007, -90.000007, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 757.655578, -1403.706054, 12.912844, 0.000000, -0.000007, -90.000007, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(19373, 766.081909, -1405.711425, 14.257536, -0.400943, 0.000821, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "KOLABORASI", 140, "Arial Black", 30, 1, 0xFFBBBBBB, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19373, 766.071899, -1405.890136, 14.086279, -0.400943, 0.000821, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PAHLAWAN BERKAH", 140, "Arial Black", 30, 1, 0xFFBBBBBB, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19832, 766.209472, -1405.405639, 14.091089, 90.000000, 630.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 18646, "matcolours", "red-4", 0x00000000);
    RamadhanObj = CreateDynamicObject(18762, 721.662719, -1396.989990, 14.767108, 0.000855, 0.400956, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(18762, 721.662719, -1400.003784, 16.736122, 0.000855, 90.400955, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(18762, 721.670776, -1403.184204, 16.713914, 0.000855, 90.400955, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(18762, 721.662597, -1405.210327, 14.709720, 0.000855, 0.400956, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(2790, 721.223022, -1401.208496, 16.365745, 0.002255, 0.400965, -89.801040, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 1, "KE XX1 - 1445 H TAHUN 2024", 130, "Verdana", 25, 1, 0xFFBBBBBB, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(2790, 721.222961, -1401.211791, 16.825742, 0.002255, 0.400965, -89.801040, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 1, "RAMADHAN FAIR", 130, "Verdana", 50, 1, 0xFFB0AB4D, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(2695, 721.091369, -1405.218017, 14.055610, 0.000855, 0.400956, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 721.091369, -1405.227050, 15.345582, 0.000855, 0.400956, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 721.091369, -1405.209960, 12.895641, 0.000855, 0.400956, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 721.091613, -1396.957519, 14.113282, 0.000855, 0.400963, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 721.091613, -1396.966430, 15.403250, 0.000855, 0.400963, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 721.091613, -1396.949340, 12.953310, 0.000855, 0.400963, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 721.091674, -1397.325195, 16.560779, 0.000855, 90.400962, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 721.091552, -1397.897583, 16.866790, 0.000855, 90.400962, -90.001190, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 721.091430, -1404.447631, 16.821067, 0.000873, -89.598991, -90.000877, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 721.091430, -1404.996093, 16.507228, 0.000873, -89.598991, -90.000877, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(19832, 766.209472, -1405.785766, 14.091089, 90.000000, 630.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 18646, "matcolours", "red-4", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 758.265014, -1400.619628, 20.009220, -0.000845, -0.400950, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 750.084899, -1400.619384, 20.009220, -0.000845, -0.400950, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 712.901855, -1388.263427, 19.259042, -0.000846, -0.400965, -172.401687, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 733.265197, -1400.619018, 20.009220, -0.000845, -0.400950, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 758.265075, -1396.044677, 19.341136, -0.000845, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 750.085083, -1396.044433, 19.341140, -0.000845, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 741.575256, -1396.044189, 19.341140, -0.000845, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 733.265319, -1396.044067, 19.341140, -0.000845, -0.400943, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 758.264892, -1405.205200, 19.277181, -0.000845, -0.400936, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 750.084838, -1405.204956, 19.277183, -0.000845, -0.400936, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 741.575012, -1405.204711, 19.277185, -0.000845, -0.400936, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 733.265075, -1405.204589, 19.277187, -0.000845, -0.400936, 89.998222, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(18981, 756.084350, -1401.788818, 11.954895, 0.399998, 90.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 11145, "carrierint_sfs", "ws_floor2", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 749.577941, -1410.054443, 16.880302, 59.599010, 0.001589, 179.996505, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(975, 758.428039, -1410.054687, 16.880292, 59.599010, 0.001589, 179.996505, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 4, 19480, "signsurf", "sign", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 748.164916, -1396.974853, 12.952844, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 744.909240, -1398.891113, 12.443745, -0.400920, 0.000865, -146.302139, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 740.735046, -1402.582275, 12.403596, -0.400920, 0.000872, 118.497917, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 745.399230, -1403.370727, 12.422475, -0.400920, 0.000872, 147.197921, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 739.109130, -1398.710449, 12.455030, -0.400920, 0.000858, 127.897827, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 734.359130, -1398.520385, 12.446297, -0.400920, 0.000865, 179.997833, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 734.979125, -1403.071044, 12.424535, -0.400920, 0.000865, -136.202148, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 725.798706, -1400.591552, 12.431818, 0.400994, -0.000905, 54.998226, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 729.848815, -1402.510864, 12.428432, 0.400994, -0.000898, -0.001775, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 729.848815, -1398.521484, 12.466288, 0.400994, -0.000898, -0.001775, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(19373, 768.242370, -1392.080810, 14.131290, -0.400950, 0.000851, 179.997955, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(19373, 768.142211, -1394.930908, 14.111392, -0.400950, 0.000851, 179.997955, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(19373, 768.141845, -1407.220947, 14.025591, -0.400950, 0.000851, 179.997955, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(19373, 768.302001, -1409.031616, 14.012953, -0.400950, 0.000851, 179.997955, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(18981, 727.904052, -1401.788818, 11.964895, 0.399998, 90.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 11145, "carrierint_sfs", "ws_floor2", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 718.348999, -1394.070312, 12.497330, 0.400994, -0.000905, -0.001775, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(1825, 718.348693, -1408.079956, 12.399279, 0.400994, -0.000905, -56.701774, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14771, "int_brothelint3", "GB_nastybar12", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 14771, "int_brothelint3", "wallpbroth1", 0x00000000);
    RamadhanObj = CreateDynamicObject(638, 760.767761, -1405.542236, 12.908704, -0.400950, 0.000821, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 801, "gta_proc_ferns", "veg_bush2", 0x00000000);
    RamadhanObj = CreateDynamicObject(18764, 763.619506, -1405.539428, 10.368663, -0.000821, -0.400950, 89.998130, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF899D48);
    RamadhanObj = CreateDynamicObject(19373, 766.099731, -1404.638427, 14.465052, -0.400950, 0.000821, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(19373, 766.091857, -1406.473999, 14.452239, -0.400950, 0.000821, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(19373, 766.081909, -1405.686279, 14.787746, -0.400943, 0.000821, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PEMDA PAHLAWAN", 140, "Verdana", 60, 1, 0xFFB0AB4D, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19373, 766.081909, -1405.010986, 14.172443, -0.400943, 0.000821, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "#", 100, "Verdana", 40, 1, 0xFFBBBBBB, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19832, 766.209472, -1406.166137, 14.091089, 90.000000, 630.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 18646, "matcolours", "red-4", 0x00000000);
    RamadhanObj = CreateDynamicObject(19832, 766.209472, -1406.396362, 14.091089, 90.000000, 630.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 18646, "matcolours", "red-4", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961486, -1403.656494, 13.788142, 0.000826, 720.400939, -90.001014, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961364, -1407.606811, 13.760353, 0.000826, 720.400939, -90.001014, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961364, -1407.439331, 14.121526, 0.000826, 720.400939, -90.001014, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961486, -1403.879150, 14.146590, 0.000826, 720.400939, -90.001014, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961486, -1403.715087, 15.000975, 0.000832, 720.400939, -90.001037, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961425, -1407.465087, 14.971372, 0.000826, 720.400939, -90.001014, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.960693, -1406.841064, 15.815748, 0.000826, 810.400939, -90.001014, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.960754, -1405.530883, 15.824892, 0.000826, 810.400939, -90.001014, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3red", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.960754, -1404.381103, 15.832921, 0.000826, 810.400939, -90.001014, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(638, 760.777709, -1395.582519, 12.948706, -0.400950, 0.000806, 179.997680, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 1, 801, "gta_proc_ferns", "veg_bush2", 0x00000000);
    RamadhanObj = CreateDynamicObject(18764, 763.619506, -1395.570068, 10.438735, -0.000806, -0.400950, 89.998085, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF899D48);
    RamadhanObj = CreateDynamicObject(19373, 766.099731, -1394.678710, 14.505054, -0.400950, 0.000806, 179.997680, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(19373, 766.091857, -1396.514282, 14.492240, -0.400950, 0.000806, 179.997680, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 16640, "a51", "scratchedmetal", 0xFF1B604E);
    RamadhanObj = CreateDynamicObject(19373, 766.082031, -1395.676635, 14.857790, -0.400943, 0.000821, 179.997772, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PEMDA PAHLAWAN", 140, "Verdana", 60, 1, 0xFFB0AB4D, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(3038, 713.992919, -1396.440551, 19.258914, -0.000846, -0.400965, -172.401687, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 715.082519, -1404.608032, 19.258789, -0.000846, -0.400965, -172.401687, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 716.168518, -1412.746826, 19.258682, -0.000846, -0.400965, -172.401687, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961486, -1393.666992, 13.828143, 0.000811, 720.400939, -90.000968, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961364, -1397.647094, 13.800354, 0.000811, 720.400939, -90.000968, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961364, -1397.479614, 14.161527, 0.000811, 720.400939, -90.000968, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961486, -1393.889648, 14.186591, 0.000811, 720.400939, -90.000968, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 801, "gta_proc_ferns", "veg_bushred", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961486, -1393.705566, 15.037902, 0.000811, 720.400939, -90.000968, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.961425, -1397.505371, 15.011374, 0.000811, 720.400939, -90.000968, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.960693, -1396.881347, 15.855749, 0.000811, 810.400939, -90.000968, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.960754, -1395.571166, 15.864893, 0.000811, 810.400939, -90.000968, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3red", 0x00000000);
    RamadhanObj = CreateDynamicObject(2695, 765.960754, -1394.421386, 15.872921, 0.000811, 810.400939, -90.000968, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(19373, 766.081909, -1395.690917, 14.257536, -0.400943, 0.000798, 179.997634, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "KOLABORASI", 140, "Arial Black", 30, 1, 0xFFBBBBBB, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19373, 766.071899, -1395.869628, 14.086279, -0.400943, 0.000798, 179.997634, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PAHLAWAN BERKAH", 140, "Arial Black", 30, 1, 0xFFBBBBBB, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19832, 766.209472, -1395.385131, 14.091089, 89.999992, 720.000000, -89.999969, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 18646, "matcolours", "red-4", 0x00000000);
    RamadhanObj = CreateDynamicObject(19832, 766.209472, -1395.765258, 14.091089, 89.999992, 720.000000, -89.999969, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 18646, "matcolours", "red-4", 0x00000000);
    RamadhanObj = CreateDynamicObject(19373, 766.081909, -1394.990478, 14.172443, -0.400943, 0.000798, 179.997634, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 2, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(RamadhanObj, 3, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "#", 100, "Verdana", 40, 1, 0xFFBBBBBB, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19832, 766.209472, -1396.145629, 14.091089, 89.999992, 720.000000, -89.999969, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 18646, "matcolours", "red-4", 0x00000000);
    RamadhanObj = CreateDynamicObject(19832, 766.209472, -1396.375854, 14.091089, 89.999992, 720.000000, -89.999969, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 18646, "matcolours", "red-4", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 708.457824, -1388.177490, 19.259042, -0.000845, -0.400981, 167.498260, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 706.672302, -1396.231445, 19.258914, -0.000845, -0.400981, 167.498260, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 704.888732, -1404.276000, 19.258789, -0.000845, -0.400981, 167.498260, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 703.111572, -1412.292236, 19.258682, -0.000845, -0.400981, 167.498260, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 697.299682, -1388.446655, 19.359045, -0.000844, -0.401003, -170.101806, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 698.718017, -1396.573242, 19.358917, -0.000844, -0.401003, -170.101806, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 700.134643, -1404.690551, 19.358793, -0.000844, -0.401003, -170.101806, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 701.546264, -1412.779174, 19.358684, -0.000844, -0.401003, -170.101806, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 691.687133, -1389.063232, 19.809055, -0.000849, -0.401026, -169.101669, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 693.247009, -1397.163818, 19.808927, -0.000849, -0.401026, -169.101669, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 694.805053, -1405.255126, 19.808803, -0.000849, -0.401026, -169.101669, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 689.933593, -1386.577758, 19.809068, -0.000846, -0.401048, 167.098205, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 688.101928, -1394.578247, 19.808919, -0.000846, -0.401048, 167.098205, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 686.270019, -1402.573486, 19.808832, -0.000846, -0.401048, 167.098205, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 675.567260, -1388.190673, 19.809068, -0.000846, -0.401062, -175.801712, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 684.526611, -1410.557250, 19.808946, -0.000843, -0.401062, 167.098114, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 682.702270, -1418.521606, 19.808828, -0.000843, -0.401062, 167.098114, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 676.169067, -1396.375854, 19.808919, -0.000846, -0.401062, -175.801712, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 676.768981, -1404.556396, 19.808832, -0.000846, -0.401062, -175.801712, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 677.450256, -1412.699829, 19.808946, -0.000843, -0.401077, -175.801818, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 678.048400, -1420.848510, 19.808828, -0.000843, -0.401077, -175.801818, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 671.271118, -1388.485473, 19.809068, -0.000844, -0.401077, 164.398178, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 669.064697, -1396.390625, 19.808919, -0.000844, -0.401077, 164.398178, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 666.858093, -1404.290771, 19.808832, -0.000844, -0.401077, 164.398178, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 664.740600, -1412.183593, 19.808946, -0.000842, -0.401093, 164.398071, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(3038, 662.543090, -1420.053100, 19.808828, -0.000842, -0.401093, 164.398071, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14548, "ab_cargo_int", "cargo_gir2", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 754.405151, -1399.144775, 12.952844, 0.000014, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 754.405151, -1400.414916, 12.952844, 0.000014, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 757.655578, -1400.414916, 12.952844, -0.000014, -0.000007, -89.999961, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 757.655578, -1399.144897, 12.952844, -0.000014, -0.000007, -89.999961, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 754.405151, -1394.645629, 12.982847, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 754.405151, -1395.915771, 12.982847, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 757.655578, -1395.915771, 12.982847, -0.000022, -0.000007, -89.999938, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 757.655578, -1394.645751, 12.982847, -0.000022, -0.000007, -89.999938, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 748.164916, -1398.244995, 12.952844, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 751.415344, -1398.244995, 12.952844, -0.000022, -0.000007, -89.999938, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 751.415344, -1396.974975, 12.952844, -0.000022, -0.000007, -89.999938, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 748.164916, -1401.764892, 12.952844, 0.000029, 0.000000, 89.999908, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 748.164916, -1403.035034, 12.952844, 0.000029, 0.000000, 89.999908, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 751.415344, -1403.035034, 12.952844, -0.000029, -0.000007, -89.999916, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(2121, 751.415344, -1401.765014, 12.952844, -0.000029, -0.000007, -89.999916, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    RamadhanObj = CreateDynamicObject(8330, 696.213745, -1187.713378, 34.145793, 0.000000, 0.000000, -93.800048, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 19655, "mattubes", "greendirt1", 0x00000000);
    RamadhanObj = CreateDynamicObject(19479, 695.831420, -1187.963745, 34.317005, 0.000000, 0.000000, 177.199905, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "SELAMAT MENUNAIKAN IBADAH", 130, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19479, 695.831420, -1187.963745, 35.116947, 0.000000, 0.000000, 177.199905, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "MARHABAN YAA RAMADHAN", 130, "Arial", 35, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19479, 695.831420, -1187.963745, 33.617015, 0.000000, 0.000000, 177.199905, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PUASA RAMADHAN 1445 H", 130, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(8330, 703.995788, -1115.171020, 32.345809, 0.000000, 0.000000, -26.200052, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    RamadhanObj = CreateDynamicObject(19479, 704.080383, -1115.629882, 32.426853, 0.000000, 0.000000, -115.199897, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "GO     JEK", 90, "Arial", 50, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19479, 703.691955, -1115.446166, 32.586849, 0.000000, 0.000000, -115.199897, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "b", 90, "Webdings", 55, 1, 0xFF93C343, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19479, 703.546875, -1115.377929, 33.456851, 90.000000, 0.000000, -115.199897, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, ")", 130, "Calibri", 50, 0, 0xFF93C343, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19479, 703.528808, -1115.369384, 33.666854, 90.000000, 0.000000, -115.199897, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, ")", 130, "Calibri", 70, 0, 0xFF93C343, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19479, 703.510742, -1115.360839, 33.876850, 90.000000, 0.000000, -115.199897, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, ")", 130, "Calibri", 80, 0, 0xFF93C343, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(8330, 733.197570, -1102.206176, 33.305820, 0.000000, 0.000000, 148.699768, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    RamadhanObj = CreateDynamicObject(2790, 733.243103, -1101.930664, 34.300529, 0.000000, 0.000000, 149.699859, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 1, "SELAMAT MENUNAIKAN", 90, "Arial", 25, 1, 0xFFFFFFFF, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19479, 733.222595, -1101.803833, 33.229537, 0.000000, 0.000000, 59.700038, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "IBADAH PUASA", 130, "Arial", 50, 1, 0xFFFFFFFF, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(2790, 733.243103, -1101.930664, 32.230583, 0.000000, 0.000000, 149.699859, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 1, "RAMADHAN 1445 H", 90, "Arial", 25, 1, 0xFFFFFFFF, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19482, 728.710510, -1099.162231, 34.942554, 0.000000, 0.000000, 59.600032, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(19482, 738.223327, -1104.705688, 31.692565, 180.000000, 0.000000, 419.700042, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(8330, 2029.255249, -1763.515869, 34.707393, 0.000000, 0.000000, 179.199996, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    RamadhanObj = CreateDynamicObject(4735, 2028.982910, -1763.133422, 35.801338, 0.000000, 0.000000, -89.200004, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "MARHABAN YAA RAMADHAN", 120, "Arial", 30, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 2028.982910, -1763.133422, 34.601345, 0.000000, 0.000000, -89.200004, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "SELAMAT MENUNAIKAN", 120, "Arial", 20, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 2028.982910, -1763.133422, 33.601371, 0.000000, 0.000000, -89.200004, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "IBADAH PUASA 1445 H", 120, "Arial", 20, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19482, 2035.185058, -1763.108886, 33.120815, 0.000000, 0.000000, 90.100006, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(19482, 2024.110107, -1763.129272, 33.557365, -135.699996, 0.000000, 90.100006, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 14803, "bdupsnew", "Bdup2_plant", 0x00000000);
    RamadhanObj = CreateDynamicObject(4735, 1648.006469, -1795.029174, 31.118396, 0.000000, 0.000000, 60.400051, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 5168, "lashops6_las2", "yellow2_128", 0x00000000);
    RamadhanObj = CreateDynamicObject(4735, 1648.328002, -1795.283325, 32.341461, 0.000000, 0.000000, 60.400081, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "SELAMAT MENUNAIKAN", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1648.267333, -1795.248779, 31.091447, 0.000000, 0.000000, 60.400081, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "IBADAH PUASA RAMADHAN 1445 H", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19482, 1641.189331, -1791.080444, 29.616796, 0.000000, 0.000000, 59.800071, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(19482, 1654.845458, -1799.027587, 32.646781, 180.000000, 0.000000, 59.800071, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(4735, 1353.747680, -1713.588745, 25.946226, 0.000000, 0.000000, -179.599990, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    RamadhanObj = CreateDynamicObject(4735, 1353.787719, -1713.017700, 27.346210, 0.000000, -0.000014, -179.599899, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PEMERINTAH PAHLAWAN", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1353.787719, -1713.017700, 26.336217, 0.000000, -0.000014, -179.599899, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "MENGUCAPKAN", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1353.787719, -1713.017700, 25.366207, 0.000000, -0.000014, -179.599899, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "SELAMAT MENUNAIKAN IBADAH", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1353.787719, -1713.017700, 24.416193, 0.000000, -0.000014, -179.599899, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PUASA RAMADHAN 1445 H", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(19482, 1353.723022, -1721.586181, 24.376768, 0.000000, 0.000000, 359.699615, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(19482, 1353.805664, -1705.776489, 27.516763, 180.000000, 0.000000, 359.699615, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 802, "gta_proc_bushland", "veg_bush3", 0x00000000);
    RamadhanObj = CreateDynamicObject(8330, 1030.751831, -2075.131835, 22.052486, 0.000000, 0.000000, 168.999984, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    RamadhanObj = CreateDynamicObject(4735, 1030.849365, -2074.449218, 23.496204, -0.000082, -0.000061, -99.199424, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PEMERINTAH PAHLAWAN", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1030.849365, -2074.449218, 22.486211, -0.000082, -0.000061, -99.199424, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "MENGUCAPKAN", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1030.849365, -2074.449218, 21.516201, -0.000082, -0.000061, -99.199424, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "SELAMAT MENUNAIKAN IBADAH", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1030.849365, -2074.449218, 20.566186, -0.000082, -0.000061, -99.199424, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PUASA RAMADHAN 1445 H", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(8330, 356.983093, -1719.132324, 26.558464, 0.000000, 0.000000, -90.999992, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    RamadhanObj = CreateDynamicObject(8330, 356.923065, -1719.131713, 27.718465, -0.000014, 0.000000, -90.999946, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "MARHABAN YAA RAMADHAN", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(8330, 1022.602172, -2234.243652, 22.052486, 0.000000, 0.000019, 13.899943, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    RamadhanObj = CreateDynamicObject(4735, 1022.801025, -2234.903808, 23.496206, -0.000047, -0.000062, 105.700401, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PEMERINTAH PAHLAWAN", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1022.801025, -2234.903808, 22.486213, -0.000047, -0.000062, 105.700401, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "MENGUCAPKAN", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1022.801025, -2234.903808, 21.516202, -0.000047, -0.000062, 105.700401, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "SELAMAT MENUNAIKAN IBADAH", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 1022.801025, -2234.903808, 20.566188, -0.000047, -0.000062, 105.700401, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 1273, "icons3", "greengrad32", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "PUASA RAMADHAN 1445 H", 120, "Arial", 25, 1, 0xFFFFFF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(8330, 356.923065, -1719.131713, 26.698457, -0.000014, 0.000000, -90.999946, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "Selamat Menunaikan Ibadah", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(8330, 356.923065, -1719.131713, 25.618442, -0.000014, 0.000000, -90.999946, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "Puasa Ramadhan 1445 H", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 356.600524, -1713.732788, 24.448078, 0.000000, 0.000007, 0.700004, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "GO      JEK", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 356.598083, -1713.532836, 24.538080, 0.000000, 0.000007, 0.700004, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "b", 120, "Webdings", 35, 1, 0xFF00FF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 356.597106, -1713.452758, 25.028074, -89.999992, 89.999992, 90.700004, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, ")", 120, "Calibri", 15, 1, 0xFF00FF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 356.596740, -1713.422729, 25.198078, -89.999992, 89.999992, 90.700004, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, ")", 120, "Calibri", 25, 1, 0xFF00FF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 356.597412, -1713.442016, 25.398817, -89.399963, 0.000728, 0.400734, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, ")", 120, "Calibri", 30, 1, 0xFF00FF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(8330, 515.954833, -1726.686401, 31.388502, 0.000051, 0.000012, 81.399803, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    RamadhanObj = CreateDynamicObject(8330, 516.014343, -1726.692260, 32.548503, 0.000051, 0.000012, 81.399803, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "MARHABAN YAA RAMADHAN", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(8330, 516.014343, -1726.692260, 31.528495, 0.000051, 0.000012, 81.399803, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "Selamat Menunaikan Ibadah", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(8330, 516.014343, -1726.692260, 30.448480, 0.000051, 0.000012, 81.399803, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(RamadhanObj, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    SetDynamicObjectMaterialText(RamadhanObj, 0, "Puasa Ramadhan 1445 H", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 515.620117, -1732.086425, 29.278116, 0.000011, -0.000059, 173.099899, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "GO      JEK", 120, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 515.596008, -1732.284912, 29.368118, 0.000011, -0.000059, 173.099899, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, "b", 120, "Webdings", 35, 1, 0xFF00FF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 515.582641, -1732.394287, 30.028116, -89.999992, -83.114974, 89.984870, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, ")", 120, "Calibri", 25, 1, 0xFF00FF00, 0x00000000, 1);
    RamadhanObj = CreateDynamicObject(4735, 515.584594, -1732.375000, 30.228855, -89.399963, -0.005803, 172.794113, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(RamadhanObj, 0, ")", 120, "Calibri", 30, 1, 0xFF00FF00, 0x00000000, 1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CreateDynamicObject(1841, 761.291870, -1402.609619, 12.365207, 0.400950, -0.000846, -0.001424, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1841, 761.291992, -1398.509521, 12.393835, 0.400950, -0.000846, -0.001424, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2762, 756.067077, -1404.314575, 12.811930, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2762, 756.067077, -1399.753417, 12.851930, 0.000014, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2762, 749.826843, -1397.583496, 12.851930, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(640, 721.415527, -1393.536499, 12.911502, -0.499998, 0.000000, 180.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(638, 721.320739, -1407.984252, 12.801127, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1841, 761.261840, -1407.600463, 12.365207, 0.400950, -0.000823, -0.001424, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1841, 761.261962, -1403.500366, 12.393835, 0.400950, -0.000823, -0.001424, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1841, 761.261840, -1397.640747, 12.405208, 0.400950, -0.000808, -0.001425, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1841, 761.261962, -1393.540649, 12.433835, 0.400950, -0.000808, -0.001425, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2762, 756.067077, -1395.254272, 12.881933, 0.000022, 0.000000, 89.999931, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2762, 749.826843, -1402.373535, 12.851930, 0.000029, 0.000000, 89.999908, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 785.903625, -1409.746948, 12.388633, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 785.903625, -1405.556518, 12.348628, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 785.903625, -1400.487060, 12.358630, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 785.903625, -1395.306762, 12.328628, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 785.903625, -1390.766479, 12.378623, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(997, 785.886108, -1394.612670, 12.466032, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(997, 785.886108, -1409.253784, 12.466032, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(997, 785.886108, -1405.104492, 12.466032, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(997, 785.886108, -1399.024536, 12.466032, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 781.313537, -1384.915893, 12.688620, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 774.523437, -1384.915893, 12.688620, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(997, 779.656005, -1385.001586, 12.826029, 0.000000, 0.000000, 180.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 656.742919, -1409.807006, 12.418635, 0.000000, 0.000014, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 656.742919, -1405.616577, 12.378629, 0.000000, 0.000014, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 656.742919, -1400.547119, 12.388629, 0.000000, 0.000014, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 656.742919, -1395.366821, 12.358630, 0.000000, 0.000014, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1237, 656.742919, -1390.826538, 12.408624, 0.000000, 0.000014, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(997, 656.725402, -1394.672729, 12.496033, 0.000014, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(997, 656.725402, -1409.313842, 12.496033, 0.000014, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(997, 656.725402, -1405.164550, 12.496033, 0.000014, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(997, 656.725402, -1399.084594, 12.496033, 0.000014, 0.000000, 89.999954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 735.251342, -1391.834106, 12.587141, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 728.811157, -1391.834106, 12.587141, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 743.941467, -1391.834106, 12.587141, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 752.991821, -1391.834106, 12.587141, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 761.681945, -1391.834106, 12.587141, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 752.952026, -1409.234375, 12.587141, -0.000014, -0.000007, -89.999961, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 761.682006, -1409.234375, 12.587141, -0.000014, -0.000007, -89.999961, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 743.881652, -1409.234375, 12.587141, -0.000014, -0.000007, -89.999961, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 735.211669, -1409.234375, 12.587141, -0.000014, -0.000007, -89.999961, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1294, 728.811157, -1409.234375, 12.587141, -0.000014, -0.000007, -89.999961, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19121, 715.750488, -1390.453247, 13.090860, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19121, 715.750488, -1410.344238, 13.090860, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19611, 762.060302, -1400.624023, 12.884188, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19610, 762.049316, -1400.617675, 14.499090, 27.300008, 0.000000, 270.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(18652, 693.567810, -1187.553955, 31.104316, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(18652, 702.769714, -1117.078247, 29.334310, 0.000000, 0.000000, 64.699981, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(18652, 734.270080, -1099.842285, 30.340047, 0.000000, 0.000000, 58.699989, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(18652, 2029.418334, -1761.461425, 31.370464, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 

    for(new i; i < sizeof(g_RamadhanStand); i++)
	{
        CreateDynamicPickup(1239, 23, g_RamadhanStand[i][StandPos][0], g_RamadhanStand[i][StandPos][1], g_RamadhanStand[i][StandPos][2], 0, 0, -1, 15.00, -1, 0);
        
        new string[144];
        format(string, sizeof(string), "[Y] "WHITE"%s", g_RamadhanStand[i][StandName]);
        CreateDynamic3DTextLabel(string, Y_GREEN, g_RamadhanStand[i][StandPos][0], g_RamadhanStand[i][StandPos][1], g_RamadhanStand[i][StandPos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 10.00, -1, 0);
    }
    RamadhanMusic = CreateDynamicSphere(741.9867,-1400.7260,13.4523, 35.00, 0, 0, -1);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new standid = Stand_Nearest(playerid);
        if(standid != -1)
        {
            if(AccountData[playerid][pMoney] < 25)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup ($25)");

            TakePlayerMoneyEx(playerid, 25);
            ShowItemBox(playerid, "Cash", "Removed $25x", 1212, 5);

            switch(standid)
            {
                case 0:
                {
                    PlayDrinkingAnim(playerid, 1546, "VENDING", "VEND_Drink2_P", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "meminum kolak pisang");
                    AccountData[playerid][pThirst] += 15;
                }
                case 1:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan gorengan");
                    AccountData[playerid][pHunger] += 15;
                }
                case 2:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan bubur sumsum");
                    AccountData[playerid][pHunger] += 15;
                }
                case 3:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan pancake durian");
                    AccountData[playerid][pHunger] += 15;
                }
                case 4:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan lontong medan");
                    AccountData[playerid][pHunger] += 15;
                }
                case 5:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan soto medan");
                    AccountData[playerid][pHunger] += 15;
                }
                case 6:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan ayam geprek");
                    AccountData[playerid][pHunger] += 15;
                }
                case 7:
                {
                    PlayDrinkingAnim(playerid, 1546, "VENDING", "VEND_Drink2_P", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "meminum teh poci");
                    AccountData[playerid][pThirst] += 15;
                }
                case 8:
                {
                    PlayDrinkingAnim(playerid, 1546, "VENDING", "VEND_Drink2_P", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "meminum es cendol");
                    AccountData[playerid][pThirst] += 15;
                }
                case 9:
                {
                    PlayDrinkingAnim(playerid, 1546, "VENDING", "VEND_Drink2_P", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan mie ayam jamur haji mahmud");
                    AccountData[playerid][pHunger] += 15;
                }
                case 10:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan martabak");
                    AccountData[playerid][pHunger] += 15;
                }
                case 11:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan sup iga");
                    AccountData[playerid][pHunger] += 15;
                }
                case 12:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan sate padang");
                    AccountData[playerid][pHunger] += 15;
                }
                case 13:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan pecel lele");
                    AccountData[playerid][pHunger] += 15;
                }
                case 14:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan seblak");
                    AccountData[playerid][pHunger] += 15;
                }
                case 15:
                {
                    PlayEatingAnim(playerid, 19993, "FOOD", "EAT_Burger", 3.0, false, false, false, false, false);
                    SendRPMeAboveHead(playerid, "memakan bakso");
                    AccountData[playerid][pHunger] += 15;
                }
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(areaid == RamadhanMusic)
    {
        PlayAudioStreamForPlayer(playerid, "https://shorturl.at/dBGX9", 741.9867,-1400.7260,13.4523, 50.0, 1);
    }
    return 1;
}

task SendCongrats[1500000]() 
{
    foreach(new i : Player) if(AccountData[i][pSpawned])
    {
        SendClientMessage(i, Y_GREEN, "[Ramadhan] "WHITE"Selamat menunaikan ibadah Puasa Ramadhan 1445 H.");
    }
    return 1;
}

task SendAsmaulHusna[900000]()
{
    foreach(new i : Player) if(AccountData[i][pSpawned])
    {
        new string[144], randasmaul = random(sizeof(g_AsmaulHusnaMUI));
        format(string, sizeof(string), "> %s", g_AsmaulHusnaMUI[randasmaul]);
        SendClientMessage(i, X11_GREEN, string);
    }
    return 1;
}

task PrayerTime[1000]()
{
    static Hour, Minute, Second;
    gettime(Hour, Minute, Second);

    if(Hour == 5 && Minute == 12 && Second == 0)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            PlayAudioStreamForPlayer(i, "https://shorturl.at/aBK38", 0.0, 0.0, 0.0, 50.0, 0);
            SendClientMessage(i, Y_GREEN, "[Tarhim Subuh] "WHITE"Hampir tiba waktu solat Subuh untuk Medan sekitarnya.");
        }
    }

    if(Hour == 5 && Minute == 17 && Second == 0)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            PlayAudioStreamForPlayer(i, "https://shorturl.at/CNPZ8", 0.0, 0.0, 0.0, 50.0, 0);
            SendClientMessage(i, Y_GREEN, "[Subuh] "WHITE"Waktunya memasuki solat Subuh untuk Medan sekitarnya.");
        }
    }

    if(Hour == 12 && Minute == 36 && Second == 0)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            PlayAudioStreamForPlayer(i, "https://shorturl.at/CNPZ8", 0.0, 0.0, 0.0, 50.0, 0);
            SendClientMessage(i, Y_GREEN, "[Dzuhur] "WHITE"Waktunya memasuki solat Dzuhur untuk Medan sekitarnya.");
        }
    }

    if(Hour == 15 && Minute == 48 && Second == 0)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            PlayAudioStreamForPlayer(i, "https://shorturl.at/CNPZ8", 0.0, 0.0, 0.0, 50.0, 0);
            SendClientMessage(i, Y_GREEN, "[Ashar] "WHITE"Waktunya memasuki solat Ashar untuk Medan sekitarnya.");
        }
    }

    if(Hour == 18 && Minute == 33 && Second == 0)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            PlayAudioStreamForPlayer(i, "https://shorturl.at/aBK38", 0.0, 0.0, 0.0, 50.0, 0);
            SendClientMessage(i, Y_GREEN, "[Tarhim Maghrib] "WHITE"Hampir tiba waktu solat Maghrib untuk Medan sekitarnya.");
        }
    }

    if(Hour == 18 && Minute == 38 && Second == 0)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            PlayAudioStreamForPlayer(i, "https://shorturl.at/CNPZ8", 0.0, 0.0, 0.0, 50.0, 0);
            SendClientMessage(i, Y_GREEN, "[Maghrib] "WHITE"Waktunya memasuki solat Maghrib untuk Medan sekitarnya.");
        }
    }

    if(Hour == 19 && Minute == 47 && Second == 0)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned])
        {
            PlayAudioStreamForPlayer(i, "https://shorturl.at/CNPZ8", 0.0, 0.0, 0.0, 50.0, 0);
            SendClientMessage(i, Y_GREEN, "[Isya] "WHITE"Waktunya memasuki solat Isya untuk Medan sekitarnya.");
        }
    }
    return 1;
}