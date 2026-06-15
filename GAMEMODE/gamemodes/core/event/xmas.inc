#include <YSI_Coding\y_hooks>

#define MAX_XMASTREE 100

enum e_xmastree
{
    Float:xmasPos[6],
    xmasVw,
    xmasInt,

    //not save
    STREAMER_TAG_OBJECT:xmasObject,
    STREAMER_TAG_3D_TEXT_LABEL:xmasLabel
};
new XmasTree[MAX_XMASTREE][e_xmastree],
    Iterator:XmasTrees<MAX_XMASTREE>;

Xmas_Nearest(playerid)
{
    foreach(new i : XmasTrees) if (IsPlayerInRangeOfPoint(playerid, 3.0, XmasTree[i][xmasPos][0], XmasTree[i][xmasPos][1], XmasTree[i][xmasPos][2]))
	{
		if (GetPlayerInterior(playerid) == XmasTree[i][xmasInt] && GetPlayerVirtualWorld(playerid) == XmasTree[i][xmasVw])
			return i;
	}
	return -1;
}

Xmas_Save(xmasid)
{
    new gjhs[512];
    mysql_format(g_SQL, gjhs, sizeof(gjhs), "UPDATE `xmas_trees` SET `X` = '%f', `Y` = '%f', `Z` = '%f', `RX` = '%f', `RY` = '%f', `RZ` = '%f', `Vw` = %d, `Int` = %d WHERE `ID` = %d", 
    XmasTree[xmasid][xmasPos][0], XmasTree[xmasid][xmasPos][1], XmasTree[xmasid][xmasPos][2], XmasTree[xmasid][xmasPos][3], XmasTree[xmasid][xmasPos][4], XmasTree[xmasid][xmasPos][5],
    XmasTree[xmasid][xmasVw], XmasTree[xmasid][xmasInt], xmasid);
    mysql_pquery(g_SQL, gjhs);
    return 1;
}

Xmas_Rebuild(xmasid)
{
    if(xmasid != -1)
    {
        XmasTree[xmasid][xmasObject] = CreateDynamicObject(19076, XmasTree[xmasid][xmasPos][0], XmasTree[xmasid][xmasPos][1], XmasTree[xmasid][xmasPos][2], XmasTree[xmasid][xmasPos][3], XmasTree[xmasid][xmasPos][4], XmasTree[xmasid][xmasPos][5], 
        XmasTree[xmasid][xmasVw], XmasTree[xmasid][xmasInt], -1, 200.00, 200.00, -1);

        XmasTree[xmasid][xmasLabel] = CreateDynamic3DTextLabel("'/xmasgift'", Y_YELLOW, XmasTree[xmasid][xmasPos][0], XmasTree[xmasid][xmasPos][1], XmasTree[xmasid][xmasPos][2]+1.5, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, XmasTree[xmasid][xmasVw], XmasTree[xmasid][xmasInt], -1, 10.00, -1, 0);
    }
    return 1;
}

/*
Xmas_Refresh(xmasid)
{
    if(xmasid != -1)
    {
        SetDynamicObjectPos(XmasTree[xmasid][xmasObject], XmasTree[xmasid][xmasPos][0], XmasTree[xmasid][xmasPos][1], XmasTree[xmasid][xmasPos][2]);
        SetDynamicObjectRot(XmasTree[xmasid][xmasObject], XmasTree[xmasid][xmasPos][3], XmasTree[xmasid][xmasPos][4], XmasTree[xmasid][xmasPos][5]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, XmasTree[xmasid][xmasObject], E_STREAMER_WORLD_ID, XmasTree[xmasid][xmasVw]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, XmasTree[xmasid][xmasObject], E_STREAMER_INTERIOR_ID, XmasTree[xmasid][xmasInt]);

        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, XmasTree[xmasid][xmasLabel], XmasTree[xmasid][xmasPos][0], XmasTree[xmasid][xmasPos][1], XmasTree[xmasid][xmasPos][2]+1.5);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, XmasTree[xmasid][xmasLabel], E_STREAMER_WORLD_ID, XmasTree[xmasid][xmasVw]);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, XmasTree[xmasid][xmasLabel], E_STREAMER_INTERIOR_ID, XmasTree[xmasid][xmasInt]);
    }
    return 1;
}
*/

