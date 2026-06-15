YCMD:addactor(playerid, params[], help)
{
    new actorid = Iter_Free(DActors), actorskin, actorname[24], actoranimation, frmtsql[522];

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(actorid <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic Actors sudah mencapai batas maksimum!");
    if(sscanf(params, "dds[24]", actorskin, actoranimation, actorname)) return SUM(playerid, "/addactor [skin] [animation] [name]");
    if(actorskin < 0 || actorskin > 311)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid skin ID (0 - 311)");

    ActorData[actorid][actorSkin] = actorskin;
    strcopy(ActorData[actorid][actorName], actorname);
    ActorData[actorid][actorAnim] = actoranimation;
    ActorData[actorid][actorInvul] = 1;
    ActorData[actorid][actorHealth] = 100.00;

    GetPlayerPos(playerid, ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2]);
    GetPlayerFacingAngle(playerid, ActorData[actorid][actorPos][3]);
    ActorData[actorid][actorWorld] = GetPlayerVirtualWorld(playerid);
    ActorData[actorid][actorInterior] = GetPlayerInterior(playerid);

    ActorData[actorid][actorPhysic] = CreateDynamicActor(ActorData[actorid][actorSkin], ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2], ActorData[actorid][actorPos][3], ActorData[actorid][actorInvul], ActorData[actorid][actorHealth], ActorData[actorid][actorWorld], ActorData[actorid][actorInterior], -1, 300.00, -1, 0);
    ActorData[actorid][actorLabel] = CreateDynamic3DTextLabel(ActorData[actorid][actorName], Y_WHITE, ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2]+1.25, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, ActorData[actorid][actorWorld], ActorData[actorid][actorInterior], -1, 300.00, -1, 0);
    SetPlayerPos(playerid, ActorData[actorid][actorPos][0]-1.0, ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2]);
    
    Iter_Add(DActors, actorid);
    
    mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "INSERT INTO `actors` SET `ID`=%d, `ActorSkin`=%d, `ActorName`='%e', `ActorAnim`=%d, `ActorInvul`=%d, `ActorHealth`='%f', `ActorX`='%f', `ActorY`='%f', `ActorZ`='%f', \
    `ActorA`='%f', `ActorWorld`=%d, `ActorInterior`=%d", actorid, ActorData[actorid][actorSkin], ActorData[actorid][actorName], ActorData[actorid][actorAnim], ActorData[actorid][actorInvul], ActorData[actorid][actorHealth],
    ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2], ActorData[actorid][actorPos][3], ActorData[actorid][actorWorld], ActorData[actorid][actorInterior]);
    mysql_pquery(g_SQL, frmtsql, "OnActorCreated", "ii", playerid, actorid);
    return 1;
}

