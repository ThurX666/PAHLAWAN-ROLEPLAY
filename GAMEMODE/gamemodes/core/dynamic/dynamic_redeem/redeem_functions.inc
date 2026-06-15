#include <YSI_Coding\y_hooks>

#define MAX_REDEEM 1000

enum e_coderedeem
{
    codeID,
    codeText[32],
    codeName[64],

    //benefit
    codeVIP,
    codeMoney,
    codeItem[32],
    codeQuantity,
    codeVehicle,

    //stuff
    codeExpired,
    codeClaimed,
    codeMaxClaim
};
new CodeRedeem[MAX_REDEEM][e_coderedeem],
    Iterator:Codes<MAX_REDEEM>;

forward OnRedeemCreated(playerid, codeid);
public OnRedeemCreated(playerid, codeid)
{
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat kode redeem %s [%s]", AccountData[playerid][pAdminname], CodeRedeem[codeid][codeText], CodeRedeem[codeid][codeName]);
    return 1;
}

forward LoadRedeem();
public LoadRedeem()
{
 	if(cache_num_rows())
  	{
 		new actorid, actorname[24];
		for(new i; i < cache_num_rows(); i++)
		{
            cache_get_value_name_int(i, "ID", actorid);
            cache_get_value_name_int(i, "ActorSkin", ActorData[actorid][actorSkin]);
            cache_get_value_name(i, "ActorName", actorname);
            strcopy(ActorData[actorid][actorName], actorname);
            cache_get_value_name_int(i, "ActorAnim", ActorData[actorid][actorAnim]);
            cache_get_value_name_int(i, "ActorInvul", ActorData[actorid][actorInvul]);
            cache_get_value_name_float(i, "ActorHealth", ActorData[actorid][actorHealth]);
            cache_get_value_name_float(i, "ActorX", ActorData[actorid][actorPos][0]);
            cache_get_value_name_float(i, "ActorY", ActorData[actorid][actorPos][1]);
            cache_get_value_name_float(i, "ActorZ", ActorData[actorid][actorPos][2]);
            cache_get_value_name_float(i, "ActorA", ActorData[actorid][actorPos][3]);
            cache_get_value_name_int(i, "ActorWorld", ActorData[actorid][actorWorld]);
            cache_get_value_name_int(i, "ActorInterior", ActorData[actorid][actorInterior]);
            
			Actor_Rebuild(actorid);
			Iter_Add(DActors, actorid);
        }
        printf("[Dynamic Actors] Jumlah total Actors yang dimuat: %d.", rows);
	}
}

