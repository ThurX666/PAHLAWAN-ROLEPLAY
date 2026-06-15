RemoveKampusBuilding(playerid)
{
    RemoveBuildingForPlayer(playerid, 4189, 1794.619, -1576.729, 17.757, 0.250);
    RemoveBuildingForPlayer(playerid, 1216, 1805.410, -1600.459, 13.226, 0.250);
    RemoveBuildingForPlayer(playerid, 1216, 1806.390, -1599.619, 13.226, 0.250);
    RemoveBuildingForPlayer(playerid, 1216, 1807.380, -1598.780, 13.226, 0.250);
    RemoveBuildingForPlayer(playerid, 1216, 1808.380, -1597.920, 13.226, 0.250);
    RemoveBuildingForPlayer(playerid, 1216, 1809.339, -1597.089, 13.226, 0.250);
}

CreateKampusExt()
{
    new STREAMER_TAG_OBJECT:KMPUXEXTA;

    KMPUXEXTA = CreateDynamicObject(19353, 1803.850830, -1594.028442, 13.015951, 0.000011, -0.000009, 132.799942, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 3878, "headstones_sfsx", "ws_wargrave2", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(19483, 1803.954467, -1594.061279, 14.210432, -0.000011, 0.000009, -47.199981, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(KMPUXEXTA, 0, "UNIVERSITAS", 50, "Arial", 23, 1, 0xFF000000, 0x00000000, 1);
    KMPUXEXTA = CreateDynamicObject(19483, 1803.954467, -1594.061279, 13.730429, -0.000011, 0.000009, -47.199981, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(KMPUXEXTA, 0, "PAHLAWAN", 50, "Arial", 25, 1, 0xFF000000, 0x00000000, 1);
    KMPUXEXTA = CreateDynamicObject(19353, 1803.840454, -1594.026611, 14.676306, 0.000000, 0.000000, -47.500026, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 3878, "headstones_sfsx", "ws_wargrave", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(1307, 1802.476440, -1592.546752, 25.754955, 0.000000, 180.000000, 40.199989, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    SetDynamicObjectMaterial(KMPUXEXTA, 1, 10765, "airportgnd_sfse", "white", 0x00000000);
    SetDynamicObjectMaterial(KMPUXEXTA, 2, 10765, "airportgnd_sfse", "white", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(3281, 1803.718261, -1591.383911, 25.130748, 0.000000, 0.000000, 46.400005, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 18646, "matcolours", "red-4", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(3281, 1803.718261, -1591.383911, 24.000751, 0.000000, 0.000000, 46.400005, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1810.080932, -1559.704589, 22.437465, 0.000000, 0.000000, 64.899993, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1808.312011, -1563.481079, 22.437465, 0.000000, 0.000000, 64.899993, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1805.034423, -1568.391113, 22.437465, 0.000000, 0.000000, 40.599975, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1807.523681, -1565.165893, 22.437465, 0.000000, 0.000000, 64.899993, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1801.148681, -1571.693847, 22.437465, 0.000003, 0.000004, 41.199974, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1798.024169, -1574.429687, 22.437465, 0.000003, 0.000004, 41.199974, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1794.148925, -1577.820922, 22.437465, 0.000009, 0.000011, 41.099967, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1791.019531, -1580.551391, 22.437465, 0.000009, 0.000011, 41.099967, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1787.880737, -1583.284423, 22.437465, 0.000018, 0.000023, 41.099967, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1785.373168, -1585.510986, 22.437465, 0.000018, 0.000023, 41.099967, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1781.763305, -1587.278808, 22.437465, 0.000018, 0.000023, 10.999960, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(970, 1776.806518, -1588.242797, 22.437465, 0.000018, 0.000023, 10.999960, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 1717, "cj_tv", "green_glass_64", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1786.312988, -1576.142700, 21.590196, 90.000000, 130.599990, 90.699989, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 14534, "ab_wooziea", "walp72S", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1793.817504, -1569.550170, 21.590196, 90.000000, 130.599990, 90.699989, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 14534, "ab_wooziea", "walp72S", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1790.075073, -1576.442138, 20.734895, 0.599996, 580.599975, 41.099998, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 14581, "ab_mafiasuitea", "walp45S", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1794.297119, -1572.743164, 19.493156, 0.599996, 580.599975, 41.099998, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 14581, "ab_mafiasuitea", "walp45S", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1795.145874, -1571.045410, 20.277715, 0.599996, -179.900024, 41.099998, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 14581, "ab_mafiasuitea", "walp45S", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1778.549194, -1554.635131, 26.854154, -0.399999, -89.800025, 42.999996, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 3820, "boxhses_sfsx", "LAcreamwall1", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1778.529785, -1554.581542, 32.973884, -0.399999, -89.800025, 42.999996, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 3820, "boxhses_sfsx", "LAcreamwall1", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1784.670776, -1574.271362, 21.470193, 90.000000, 130.599990, 90.699989, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 12844, "cos_liquorstore", "ws_cleanblock", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1792.154052, -1567.699096, 21.470193, 90.000000, 130.599990, 90.699989, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 12844, "cos_liquorstore", "ws_cleanblock", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1781.382812, -1570.531005, 21.590196, 90.000000, 130.599990, 90.699989, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1788.873291, -1563.952026, 21.590196, 90.000000, 130.599990, 90.699989, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 10765, "airportgnd_sfse", "desgreengrass", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18762, 1792.257568, -1560.965087, 21.687187, 0.000000, 90.000000, 131.300018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 14581, "ab_mafiasuitea", "walp45S", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18762, 1777.990966, -1573.498535, 21.687187, 0.000000, 90.000000, 131.300018, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 14581, "ab_mafiasuitea", "walp45S", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1787.531372, -1562.393066, 19.928449, 0.599996, -179.900024, 41.099998, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 14581, "ab_mafiasuitea", "walp45S", 0x00000000);
    KMPUXEXTA = CreateDynamicObject(18766, 1780.025634, -1568.941162, 19.945817, 0.599996, -179.900024, 41.099998, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(KMPUXEXTA, 0, 14581, "ab_mafiasuitea", "walp45S", 0x00000000);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CreateDynamicObject(1216, 1811.885742, -1592.561767, 13.233861, 0.000000, 0.000000, 87.599952, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1216, 1812.174438, -1585.657348, 13.233861, 0.000000, 0.000000, 87.599952, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1256, 1812.081787, -1589.221801, 13.216732, 0.000000, 0.000000, 179.999984, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(860, 1807.771484, -1594.975219, 12.988441, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(860, 1803.571289, -1597.034790, 12.988441, 0.000000, 0.000000, -165.099990, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19176, 1772.997680, -1578.253417, 23.515350, 0.000000, 0.000000, 129.499954, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19121, 1803.019165, -1570.015380, 22.467376, 0.000000, 0.000000, 41.100006, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19121, 1796.055297, -1576.103149, 22.467376, 0.000000, 0.000000, 41.100006, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19121, 1779.272827, -1587.641235, 22.457376, 0.000000, 0.000000, 10.000002, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(644, 1809.823608, -1558.353393, 22.196258, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(644, 1792.523681, -1551.494506, 22.196258, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(644, 1771.503051, -1569.124145, 22.196258, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(644, 1775.393188, -1587.994384, 22.196258, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1341, 1786.292968, -1575.606933, 23.083513, 0.000004, -0.000003, 669.899963, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2456, 1786.452270, -1574.703491, 22.084701, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1445, 1792.760375, -1568.815307, 22.692989, 0.000000, 0.000000, 83.400016, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1571, 1795.720947, -1567.598022, 23.167497, 0.000000, 0.000000, -138.300094, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2132, 1797.100463, -1567.793090, 22.135562, 0.000000, 0.000000, -137.199966, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1342, 1789.098266, -1573.762939, 23.090078, 0.000000, 0.000000, -48.299983, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1825, 1780.024902, -1572.379882, 22.049119, 0.000000, 0.000000, -78.699974, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1825, 1784.131347, -1568.259277, 22.049119, 0.000000, 0.000000, 178.600021, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(1825, 1788.570068, -1564.112426, 22.049119, 0.000000, 0.000000, 113.000007, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(638, 1783.209472, -1571.640869, 22.448354, 0.000000, 0.000000, -48.699962, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(638, 1787.731079, -1567.695312, 22.448354, 0.000000, 0.000000, -48.699962, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(638, 1792.089965, -1563.839843, 22.448354, 0.000000, 0.000000, -48.699962, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19158, 1787.898193, -1568.702880, 23.371406, 0.000000, 0.000000, 41.200016, 0, 0, -1, 200.00, 200.00);
}