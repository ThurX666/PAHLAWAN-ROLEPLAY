#include <YSI_Coding\y_hooks>

#define MAX_DYNACTORS 1000

enum e_ActorsDetails
{
    actorSkin,
    actorName[24],
    actorAnim,
    actorInvul,
    Float:actorHealth,
    Float:actorPos[4],
    actorWorld,
    actorInterior,

    //not save
    STREAMER_TAG_ACTOR:actorPhysic,
    STREAMER_TAG_3D_TEXT_LABEL:actorLabel
};
new ActorData[MAX_DYNACTORS][e_ActorsDetails],
    Iterator:DActors<MAX_DYNACTORS>;

Actor_Nearest(playerid)
{
    foreach(new i : DActors) if (IsPlayerInRangeOfPoint(playerid, 3.0, ActorData[i][actorPos][0], ActorData[i][actorPos][1], ActorData[i][actorPos][2]))
	{
		if (GetPlayerInterior(playerid) == ActorData[i][actorInterior] && GetPlayerVirtualWorld(playerid) == ActorData[i][actorWorld])
			return i;
	}
	return -1;
}

Actor_Save(actorid)
{
    new frmtsql[522];

    mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `actors` SET `ActorSkin`=%d, `ActorName`='%e', `ActorAnim`=%d, `ActorInvul`=%d, `ActorHealth`='%f', `ActorX`='%f', `ActorY`='%f', `ActorZ`='%f', \
    `ActorA`='%f', `ActorWorld`=%d, `ActorInterior`=%d WHERE `ID`=%d", ActorData[actorid][actorSkin], ActorData[actorid][actorName], ActorData[actorid][actorAnim], ActorData[actorid][actorInvul], ActorData[actorid][actorHealth],
    ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2], ActorData[actorid][actorPos][3], ActorData[actorid][actorWorld], ActorData[actorid][actorInterior], actorid);
    mysql_pquery(g_SQL, frmtsql);
    return 1;
}

Actor_Refresh(actorid)
{
    if(actorid != -1)
    {
        new animlib[32], animname[32];

        Streamer_SetIntData(STREAMER_TYPE_ACTOR, ActorData[actorid][actorPhysic], E_STREAMER_MODEL_ID, ActorData[actorid][actorSkin]);

        if(ActorData[actorid][actorAnim] != 0)
		{
			GetAnimationName(ActorData[actorid][actorAnim], animlib, 32, animname, 32);
			ApplyDynamicActorAnimation(ActorData[actorid][actorPhysic], animlib, animname, 4.1, 1, 0, 0, 1, 0);
		}
        else
        {
            ApplyDynamicActorAnimation(ActorData[actorid][actorPhysic], "PED", "IDLE_stance", 1.50, 1, 0, 0, 0, 0);
        }

        SetDynamicActorInvulnerable(ActorData[actorid][actorPhysic], ActorData[actorid][actorInvul]);
        SetDynamicActorHealth(ActorData[actorid][actorPhysic], ActorData[actorid][actorHealth]);
        SetDynamicActorPos(ActorData[actorid][actorPhysic], ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2]);
        SetDynamicActorFacingAngle(ActorData[actorid][actorPhysic], ActorData[actorid][actorPos][3]);
        SetDynamicActorVirtualWorld(ActorData[actorid][actorPhysic], ActorData[actorid][actorWorld]);
        Streamer_SetIntData(STREAMER_TYPE_ACTOR, ActorData[actorid][actorPhysic], E_STREAMER_INTERIOR_ID, ActorData[actorid][actorInterior]);

        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, ActorData[actorid][actorLabel], ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2]+1.25);
        UpdateDynamic3DTextLabelText(ActorData[actorid][actorLabel], Y_WHITE, ActorData[actorid][actorName]);
    }
    return 1;
}

Actor_Rebuild(actorid)
{
    if(actorid != -1)
    {
        ActorData[actorid][actorPhysic] = CreateDynamicActor(ActorData[actorid][actorSkin], ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2], ActorData[actorid][actorPos][3], ActorData[actorid][actorInvul], ActorData[actorid][actorHealth], ActorData[actorid][actorWorld], ActorData[actorid][actorInterior], -1, 300.00, -1, 0);
        ActorData[actorid][actorLabel] = CreateDynamic3DTextLabel(ActorData[actorid][actorName], Y_WHITE, ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2]+1.25, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, ActorData[actorid][actorWorld], ActorData[actorid][actorInterior], -1, 300.00, -1, 0);

        Actor_Refresh(actorid);
    }
    return 1;
}

forward OnActorCreated(playerid, actorid);
public OnActorCreated(playerid, actorid)
{
    Actor_Save(actorid);
    Actor_Refresh(actorid);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Actor dengan ID: %d.", AccountData[playerid][pAdminname], actorid);
    return 1;
}

forward LoadActors();
public LoadActors()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new actorid, actorname[24];
		for(new i; i < rows; i++)
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