// YCMD:fish(playerid, params[], help)
// {
//     if(AccountData[playerid][pFishingDelay] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "You've to waiting for %d minutes as your fishing delay!", AccountData[playerid][pFishingDelay]/60);

//     new count, fishzoneid = GetPlayerFishingAreaID(playerid);

//     if(fishzoneid == -1)
//     {
//         return SEM(playerid, "You are not in any fishing zone!");
//     }

//     if(__g_FishingLoc[fishzoneid][Type] >= AREA_TYPE_OCEAN_BOAT)
//     {
//         if(IsPlayerInWater(playerid))
//         {
//             return SEM(playerid, "You need to be on a boat!");
//         }

//         if(AccountData[playerid][pFishingSkill] < 2)
//         {
//             return SEM(playerid, "You can only fish from a boat if your fishing skill level is 2 or higher!");
//         }
//     }

//     if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
//         return SEM(playerid, "Anda harus berjalan kaki!");

//     if(!PlayerHasItem(playerid, "Pancingan"))
//         return SEM(playerid, "You don't have a Pancingan!");

//     if(!PlayerHasItem(playerid, "Bait"))
//         return SEM(playerid, "You don't have a bait!");

//     if(IsPlayerFishing[playerid])
//         return SEM(playerid, "You are currently fishing!");

//     if(AccountData[playerid][pKnockdown])
//         return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

//     for(new x; x < 5; x++)
//     {
//         if(PlayerFishes[playerid][x][Weight] != 0)
//         {
//             count++;
//         }
//     }
//     if(count >= 5) return SEM(playerid, "You have reached maximum fish amount!");

//     new randfishtime = RandomEx(45570, 61500);
//     new randevent = Random(101);

//     Inventory_Remove(playerid, "Bait");
//     switch(randevent)
//     {
//         case 0.. 95: //fishing berhasil
//         {
//             SetTimerEx("FishingFunc", randfishtime, false, "i", playerid);
//             IsPlayerFishing[playerid] = true;
//             AccountData[playerid][pInFishingArea] = fishzoneid;
//             ApplyAnimation(playerid, "SWORD", "sword_block", 4.1, false, true, true, true, true, true);
//             SetPlayerAttachedObject(playerid, 9, 18632, 6, 0.00000, 0.00000, 0.00000, 0.00000, 180.00000, 90.00000, 1, 1, 1);
//             SendClientMessage(playerid, -1, "You have started fishing.");
//         }

//         case 96.. 101: //pancingan kecebur
//         {
//             Inventory_Remove(playerid, "Pancingan");
//             SendClientMessage(playerid, -1, "When you cast your bait, your Pancingan will also be thrown into the water.");
//         }
//     }
//     return 1;
// }

// YCMD:fishes(playerid, params[], help)
// {
//     new count, string[144], Float:totallbs;

//     SendClientMessage(playerid, X11_YELLOW, "Here is a list of fish you have caught:");
//     for(new x; x < 5; x++)
//     {
//         if(PlayerFishes[playerid][x][Weight] != 0)
//         {
//             count++;
//             format(string, sizeof(string), "Fish %d: "WHITE"%doz (%.1flbs) - %s", count, PlayerFishes[playerid][x][Weight], (PlayerFishes[playerid][x][Weight]*0.0625),  GetFishTypeName(PlayerFishes[playerid][x][Type]));
//             SendClientMessage(playerid, X11_AQUAMARINE, string);

//             totallbs += (PlayerFishes[playerid][x][Weight]*0.0625);
//         }
//     }

//     if(count < 1)
//     {
//         SendClientMessage(playerid, X11_AQUAMARINE, "> You don't have any fishes!");
//     }
//     else
//     {
//         SendClientMessageEx(playerid, X11_YELLOW, "Total weight: "ORANGE"%.1flbs", totallbs);
//     }
//     return 1;
// }

// YCMD:sellallfish(playerid, params[], help)
// {
//     if(AccountData[playerid][pFishingDelay] != 0) return SEM(playerid, "You've to waiting for %d minutes as your fishing delay!", AccountData[playerid][pFishingDelay]/60);

//     if(!IsPlayerInRangeOfPoint(playerid, 1.0, -2057.6643,-2464.8784,31.1797)) return SEM(playerid, "You are not at Fish Factory!");

//     new count, Float:pricing[4], Float:totallbs;
//     for(new x; x < 5; x++)
//     {
//         if(PlayerFishes[playerid][x][Weight] != 0)
//         {
//             if(PlayerFishes[playerid][x][Type] == AREA_TYPE_OCEAN)
//             {
//                 pricing[0] += GM[g_OceanFishPrice] * (PlayerFishes[playerid][x][Weight]*0.0625);
//             }

//             if(PlayerFishes[playerid][x][Type] == AREA_TYPE_LAKE)
//             {
//                 pricing[1] += GM[g_LakeFishPrice] * (PlayerFishes[playerid][x][Weight]*0.0625);
//             }

//             if(PlayerFishes[playerid][x][Type] == AREA_TYPE_RIVER)
//             {
//                 pricing[2] += GM[g_RiverFishPrice] * (PlayerFishes[playerid][x][Weight]*0.0625);
//             }
//             totallbs += (PlayerFishes[playerid][x][Weight]*0.0625);
//             count++;
//         }
//     }

//     if(count == 0) return SEM(playerid, "You don't have any fish to be sold!");
//     pricing[3] = pricing[0] + pricing[1] + pricing[2];

//     AccountData[playerid][pFishingDelay] = count * 180;

//     AssignPlayerSkill(playerid, 1, floatround(totallbs, floatround_floor));
    
//     GivePlayerMoneyEx(playerid, floatround(pricing[3]));
//     SendClientMessageEx(playerid, X11_LIGHTBLUE, "INFO "WHITE"You successfully sold all the fish for "GREEN"$%s", FormatMoney(floatround(pricing[3])));
//     ShowItemBox(playerid, "Cash", sprintf("Received $%sx",FormatMoney(floatround(pricing[3]))), 1212, 4);

//     for(new x; x < 5; x++)
//     {
//         PlayerFishes[playerid][x][Weight] = 0;
//         PlayerFishes[playerid][x][Type] = -1;
//     }

//     new sqlstring[168];
//     mysql_format(g_SQL, sqlstring, sizeof(sqlstring), "DELETE FROM `player_fishes` WHERE `Owner` = %d", AccountData[playerid][pID]);
//     mysql_pquery(g_SQL, sqlstring);
//     return 1;
// }