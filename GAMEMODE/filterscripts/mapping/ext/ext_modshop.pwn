RemoveModshopBuilding(playerid)
{
    RemoveBuildingForPlayer(playerid, 4848, 1931.000, -1871.390, 15.843, 0.250);
    RemoveBuildingForPlayer(playerid, 4976, 1931.000, -1871.390, 15.843, 0.250);
    RemoveBuildingForPlayer(playerid, 1226, 1931.880, -1863.459, 16.320, 0.250);
    RemoveBuildingForPlayer(playerid, 1226, 1915.739, -1863.459, 16.320, 0.250);
}

CreateModshopExt()
{
    static mdstxt;
    mdstxt = CreateDynamicObject(18981, 2059.164062, -1875.726562, 12.089279, 0.000000, 90.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(mdstxt, 0, 11013, "crackdrive_sfse", "ws_asphalt2", 0x00000000);
    mdstxt = CreateDynamicObject(18981, 2034.184692, -1875.986816, 12.089279, 0.000000, 90.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(mdstxt, 0, 11013, "crackdrive_sfse", "ws_asphalt2", 0x00000000);
    mdstxt = CreateDynamicObject(17950, 2067.870849, -1867.675292, 14.841187, 0.000000, -0.000007, 179.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(mdstxt, 0, 12978, "ce_payspray", "sf_spray_floor1", 0x00000000);
    SetDynamicObjectMaterial(mdstxt, 4, 3355, "cxref_savhus", "des_brick1", 0x00000000);
    mdstxt = CreateDynamicObject(17950, 2061.091552, -1867.655273, 14.841187, 0.000000, -0.000007, 179.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(mdstxt, 0, 12978, "ce_payspray", "sf_spray_floor1", 0x00000000);
    SetDynamicObjectMaterial(mdstxt, 4, 3355, "cxref_savhus", "des_brick1", 0x00000000);
    mdstxt = CreateDynamicObject(17950, 2054.291015, -1867.715332, 14.841187, 0.000000, -0.000007, 179.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(mdstxt, 0, 12978, "ce_payspray", "sf_spray_floor1", 0x00000000);
    SetDynamicObjectMaterial(mdstxt, 4, 3355, "cxref_savhus", "des_brick1", 0x00000000);
    mdstxt = CreateDynamicObject(17950, 2047.520996, -1867.775390, 14.841187, 0.000000, -0.000007, 179.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(mdstxt, 0, 12978, "ce_payspray", "sf_spray_floor1", 0x00000000);
    SetDynamicObjectMaterial(mdstxt, 4, 3355, "cxref_savhus", "des_brick1", 0x00000000);
    mdstxt = CreateDynamicObject(17950, 2040.750366, -1867.835449, 14.841187, 0.000000, -0.000007, 179.999954, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(mdstxt, 0, 12978, "ce_payspray", "sf_spray_floor1", 0x00000000);
    SetDynamicObjectMaterial(mdstxt, 4, 3355, "cxref_savhus", "des_brick1", 0x00000000);
    mdstxt = CreateDynamicObject(4735, 2036.265869, -1878.181274, 12.600731, 0.599993, 90.000000, -178.799957, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterialText(mdstxt, 0, "TRUCK ONLY", 120, "Arial", 35, 1, 0xFFFFFF00, 0x00000000, 1);
    mdstxt = CreateDynamicObject(18981, 2029.655273, -1875.986816, 12.079278, 0.000000, 90.000000, 90.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(mdstxt, 0, 11013, "crackdrive_sfse", "ws_asphalt2", 0x00000000);
    mdstxt = CreateDynamicObject(19445, 2037.172851, -1878.107666, 10.843669, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    SetDynamicObjectMaterial(mdstxt, 0, 7650, "vgnusedcar", "lightyellow2_32", 0x00000000);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CreateDynamicObject(997, 2027.504028, -1897.828613, 12.587656, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(984, 2005.061035, -1863.521728, 13.199301, 0.000000, 0.000000, 630.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(984, 2030.702026, -1863.521728, 13.199301, 0.000000, 0.000000, 630.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(984, 2028.163085, -1888.422363, 13.199301, 0.000000, 0.000000, 270.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19817, 2067.872558, -1869.923095, 10.699492, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19817, 2061.022460, -1869.923095, 10.699492, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19817, 2054.273193, -1869.923095, 10.699492, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19817, 2047.483276, -1869.923095, 10.699492, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19817, 2040.672241, -1869.923095, 10.699492, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2614, 2044.149780, -1872.297729, 16.954040, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2614, 2057.689697, -1872.197631, 16.954040, 0.000000, 0.000007, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(2048, 2031.602050, -1886.229492, 15.087965, 0.000000, 0.000000, 270.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19817, 2019.960693, -1869.923095, 10.669490, 0.000000, 0.000015, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(984, 1999.451538, -1863.551757, 13.199301, 0.000000, 0.000000, 630.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(19817, 2029.781250, -1869.923095, 10.679491, 0.000000, 0.000015, 0.000000, 0, 0, -1, 200.00, 200.00); 
    CreateDynamicObject(984, 2017.871337, -1863.521728, 13.199301, 0.000000, 0.000000, 630.000000, 0, 0, -1, 200.00, 200.00); 
}