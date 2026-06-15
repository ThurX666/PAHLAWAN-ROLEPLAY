#include <YSI_Coding\y_hooks>

#define MAX_GRAFFITIS 1000

enum graffInfo
{
    gfModel,
    gfVW,
    gfInt,
    gfText[144],
    gfCreatorID,
    gfCreator[MAX_PLAYER_NAME + 1],
    Float:gfPos[6],
    gfExpiredTime,

    //not saved
    STREAMER_TAG_OBJECT: gfObjid
};
new GraffitiInfo[MAX_GRAFFITIS][graffInfo],
    Iterator:ServerTags<MAX_GRAFFITIS>;

enum p_graffInfos
{
    SprayMax
};
new PlayerGraffitiInfo[MAX_PLAYERS][p_graffInfos];

Graffiti_BeingEdited(id)
{
	if(!Iter_Contains(ServerTags, id)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingGraffitiID] == id) return 1;
	return 0;
}

Graffiti_Nearest(playerid)
{
    foreach(new i : ServerTags) if(IsPlayerInRangeOfPoint(playerid, 4.0, GraffitiInfo[i][gfPos][0], GraffitiInfo[i][gfPos][1], GraffitiInfo[i][gfPos][2]))
	{
		if(GetPlayerInterior(playerid) == GraffitiInfo[i][gfInt] && GetPlayerVirtualWorld(playerid) == GraffitiInfo[i][gfVW])
			return i;
	}
	return -1;
}

GetPlayerTagLimit(playerid)
{
	new limit = 1;
	switch(AccountData[playerid][pVIP])
	{
		case 0:
		{
			limit = 1;
		}
		case 1:
		{
			limit = 2;
		}
		case 2:
		{
			limit = 3;
		}
		case 3:
		{
			limit = 4;
		}
	}
	return limit;
}

CountingPlayerTags(playerid)
{
    new counting = 0;
    foreach(new v : ServerTags)
    {
        if(GraffitiInfo[v][gfCreatorID] == AccountData[playerid][pID])
            counting++;
    }
    return counting;
}

ResetPlayerTagEnum(playerid)
{
    PlayerGraffitiInfo[playerid][SprayMax] = 0;
}

Graffiti_Save(tgid)
{
	new
	    query[555];
        
	mysql_format(g_SQL, query, sizeof(query), "UPDATE `server_tags` SET `Model` = %d, `VW` = %d, `Int` = %d, `Text` = '%e', `CreatorID` = %d, `Creator` = '%e', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `PosRX` = '%f', `PosRY` = '%f', `PosRZ` = '%f', `Expired` = %d WHERE `id` = %d",
        GraffitiInfo[tgid][gfModel], GraffitiInfo[tgid][gfVW], GraffitiInfo[tgid][gfInt], GraffitiInfo[tgid][gfText], GraffitiInfo[tgid][gfCreatorID], GraffitiInfo[tgid][gfCreator], 
        GraffitiInfo[tgid][gfPos][0], GraffitiInfo[tgid][gfPos][1], GraffitiInfo[tgid][gfPos][2], GraffitiInfo[tgid][gfPos][3], GraffitiInfo[tgid][gfPos][4], GraffitiInfo[tgid][gfPos][5], GraffitiInfo[tgid][gfExpiredTime], tgid);
    mysql_pquery(g_SQL, query);
	return 1;
}

