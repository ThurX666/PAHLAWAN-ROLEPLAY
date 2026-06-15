#define MAX_ICONS 200

enum E_MAPICONS
{
    iconVw,
    iconInt,
    Float:iconPos[3],
    iconType,
    iconColor,

    //not save
    iconMapID
};
new IconData[MAX_ICONS][E_MAPICONS],
    Iterator:Icons<MAX_ICONS>;

MapIcon_Save(id)
{
	new gpqqery[2048];
	mysql_format(g_SQL, gpqqery, sizeof(gpqqery), "UPDATE `mapicons` SET `iconvw`=%d, `iconint`=%d, `iconpos0`=%f, `iconpos1`=%f, `iconpos2`=%f, `icontype`=%d, `iconcolor`=%d WHERE `ID`=%d",
	IconData[id][iconVw], IconData[id][iconInt], IconData[id][iconPos][0], IconData[id][iconPos][1], IconData[id][iconPos][2], IconData[id][iconType], IconData[id][iconColor], id);
	mysql_pquery(g_SQL, gpqqery);
	return 1;
}

MapIcon_Rebuild(id)
{
    if(id != -1)
	{
		IconData[id][iconMapID] = CreateDynamicMapIcon(IconData[id][iconPos][0], IconData[id][iconPos][1], IconData[id][iconPos][2], IconData[id][iconType], IconData[id][iconColor], IconData[id][iconVw], IconData[id][iconInt], -1, 1000.00, MAPICON_LOCAL, -1, 0);
	}
}

MapIcon_Refresh(id)
{
    Streamer_SetItemPos(STREAMER_TYPE_MAP_ICON, IconData[id][iconMapID], IconData[id][iconPos][0], IconData[id][iconPos][1], IconData[id][iconPos][2]);
    Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, IconData[id][iconMapID], E_STREAMER_WORLD_ID, IconData[id][iconVw]);
    Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, IconData[id][iconMapID], E_STREAMER_INTERIOR_ID, IconData[id][iconInt]);

    Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, IconData[id][iconMapID], E_STREAMER_TYPE, IconData[id][iconType]);
}

forward OnIconCreated(playerid, id);
public OnIconCreated(playerid, id)
{
	MapIcon_Save(id);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat map icon dengan ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

forward LoadMapIcons();
public LoadMapIcons()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new iconids;
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", iconids);
		    cache_get_value_name_int(i, "iconvw", IconData[iconids][iconVw]);
		    cache_get_value_name_int(i, "iconint", IconData[iconids][iconInt]);
		    cache_get_value_name_float(i, "iconpos0", IconData[iconids][iconPos][0]);
		    cache_get_value_name_float(i, "iconpos1", IconData[iconids][iconPos][1]);
		    cache_get_value_name_float(i, "iconpos2", IconData[iconids][iconPos][2]);
		    cache_get_value_name_int(i, "icontype", IconData[iconids][iconType]);
            cache_get_value_name_int(i, "iconcolor", IconData[iconids][iconColor]);
			MapIcon_Rebuild(iconids);
			Iter_Add(Icons, iconids);
	    }
	    printf("[Dynamic Map Icons] Jumlah total map icons yang dimuat: %d.", rows);
	}
}