YCMD:addredeem(playerid, params[], help)
{
    new vip, money, item[64], vehid, expiredhour, maxclaim, codeid = Iter_Free(Codes), quantity, haleluya[258], codename[64], testa[32], string[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(sscanf(params, "dddddds[64]s[64]S()[128]", vip, money, vehid, expiredhour, maxclaim, quantity, item, codename, string))
        return SUM(playerid, "/addredeem [vip] [money] [vehid] [jam expired] [max claim] [quantity] [item] [nama kode]");

    if(vip < 0 || vip > 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "VIP hanya dapat 0 - 3!");
    if(money < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nilai uang tidak valid!");
    if(vehid < 400 || vehid > 611) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehid!");
    if(expiredhour < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid jam expired!");
    if(maxclaim < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid max claim!");
    if(quantity < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid quantity!");
    if(isnull(codename)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan nama code!");

    if(strcmp(item, "none", true)) //jika bukan none
    {
        for (new i; i < sizeof(g_aInventoryItems); i ++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
        {
            strcopy(CodeRedeem[codeid][codeItem], item);
            CodeRedeem[codeid][codeQuantity] = quantity;

            new totalsecond = expiredhour*3600;
            new xd1 = random(sizeof(g_Alphabet)),
                xd2 = random(sizeof(g_Alphabet));

            strcopy(CodeRedeem[codeid][codeName], codename);
            CodeRedeem[codeid][codeVIP] = vip;
            CodeRedeem[codeid][codeMoney] = money;
            CodeRedeem[codeid][codeVehicle] = vehid;
            if(expiredhour > 0)
                CodeRedeem[codeid][codeExpired] = gettime() + totalsecond;
            else
                CodeRedeem[codeid][codeExpired] = 0;
            CodeRedeem[codeid][codeMaxClaim] = maxclaim;

            format(testa, sizeof(testa), "AV%d%s%d%s%d", random(10), g_Alphabet[xd1], random(10), g_Alphabet[xd2], random(10));
            strcopy(CodeRedeem[codeid][codeText], testa);

            Iter_Add(Codes, codeid);

            mysql_format(g_SQL, haleluya, sizeof(haleluya), "INSERT INTO `redeem` SET `ID` = %d, `Text`='%e', `Name`='%e', `VIP`=%d, `Money`=%d, `Item`='%e', \
            Quantity=%d, VehicleID=%d, Expired=%d, MaxClaim=%d", codeid, CodeRedeem[codeid][codeText], CodeRedeem[codeid][codeName], CodeRedeem[codeid][codeVIP], CodeRedeem[codeid][codeMoney],
            CodeRedeem[codeid][codeItem], CodeRedeem[codeid][codeQuantity], CodeRedeem[codeid][codeVehicle], CodeRedeem[codeid][codeExpired], CodeRedeem[codeid][codeMaxClaim]);
            mysql_pquery(g_SQL, haleluya, "OnRedeemCreated", "ii", playerid, codeid);
            return 1;
        }
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama item tersebut tidak ada!");
    }
    else //jika none
    {
        CodeRedeem[codeid][codeItem][0] = EOS;
        CodeRedeem[codeid][codeQuantity] = 0;

        new totalsecond = expiredhour*3600;
        new xd1 = random(sizeof(g_Alphabet)),
            xd2 = random(sizeof(g_Alphabet));

        strcopy(CodeRedeem[codeid][codeName], codename);
        CodeRedeem[codeid][codeVIP] = vip;
        CodeRedeem[codeid][codeMoney] = money;
        CodeRedeem[codeid][codeVehicle] = vehid;
        if(expiredhour > 0)
            CodeRedeem[codeid][codeExpired] = gettime() + totalsecond;
        else
            CodeRedeem[codeid][codeExpired] = 0;
        CodeRedeem[codeid][codeMaxClaim] = maxclaim;

        format(testa, sizeof(testa), "AV%d%s%d%s%d", random(10), g_Alphabet[xd1], random(10), g_Alphabet[xd2], random(10));
        strcopy(CodeRedeem[codeid][codeText], testa);

        Iter_Add(Codes, codeid);

        mysql_format(g_SQL, haleluya, sizeof(haleluya), "INSERT INTO `redeem` SET `ID` = %d, `Text`='%e', `Name`='%e', `VIP`=%d, `Money`=%d, `Item`='%e', \
        Quantity=%d, VehicleID=%d, Expired=%d, MaxClaim=%d", codeid, CodeRedeem[codeid][codeText], CodeRedeem[codeid][codeName], CodeRedeem[codeid][codeVIP], CodeRedeem[codeid][codeMoney],
        CodeRedeem[codeid][codeItem], CodeRedeem[codeid][codeQuantity], CodeRedeem[codeid][codeVehicle], CodeRedeem[codeid][codeExpired], CodeRedeem[codeid][codeMaxClaim]);
        mysql_pquery(g_SQL, haleluya, "OnRedeemCreated", "ii", playerid, codeid);
    }
    return 1;
}

YCMD:redeem(playerid, params[], help)
{
    new code[32], Float:px, Float:py, Float:pz, Float:pa;

    if(sscanf(params, "s[32]", code)) return SUM(playerid, "/redeem [code]");

    foreach(new codeid : Codes)
    {
        if(!strcmp(code, CodeRedeem[codeid][codeText], false))
        {
            if(gettime() > CodeRedeem[codeid][codeExpired])
            {
                mysql_format(g_SQL, removed, sizeof(removed), "DELETE FROM `redeem` WHERE `ID` = %d", CodeRedeem[codeid][codeID]);
                mysql_pquery(g_SQL);

                ShowTDN(playerid, NOTIFICATION_ERROR, "Kode redeem sudah expired!");
                return 1;
            }

            if(CodeRedeem[codeid][codeMaxClaim] != 0)
            {
                if(CodeRedeem[codeid][codeClaimed] >= CodeRedeem[codeid][codeMaxClaim])
                {
                    mysql_format(g_SQL, removed, sizeof(removed), "DELETE FROM `redeem` WHERE `ID` = %d", CodeRedeem[codeid][codeID]);
                    mysql_pquery(g_SQL);

                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kode redeem sudah mencapai batas maximum klaim!");
                    return 1;
                }
            } 

            if(CodeRedeem[codeid][codeVIP] != 0)
                AccountData[playerid][pVIP] = CodeRedeem[codeid][codeVIP];
            
            GivePlayerMoneyEx(playerid, CodeRedeem[codeid][codeMoney]);

            if(!isnull(CodeRedeem[codeid][codeItem]))
                Inventory_Add(playerid, CodeRedeem[codeid][codeItem], 2355, CodeRedeem[codeid][codeQuantity]);

            GetPlayerPos(playerid, px, py, pz);
            GetPlayerFacingAngle(playerid, pa);
            if(CodeRedeem[codeid][codeVehicle] != 0)
                Vehicle_Create(playerid, CodeRedeem[codeid][codeVehicle], px, py, pz, pa, random(255), random(255), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

            CodeRedeem[codeid][codeClaimed]++;
            SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"You've successfully claimed that redeem code");
            return 1;
        }
    }
    ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid code/already claimed by others!");
    return 1;
}