#include <YSI_Coding\y_hooks>

new Float: StallBuyPoint[][3] = {
    {-46.3655,-463.7533,1.8622},
    {-193.3846,270.7303,6.0896}
};

IsPlayerAtPecelLele(playerid)
{
    for(new x; x < sizeof(StallBuyPoint); x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, StallBuyPoint[x][0], StallBuyPoint[x][1], StallBuyPoint[x][2]))
        {
            return true;
        }
    }
    return false;
}

hook OnGameModeInit()
{
    new STREAMER_TAG_OBJECT:ppsaw;
    ppsaw = CreateDynamicObject(16101, -40.607357, -462.505584, 5.013254, 0.000000, 180.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14651, "ab_trukstpd", "Bow_bar_tabletop_wood", 0x00000000);
    ppsaw = CreateDynamicObject(16101, -48.507339, -458.225982, 4.953250, 0.000000, 180.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14651, "ab_trukstpd", "Bow_bar_tabletop_wood", 0x00000000);
    ppsaw = CreateDynamicObject(19445, -48.446292, -466.360351, 3.603269, -1.799999, 0.000000, 58.600006, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 15041, "bigsfsave", "ah_greencarp", 0x00000000);
    ppsaw = CreateDynamicObject(19445, -47.545677, -464.789459, 5.182490, -1.799999, 90.000000, 58.600006, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    ppsaw = CreateDynamicObject(19445, -47.532493, -464.809204, 5.133144, -1.799999, 90.000000, 58.600006, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 19267, "mapmarkers", "samporange", 0x00000000);
    ppsaw = CreateDynamicObject(16101, -44.824245, -472.530120, 2.473248, 0.000000, 180.000000, 32.599994, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14651, "ab_trukstpd", "Bow_bar_tabletop_wood", 0x00000000);
    ppsaw = CreateDynamicObject(16101, -56.015583, -465.264587, 2.443248, 0.000000, 180.000000, -40.099975, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14651, "ab_trukstpd", "Bow_bar_tabletop_wood", 0x00000000);
    ppsaw = CreateDynamicObject(16101, -44.806568, -470.145019, 3.653247, 0.000000, 180.000000, 32.599994, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14651, "ab_trukstpd", "Bow_bar_tabletop_wood", 0x00000000);
    ppsaw = CreateDynamicObject(16101, -53.695323, -464.505584, 3.273247, 0.000000, 180.000000, 32.599994, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14651, "ab_trukstpd", "Bow_bar_tabletop_wood", 0x00000000);
    ppsaw = CreateDynamicObject(19445, -45.735656, -461.829284, 5.182490, -1.799993, 90.000007, 58.599994, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    ppsaw = CreateDynamicObject(19445, -45.722473, -461.849029, 5.133144, -1.799993, 90.000007, 58.599994, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 19267, "mapmarkers", "samporange", 0x00000000);
    ppsaw = CreateDynamicObject(19426, -47.152637, -458.303466, 4.574593, 138.299972, -87.399848, -33.099956, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    ppsaw = CreateDynamicObject(19426, -44.183025, -460.114105, 4.692467, 138.299972, -87.399848, -33.099956, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    ppsaw = CreateDynamicObject(19426, -41.933101, -461.511566, 4.788076, 138.299972, -87.399848, -33.099956, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    ppsaw = CreateDynamicObject(2047, -43.793811, -460.805511, 3.309350, 0.000007, -0.000012, 148.800018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14668, "711c", "cj_white_wall2", 0x00000000);
    ppsaw = CreateDynamicObject(2047, -45.316356, -459.883422, 3.309350, 0.000007, 360.000000, 148.800018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14668, "711c", "cj_white_wall2", 0x00000000);
    ppsaw = CreateDynamicObject(2047, -45.316356, -459.883422, 2.489351, 0.000007, 179.999984, 148.800018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14668, "711c", "cj_white_wall2", 0x00000000);
    ppsaw = CreateDynamicObject(2047, -43.785255, -460.810577, 2.489351, 0.000007, -0.000012, 148.800018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14668, "711c", "cj_white_wall2", 0x00000000);
    ppsaw = CreateDynamicObject(18667, -44.518321, -460.247039, 2.903731, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "SOTO LAMONGAN", 130, "Arial", 55, 1, 0xFF8C00FF, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -44.518321, -460.247039, 3.323730, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "PECEL   LELE", 140, "Arial", 90, 1, 0xFFF13602, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -44.506004, -460.265716, 3.343730, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "PECEL   LELE", 140, "Arial", 90, 1, 0xFFFF0000, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -44.496002, -460.248382, 2.933731, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "SOTO LAMONGAN", 130, "Arial", 55, 1, 0xFF00FF00, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -44.461364, -460.268402, 2.513731, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "SAMBEL IJO", 140, "Arial", 35, 1, 0xFF00FF00, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -44.440387, -460.292083, 2.333731, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "GORENG - BAKAR", 140, "Arial", 50, 1, 0xFF8C00FF, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -43.370185, -460.898620, 2.333731, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "SATE KULIT", 140, "Arial", 35, 1, 0xFF00FF00, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -45.561214, -459.633544, 2.333731, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "TERONG PECAK", 140, "Arial", 35, 1, 0xFF00FF00, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -43.474098, -460.838562, 2.973731, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "TAHU", 140, "Arial", 35, 1, 0xFF00FF00, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -43.470436, -460.852081, 2.843730, 0.000000, 0.000000, -120.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "TEMPE", 140, "Arial", 35, 1, 0xFF8C00FF, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -45.583377, -459.618499, 2.973731, -0.000006, -0.000003, -119.999977, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "ATI", 140, "Arial", 35, 1, 0xFF00FF00, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -45.588375, -459.627014, 2.843730, -0.000006, -0.000003, -119.999977, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(ppsaw, 0, "AMPELA", 140, "Arial", 35, 1, 0xFF8C00FF, 0x00000000, 1);
    ppsaw = CreateDynamicObject(19940, -45.093990, -466.437042, 1.434770, -2.599998, 0.000003, 54.899936, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14786, "ab_sfgymbeams", "knot_wood128", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -44.578041, -467.002441, 1.218016, -2.599998, 124.200004, 54.899936, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -44.394821, -466.741790, 1.217414, -2.599998, 57.199977, 54.899936, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -46.384307, -465.732971, 1.117763, -2.599998, 124.200012, 54.899936, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -46.201087, -465.472320, 1.117159, -2.599998, 57.199985, 54.899936, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19940, -45.726211, -465.980468, 1.409371, -2.599998, 0.000003, 54.899936, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14786, "ab_sfgymbeams", "knot_wood128", 0x00000000);
    ppsaw = CreateDynamicObject(19940, -48.652297, -463.886871, 1.281667, -2.109023, 0.345266, 54.914108, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14786, "ab_sfgymbeams", "knot_wood128", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -48.138648, -464.452270, 1.059522, -2.109023, 124.545272, 54.914108, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -47.955444, -464.191619, 1.057000, -2.109023, 57.545238, 54.914108, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -49.945865, -463.182800, 0.978188, -2.109023, 124.545280, 54.914108, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -49.762660, -462.922149, 0.975666, -2.109023, 57.545246, 54.914108, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19940, -49.284751, -463.430297, 1.262891, -2.109023, 0.345266, 54.914108, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14786, "ab_sfgymbeams", "knot_wood128", 0x00000000);
    ppsaw = CreateDynamicObject(19899, -50.547149, -459.482055, 0.620501, -4.600001, -0.599992, -32.699947, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14581, "ab_mafiasuitea", "wood02S", 0x00000000);
    ppsaw = CreateDynamicObject(19353, -51.729259, -460.739105, 0.195737, 2.800004, -0.000006, 147.600006, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14581, "ab_mafiasuitea", "wood02S", 0x00000000);
    ppsaw = CreateDynamicObject(2762, -44.616741, -465.121246, 1.362285, 0.000000, -2.899998, -35.799999, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14581, "ab_mafiasuitea", "wood02S", 0x00000000);
    ppsaw = CreateDynamicObject(2762, -48.155475, -462.566467, 1.191143, -2.599998, -0.399998, -35.799999, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14581, "ab_mafiasuitea", "wood02S", 0x00000000);
    ppsaw = CreateDynamicObject(19940, -47.162342, -461.525970, 1.113754, -2.453844, 0.836719, 54.933666, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14786, "ab_sfgymbeams", "knot_wood128", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -46.648693, -462.093658, 0.897540, -2.453844, 125.036727, 54.933666, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -46.465488, -461.833038, 0.892289, -2.453844, 58.036689, 54.933666, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -48.455909, -460.825103, 0.802918, -2.453844, 125.036735, 54.933666, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -48.272705, -460.564483, 0.797667, -2.453844, 58.036697, 54.933666, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19940, -47.794795, -461.069610, 1.090196, -2.453844, 0.836719, 54.933666, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14786, "ab_sfgymbeams", "knot_wood128", 0x00000000);
    ppsaw = CreateDynamicObject(19940, -43.722347, -463.926025, 1.323752, -2.453836, 0.836723, 54.933662, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14786, "ab_sfgymbeams", "knot_wood128", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -43.208698, -464.493713, 1.107540, -2.453836, 125.036735, 54.933662, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -43.025493, -464.233093, 1.102288, -2.453836, 58.036693, 54.933662, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -45.015914, -463.225158, 1.012917, -2.453836, 125.036743, 54.933662, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19793, -44.832710, -462.964538, 1.007666, -2.453836, 58.036701, 54.933662, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 14652, "ab_trukstpa", "wood01", 0x00000000);
    ppsaw = CreateDynamicObject(19940, -44.354801, -463.469665, 1.300196, -2.453836, 0.836723, 54.933662, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14786, "ab_sfgymbeams", "knot_wood128", 0x00000000);
    ppsaw = CreateDynamicObject(2047, -43.793811, -460.805511, 3.309350, 0.000007, -0.000012, 328.800018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14668, "711c", "cj_white_wall2", 0x00000000);
    ppsaw = CreateDynamicObject(2047, -45.316356, -459.883422, 3.309350, 0.000007, 360.000000, 328.800018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14668, "711c", "cj_white_wall2", 0x00000000);
    ppsaw = CreateDynamicObject(2047, -45.316356, -459.883422, 2.489351, 0.000007, 179.999984, 328.800018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14668, "711c", "cj_white_wall2", 0x00000000);
    ppsaw = CreateDynamicObject(2047, -43.819465, -460.789825, 2.489351, 0.000007, -0.000012, 328.800018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14668, "711c", "cj_white_wall2", 0x00000000);
    ppsaw = CreateDynamicObject(16101, -44.393035, -468.824401, 2.083247, 0.000000, 180.000000, 32.599994, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14651, "ab_trukstpd", "Bow_bar_tabletop_wood", 0x00000000);
    ppsaw = CreateDynamicObject(16101, -52.295936, -464.002929, 1.743247, 0.000000, 180.000000, 32.599994, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 14651, "ab_trukstpd", "Bow_bar_tabletop_wood", 0x00000000);
    ppsaw = CreateDynamicObject(19426, -48.336051, -466.413055, 4.394416, 89.099945, 148.600036, 89.999900, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 3820, "boxhses_sfsx", "LAbluewall", 0x00000000);
    ppsaw = CreateDynamicObject(18667, -48.286853, -466.327575, 4.461401, 1.368228, 0.469022, -121.407974, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 10765, "airportgnd_sfse", "black64", 0x00000000);
    SetDynamicObjectMaterialText(ppsaw, 0, "PARTAI DEMOKRAT", 100, "Arial", 25, 1, 0xFFFFFFFF, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -48.537940, -466.168884, 3.888494, 0.568266, 0.468912, -121.401443, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 10765, "airportgnd_sfse", "black64", 0x00000000);
    SetDynamicObjectMaterialText(ppsaw, 0, "KUKUH HARYANTO", 100, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    ppsaw = CreateDynamicObject(19832, -48.183227, -466.656250, 3.898092, 89.099945, 58.600036, 89.999900, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    ppsaw = CreateDynamicObject(19832, -48.507686, -466.458129, 3.892995, 89.099945, 58.600036, 89.999900, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    ppsaw = CreateDynamicObject(19832, -48.823410, -466.265319, 3.888035, 89.099945, 58.600036, 89.999900, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    ppsaw = CreateDynamicObject(19832, -49.138973, -466.072723, 3.883078, 89.099945, 58.600036, 89.999900, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    ppsaw = CreateDynamicObject(19562, -47.804302, -466.682037, 3.697983, -0.468890, 0.768236, 148.603027, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    ppsaw = CreateDynamicObject(18667, -47.773002, -466.624053, 3.897413, 0.568266, 0.468912, -121.401443, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 10765, "airportgnd_sfse", "black64", 0x00000000);
    SetDynamicObjectMaterialText(ppsaw, 0, "4", 100, "Arial", 50, 1, 0xFF000000, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -48.506122, -466.190002, 4.068872, 0.568266, 0.468912, -121.401443, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 10765, "airportgnd_sfse", "black64", 0x00000000);
    SetDynamicObjectMaterialText(ppsaw, 0, "Jangan lupa coblos no. papat!!", 100, "Arial", 15, 1, 0xFFFFFFFF, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -48.140552, -466.414306, 4.193132, 0.568266, 0.468912, -121.401443, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 10765, "airportgnd_sfse", "black64", 0x00000000);
    SetDynamicObjectMaterialText(ppsaw, 0, "MATUR NUWUN !!", 100, "Arial", 20, 1, 0xFFFFFFFF, 0x00000000, 1);
    ppsaw = CreateDynamicObject(18667, -48.630039, -466.111267, 3.747431, 0.568266, 0.468912, -121.401443, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(ppsaw, 1, 10765, "airportgnd_sfse", "black64", 0x00000000);
    SetDynamicObjectMaterialText(ppsaw, 0, "CALEG DPRD KAB. WONOGIRI DAPIL 1", 100, "Arial", 15, 1, 0xFFFFFFFF, 0x00000000, 1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CreateDynamicObject(19087, -44.814533, -468.576293, 5.402521, -40.600025, 0.000007, -1.100008, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19088, -44.830196, -470.153930, 3.553179, -55.700000, 0.000011, 0.800004, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19087, -52.218471, -464.075225, 5.032513, -40.600025, 0.000015, -73.799980, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19088, -53.729396, -464.529418, 3.183171, -55.700000, 0.000023, -71.899940, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19087, -46.048381, -459.424987, 2.207894, 0.000000, 64.800003, -26.100000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19087, -46.447105, -459.240661, 1.990213, 0.000000, 64.800003, -26.100000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19087, -46.100555, -459.410583, 3.692914, 0.000000, 98.900009, -26.100000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19087, -46.203945, -459.371154, 3.700052, 0.000000, 98.900009, -26.100000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19087, -40.886043, -462.265777, 1.801337, 0.000000, 98.900009, -26.100000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19087, -40.465953, -462.482666, 1.717198, 0.000000, 98.900009, -26.100000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19087, -40.921962, -462.303680, 4.250432, 0.000000, 77.099967, -26.100000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19087, -40.495422, -462.524047, 4.350080, 0.000000, 77.099967, -26.100000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2336, -51.869285, -461.932098, 0.805854, 0.000006, 3.800003, 56.199970, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(11722, -48.184513, -462.426635, 1.716307, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(11722, -44.674530, -464.966674, 1.896306, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(11723, -44.696048, -465.091125, 1.905336, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(11723, -48.046058, -462.480987, 1.735337, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2831, -51.864757, -461.720184, 1.863085, 3.599998, -0.599999, 180.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2049, -47.166507, -466.989532, 4.154872, -0.468890, 0.768229, 148.603027, 0, 0, -1, 200.00, 200.00); 

    for(new x; x < sizeof(StallBuyPoint); x++)
    {
        CreateDynamicPickup(1239, 23, StallBuyPoint[x][0],StallBuyPoint[x][1],StallBuyPoint[x][2], 0, 0, -1, 30.00, -1, 0);
        CreateDynamic3DTextLabel("[Pecel Lele]\n"WHITE"Gunakan "YELLOW"'/eat' "WHITE"untuk akses menu pecel lele", 0xc0c0c8A6, StallBuyPoint[x][0],StallBuyPoint[x][1],StallBuyPoint[x][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 10.00, -1, 0);
    }
    return 1;
}

YCMD:eat(playerid, params[], help)
{
    if(!IsPlayerAtPecelLele(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di pecel lele manapun!");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus jalan kaki!");

	Dialog_Show(playerid, "FoodTruckMenu", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Warung Lokal Pecel Lele", 
	"Hidangan\tHarga\n\
	Pecel Ayam (+20)\t$254\n\
	"GRAY"Es Cincau (+20)\t"GRAY"$205", "Beli", "Batal");
    return 1;
}

Dialog:FoodTruckMenu(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    switch(listitem)
    {
        case 0:
        {
            if(AccountData[playerid][pMoney] < 254) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            TakePlayerMoneyEx(playerid, 254);
            ShowItemBox(playerid, "Cash", "Removed $254x", 1212, 6);

            AccountData[playerid][pHunger] += 20;
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membeli pecel ayam dan segera memakannya.");
            SendRPMeAboveHead(playerid, "Membeli pecel ayam lalu memakannyat.");

            PlayEatingAnim(playerid, 2769, "FOOD", "EAT_Burger", 3.0, false, true, true, true, 1);
        }
        case 1:
        {
            if(AccountData[playerid][pMoney] < 205) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            TakePlayerMoneyEx(playerid, 205);
            ShowItemBox(playerid, "Cash", "Removed $205x", 1212, 6);

            AccountData[playerid][pThirst] += 20;
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membeli es cincau dan segera meminumnya.");
            SendRPMeAboveHead(playerid, "Membeli es cincau lalu meminumnya.");

            PlayDrinkingAnim(playerid, 1669, "VENDING", "VEND_Drink2_P", 3.0, false, true, true, true, 1);
        }
    }
    return 1;
}