YCMD:editactor(playerid, params[], help)
{
    new actorid, type[24], string[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", actorid, type, string)) return SUM(playerid, "/editactor [id] [type]~n~pos, skin, name, anim, invul, health");
    if(!Iter_Contains(DActors, actorid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Actor ID tersebut tidak valid!");

    if(!strcmp(type, "pos", true))
    {
        GetPlayerPos(playerid, ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2]);
        GetPlayerFacingAngle(playerid, ActorData[actorid][actorPos][3]);
        ActorData[actorid][actorWorld] = GetPlayerVirtualWorld(playerid);
        ActorData[actorid][actorInterior] = GetPlayerInterior(playerid);

        SetPlayerPos(playerid, ActorData[actorid][actorPos][0]-1.0, ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2]);

        Actor_Save(actorid);
        Actor_Refresh(actorid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the position for Actor ID: %d.", AccountData[playerid][pAdminname], actorid);
    }
    else if(!strcmp(type, "skin", true))
    {
        new actorskin;

        if(sscanf(string, "d", actorskin)) return SUM(playerid, "/editactor [id] [skin] [skin id]");

        if (actorskin < 0 || actorskin > 311)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid skin ID (0 - 311)");

        ActorData[actorid][actorSkin] = actorskin;

        Actor_Save(actorid);
        Actor_Refresh(actorid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the skin for Actor ID: %d to %d.", AccountData[playerid][pAdminname], actorid, actorskin);
    }
    else if(!strcmp(type, "name", true))
    {
        new newactorname[24];

        if(sscanf(string, "s[24]", newactorname)) return SUM(playerid, "/editactor [id] [name] [new name]");

        strcopy(ActorData[actorid][actorName], newactorname);

        Actor_Save(actorid);
        Actor_Refresh(actorid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the name for Actor ID: %d to %s.", AccountData[playerid][pAdminname], actorid, ActorData[actorid][actorName]);
    }
    else if(!strcmp(type, "anim", true))
    {
        new animidx;

        if(sscanf(string, "d", animidx)) return SUM(playerid, "/editactor [id] [anim] [index]");

        ActorData[actorid][actorAnim] = animidx;

        Actor_Save(actorid);
        Actor_Refresh(actorid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the animation for Actor ID: %d to %d.", AccountData[playerid][pAdminname], actorid, animidx);
    }
    else if(!strcmp(type, "invul", true))
    {
        switch(ActorData[actorid][actorInvul])
        {
            case 0:
            {
                ActorData[actorid][actorInvul] = 1;
            }
            case 1:
            {
                ActorData[actorid][actorInvul] = 0;
            }
        }

        Actor_Save(actorid);
        Actor_Refresh(actorid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the invulnerability for Actor ID: %d to %d.", AccountData[playerid][pAdminname], actorid, ActorData[actorid][actorInvul]);
    }
    else if(!strcmp(type, "health", true))
    {
        new Float:actorhealth;

        if(sscanf(string, "f", actorhealth)) return SUM(playerid, "/editactor [id] [health] [amount]");

        ActorData[actorid][actorHealth] = actorhealth;

        Actor_Save(actorid);
        Actor_Refresh(actorid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the health for Actor ID: %d to %.3f.", AccountData[playerid][pAdminname], actorid, actorhealth);
    }
    return 1;
}

YCMD:gotoactor(playerid, params[], help)
{
    new id;
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
        
    if(sscanf(params, "d", id))
        return SUM(playerid, "/gotoactor [id]");

    if(!Iter_Contains(DActors, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Actor ID tersebut tidak valid!");
    SetPlayerPositionEx(playerid, ActorData[id][actorPos][0]-1.0, ActorData[id][actorPos][1], ActorData[id][actorPos][2], ActorData[id][actorPos][3]);
    SetPlayerVirtualWorldEx(playerid, ActorData[id][actorWorld]);
    SetPlayerInteriorEx(playerid, ActorData[id][actorInterior]);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}

YCMD:removeactor(playerid, params[], help)
{
    new actorid, strgbg[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(sscanf(params, "d", actorid)) return SUM(playerid, "/removeactor [id]");
    if(!Iter_Contains(DActors, actorid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Actor ID tersebut tidak valid!");

    ActorData[actorid][actorSkin] = 0;
    ActorData[actorid][actorName][0] = EOS;
    ActorData[actorid][actorAnim] = 0;
    ActorData[actorid][actorInvul] = 1;
    ActorData[actorid][actorHealth] = 100.00;
    ActorData[actorid][actorPos][0] = ActorData[actorid][actorPos][1] = ActorData[actorid][actorPos][2] = ActorData[actorid][actorPos][3] = 0.0;
    ActorData[actorid][actorWorld] = 0;
    ActorData[actorid][actorInterior] = 0;

    if(DestroyDynamicActor(ActorData[actorid][actorPhysic]))
    {
        ActorData[actorid][actorPhysic] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;
    }

    if(DestroyDynamic3DTextLabel(ActorData[actorid][actorLabel]))
    {
        ActorData[actorid][actorLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    Iter_Remove(DActors, actorid);
    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `actors` WHERE `ID` = %d", actorid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s deleted Actor ID: %d.", AccountData[playerid][pAdminname], actorid);
    return 1;
}