forward LoadGraffities();
public LoadGraffities()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new id;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", id);
            cache_get_value_name_int(i, "Model", GraffitiInfo[id][gfModel]);
            cache_get_value_name_int(i, "VW", GraffitiInfo[id][gfVW]);
            cache_get_value_name_int(i, "Int", GraffitiInfo[id][gfInt]);
            cache_get_value_name(i, "Text", GraffitiInfo[id][gfText]);
            cache_get_value_name_int(i, "CreatorID", GraffitiInfo[id][gfCreatorID]);
            cache_get_value_name(i, "Creator", GraffitiInfo[id][gfCreator]);
            cache_get_value_name_float(i, "PosX", GraffitiInfo[id][gfPos][0]);
            cache_get_value_name_float(i, "PosY", GraffitiInfo[id][gfPos][1]);
            cache_get_value_name_float(i, "PosZ", GraffitiInfo[id][gfPos][2]);
            cache_get_value_name_float(i, "PosRX", GraffitiInfo[id][gfPos][3]);
            cache_get_value_name_float(i, "PosRY", GraffitiInfo[id][gfPos][4]);
            cache_get_value_name_float(i, "PosRZ", GraffitiInfo[id][gfPos][5]);
            cache_get_value_name_int(i, "Expired", GraffitiInfo[id][gfExpiredTime]);
            
			if(DestroyDynamicObject(GraffitiInfo[id][gfObjid]))
                GraffitiInfo[id][gfObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
            
            GraffitiInfo[id][gfObjid] = CreateDynamicObject(18661, GraffitiInfo[id][gfPos][0], GraffitiInfo[id][gfPos][1], GraffitiInfo[id][gfPos][2], GraffitiInfo[id][gfPos][3], GraffitiInfo[id][gfPos][4], GraffitiInfo[id][gfPos][5], GraffitiInfo[id][gfVW], GraffitiInfo[id][gfInt], -1, 100.00, 100.00, -1);
            
            if(!isnull(GraffitiInfo[id][gfText]))
            {
                SetDynamicObjectMaterialText(GraffitiInfo[id][gfObjid], 0, GraffitiInfo[id][gfText], OBJECT_MATERIAL_SIZE_512x256, "Arial", 50, 1, -1, 0, 1);
            }
			Iter_Add(ServerTags, id);
        }
        printf("[Dynamic Graffities] Total Graffiti Tags loaded: %d.", rows);
	}
    return 1;
}