Xmas_BeingEdited(id)
{
	if(!Iter_Contains(XmasTrees, id)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingXmasTreeID] == id) return 1;
	return 0;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingXmasTreeID] != -1 && Iter_Contains(XmasTrees, AccountData[playerid][EditingXmasTreeID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new edgid = AccountData[playerid][EditingXmasTreeID];
	        XmasTree[edgid][xmasPos][0] = x;
	        XmasTree[edgid][xmasPos][1] = y;
	        XmasTree[edgid][xmasPos][2] = z;
	        XmasTree[edgid][xmasPos][3] = rx;
	        XmasTree[edgid][xmasPos][4] = ry;
	        XmasTree[edgid][xmasPos][5] = rz;

			SetDynamicObjectPos(objectid, XmasTree[edgid][xmasPos][0], XmasTree[edgid][xmasPos][1], XmasTree[edgid][xmasPos][2]);
	        SetDynamicObjectRot(objectid, XmasTree[edgid][xmasPos][3], XmasTree[edgid][xmasPos][4], XmasTree[edgid][xmasPos][5]);

			Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, XmasTree[edgid][xmasLabel], XmasTree[edgid][xmasPos][0], XmasTree[edgid][xmasPos][1], XmasTree[edgid][xmasPos][2]+1.5);
			
		    Xmas_Save(edgid);
	        AccountData[playerid][EditingXmasTreeID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new edgid = AccountData[playerid][EditingXmasTreeID];
	        SetDynamicObjectPos(objectid, XmasTree[edgid][xmasPos][0], XmasTree[edgid][xmasPos][1], XmasTree[edgid][xmasPos][2]);
	        SetDynamicObjectRot(objectid, XmasTree[edgid][xmasPos][3], XmasTree[edgid][xmasPos][4], XmasTree[edgid][xmasPos][5]);
	        AccountData[playerid][EditingXmasTreeID] = -1;
	    }
	}
	return 0;
}

forward OnXmasTreeCreated(xmasid);
public OnXmasTreeCreated(xmasid)
{
    Xmas_Save(xmasid);
    Xmas_Rebuild(xmasid);
    return 1;
}

forward LoadXmasTrees();
public LoadXmasTrees()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new xmasid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", xmasid);
            cache_get_value_name_float(i, "X", XmasTree[xmasid][xmasPos][0]);
            cache_get_value_name_float(i, "Y", XmasTree[xmasid][xmasPos][1]);
            cache_get_value_name_float(i, "Z", XmasTree[xmasid][xmasPos][2]);
            cache_get_value_name_float(i, "RX", XmasTree[xmasid][xmasPos][3]);
            cache_get_value_name_float(i, "RY", XmasTree[xmasid][xmasPos][4]);
            cache_get_value_name_float(i, "RZ", XmasTree[xmasid][xmasPos][5]);
            cache_get_value_name_int(i, "Vw", XmasTree[xmasid][xmasVw]);
            cache_get_value_name_int(i, "Int", XmasTree[xmasid][xmasInt]);
            
			Xmas_Rebuild(xmasid);
			Iter_Add(XmasTrees, xmasid);
        }
        printf("[Dynamic Xmas Tree] Jumlah total Xmas Tree yang dimuat: %d.", rows);
	}
}

