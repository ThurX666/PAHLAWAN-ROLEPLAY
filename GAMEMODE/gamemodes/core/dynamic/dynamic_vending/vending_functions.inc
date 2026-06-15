#include <YSI_Coding\y_hooks>

#define MAX_VENDINGS 1000

enum e_vendetails
{
    Float:venPos[6],
    venWorld,
    venInt,
    venType,

    //not save
    STREAMER_TAG_OBJECT:venObject,
    STREAMER_TAG_3D_TEXT_LABEL:venLabel
};
new VendingData[MAX_VENDINGS][e_vendetails];
new Iterator:Vendings<MAX_VENDINGS>;

Vending_Nearest(playerid)
{
    foreach(new i : Vendings) if (IsPlayerInRangeOfPoint(playerid, 2.0, VendingData[i][venPos][0], VendingData[i][venPos][1], VendingData[i][venPos][2]))
	{
		if (GetPlayerInterior(playerid) == VendingData[i][venInt] && GetPlayerVirtualWorld(playerid) == VendingData[i][venWorld])
			return i;
	}
	return -1;
}

Vending_BeingEdited(vdid)
{
	if(!Iter_Contains(Vendings, vdid)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingVendingID] == vdid) return 1;
	return 0;
}

Vending_Save(vdid)
{
	static trqqry[600];
	mysql_format(g_SQL, trqqry, sizeof(trqqry), "UPDATE `vendings` SET `World`=%d, `Interior`=%d, `X`='%f', `Y`='%f', `Z`='%f', `RX`='%f', `RY`='%f', `RZ`='%f', `Type`=%d WHERE `ID`=%d",
	VendingData[vdid][venWorld], VendingData[vdid][venInt], VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2], VendingData[vdid][venPos][3], VendingData[vdid][venPos][4], VendingData[vdid][venPos][5], VendingData[vdid][venType], vdid);
	mysql_pquery(g_SQL, trqqry);
	return 1;
}

Vending_Rebuild(vdid)
{
    if(vdid != -1)
	{
        if(DestroyDynamicObject(VendingData[vdid][venObject]))
            VendingData[vdid][venObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(VendingData[vdid][venLabel]))
            VendingData[vdid][venLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(VendingData[vdid][venType] == 1)
        {
            VendingData[vdid][venObject] = CreateDynamicObject(1209, VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2], VendingData[vdid][venPos][3], VendingData[vdid][venPos][4], VendingData[vdid][venPos][5], VendingData[vdid][venWorld], VendingData[vdid][venInt], -1, 100.00, 100.00, -1);
        }
        else
        {
            VendingData[vdid][venObject] = CreateDynamicObject(1776, VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2], VendingData[vdid][venPos][3], VendingData[vdid][venPos][4], VendingData[vdid][venPos][5], VendingData[vdid][venWorld], VendingData[vdid][venInt], -1, 100.00, 100.00, -1);
            SetDynamicObjectMaterial(VendingData[vdid][venObject], 0, 5443, "glenpark1_lae", "chocolate1", 0x00000000);
            SetDynamicObjectMaterial(VendingData[vdid][venObject], 1, 2221, "donut_tray", "rustycoffeerap_rb", 0x00000000);
            SetDynamicObjectMaterial(VendingData[vdid][venObject], 3, 5443, "glenpark1_lae", "chocolate1", 0x00000000);
        }
        VendingData[vdid][venLabel] = CreateDynamic3DTextLabel("[Y] "WHITE"Use vending machine", 0x00FF00A6, VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2]+1.0, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, VendingData[vdid][venWorld], VendingData[vdid][venInt], -1, 10.00, -1, 0);
	}
}

forward LoadVendings();
public LoadVendings()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new vdid;

		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", vdid);
		    cache_get_value_name_int(i, "World", VendingData[vdid][venWorld]);
		    cache_get_value_name_int(i, "Interior", VendingData[vdid][venInt]);
		    cache_get_value_name_float(i, "X", VendingData[vdid][venPos][0]);
			cache_get_value_name_float(i, "Y", VendingData[vdid][venPos][1]);
			cache_get_value_name_float(i, "Z", VendingData[vdid][venPos][2]);
			
			cache_get_value_name_float(i, "RX", VendingData[vdid][venPos][3]);
			cache_get_value_name_float(i, "RY", VendingData[vdid][venPos][4]);
			cache_get_value_name_float(i, "RZ", VendingData[vdid][venPos][5]);

            cache_get_value_name_int(i, "Type", VendingData[vdid][venType]);
			
			Iter_Add(Vendings, vdid);
			Vending_Rebuild(vdid);
	    }
	    printf("[Dynamic Vending] Total dynamic vending loaded: %d.", rows);
	}
}

forward OnVendingCreated(playerid, vdid);
public OnVendingCreated(playerid, vdid)
{
	Vending_Save(vdid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has created Vending ID: %d.", AccountData[playerid][pAdminname], vdid);
	return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingVendingID] != -1 && Iter_Contains(Vendings, (AccountData[playerid][EditingVendingID])))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new vdid = AccountData[playerid][EditingVendingID];
	        VendingData[vdid][venPos][0] = x;
	        VendingData[vdid][venPos][1] = y;
	        VendingData[vdid][venPos][2] = z;
	        VendingData[vdid][venPos][3] = rx;
	        VendingData[vdid][venPos][4] = ry;
	        VendingData[vdid][venPos][5] = rz;

	        SetDynamicObjectPos(objectid, VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2]);
	        SetDynamicObjectRot(objectid, VendingData[vdid][venPos][3], VendingData[vdid][venPos][4], VendingData[vdid][venPos][5]);

		    Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, VendingData[vdid][venLabel], VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2]+1.0);

		    Vending_Save(vdid);
	        AccountData[playerid][EditingVendingID] = -1;
	    }

	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new vdid = AccountData[playerid][EditingVendingID];
	        SetDynamicObjectPos(objectid, VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2]);
	        SetDynamicObjectRot(objectid, VendingData[vdid][venPos][3], VendingData[vdid][venPos][4], VendingData[vdid][venPos][5]);
	        AccountData[playerid][EditingVendingID] = -1;
	    }
	}
	return 0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!AccountData[playerid][pKnockdown])
		{
            new id = Vending_Nearest(playerid);

            if(id != -1)
            {
                if(!AVC_PConnected[playerid]) return Kick(playerid);
                
                if(VendingData[id][venType] == 1)
                {
                    Dialog_Show(playerid, "VendingDrink", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Vending Menu", 
                    "Name\tPrice\n\
                    Cola\t$10.50\n\
                    Sprunk\t$10.50", "Buy", "Batal");
                }
                else
                {
                    Dialog_Show(playerid, "VendingSnack", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Vending Menu", 
                    "Name\tPrice\n\
                    Snack\t$10.50\n\
                    Cereal\t$10.50", "Buy", "Batal");
                }
            }
        }
    }
    return 1;
}