task CheckingGraffitiExp[60000]() 
{
    foreach(new x : ServerTags) if(x != INVALID_ITERATOR_SLOT)
    {
        if(GraffitiInfo[x][gfExpiredTime] != 0 && GraffitiInfo[x][gfExpiredTime] <= gettime())
        {
            if(DestroyDynamicObject(GraffitiInfo[x][gfObjid]))
                GraffitiInfo[x][gfObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            GraffitiInfo[x][gfModel] = 0;
            GraffitiInfo[x][gfVW] = 0;
            GraffitiInfo[x][gfInt] = 0;
            GraffitiInfo[x][gfText][0] = EOS;
            GraffitiInfo[x][gfCreatorID] = 0;
            GraffitiInfo[x][gfCreator][0] = EOS;
            GraffitiInfo[x][gfPos][0] = 0.0;
            GraffitiInfo[x][gfPos][1] = 0.0;
            GraffitiInfo[x][gfPos][2] = 0.0;
            GraffitiInfo[x][gfPos][3] = 0.0;
            GraffitiInfo[x][gfPos][4] = 0.0;
            GraffitiInfo[x][gfPos][5] = 0.0;
            GraffitiInfo[x][gfExpiredTime] = 0;
            
            Iter_Remove(ServerTags, x);

            static string[144];
            mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `server_tags` WHERE `id` = %d", x);
            mysql_pquery(g_SQL, string);
        }
    }
    return 1;
}

ptask UpdateTaggingTimer[1000](playerid) 
{
    if(AccountData[playerid][pSpawned] && pTaggingTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            if(DestroyDynamicObject(GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfObjid]))
                GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfModel] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfVW] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfInt] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfText][0] = EOS;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfCreatorID] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfCreator][0] = EOS;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][0] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][1] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][2] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][3] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][4] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][5] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfExpiredTime] = 0;
            
            Iter_Remove(ServerTags, AccountData[playerid][EditingGraffitiID]);
            
            static string[144];
            mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `server_tags` WHERE `id` = %d", AccountData[playerid][EditingGraffitiID]);
            mysql_pquery(g_SQL, string);

            AccountData[playerid][EditingGraffitiID] = -1;

            ResetPlayerTagEnum(playerid);
            pTaggingTimer[playerid] = false;
            return 0;
        }
    
        if(!PlayerHasItem(playerid, "Pilox"))
        {
            if(DestroyDynamicObject(GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfObjid]))
                GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfModel] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfVW] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfInt] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfText][0] = EOS;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfCreatorID] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfCreator][0] = EOS;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][0] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][1] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][2] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][3] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][4] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][5] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfExpiredTime] = 0;
            
            Iter_Remove(ServerTags, AccountData[playerid][EditingGraffitiID]);

            static string[144];
            mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `server_tags` WHERE `id` = %d", AccountData[playerid][EditingGraffitiID]);
            mysql_pquery(g_SQL, string);

            AccountData[playerid][EditingGraffitiID] = -1;

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ResetPlayerTagEnum(playerid);
            AccountData[playerid][pActivityTime] = 0;
            pTaggingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki spraycan!");
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 3.5, GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][0], GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][1], GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][2]))
        {
            if(DestroyDynamicObject(GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfObjid]))
                GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfModel] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfVW] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfInt] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfText][0] = EOS;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfCreatorID] = 0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfCreator][0] = EOS;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][0] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][1] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][2] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][3] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][4] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfPos][5] = 0.0;
            GraffitiInfo[AccountData[playerid][EditingGraffitiID]][gfExpiredTime] = 0;
            
            Iter_Remove(ServerTags, AccountData[playerid][EditingGraffitiID]);

            static string[144];
            mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `server_tags` WHERE `id` = %d", AccountData[playerid][EditingGraffitiID]);
            mysql_pquery(g_SQL, string);

            AccountData[playerid][EditingGraffitiID] = -1;

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ResetPlayerTagEnum(playerid);
            AccountData[playerid][pActivityTime] = 0;
            pTaggingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan graffiti tersebut!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= PlayerGraffitiInfo[playerid][SprayMax])
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            pTaggingTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Pilox");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat graffiti pada dinding tersebut.");

            AccountData[playerid][EditingGraffitiID] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/PlayerGraffitiInfo[playerid][SprayMax];
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingGraffitiID] != -1 && Iter_Contains(ServerTags, AccountData[playerid][EditingGraffitiID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new edgid = AccountData[playerid][EditingGraffitiID];

            GraffitiInfo[edgid][gfPos][0] = x;
	        GraffitiInfo[edgid][gfPos][1] = y;
	        GraffitiInfo[edgid][gfPos][2] = z;
	        GraffitiInfo[edgid][gfPos][3] = rx;
	        GraffitiInfo[edgid][gfPos][4] = ry;
	        GraffitiInfo[edgid][gfPos][5] = rz;

            if(!IsPlayerInRangeOfPoint(playerid, 3.5, GraffitiInfo[edgid][gfPos][0], GraffitiInfo[edgid][gfPos][1], GraffitiInfo[edgid][gfPos][2]))
            {
                if(DestroyDynamicObject(GraffitiInfo[edgid][gfObjid]))
                    GraffitiInfo[edgid][gfObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                GraffitiInfo[edgid][gfModel] = 0;
                GraffitiInfo[edgid][gfVW] = 0;
                GraffitiInfo[edgid][gfInt] = 0;
                GraffitiInfo[edgid][gfText][0] = EOS;
                GraffitiInfo[edgid][gfCreatorID] = 0;
                GraffitiInfo[edgid][gfCreator][0] = EOS;
                GraffitiInfo[edgid][gfPos][0] = 0.0;
                GraffitiInfo[edgid][gfPos][1] = 0.0;
                GraffitiInfo[edgid][gfPos][2] = 0.0;
                GraffitiInfo[edgid][gfPos][3] = 0.0;
                GraffitiInfo[edgid][gfPos][4] = 0.0;
                GraffitiInfo[edgid][gfPos][5] = 0.0;
                GraffitiInfo[edgid][gfExpiredTime] = 0;
                
                Iter_Remove(ServerTags, edgid);

                static string[144];
                mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `server_tags` WHERE `id` = %d", edgid);
                mysql_pquery(g_SQL, string);

                AccountData[playerid][EditingGraffitiID] = -1;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan graffiti tersebut!");
            }

			SetDynamicObjectPos(objectid, GraffitiInfo[edgid][gfPos][0], GraffitiInfo[edgid][gfPos][1], GraffitiInfo[edgid][gfPos][2]);
	        SetDynamicObjectRot(objectid, GraffitiInfo[edgid][gfPos][3], GraffitiInfo[edgid][gfPos][4], GraffitiInfo[edgid][gfPos][5]);

            Graffiti_Save(edgid);

            AccountData[playerid][pActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENYEMPROT");
            ShowProgressBar(playerid);

            pTaggingTimer[playerid] = true;

            TogglePlayerControllable(playerid, false);
            ApplyAnimation(playerid, "GRAFFITI", "spraycan_fire", 2.33, true, false, false, false, 0, true);
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new edgid = AccountData[playerid][EditingGraffitiID];
	        
            if(DestroyDynamicObject(GraffitiInfo[edgid][gfObjid]))
                GraffitiInfo[edgid][gfObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            GraffitiInfo[edgid][gfModel] = 0;
            GraffitiInfo[edgid][gfVW] = 0;
            GraffitiInfo[edgid][gfInt] = 0;
            GraffitiInfo[edgid][gfText][0] = EOS;
            GraffitiInfo[edgid][gfCreatorID] = 0;
            GraffitiInfo[edgid][gfCreator][0] = EOS;
            GraffitiInfo[edgid][gfPos][0] = 0.0;
            GraffitiInfo[edgid][gfPos][1] = 0.0;
            GraffitiInfo[edgid][gfPos][2] = 0.0;
            GraffitiInfo[edgid][gfPos][3] = 0.0;
            GraffitiInfo[edgid][gfPos][4] = 0.0;
            GraffitiInfo[edgid][gfPos][5] = 0.0;
            GraffitiInfo[edgid][gfExpiredTime] = 0;
            
            Iter_Remove(ServerTags, edgid);

            static string[144];
            mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `server_tags` WHERE `id` = %d", edgid);
            mysql_pquery(g_SQL, string);

	        AccountData[playerid][EditingGraffitiID] = -1;
            SendClientMessage(playerid, -1, "Anda telah membatalkan pembuatan graffiti dan graffiti tersebut telah dihapus.");
	    }
	}
	return 0;
}

Dialog:GraffitiAdd(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(isnull(inputtext))
    {
        Dialog_Show(playerid, "GraffitiAdd", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Add Graffiti", 
        "Error: Tag tidak bisa diisi kosong!\n\
        Mohon masukkan tulisan graffiti yang ingin dibuat:\n\
        (n) = text akan berada di bawah/baris baru.\n\
        (r) = warna text merah.\n\
        (b) = warna text hitam.\n\
        (y) = warna text kuning.\n\
        (bl) = warna text biru.\n\
        (g) = warna text hijau.\n\
        (o) = warna text orange.\n\
        (w) = warna text putih.", "Input", "Batal");
        return 1;
    }

    if(strlen(inputtext) < 4 || strlen(inputtext) > 144)
    {
        Dialog_Show(playerid, "GraffitiAdd", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Add Graffiti", 
        "Error: Tag terlalu singkat minimal 4 karakter dan max 144 karakter!\n\
        Mohon masukkan tulisan graffiti yang ingin dibuat:\n\
        (n) = text akan berada di bawah/baris baru.\n\
        (r) = warna text merah.\n\
        (b) = warna text hitam.\n\
        (y) = warna text kuning.\n\
        (bl) = warna text biru.\n\
        (g) = warna text hijau.\n\
        (o) = warna text orange.\n\
        (w) = warna text putih.", "Input", "Batal");
        return 1;
    }

    if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1) 
    {
        Dialog_Show(playerid, "GraffitiAdd", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Add Graffiti", 
        "Error: Tidak dapat memasukkan simbol/tanda persen!\n\
        Mohon masukkan tulisan graffiti yang ingin dibuat:\n\
        (n) = text akan berada di bawah/baris baru.\n\
        (r) = warna text merah.\n\
        (b) = warna text hitam.\n\
        (y) = warna text kuning.\n\
        (bl) = warna text biru.\n\
        (g) = warna text hijau.\n\
        (o) = warna text orange.\n\
        (w) = warna text putih.", "Input", "Batal");
        return 1;
    }

    new tgid = Iter_Free(ServerTags);
    if(tgid <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "The server tags telah mencapai batas maksimum!");
    
    strcopy(GraffitiInfo[tgid][gfText], inputtext);
    PlayerGraffitiInfo[playerid][SprayMax] = strlen(inputtext);

    ReplaceText(GraffitiInfo[tgid][gfText], "(n)", "\n");
    ReplaceText(GraffitiInfo[tgid][gfText], "(r)", "{FF0000}"); // red
    ReplaceText(GraffitiInfo[tgid][gfText], "(b)", "{0E0101}"); // black
    ReplaceText(GraffitiInfo[tgid][gfText], "(y)", "{FFFF00}"); // yellow
    ReplaceText(GraffitiInfo[tgid][gfText], "(bl)", "{0000FF}"); // blue
    ReplaceText(GraffitiInfo[tgid][gfText], "(g)", "{00FF00}"); // green
    ReplaceText(GraffitiInfo[tgid][gfText], "(o)", "{FFA500}"); // orange
    ReplaceText(GraffitiInfo[tgid][gfText], "(w)", "{FFFFFF}"); // white

    if(DestroyDynamicObject(GraffitiInfo[tgid][gfObjid]))
        GraffitiInfo[tgid][gfObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    GraffitiInfo[tgid][gfModel] = 18661;
    GraffitiInfo[tgid][gfVW] = GetPlayerVirtualWorld(playerid);
    GraffitiInfo[tgid][gfInt] = GetPlayerInterior(playerid);

    GetPlayerPos(playerid, GraffitiInfo[tgid][gfPos][0], GraffitiInfo[tgid][gfPos][1], GraffitiInfo[tgid][gfPos][2]);
    GraffitiInfo[tgid][gfPos][3] = GraffitiInfo[tgid][gfPos][4] = GraffitiInfo[tgid][gfPos][5] = 0.0;
    GraffitiInfo[tgid][gfObjid] = CreateDynamicObject(18661, GraffitiInfo[tgid][gfPos][0], GraffitiInfo[tgid][gfPos][1], GraffitiInfo[tgid][gfPos][2], GraffitiInfo[tgid][gfPos][3], GraffitiInfo[tgid][gfPos][4], GraffitiInfo[tgid][gfPos][5], GraffitiInfo[tgid][gfVW], GraffitiInfo[tgid][gfInt], -1, 100.00, 100.00, -1);
    GraffitiInfo[tgid][gfCreatorID] = AccountData[playerid][pID];
    strcopy(GraffitiInfo[tgid][gfCreator], AccountData[playerid][pName]);
    GraffitiInfo[tgid][gfExpiredTime] = gettime() + 604800; //7 hari

    if(!isnull(GraffitiInfo[tgid][gfText]))
    {
        SetDynamicObjectMaterialText(GraffitiInfo[tgid][gfObjid], 0, GraffitiInfo[tgid][gfText], OBJECT_MATERIAL_SIZE_512x256, "Arial", 50, 1, -1, 0, 1);
    }

    Iter_Add(ServerTags, tgid);

    static string[555];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `server_tags` (`id`, `Model`, `VW`, `Int`, `Text`, `CreatorID`, `Creator`, `PosX`, `PosY`, `PosZ`, `PosRX`, `PosRY`, `PosRZ`, `Expired`) VALUES (%d, %d, %d, %d, '%e', %d, '%e', '%f', '%f', '%f', '%f', '%f', '%f', %d)", tgid, GraffitiInfo[tgid][gfModel], GraffitiInfo[tgid][gfVW], GraffitiInfo[tgid][gfInt], GraffitiInfo[tgid][gfText], GraffitiInfo[tgid][gfCreatorID], GraffitiInfo[tgid][gfCreator], 
    GraffitiInfo[tgid][gfPos][0], GraffitiInfo[tgid][gfPos][1], GraffitiInfo[tgid][gfPos][2], GraffitiInfo[tgid][gfPos][3], GraffitiInfo[tgid][gfPos][4], GraffitiInfo[tgid][gfPos][5], GraffitiInfo[tgid][gfExpiredTime]);
    mysql_pquery(g_SQL, string);

    EditDynamicObject(playerid, GraffitiInfo[tgid][gfObjid]);
    AccountData[playerid][EditingGraffitiID] = tgid;
    return 1;
}

Dialog:GraffitiEdit(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(isnull(inputtext))
    {
        Dialog_Show(playerid, "GraffitiEdit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Add Graffiti", 
        "Error: Tag tidak bisa diisi kosong!\n\
        Mohon masukkan tulisan graffiti yang ingin dibuat:\n\
        (n) = text akan berada di bawah/baris baru.\n\
        (r) = warna text merah.\n\
        (b) = warna text hitam.\n\
        (y) = warna text kuning.\n\
        (bl) = warna text biru.\n\
        (g) = warna text hijau.\n\
        (o) = warna text orange.\n\
        (w) = warna text putih.", "Input", "Batal");
        return 1;
    }

    if(strlen(inputtext) < 4 || strlen(inputtext) > 144)
    {
        Dialog_Show(playerid, "GraffitiEdit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Add Graffiti", 
        "Error: Tag terlalu singkat minimal 4 karakter dan max 144 karakter!\n\
        Mohon masukkan tulisan graffiti yang ingin dibuat:\n\
        (n) = text akan berada di bawah/baris baru.\n\
        (r) = warna text merah.\n\
        (b) = warna text hitam.\n\
        (y) = warna text kuning.\n\
        (bl) = warna text biru.\n\
        (g) = warna text hijau.\n\
        (o) = warna text orange.\n\
        (w) = warna text putih.", "Input", "Batal");
        return 1;
    }

    if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1) 
    {
        Dialog_Show(playerid, "GraffitiEdit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Add Graffiti", 
        "Error: You cannot input percent symbol!\n\
        Mohon masukkan tulisan graffiti yang ingin dibuat:\n\
        (n) = text akan berada di bawah/baris baru.\n\
        (r) = warna text merah.\n\
        (b) = warna text hitam.\n\
        (y) = warna text kuning.\n\
        (bl) = warna text biru.\n\
        (g) = warna text hijau.\n\
        (o) = warna text orange.\n\
        (w) = warna text putih.", "Input", "Batal");
        return 1;
    }

    new tgid = AccountData[playerid][pTempValue];
    if(!Iter_Contains(ServerTags, tgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Graffiti Tag ID tersebut tidak valid!");
    if(Graffiti_BeingEdited(tgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Graffiti Tag ID sedang diedit oleh admin lain!");

    strcopy(GraffitiInfo[tgid][gfText], inputtext);

    ReplaceText(GraffitiInfo[tgid][gfText], "(n)", "\n");
    ReplaceText(GraffitiInfo[tgid][gfText], "(r)", "{FF0000}"); // red
    ReplaceText(GraffitiInfo[tgid][gfText], "(b)", "{0E0101}"); // black
    ReplaceText(GraffitiInfo[tgid][gfText], "(y)", "{FFFF00}"); // yellow
    ReplaceText(GraffitiInfo[tgid][gfText], "(bl)", "{0000FF}"); // blue
    ReplaceText(GraffitiInfo[tgid][gfText], "(g)", "{00FF00}"); // green
    ReplaceText(GraffitiInfo[tgid][gfText], "(o)", "{FFA500}"); // orange
    ReplaceText(GraffitiInfo[tgid][gfText], "(w)", "{FFFFFF}"); // white

    if(!isnull(GraffitiInfo[tgid][gfText]))
    {
        SetDynamicObjectMaterialText(GraffitiInfo[tgid][gfObjid], 0, GraffitiInfo[tgid][gfText], OBJECT_MATERIAL_SIZE_512x256, "Arial", 50, 1, -1, 0, 1);
    }

    Graffiti_Save(tgid);

    EditDynamicObject(playerid, GraffitiInfo[tgid][gfObjid]);
    AccountData[playerid][EditingGraffitiID] = tgid;
    return 1;
}