YCMD:addxmastree(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new xmasid = Iter_Free(XmasTrees), gjhs[512];

    if(xmasid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah Xmas Tree telah mencapai batas maksimal!");

    GetPlayerPos(playerid, XmasTree[xmasid][xmasPos][0], XmasTree[xmasid][xmasPos][1], XmasTree[xmasid][xmasPos][2]);
    XmasTree[xmasid][xmasPos][3] = 0.0;
    XmasTree[xmasid][xmasPos][4] = 0.0;
    GetPlayerFacingAngle(playerid, XmasTree[xmasid][xmasPos][5]);

    XmasTree[xmasid][xmasVw] = GetPlayerVirtualWorld(playerid);
    XmasTree[xmasid][xmasInt] = GetPlayerInterior(playerid);

    Iter_Add(XmasTrees, xmasid);

    mysql_format(g_SQL, gjhs, sizeof(gjhs), "INSERT INTO `xmas_trees` SET `ID` = %d, `X` = '%f', `Y` = '%f', `Z` = '%f', `RX` = '%f', `RY` = '%f', `RZ` = '%f', `Vw` = %d, `Int` = %d", 
    xmasid, XmasTree[xmasid][xmasPos][0], XmasTree[xmasid][xmasPos][1], XmasTree[xmasid][xmasPos][2], XmasTree[xmasid][xmasPos][3], XmasTree[xmasid][xmasPos][4], XmasTree[xmasid][xmasPos][5],
    XmasTree[xmasid][xmasVw], XmasTree[xmasid][xmasInt]);
    mysql_pquery(g_SQL, gjhs, "OnXmasTreeCreated", "i", xmasid);
    return 1;
}

YCMD:editxmastree(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new xmasid;
    if(sscanf(params, "d", xmasid)) return SUM(playerid, "/editxmastree [id]");
    if(!Iter_Contains(XmasTrees, xmasid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Xmas Tree tersebut tidak valid!");

    if(AccountData[playerid][EditingXmasTreeID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada dalam mode editing!");

    if(!IsPlayerInRangeOfPoint(playerid, 30.0, XmasTree[xmasid][xmasPos][0], XmasTree[xmasid][xmasPos][1], XmasTree[xmasid][xmasPos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan dynamic Xmas Tree tersebut!");
    if(Xmas_BeingEdited(xmasid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Xmas Tree tersebut sedang diedit oleh staff lain!");

    AccountData[playerid][EditingXmasTreeID] = xmasid;
    EditDynamicObject(playerid, XmasTree[xmasid][xmasObject]);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s editing position of Xmas Tree ID: %d.", AccountData[playerid][pAdminname], xmasid);
    return 1;
}

YCMD:xmasgift(playerid, params[], help)
{
    new xmasid = Xmas_Nearest(playerid);
    if(xmasid == -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Xmas Tree manapun!");
    if(gettime() < AccountData[playerid][pXmasGiftTime])
        return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda harus menunggu %s untuk kembali klaim hadiah!", ReturnTimelapse(gettime(), AccountData[playerid][pXmasGiftTime], ""GREEN"Sekarang!")));
    
    AccountData[playerid][pXmasGiftTime] = gettime() + 43200;

    new randgift = Random(101);
    switch(randgift)
    {
        case 0..29: // Botol
        {
            Inventory_Add(playerid, "Botol", 19570, 5);
            ShowItemBox(playerid, "Botol", "Received 5x", 19570, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mendapatkan 5x Botols dari Santa Claus.");
        }
        case 30..50: // food and drink
        {
            Inventory_Add(playerid, "Chicken BBQ", 2355, 3);
            Inventory_Add(playerid, "Coconut Water", 19564, 3);
            ShowItemBox(playerid, "Chicken BBQ", "Received 3x", 2355, 4);
            ShowItemBox(playerid, "Coconut Water", "Received 3x", 19564, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mendapatkan paket makan-minum dari Santa Claus.");
        }
        case 51..71: // cash
        {
            new randmoney = RandomEx(10000, 50000);
            GivePlayerMoneyEx(playerid, randmoney);
            ShowItemBox(playerid, "Cash", sprintf("Received $%s", FormatMoney(randmoney)), 1212, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah mendapatkan ~g~$%s ~l~dari Santa Claus.", FormatMoney(randmoney)));
        }
        case 72..86: // baseball bat
        {
            GivePlayerWeaponEx(playerid, 5, 1, WEAPON_TYPE_PLAYER);
            ShowItemBox(playerid, "Baseball Bat", "Received 1x", 336, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mendapatkan 1x Baseball Bat dari Santa Claus.");
        }
        case 87..96: // knife
        {
            GivePlayerWeaponEx(playerid, 4, 1, WEAPON_TYPE_PLAYER);
            ShowItemBox(playerid, "Knife", "Received 1x", 335, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mendapatkan 1x Knife dari Santa Claus.");
        }
        case 97..100: // diamond
        {
            Inventory_Add(playerid, "Berlian", 19874);
            ShowItemBox(playerid, "Berlian", "Received 1x", 19874, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mendapatkan 1x Diamond dari Santa Claus.");
        }
        case 101: // VIP REGULAR 7 DAYS
        {
            if(AccountData[playerid][pVIP] < 1)
            {
                AccountData[playerid][pVIP] = 1;
                AccountData[playerid][pVIPTime] = gettime() + (7 * 86400);
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mendapatkan VIP Regular Pinky 7 hari dari Santa Claus.");
            }
            else
            {
                GivePlayerMoneyEx(playerid, 1000);
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mendapatkan VIP Regular Pinky 7 hari dari Santa Claus.");
                ShowTDN(playerid, NOTIFICATION_INFO, "Namun karena anda sudah VIP maka hadiah diganti menjadi $1,000.");
            }
        }
    }
    return 1;

}

YCMD:removexmastree(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new id, strgbg[128];
	if(sscanf(params, "i", id)) return SUM(playerid, "/removexmastree [id]");
	if(!Iter_Contains(XmasTrees, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID Xmas Tree!");

    if(Xmas_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Xmas Tree tersebut sedang diedit oleh staff lain!");

    if(DestroyDynamic3DTextLabel(XmasTree[id][xmasLabel]))
        XmasTree[id][xmasLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicObject(XmasTree[id][xmasObject]))
        XmasTree[id][xmasObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;

    XmasTree[id][xmasPos][0] = XmasTree[id][xmasPos][1] = XmasTree[id][xmasPos][2] = XmasTree[id][xmasPos][3] = XmasTree[id][xmasPos][4] = XmasTree[id][xmasPos][5] = 0.0;
    XmasTree[id][xmasInt] = XmasTree[id][xmasVw] = 0;
    Iter_Remove(XmasTrees, id);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `xmas_trees` WHERE `ID` = %d", id);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has removed Xmas Tree with ID: %d.", AccountData[playerid][pAdminname], id);
    return 1;
}

YCMD:gotoxmastree(playerid, params[], help)
{
	new id;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return SUM(playerid, "/gotoxmastree [id]");

	if(!Iter_Contains(XmasTrees, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID Xmas Tree!");
	SetPlayerPositionEx(playerid, XmasTree[id][xmasPos][0], XmasTree[id][xmasPos][1], XmasTree[id][xmasPos][2], XmasTree[id][xmasPos][5]);
    SetPlayerInteriorEx(playerid, XmasTree[id][xmasInt]);
    SetPlayerVirtualWorldEx(playerid, XmasTree[id][xmasVw]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}