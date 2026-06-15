#include <YSI_Coding\y_hooks>

#define MAX_BIZ 100
#define BIZ_SIGN_MODEL 19972
#define BIZ_SIGN_TEXT_MODEL 2662
#define BIZ_SIGN_TEXT_OFFSET_X (-0.007080)
#define BIZ_SIGN_TEXT_OFFSET_Y (-0.046753)
#define BIZ_SIGN_TEXT_OFFSET_Z (2.590001)
#define BIZ_SIGN_STREAM_DISTANCE (300.00)
#define BIZ_SIGN_DRAW_DISTANCE (300.00)
#define BIZ_DOLLAR_PICKUP_MODEL 1274
#define BIZ_INFO_OFFSET_DISTANCE (1.0)
#define MAX_BIZ_EMPLOYEES 4
#define MAX_BIZ_BID_LEADERBOARD 10
#define BIZ_POINT_NONE 0
#define BIZ_POINT_CASH_SALE 1
#define BIZ_POINT_AUCTION 2
#define BIZ_AUCTION_NONE 0
#define BIZ_AUCTION_SCHEDULED 1
#define BIZ_AUCTION_RUNNING 2
#define BIZ_AUCTION_ENDED 3
#define BIZ_AUCTION_ENDED_DURATION 86400
#define BIZ_MENU_RADIUS (15.0)
#define BIZ_AUCTION_KEY_RADIUS (10.0)
#define BIZ_AUCTION_CMD_RADIUS (30.0)
#define BIZ_POINT_DRAW_DISTANCE (5.0)
#define BIZ_POINT_STREAM_DISTANCE (15.0)
#define BIZ_AUCTION_ANTI_SNIPE_SECONDS 86400
#define BIZ_AUCTION_MIN_INCREMENT 100

enum e_bizdetails
{
    bizName[64],
    bizOwnerID,
    bizOwnerName[MAX_PLAYER_NAME + 1],
    bizMoney,
    bizType,
    bizPrice,
    bool:bizBid,
    bizAuctionID,
    bizOpenBid,
    bizAuctionStart,
    bizAuctionEnd,
    bizAuctionStartedByID,
    bizAuctionStartedBy[MAX_PLAYER_NAME + 1],
    bizProdStock[11],
    bizProdPrice[11],
    Float:bizSignPos[6],
    bizSignVw,
    bizSignInt,

    //not saved
    STREAMER_TAG_OBJECT:bizSign,
    STREAMER_TAG_OBJECT:bizSignText,
    STREAMER_TAG_PICKUP:bizInfoPickup,
    STREAMER_TAG_3D_TEXT_LABEL:bizInfoLabel
};
new BizData[MAX_BIZ][e_bizdetails],
    Iterator:Bizes<MAX_BIZ>;
new EditingBizID[MAX_PLAYERS] = {-1, ...};
new PlayerShopBizID[MAX_PLAYERS] = {-1, ...};
new PlayerBidBizID[MAX_PLAYERS] = {-1, ...};
new PlayerEditBidBizID[MAX_PLAYERS] = {-1, ...};
new PlayerEditBidDateMode[MAX_PLAYERS];
new PlayerBidListID[MAX_PLAYERS][MAX_BIZ_BID_LEADERBOARD];
new PlayerBidListRank[MAX_PLAYERS][MAX_BIZ_BID_LEADERBOARD];
new bool:PlayerInBizAuctionOOC[MAX_PLAYERS];
new BizAuctionLastStatus[MAX_BIZ];
new bool:BizAuctionFinalizing[MAX_BIZ];
new BizInfoPointMode[MAX_BIZ];
new BizEmployeeID[MAX_BIZ][MAX_BIZ_EMPLOYEES],
    BizEmployeeName[MAX_BIZ][MAX_BIZ_EMPLOYEES][MAX_PLAYER_NAME + 1],
    BizHighestBid[MAX_BIZ],
    BizHighestBidder[MAX_BIZ][MAX_PLAYER_NAME + 1];

ReturnBizTypeName(bizid)
{
    new typename[24];

    if(bizid != -1)
    {
        switch(BizData[bizid][bizType])
        {
            case 1:
            {
                strcopy(typename, "Minimarket");
            }
            case 2:
            {
                strcopy(typename, "Clothes");
            }
            case 3:
            {
                strcopy(typename, "Electronic");
            }
            case 4:
            {
                strcopy(typename, "Ammunation");
            }
            default:
            {
                strcopy(typename, "Unknown");
            }
        }
    }
    return typename;
}

Biz_GetTotalStock(bizid)
{
    new total;
    for(new i; i < 11; i++)
    {
        total += BizData[bizid][bizProdStock][i];
    }
    return total;
}

Biz_GetEmployeeCount(bizid)
{
    new total;
    for(new i; i < MAX_BIZ_EMPLOYEES; i++)
    {
        if(BizEmployeeID[bizid][i] > 0)
        {
            total++;
        }
    }
    return total;
}

Biz_GetFreeEmployeeSlot(bizid)
{
    for(new i; i < MAX_BIZ_EMPLOYEES; i++)
    {
        if(BizEmployeeID[bizid][i] == 0)
        {
            return i;
        }
    }
    return -1;
}

Biz_GetEmployeeSlotByPlayerID(bizid, playerDBID)
{
    for(new i; i < MAX_BIZ_EMPLOYEES; i++)
    {
        if(BizEmployeeID[bizid][i] == playerDBID)
        {
            return i;
        }
    }
    return -1;
}

Biz_IsEmployee(bizid, playerid)
{
    if(!IsPlayerConnected(playerid)) return 0;
    return Biz_GetEmployeeSlotByPlayerID(bizid, AccountData[playerid][pID]) != -1;
}

Biz_ClearEmployees(bizid)
{
    for(new i; i < MAX_BIZ_EMPLOYEES; i++)
    {
        BizEmployeeID[bizid][i] = 0;
        BizEmployeeName[bizid][i][0] = EOS;
    }
    return 1;
}

Biz_ClearAuction(bizid, bool:closeBids = true)
{
    new auctionID = BizData[bizid][bizAuctionID];
    BizData[bizid][bizBid] = false;
    BizData[bizid][bizAuctionID] = 0;
    BizData[bizid][bizOpenBid] = 0;
    BizData[bizid][bizAuctionStart] = 0;
    BizData[bizid][bizAuctionEnd] = 0;
    BizData[bizid][bizAuctionStartedByID] = 0;
    BizData[bizid][bizAuctionStartedBy][0] = EOS;
    BizHighestBid[bizid] = 0;
    BizHighestBidder[bizid][0] = EOS;

    if(closeBids)
    {
        if(auctionID > 0)
        {
            mysql_pquery(g_SQL, sprintf("UPDATE `business_auctions` SET `status`='No Bid', `updated_at`=NOW() WHERE `id`=%d", auctionID));
        }
        mysql_pquery(g_SQL, sprintf("UPDATE `biz_bids` SET `Status`=0 WHERE `BizID`=%d AND `AuctionID`=%d", bizid, auctionID));
    }
    BizAuctionFinalizing[bizid] = false;
    return 1;
}

Biz_FormatEmployeeList(bizid, output[], size)
{
    output[0] = EOS;
    for(new i; i < MAX_BIZ_EMPLOYEES; i++)
    {
        format(output, size, "%s%d. %s\n", output, i + 1, BizEmployeeID[bizid][i] > 0 ? (BizEmployeeName[bizid][i]) : ("-"));
    }
    return 1;
}

Biz_GetInfoPosition(bizid, &Float:x, &Float:y, &Float:z, &Float:a)
{
    a = BizData[bizid][bizSignPos][5];
    x = BizData[bizid][bizSignPos][0] - (BIZ_INFO_OFFSET_DISTANCE * floatsin(-a, degrees));
    y = BizData[bizid][bizSignPos][1] - (BIZ_INFO_OFFSET_DISTANCE * floatcos(-a, degrees));
    z = BizData[bizid][bizSignPos][2] + 1.5;
    return 1;
}

Biz_IsCashSale(bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return 0;
    if(!isnull(BizData[bizid][bizOwnerName])) return 0;
    if(BizData[bizid][bizBid]) return 0;
    if(BizData[bizid][bizPrice] < 1) return 0;
    return 1;
}

Biz_GetInfoPointMode(bizid)
{
    if(Biz_IsAuctionRunning(bizid)) return BIZ_POINT_AUCTION;
    if(Biz_IsCashSale(bizid)) return BIZ_POINT_CASH_SALE;
    return BIZ_POINT_NONE;
}

Biz_GetAuctionStatus(bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return BIZ_AUCTION_NONE;
    if(!BizData[bizid][bizBid]) return BIZ_AUCTION_NONE;
    if(!isnull(BizData[bizid][bizOwnerName])) return BIZ_AUCTION_NONE;
    if(BizData[bizid][bizOpenBid] < 1) return BIZ_AUCTION_NONE;
    if(BizData[bizid][bizAuctionStart] < 1 || BizData[bizid][bizAuctionEnd] < 1) return BIZ_AUCTION_NONE;

    new now = gettime();
    if(now < BizData[bizid][bizAuctionStart]) return BIZ_AUCTION_SCHEDULED;
    if(now >= BizData[bizid][bizAuctionEnd])
    {
        if(now < Biz_GetAuctionManageTime(bizid)) return BIZ_AUCTION_ENDED;
        return BIZ_AUCTION_NONE;
    }
    return BIZ_AUCTION_RUNNING;
}

Biz_IsAuctionRunning(bizid)
{
    return Biz_GetAuctionStatus(bizid) == BIZ_AUCTION_RUNNING;
}

Biz_GetAuctionManageTime(bizid)
{
    if(!Iter_Contains(Bizes, bizid) || BizData[bizid][bizAuctionEnd] < 1) return 0;
    return BizData[bizid][bizAuctionEnd] + BIZ_AUCTION_ENDED_DURATION;
}

Biz_IsAuctionEndedWindowExpired(bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return 0;
    if(!BizData[bizid][bizBid]) return 0;
    if(!isnull(BizData[bizid][bizOwnerName])) return 0;
    if(BizData[bizid][bizAuctionEnd] < 1) return 0;
    return gettime() >= Biz_GetAuctionManageTime(bizid);
}

Biz_GetAuctionStatusName(status)
{
    new name[20];
    switch(status)
    {
        case BIZ_AUCTION_SCHEDULED: strcopy(name, "Scheduled");
        case BIZ_AUCTION_RUNNING: strcopy(name, "Running");
        case BIZ_AUCTION_ENDED: strcopy(name, "Ended");
        default: strcopy(name, "No Bid");
    }
    return name;
}

Biz_FormatAuctionDate(timestamp, output[], size)
{
    if(timestamp < 1)
    {
        format(output, size, "Belum diatur");
        return 1;
    }

    new year, month, day, hour, minute, second;
    TimestampToDate(timestamp, year, month, day, hour, minute, second, 7);
    format(output, size, "%02d/%02d/%04d", day, month, year);
    return 1;
}

Biz_FormatAuctionDateTime(timestamp, output[], size)
{
    if(timestamp < 1)
    {
        format(output, size, "Belum diatur");
        return 1;
    }

    new year, month, day, hour, minute, second;
    TimestampToDate(timestamp, year, month, day, hour, minute, second, 7);
    format(output, size, "%02d/%02d/%04d %02d:%02d:%02d", day, month, year, hour, minute, second);
    return 1;
}

Biz_FormatAuctionEndsIn(bizid, output[], size)
{
    if(!Iter_Contains(Bizes, bizid) || BizData[bizid][bizAuctionEnd] < 1)
    {
        format(output, size, "TBA");
        return 1;
    }

    new remaining = BizData[bizid][bizAuctionEnd] - gettime();
    if(remaining <= 0)
    {
        format(output, size, "Ended");
    }
    else if(remaining > BIZ_AUCTION_ANTI_SNIPE_SECONDS)
    {
        Biz_FormatAuctionDate(BizData[bizid][bizAuctionEnd], output, size);
    }
    else
    {
        format(output, size, "%02d:%02d:%02d", remaining / 3600, (remaining % 3600) / 60, remaining % 60);
    }
    return 1;
}

Biz_GetLocalDayStart(dayOffset)
{
    new now = gettime(), year, month, day, hour, minute, second;
    TimestampToDate(now, year, month, day, hour, minute, second, 7);
    return now - (hour * 3600) - (minute * 60) - second + (dayOffset * 86400);
}

Biz_GetLocalDayEnd(dayOffset)
{
    return Biz_GetLocalDayStart(dayOffset) + 86399;
}

Biz_GetBusinessTitle(bizid, output[], size)
{
    if(!strcmp(BizData[bizid][bizName], "-", true) || isnull(BizData[bizid][bizName]))
    {
        format(output, size, "%s", ReturnBizTypeName(bizid));
    }
    else
    {
        format(output, size, "%s", BizData[bizid][bizName]);
    }
    return 1;
}

Biz_GetAuctionTitle(bizid, output[], size)
{
    new title[64];
    Biz_GetBusinessTitle(bizid, title, sizeof(title));
    format(output, size, "%s in %s", title, GetLocation(BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2]));
    return 1;
}

Biz_GetCurrentHighestBid(bizid)
{
    return BizHighestBid[bizid] > 0 ? (BizHighestBid[bizid]) : (BizData[bizid][bizOpenBid]);
}

Biz_GetHighestBidderName(bizid, output[], size)
{
    if(BizHighestBid[bizid] > 0)
    {
        format(output, size, "%s", BizHighestBidder[bizid]);
    }
    else
    {
        format(output, size, "Government");
    }
    return 1;
}

Biz_GetMinimumNextBid(bizid)
{
    return Biz_GetCurrentHighestBid(bizid) + BIZ_AUCTION_MIN_INCREMENT;
}

Biz_GetAuctionNearest(playerid, Float:radius)
{
    new Float:x, Float:y, Float:z, Float:a;
    foreach(new i : Bizes)
    {
        if(!Biz_IsAuctionRunning(i)) continue;

        Biz_GetInfoPosition(i, x, y, z, a);
        if(IsPlayerInRangeOfPoint(playerid, radius, x, y, z))
        {
            if(GetPlayerInterior(playerid) == BizData[i][bizSignInt] && GetPlayerVirtualWorld(playerid) == BizData[i][bizSignVw])
            {
                return i;
            }
        }
    }
    return -1;
}

Biz_GetSignTextPosition(Float:signX, Float:signY, Float:signZ, Float:signRZ, &Float:textX, &Float:textY, &Float:textZ)
{
    textX = signX + (BIZ_SIGN_TEXT_OFFSET_X * floatcos(-signRZ, degrees)) - (BIZ_SIGN_TEXT_OFFSET_Y * floatsin(-signRZ, degrees));
    textY = signY + (BIZ_SIGN_TEXT_OFFSET_X * floatsin(-signRZ, degrees)) + (BIZ_SIGN_TEXT_OFFSET_Y * floatcos(-signRZ, degrees));
    textZ = signZ + BIZ_SIGN_TEXT_OFFSET_Z;
    return 1;
}

Biz_SetSignTextTransform(bizid, Float:signX, Float:signY, Float:signZ, Float:signRX, Float:signRY, Float:signRZ)
{
    if(IsValidDynamicObject(BizData[bizid][bizSignText]))
    {
        new Float:textX, Float:textY, Float:textZ;
        Biz_GetSignTextPosition(signX, signY, signZ, signRZ, textX, textY, textZ);
        SetDynamicObjectPos(BizData[bizid][bizSignText], textX, textY, textZ);
        SetDynamicObjectRot(BizData[bizid][bizSignText], signRX, signRY, signRZ);
    }
    return 1;
}

Biz_UpdateSignText(bizid)
{
    if(!IsValidDynamicObject(BizData[bizid][bizSignText])) return 0;

    new text[256], fontSize = 35;
    if(!isnull(BizData[bizid][bizOwnerName]))
    {
        format(text, sizeof(text), "{00FFFF}[id:%d]\n%s\n{FFFFFF}Owner: {FFFF00}%s", bizid, BizData[bizid][bizName], BizData[bizid][bizOwnerName]);
    }
    else if(BizData[bizid][bizBid])
    {
        new title[96], startsDate[16], countdown[16], bidder[MAX_PLAYER_NAME + 1], offer = BizData[bizid][bizOpenBid];
        Biz_GetAuctionTitle(bizid, title, sizeof(title));

        switch(Biz_GetAuctionStatus(bizid))
        {
            case BIZ_AUCTION_SCHEDULED:
            {
                new startedBy[MAX_PLAYER_NAME + 1];
                Biz_FormatAuctionDate(BizData[bizid][bizAuctionStart], startsDate, sizeof(startsDate));
                if(isnull(BizData[bizid][bizAuctionStartedBy]))
                {
                    strcopy(startedBy, "-");
                }
                else
                {
                    strcopy(startedBy, BizData[bizid][bizAuctionStartedBy]);
                }
                format(text, sizeof(text), "{00FFFF}%s\n{FFFFFF}Started by: {FF0000}%s\n{FFFFFF}Starts In: {FFFF00}%s",
                    title,
                    startedBy,
                    startsDate);
            }
            case BIZ_AUCTION_RUNNING:
            {
                Biz_GetHighestBidderName(bizid, bidder, sizeof(bidder));
                offer = Biz_GetCurrentHighestBid(bizid);
                Biz_FormatAuctionEndsIn(bizid, countdown, sizeof(countdown));
                format(text, sizeof(text), "{00FFFF}%s\n{FFFFFF}Highest Bidder: {00FF00}%s\n{FFFFFF}Offer: {FFFF00}%d Gold\n{FFFFFF}Ends in: {FF0000}%s",
                    title,
                    bidder,
                    offer,
                    countdown);
            }
            case BIZ_AUCTION_ENDED:
            {
                Biz_GetHighestBidderName(bizid, bidder, sizeof(bidder));
                format(text, sizeof(text), "{00FFFF}%s\n{FF0000}Auction Ended\n{FFFFFF}Winner: {00FF00}%s\n{FFFFFF}Final Bid: {FFFF00}%d Gold",
                    title,
                    bidder,
                    Biz_GetCurrentHighestBid(bizid));
            }
            default:
            {
                format(text, sizeof(text), "{00FFFF}[id:%d]\n{FF0000}For Sale!\n{FFFFFF}Type: {00FF00}%s\n{FFFFFF}Price: {00FF00}$%s", bizid, ReturnBizTypeName(bizid), FormatMoney(BizData[bizid][bizPrice]));
                fontSize = 35;
            }
        }
        fontSize = 30;
    }
    else
    {
        new title[96];
        Biz_GetAuctionTitle(bizid, title, sizeof(title));
        format(text, sizeof(text), "{FF0000}For Sale!\n{00FFFF}%s\n{FFFFFF}Price: {00FF00}$%s", title, FormatMoney(BizData[bizid][bizPrice]));
    }
    SetDynamicObjectMaterialText(BizData[bizid][bizSignText], 0, text, 130, "Arial", fontSize, 1, 0xFFFFFFFF, 0x00000000, 1);
    return 1;
}

Biz_ApplySignMaterials(bizid)
{
    if(IsValidDynamicObject(BizData[bizid][bizSign]))
    {
        SetDynamicObjectMaterial(BizData[bizid][bizSign], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
        SetDynamicObjectMaterial(BizData[bizid][bizSign], 1, 10765, "airportgnd_sfse", "white", 0x00000000);
        SetDynamicObjectMaterial(BizData[bizid][bizSign], 2, 10765, "airportgnd_sfse", "black64", 0x00000000);
    }

    if(IsValidDynamicObject(BizData[bizid][bizSignText]))
    {
        SetDynamicObjectMaterial(BizData[bizid][bizSignText], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
        Biz_UpdateSignText(bizid);
    }
    return 1;
}

Biz_SyncSignObjects(bizid)
{
    if(IsValidDynamicObject(BizData[bizid][bizSign]))
    {
        SetDynamicObjectPos(BizData[bizid][bizSign], BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2]);
        SetDynamicObjectRot(BizData[bizid][bizSign], BizData[bizid][bizSignPos][3], BizData[bizid][bizSignPos][4], BizData[bizid][bizSignPos][5]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, BizData[bizid][bizSign], E_STREAMER_WORLD_ID, BizData[bizid][bizSignVw]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, BizData[bizid][bizSign], E_STREAMER_INTERIOR_ID, BizData[bizid][bizSignInt]);
    }

    Biz_SetSignTextTransform(bizid, BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2], BizData[bizid][bizSignPos][3], BizData[bizid][bizSignPos][4], BizData[bizid][bizSignPos][5]);
    if(IsValidDynamicObject(BizData[bizid][bizSignText]))
    {
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, BizData[bizid][bizSignText], E_STREAMER_WORLD_ID, BizData[bizid][bizSignVw]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, BizData[bizid][bizSignText], E_STREAMER_INTERIOR_ID, BizData[bizid][bizSignInt]);
    }
    Biz_UpdateSignText(bizid);
    return 1;
}

Biz_SyncInfoPoint(bizid)
{
    new Float:x, Float:y, Float:z, Float:a, pointMode = Biz_GetInfoPointMode(bizid);
    Biz_GetInfoPosition(bizid, x, y, z, a);

    if(pointMode == BIZ_POINT_NONE)
    {
        if(DestroyDynamicPickup(BizData[bizid][bizInfoPickup]))
            BizData[bizid][bizInfoPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(BizData[bizid][bizInfoLabel]))
            BizData[bizid][bizInfoLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        BizInfoPointMode[bizid] = BIZ_POINT_NONE;
        return 1;
    }

    if(BizInfoPointMode[bizid] != pointMode)
    {
        if(DestroyDynamicPickup(BizData[bizid][bizInfoPickup]))
            BizData[bizid][bizInfoPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(BizData[bizid][bizInfoLabel]))
            BizData[bizid][bizInfoLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    new label[144];
    if(pointMode == BIZ_POINT_AUCTION)
    {
        format(label, sizeof(label), "{00FFFF}[id:%d]\n{FFFFFF}[Y] untuk mengakses bid auction", bizid);
    }
    else
    {
        format(label, sizeof(label), "{00FFFF}[id:%d]\n{FFFFFF}Gunakan '{FFFF00}/buybiz{FFFFFF}' untuk membeli property ini", bizid);
    }

    if(!IsValidDynamicPickup(BizData[bizid][bizInfoPickup]))
    {
        BizData[bizid][bizInfoPickup] = CreateDynamicPickup(BIZ_DOLLAR_PICKUP_MODEL, 23, x, y, z, BizData[bizid][bizSignVw], BizData[bizid][bizSignInt], -1, BIZ_POINT_STREAM_DISTANCE, -1, 0);
    }

    if(!IsValidDynamic3DTextLabel(BizData[bizid][bizInfoLabel]))
    {
        BizData[bizid][bizInfoLabel] = CreateDynamic3DTextLabel(label, 0x00FFFFA6, x, y, z + 0.55, BIZ_POINT_DRAW_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, BizData[bizid][bizSignVw], BizData[bizid][bizSignInt], -1, BIZ_POINT_STREAM_DISTANCE, -1, 0);
    }
    else
    {
        UpdateDynamic3DTextLabelText(BizData[bizid][bizInfoLabel], 0x00FFFFA6, label);
    }

    if(IsValidDynamicPickup(BizData[bizid][bizInfoPickup]))
    {
        Streamer_SetItemPos(STREAMER_TYPE_PICKUP, BizData[bizid][bizInfoPickup], x, y, z);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, BizData[bizid][bizInfoPickup], E_STREAMER_WORLD_ID, BizData[bizid][bizSignVw]);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, BizData[bizid][bizInfoPickup], E_STREAMER_INTERIOR_ID, BizData[bizid][bizSignInt]);
        Streamer_SetFloatData(STREAMER_TYPE_PICKUP, BizData[bizid][bizInfoPickup], E_STREAMER_STREAM_DISTANCE, BIZ_POINT_STREAM_DISTANCE);
    }

    if(IsValidDynamic3DTextLabel(BizData[bizid][bizInfoLabel]))
    {
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizInfoLabel], x, y, z + 0.55);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizInfoLabel], E_STREAMER_WORLD_ID, BizData[bizid][bizSignVw]);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizInfoLabel], E_STREAMER_INTERIOR_ID, BizData[bizid][bizSignInt]);
        Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizInfoLabel], E_STREAMER_DRAW_DISTANCE, BIZ_POINT_DRAW_DISTANCE);
        Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizInfoLabel], E_STREAMER_STREAM_DISTANCE, BIZ_POINT_STREAM_DISTANCE);
    }
    BizInfoPointMode[bizid] = pointMode;
    return 1;
}

Biz_BeingEdited(bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return 0;
    foreach(new i : Player) if(EditingBizID[i] == bizid) return 1;
    return 0;
}

Biz_ShowProductMenu(playerid, bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    if(BizData[bizid][bizType] == 1)
    {
        new haji[555];
        format(haji, sizeof(haji), "Nama\tHarga\n\
        Udud (12 batang)\t$%s\n\
        "GRAY"Pancingan\t"GRAY"$%s\n\
        Baseball Bat\t$%s\n\
        "GRAY"Knife\t"GRAY"$%s\n\
        Golf Stick\t$%s\n\
        "GRAY"Pool Cue\t"GRAY"$%s\n\
        Hunting Rifle\t$%s\n\
        "GRAY"Hunting Ammo (24x)\t"GRAY"$%s\n\
        Obeng\t$%s\n\
        "GRAY"Hoe\t"GRAY"$%s",
        FormatMoney(BizData[bizid][bizProdPrice][0]),
        FormatMoney(BizData[bizid][bizProdPrice][1]),
        FormatMoney(BizData[bizid][bizProdPrice][2]),
        FormatMoney(BizData[bizid][bizProdPrice][3]),
        FormatMoney(BizData[bizid][bizProdPrice][4]),
        FormatMoney(BizData[bizid][bizProdPrice][5]),
        FormatMoney(BizData[bizid][bizProdPrice][6]),
        FormatMoney(BizData[bizid][bizProdPrice][7]),
        FormatMoney(BizData[bizid][bizProdPrice][8]),
        FormatMoney(BizData[bizid][bizProdPrice][9]));
        Dialog_Show(playerid, "BizBuyProduct", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Shop Menu", haji, "Buy", "Batal");
    }
    else if(BizData[bizid][bizType] == 3)
    {
        new haji[555];
        format(haji, sizeof(haji), "Nama\tHarga\n\
        Arivhone (Smartphone)\t$%s\n\
        "GRAY"Radio\t"GRAY"$%s\n\
        Earphone\t$%s\n\
        "GRAY"Boombox\t"GRAY"$%s\n\
        Spraycan\t"GRAY"$%s",
        FormatMoney(BizData[bizid][bizProdPrice][0]),
        FormatMoney(BizData[bizid][bizProdPrice][1]),
        FormatMoney(BizData[bizid][bizProdPrice][2]),
        FormatMoney(BizData[bizid][bizProdPrice][3]),
        FormatMoney(BizData[bizid][bizProdPrice][4]));
        Dialog_Show(playerid, "BizBuyProduct", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Shop Menu", haji, "Buy", "Batal");
    }
    return 1;
}

Biz_Save(bizid)
{
    static dddstr[3600];
    mysql_format(g_SQL, dddstr, sizeof(dddstr), "UPDATE `biz` SET `Name`='%e', `OwnerID`=%d, `OwnerName`='%e', `Money`=%d, `Type`=%d, `Price`=%d, `IsBid`=%d, `AuctionID`=%d, `OpenBid`=%d, `AuctionStart`=%d, `AuctionEnd`=%d, `AuctionStartedByID`=%d, `AuctionStartedBy`='%e', \
    `ProdStock0`=%d, `ProdStock1`=%d, `ProdStock2`=%d, `ProdStock3`=%d, `ProdStock4`=%d, `ProdStock5`=%d, `ProdStock6`=%d, `ProdStock7`=%d, `ProdStock8`=%d, `ProdStock9`=%d, `ProdStock10`=%d, \
    `ProdPrice0`=%d, `ProdPrice1`=%d, `ProdPrice2`=%d, `ProdPrice3`=%d, `ProdPrice4`=%d, `ProdPrice5`=%d, `ProdPrice6`=%d, `ProdPrice7`=%d, `ProdPrice8`=%d, `ProdPrice9`=%d, `ProdPrice10`=%d, \
    `SignX`='%f', `SignY`='%f', `SignZ`='%f', `SignRX`='%f', `SignRY`='%f', `SignRZ`='%f', `SignVw`=%d, `SignInt`=%d, \
    `EmployeeID0`=%d, `EmployeeName0`='%e', `EmployeeID1`=%d, `EmployeeName1`='%e', `EmployeeID2`=%d, `EmployeeName2`='%e', `EmployeeID3`=%d, `EmployeeName3`='%e' WHERE `ID`=%d",
    BizData[bizid][bizName], 
    BizData[bizid][bizOwnerID], 
    BizData[bizid][bizOwnerName], 
    BizData[bizid][bizMoney], 
    BizData[bizid][bizType],
    BizData[bizid][bizPrice],
    BizData[bizid][bizBid] ? 1 : 0,
    BizData[bizid][bizAuctionID],
    BizData[bizid][bizOpenBid],
    BizData[bizid][bizAuctionStart],
    BizData[bizid][bizAuctionEnd],
    BizData[bizid][bizAuctionStartedByID],
    BizData[bizid][bizAuctionStartedBy],
    BizData[bizid][bizProdStock][0],
    BizData[bizid][bizProdStock][1],
    BizData[bizid][bizProdStock][2],
    BizData[bizid][bizProdStock][3],
    BizData[bizid][bizProdStock][4],
    BizData[bizid][bizProdStock][5],
    BizData[bizid][bizProdStock][6],
    BizData[bizid][bizProdStock][7],
    BizData[bizid][bizProdStock][8],
    BizData[bizid][bizProdStock][9],
    BizData[bizid][bizProdStock][10],
    BizData[bizid][bizProdPrice][0],
    BizData[bizid][bizProdPrice][1],
    BizData[bizid][bizProdPrice][2],
    BizData[bizid][bizProdPrice][3],
    BizData[bizid][bizProdPrice][4],
    BizData[bizid][bizProdPrice][5],
    BizData[bizid][bizProdPrice][6],
    BizData[bizid][bizProdPrice][7],
    BizData[bizid][bizProdPrice][8],
    BizData[bizid][bizProdPrice][9],
    BizData[bizid][bizProdPrice][10],
    BizData[bizid][bizSignPos][0],
    BizData[bizid][bizSignPos][1],
    BizData[bizid][bizSignPos][2],
    BizData[bizid][bizSignPos][3],
    BizData[bizid][bizSignPos][4],
    BizData[bizid][bizSignPos][5],
    BizData[bizid][bizSignVw],
    BizData[bizid][bizSignInt],
    BizEmployeeID[bizid][0],
    BizEmployeeName[bizid][0],
    BizEmployeeID[bizid][1],
    BizEmployeeName[bizid][1],
    BizEmployeeID[bizid][2],
    BizEmployeeName[bizid][2],
    BizEmployeeID[bizid][3],
    BizEmployeeName[bizid][3],
    bizid);
    mysql_pquery(g_SQL, dddstr);
    return 1;
}

Biz_Refresh(bizid)
{
    if(bizid != -1)
    {
        Biz_SyncSignObjects(bizid);
        Biz_SyncInfoPoint(bizid);
        BizAuctionLastStatus[bizid] = Biz_GetAuctionStatus(bizid);
    }
    return 1;
}

Biz_Rebuild(bizid)
{
    if(bizid != -1)
    {
        if(DestroyDynamicObject(BizData[bizid][bizSign]))
            BizData[bizid][bizSign] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(DestroyDynamicObject(BizData[bizid][bizSignText]))
            BizData[bizid][bizSignText] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(DestroyDynamicPickup(BizData[bizid][bizInfoPickup]))
            BizData[bizid][bizInfoPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(BizData[bizid][bizInfoLabel]))
            BizData[bizid][bizInfoLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        new Float:textX, Float:textY, Float:textZ;
        Biz_GetSignTextPosition(BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2], BizData[bizid][bizSignPos][5], textX, textY, textZ);
        BizData[bizid][bizSign] = CreateDynamicObject(BIZ_SIGN_MODEL, BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2], BizData[bizid][bizSignPos][3], BizData[bizid][bizSignPos][4], BizData[bizid][bizSignPos][5], BizData[bizid][bizSignVw], BizData[bizid][bizSignInt], -1, BIZ_SIGN_STREAM_DISTANCE, BIZ_SIGN_DRAW_DISTANCE);
        BizData[bizid][bizSignText] = CreateDynamicObject(BIZ_SIGN_TEXT_MODEL, textX, textY, textZ, BizData[bizid][bizSignPos][3], BizData[bizid][bizSignPos][4], BizData[bizid][bizSignPos][5], BizData[bizid][bizSignVw], BizData[bizid][bizSignInt], -1, BIZ_SIGN_STREAM_DISTANCE, BIZ_SIGN_DRAW_DISTANCE);

        Biz_ApplySignMaterials(bizid);
        Biz_SyncInfoPoint(bizid);
        BizAuctionLastStatus[bizid] = Biz_GetAuctionStatus(bizid);
    }
    return 1;
}

Player_BizCount(playerid)
{
    new counting;
    foreach(new bizid : Bizes)
    {
        if(BizData[bizid][bizOwnerID] == AccountData[playerid][pID])
        {
            counting++;
        }
    }
    return counting;
}

Biz_Nearest(playerid)
{
    foreach(new i : Bizes) if (IsPlayerInRangeOfPoint(playerid, 3.0, BizData[i][bizSignPos][0], BizData[i][bizSignPos][1], BizData[i][bizSignPos][2]))
	{
		if (GetPlayerInterior(playerid) == BizData[i][bizSignInt] && GetPlayerVirtualWorld(playerid) == BizData[i][bizSignVw])
			return i;
	}
	return -1;
}

Biz_GetNearestSign(playerid, Float:radius)
{
    new nearest = -1, Float:nearestDistance = radius + 1.0, Float:distance;
    foreach(new i : Bizes)
    {
        if(GetPlayerInterior(playerid) != BizData[i][bizSignInt]) continue;
        if(GetPlayerVirtualWorld(playerid) != BizData[i][bizSignVw]) continue;

        distance = GetPlayerDistanceFromPoint(playerid, BizData[i][bizSignPos][0], BizData[i][bizSignPos][1], BizData[i][bizSignPos][2]);
        if(distance <= radius && distance < nearestDistance)
        {
            nearest = i;
            nearestDistance = distance;
        }
    }
    return nearest;
}

Biz_InfoNearest(playerid)
{
    new Float:x, Float:y, Float:z, Float:a;
    foreach(new i : Bizes)
    {
        Biz_GetInfoPosition(i, x, y, z, a);
        if(IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z))
        {
            if(GetPlayerInterior(playerid) == BizData[i][bizSignInt] && GetPlayerVirtualWorld(playerid) == BizData[i][bizSignVw])
            {
                return i;
            }
        }
    }
    return -1;
}

Biz_GetOnlineByCharID(characterID)
{
    if(characterID < 1) return INVALID_PLAYER_ID;
    foreach(new i : Player)
    {
        if(AccountData[i][pID] == characterID)
        {
            return i;
        }
    }
    return INVALID_PLAYER_ID;
}

Biz_SendCashPurchaseInfo(playerid)
{
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Bisnis berhasil dibeli!");
    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: Bisnis berhasil dibeli.");
    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: Gunakan /bizmenu di area bisnis untuk mengelola bisnis ini.");
    return 1;
}

Biz_SendAuctionWinnerInfo(playerid, manageTime)
{
    new manageDate[24];
    Biz_FormatAuctionDateTime(manageTime, manageDate, sizeof(manageDate));

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Menang lelang bisnis!");
    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: Selamat! kamu telah memenangkan lelang bisnis ini.");
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "INFO: Bisnis dapat dikelola mulai %s.", manageDate);
    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: Gunakan /bizmenu di area bisnis setelah waktunya selesai.");
    return 1;
}

Biz_LoadHighestBid(bizid)
{
    new query[256];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `CharacterName`, `BidAmount` FROM `biz_bids` WHERE `BizID`=%d AND `AuctionID`=%d AND `Status`=1 ORDER BY `BidAmount` DESC, `BidTimestamp` ASC LIMIT 1", bizid, BizData[bizid][bizAuctionID]);
    mysql_pquery(g_SQL, query, "OnBizHighestBidLoaded", "i", bizid);
    return 1;
}

Biz_SaveAuctionMain(bizid, highestPlayerid = INVALID_PLAYER_ID)
{
    if(!Iter_Contains(Bizes, bizid) || BizData[bizid][bizAuctionID] < 1) return 0;

    new businessType[24], location[32], statusName[20], highestAccountName[32], highestCharacterName[MAX_PLAYER_NAME + 1];
    new highestAccountID, highestCharacterID, highestBid = Biz_GetCurrentHighestBid(bizid);

    strcopy(businessType, ReturnBizTypeName(bizid));
    strcopy(location, GetLocation(BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2]));
    strcopy(statusName, Biz_GetAuctionStatusName(Biz_GetAuctionStatus(bizid)));

    if(BizHighestBid[bizid] > 0)
    {
        if(IsPlayerConnected(highestPlayerid))
        {
            highestAccountID = PlayerUID[highestPlayerid];
            highestCharacterID = AccountData[highestPlayerid][pID];
            strcopy(highestAccountName, AccountData[highestPlayerid][pUCP]);
            strcopy(highestCharacterName, AccountData[highestPlayerid][pName]);
        }
        else
        {
            strcopy(highestAccountName, "-");
            strcopy(highestCharacterName, BizHighestBidder[bizid]);
        }
    }
    else
    {
        strcopy(highestAccountName, "Government");
        strcopy(highestCharacterName, "Government");
    }

    static query[3000];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `business_auctions` SET `id`=%d, `business_id`=%d, `business_name`='%e', `business_type`='%e', `business_location`='%e', `started_by_admin_id`=%d, `started_by_admin_name`='%e', `starts_in`=%d, `ends_in`=%d, `status`='%e', `open_bid`=%d, `highest_account_id`=%d, `highest_account_name`='%e', `highest_character_id`=%d, `highest_character_name`='%e', `highest_bid`=%d, `created_at`=NOW(), `updated_at`=NOW() ON DUPLICATE KEY UPDATE `business_name`=VALUES(`business_name`), `business_type`=VALUES(`business_type`), `business_location`=VALUES(`business_location`), `started_by_admin_id`=VALUES(`started_by_admin_id`), `started_by_admin_name`=VALUES(`started_by_admin_name`), `starts_in`=VALUES(`starts_in`), `ends_in`=VALUES(`ends_in`), `status`=VALUES(`status`), `open_bid`=VALUES(`open_bid`), `highest_account_id`=VALUES(`highest_account_id`), `highest_account_name`=VALUES(`highest_account_name`), `highest_character_id`=VALUES(`highest_character_id`), `highest_character_name`=VALUES(`highest_character_name`), `highest_bid`=VALUES(`highest_bid`), `updated_at`=NOW()",
        BizData[bizid][bizAuctionID],
        bizid,
        BizData[bizid][bizName],
        businessType,
        location,
        BizData[bizid][bizAuctionStartedByID],
        BizData[bizid][bizAuctionStartedBy],
        BizData[bizid][bizAuctionStart],
        BizData[bizid][bizAuctionEnd],
        statusName,
        BizData[bizid][bizOpenBid],
        highestAccountID,
        highestAccountName,
        highestCharacterID,
        highestCharacterName,
        highestBid);
    mysql_pquery(g_SQL, query);
    return 1;
}

Biz_SaveAuctionBidEvent(playerid, bizid, amount)
{
    if(!IsPlayerConnected(playerid) || !Iter_Contains(Bizes, bizid) || BizData[bizid][bizAuctionID] < 1) return 0;

    new businessType[24], location[32], statusName[20], now = gettime();
    strcopy(businessType, ReturnBizTypeName(bizid));
    strcopy(location, GetLocation(BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2]));
    strcopy(statusName, Biz_GetAuctionStatusName(Biz_GetAuctionStatus(bizid)));

    static query[2200];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `business_auction_bids` SET `auction_id`=%d, `business_id`=%d, `business_name`='%e', `business_type`='%e', `business_location`='%e', `auction_status`='%e', `account_id`=%d, `account_name`='%e', `character_id`=%d, `character_name`='%e', `bid_amount`=%d, `highest_bid_after`=%d, `bid_rank`=1, `bid_date`=FROM_UNIXTIME(%d), `bid_timestamp`=%d, `ends_in`=%d, `status`='pending', `discord_notified`=0, `created_at`=NOW()",
        BizData[bizid][bizAuctionID],
        bizid,
        BizData[bizid][bizName],
        businessType,
        location,
        statusName,
        PlayerUID[playerid],
        AccountData[playerid][pUCP],
        AccountData[playerid][pID],
        AccountData[playerid][pName],
        amount,
        Biz_GetCurrentHighestBid(bizid),
        now,
        now,
        BizData[bizid][bizAuctionEnd]);
    mysql_pquery(g_SQL, query);
    return 1;
}

Biz_NotifyAuctionWinner(bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return 0;
    if(BizData[bizid][bizAuctionID] < 1 || BizHighestBid[bizid] < 1) return 0;

    new query[256];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `CharacterID`, `CharacterName` FROM `biz_bids` WHERE `BizID`=%d AND `AuctionID`=%d AND `Status`=1 ORDER BY `BidAmount` DESC, `BidTimestamp` ASC LIMIT 1",
        bizid,
        BizData[bizid][bizAuctionID]);
    mysql_pquery(g_SQL, query, "OnBizAuctionWinnerNotifyLoaded", "i", bizid);
    return 1;
}

Biz_FinalizeAuction(bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return 0;
    if(BizAuctionFinalizing[bizid]) return 0;

    BizAuctionFinalizing[bizid] = true;

    new query[320];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `CharacterID`, `CharacterName`, `BidAmount` FROM `biz_bids` WHERE `BizID`=%d AND `AuctionID`=%d AND `Status`=1 ORDER BY `BidAmount` DESC, `BidTimestamp` ASC LIMIT 1",
        bizid,
        BizData[bizid][bizAuctionID]);
    mysql_pquery(g_SQL, query, "OnBizAuctionFinalizeLoaded", "i", bizid);
    return 1;
}

Biz_ShowBidMain(playerid, bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");
    if(!Biz_IsAuctionRunning(bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada auction bisnis yang sedang berjalan di dekat anda!");

    PlayerBidBizID[playerid] = bizid;
    Dialog_Show(playerid, "BizBidMain", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Bid Auction", "Informasi Bid\nLeaderboard Bid", "Select", "Close");
    return 1;
}

Biz_ShowBidInfo(playerid, bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    new title[96], startsDate[16], endsDisplay[24], highestBidder[MAX_PLAYER_NAME + 1], info[1400];
    new status = Biz_GetAuctionStatus(bizid);
    Biz_GetAuctionTitle(bizid, title, sizeof(title));
    Biz_FormatAuctionDate(BizData[bizid][bizAuctionStart], startsDate, sizeof(startsDate));
    Biz_FormatAuctionEndsIn(bizid, endsDisplay, sizeof(endsDisplay));
    Biz_GetHighestBidderName(bizid, highestBidder, sizeof(highestBidder));

    PlayerBidBizID[playerid] = bizid;
    format(info, sizeof(info), "{00FFFF}%s\n\n{FFFFFF}Business: {00FF00}%s\n{FFFFFF}Lokasi: {00FF00}%s\n{FFFFFF}Status Auction: {FFFF00}%s\n{FFFFFF}Starts In: {FFFF00}%s\n{FFFFFF}Ends In: {FF0000}%s\n{FFFFFF}Highest Bidder: {00FF00}%s\n{FFFFFF}Highest Bid: {FFFF00}%d Gold\n{FFFFFF}Minimal Bid Berikutnya: {FFFF00}%d Gold\n\n{FFFF00}Masukkan jumlah bid gold di bawah ini.",
        title,
        BizData[bizid][bizName],
        GetLocation(BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2]),
        Biz_GetAuctionStatusName(status),
        startsDate,
        endsDisplay,
        highestBidder,
        Biz_GetCurrentHighestBid(bizid),
        Biz_GetMinimumNextBid(bizid));
    Dialog_Show(playerid, "BizBidInfo", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Informasi Bid", info, "Input", "Back");
    return 1;
}

Biz_ShowBidLeaderboard(playerid, bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");
    if(!Biz_IsAuctionRunning(bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Auction bisnis ini tidak sedang berjalan!");

    for(new i; i < MAX_BIZ_BID_LEADERBOARD; i++)
    {
        PlayerBidListID[playerid][i] = 0;
        PlayerBidListRank[playerid][i] = 0;
    }

    PlayerBidBizID[playerid] = bizid;

    new query[256];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `ID`, `AccountName`, `CharacterName`, `BidAmount`, `BidTimestamp` FROM `biz_bids` WHERE `BizID`=%d AND `AuctionID`=%d AND `Status`=1 ORDER BY `BidAmount` DESC, `BidTimestamp` ASC LIMIT %d", bizid, BizData[bizid][bizAuctionID], MAX_BIZ_BID_LEADERBOARD);
    mysql_pquery(g_SQL, query, "OnBizBidLeaderboardLoaded", "ii", playerid, bizid);
    return 1;
}

Biz_ShowAdminBidPanel(playerid, bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    new startDate[16], endDate[16], list[384];
    Biz_FormatAuctionDate(BizData[bizid][bizAuctionStart], startDate, sizeof(startDate));
    Biz_FormatAuctionDate(BizData[bizid][bizAuctionEnd], endDate, sizeof(endDate));

    PlayerEditBidBizID[playerid] = bizid;
    format(list, sizeof(list), "Starts In\t%s\nEnds In\t%s\nOpen Bid\t%d Gold\nDisable Auction\t%s",
        startDate,
        endDate,
        BizData[bizid][bizOpenBid],
        BizData[bizid][bizBid] ? ("Aktif") : ("Nonaktif"));
    Dialog_Show(playerid, "BizAdminBidPanel", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Admin Bid Business", list, "Select", "Close");
    return 1;
}

Biz_ShowAdminBidDateList(playerid, bizid, mode)
{
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    new list[640], dateText[16], timestamp;
    list[0] = EOS;
    for(new i; i <= 30; i++)
    {
        timestamp = (mode == 1) ? (Biz_GetLocalDayStart(i)) : (Biz_GetLocalDayEnd(i));
        Biz_FormatAuctionDate(timestamp, dateText, sizeof(dateText));
        format(list, sizeof(list), "%s%s\n", list, dateText);
    }

    PlayerEditBidBizID[playerid] = bizid;
    PlayerEditBidDateMode[playerid] = mode;
    Dialog_Show(playerid, "BizAdminBidDate", DIALOG_STYLE_LIST, mode == 1 ? ("{DA9100}Pahlawan Roleplay "WHITE"- Starts In") : ("{DA9100}Pahlawan Roleplay "WHITE"- Ends In"), list, "Select", "Back");
    return 1;
}

Biz_ShowInfo(playerid, bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    if(BizData[bizid][bizBid] && isnull(BizData[bizid][bizOwnerName]))
    {
        return Biz_ShowBidInfo(playerid, bizid);
    }

    new employeeList[180], info[1024], title[128];
    Biz_FormatEmployeeList(bizid, employeeList, sizeof(employeeList));

    if(!isnull(BizData[bizid][bizOwnerName]))
    {
        format(info, sizeof(info), "{FFFFFF}Tipe: {00FFFF}%s\n{FFFFFF}Status: {00FF00}Dimiliki\n{FFFFFF}Owner: {FFFF00}%s\n{FFFFFF}Employee: {00FF00}%d/%d\n\n{FFFF00}Employee List\n{FFFFFF}%s",
            ReturnBizTypeName(bizid),
            BizData[bizid][bizOwnerName],
            Biz_GetEmployeeCount(bizid),
            MAX_BIZ_EMPLOYEES,
            employeeList);
    }
    else
    {
        format(info, sizeof(info), "{FFFFFF}Tipe: {00FFFF}%s\n{FFFFFF}Status: {FF0000}Dijual\n{FFFFFF}Harga: {00FF00}$%s",
            ReturnBizTypeName(bizid),
            FormatMoney(BizData[bizid][bizPrice]));
    }
    format(title, sizeof(title), "[id:%d] %s", bizid, BizData[bizid][bizName]);
    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, title, info, "Tutup", "");
    return 1;
}

forward OnBizAuctionWinnerNotifyLoaded(bizid);
public OnBizAuctionWinnerNotifyLoaded(bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return 1;
    if(!cache_num_rows()) return 1;

    new characterID;
    cache_get_value_name_int(0, "CharacterID", characterID);

    new targetid = Biz_GetOnlineByCharID(characterID);
    if(targetid == INVALID_PLAYER_ID) return 1;

    Biz_SendAuctionWinnerInfo(targetid, Biz_GetAuctionManageTime(bizid));
    return 1;
}

forward OnBizAuctionFinalizeLoaded(bizid);
public OnBizAuctionFinalizeLoaded(bizid)
{
    if(bizid >= 0 && bizid < MAX_BIZ)
    {
        BizAuctionFinalizing[bizid] = false;
    }
    if(!Iter_Contains(Bizes, bizid)) return 1;
    if(!Biz_IsAuctionEndedWindowExpired(bizid)) return 1;

    new auctionID = BizData[bizid][bizAuctionID];
    if(!cache_num_rows())
    {
        Biz_ClearAuction(bizid);
        Biz_Save(bizid);
        Biz_Refresh(bizid);
        return 1;
    }

    new characterID, characterName[MAX_PLAYER_NAME + 1], bidAmount;
    cache_get_value_name_int(0, "CharacterID", characterID);
    cache_get_value_name(0, "CharacterName", characterName);
    cache_get_value_name_int(0, "BidAmount", bidAmount);

    if(characterID < 1 || bidAmount < 1)
    {
        Biz_ClearAuction(bizid);
        Biz_Save(bizid);
        Biz_Refresh(bizid);
        return 1;
    }

    BizData[bizid][bizOwnerID] = characterID;
    strcopy(BizData[bizid][bizOwnerName], characterName);
    BizData[bizid][bizMoney] = 0;
    Biz_ClearEmployees(bizid);

    if(auctionID > 0)
    {
        mysql_pquery(g_SQL, sprintf("UPDATE `business_auctions` SET `status`='Completed', `updated_at`=NOW() WHERE `id`=%d", auctionID));
        mysql_pquery(g_SQL, sprintf("UPDATE `biz_bids` SET `Status`=0 WHERE `BizID`=%d AND `AuctionID`=%d", bizid, auctionID));
    }

    Biz_ClearAuction(bizid, false);
    Biz_Save(bizid);
    Biz_Refresh(bizid);
    return 1;
}

forward OnBizHighestBidLoaded(bizid);
public OnBizHighestBidLoaded(bizid)
{
    if(!Iter_Contains(Bizes, bizid)) return 1;

    BizHighestBid[bizid] = 0;
    BizHighestBidder[bizid][0] = EOS;
    if(cache_num_rows())
    {
        cache_get_value_name(0, "CharacterName", BizHighestBidder[bizid]);
        cache_get_value_name_int(0, "BidAmount", BizHighestBid[bizid]);
    }
    Biz_UpdateSignText(bizid);
    return 1;
}

forward OnBizBidGoldChecked(playerid);
public OnBizBidGoldChecked(playerid)
{
    if(!IsPlayerConnected(playerid)) return 1;

    new bizid = GetPVarInt(playerid, "BizBidID"),
        amount = GetPVarInt(playerid, "BizBidAmount");

    DeletePVar(playerid, "BizBidID");
    DeletePVar(playerid, "BizBidAmount");

    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");
    if(!Biz_IsAuctionRunning(bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Auction bisnis ini tidak sedang berjalan!");
    if(amount < Biz_GetMinimumNextBid(bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bid minimal harus 100 Gold lebih tinggi dari highest bid saat ini.");

    new gold;
    if(cache_num_rows())
    {
        cache_get_value_name_int(0, "gold", gold);
    }
    PlayerUCPGold[playerid] = gold;

    if(gold < amount) return ShowTDN(playerid, NOTIFICATION_ERROR, "Gold UCP anda tidak cukup untuk mengikuti lelang ini!");

    new now = gettime(), remaining = BizData[bizid][bizAuctionEnd] - now;
    if(remaining > 0 && remaining < BIZ_AUCTION_ANTI_SNIPE_SECONDS)
    {
        BizData[bizid][bizAuctionEnd] = now + BIZ_AUCTION_ANTI_SNIPE_SECONDS - 1;
        Biz_Save(bizid);
    }

    new query[1024];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `biz_bids` SET `AuctionID`=%d, `BizID`=%d, `AccountID`=%d, `AccountName`='%e', `CharacterID`=%d, `CharacterName`='%e', `BidAmount`=%d, `BidRank`=0, `BidDate`=FROM_UNIXTIME(%d), `BidTimestamp`=%d, `Status`=1, `CreatedAt`=NOW() ON DUPLICATE KEY UPDATE `AccountID`=VALUES(`AccountID`), `AccountName`=VALUES(`AccountName`), `CharacterName`=VALUES(`CharacterName`), `BidAmount`=VALUES(`BidAmount`), `BidRank`=0, `BidDate`=VALUES(`BidDate`), `BidTimestamp`=VALUES(`BidTimestamp`), `Status`=1",
        BizData[bizid][bizAuctionID],
        bizid,
        PlayerUID[playerid],
        AccountData[playerid][pUCP],
        AccountData[playerid][pID],
        AccountData[playerid][pName],
        amount,
        now,
        now);
    mysql_pquery(g_SQL, query, "OnBizBidSubmitted", "iii", playerid, bizid, amount);
    return 1;
}

forward OnBizBidSubmitted(playerid, bizid, amount);
public OnBizBidSubmitted(playerid, bizid, amount)
{
    if(!Iter_Contains(Bizes, bizid)) return 1;

    if(amount > BizHighestBid[bizid])
    {
        BizHighestBid[bizid] = amount;
        if(IsPlayerConnected(playerid))
        {
            strcopy(BizHighestBidder[bizid], AccountData[playerid][pName]);
        }
        Biz_UpdateSignText(bizid);
    }

    Biz_SaveAuctionMain(bizid, playerid);
    Biz_SaveAuctionBidEvent(playerid, bizid, amount);

    if(IsPlayerConnected(playerid))
    {
        ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Bid sebesar %d Gold berhasil dikirim.", amount));
        Biz_ShowBidInfo(playerid, bizid);
    }
    return 1;
}

forward OnBizBidLeaderboardLoaded(playerid, bizid);
public OnBizBidLeaderboardLoaded(playerid, bizid)
{
    if(!IsPlayerConnected(playerid)) return 1;
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    new rows = cache_num_rows(), list[1024], accountName[32], characterName[MAX_PLAYER_NAME + 1], bidid, bidAmount;
    strcopy(list, "Rank\tAccount\tCharacter\tBid Amount\n");

    if(rows)
    {
        for(new i; i < rows; i++)
        {
            cache_get_value_name_int(i, "ID", bidid);
            cache_get_value_name(i, "AccountName", accountName);
            cache_get_value_name(i, "CharacterName", characterName);
            cache_get_value_name_int(i, "BidAmount", bidAmount);

            PlayerBidListID[playerid][i] = bidid;
            PlayerBidListRank[playerid][i] = i + 1;
            mysql_pquery(g_SQL, sprintf("UPDATE `biz_bids` SET `BidRank`=%d WHERE `ID`=%d", i + 1, bidid));
            format(list, sizeof(list), "%s#%d\t%s\t%s\t%d Gold\n", list, i + 1, accountName, characterName, bidAmount);
        }
    }
    else
    {
        strcat(list, "-\t-\t-\tBelum ada bid\n");
    }

    PlayerBidBizID[playerid] = bizid;
    Dialog_Show(playerid, "BizBidLeaderboard", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Leaderboard Bid", list, "Select", "Back");
    return 1;
}

forward OnBizBidDetailLoaded(playerid, bizid, rank);
public OnBizBidDetailLoaded(playerid, bizid, rank)
{
    if(!IsPlayerConnected(playerid)) return 1;
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");
    if(!cache_num_rows()) return Biz_ShowBidLeaderboard(playerid, bizid);

    new accountName[32], characterName[MAX_PLAYER_NAME + 1], bidAmount, bidTimestamp, bidDate[24], info[256];
    cache_get_value_name(0, "AccountName", accountName);
    cache_get_value_name(0, "CharacterName", characterName);
    cache_get_value_name_int(0, "BidAmount", bidAmount);
    cache_get_value_name_int(0, "BidTimestamp", bidTimestamp);
    Biz_FormatAuctionDateTime(bidTimestamp, bidDate, sizeof(bidDate));

    PlayerBidBizID[playerid] = bizid;
    format(info, sizeof(info), "Account: %s\nCharacter: %s\nBid Amount: #%d - %d Gold\nBid Date: %s", accountName, characterName, rank, bidAmount, bidDate);
    Dialog_Show(playerid, "BizBidDetail", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Detail Bidder", info, "Back", "Close");
    return 1;
}

task BizAuctionRefresh[1000]()
{
    foreach(new bizid : Bizes)
    {
        if(BizData[bizid][bizBid] && isnull(BizData[bizid][bizOwnerName]))
        {
            if(Biz_IsAuctionEndedWindowExpired(bizid))
            {
                Biz_FinalizeAuction(bizid);
                continue;
            }

            new status = Biz_GetAuctionStatus(bizid);
            Biz_UpdateSignText(bizid);

            if(status != BizAuctionLastStatus[bizid])
            {
                Biz_SyncInfoPoint(bizid);
                BizAuctionLastStatus[bizid] = status;
                Biz_SaveAuctionMain(bizid);
                if(status == BIZ_AUCTION_ENDED)
                {
                    Biz_NotifyAuctionWinner(bizid);
                }
            }
        }
    }
    return 1;
}

forward LoadBizes();
public LoadBizes()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new bizid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", bizid);
            cache_get_value_name(i, "Name", BizData[bizid][bizName]);
            cache_get_value_name_int(i, "OwnerID", BizData[bizid][bizOwnerID]);
            cache_get_value_name(i, "OwnerName", BizData[bizid][bizOwnerName]);
            cache_get_value_name_int(i, "Money", BizData[bizid][bizMoney]);
            cache_get_value_name_int(i, "Type", BizData[bizid][bizType]);
            cache_get_value_name_int(i, "Price", BizData[bizid][bizPrice]);
            cache_get_value_name_bool(i, "IsBid", BizData[bizid][bizBid]);
            cache_get_value_name_int(i, "AuctionID", BizData[bizid][bizAuctionID]);
            cache_get_value_name_int(i, "OpenBid", BizData[bizid][bizOpenBid]);
            cache_get_value_name_int(i, "AuctionStart", BizData[bizid][bizAuctionStart]);
            cache_get_value_name_int(i, "AuctionEnd", BizData[bizid][bizAuctionEnd]);
            cache_get_value_name_int(i, "AuctionStartedByID", BizData[bizid][bizAuctionStartedByID]);
            cache_get_value_name(i, "AuctionStartedBy", BizData[bizid][bizAuctionStartedBy]);
            cache_get_value_name_int(i, "ProdStock0", BizData[bizid][bizProdStock][0]);
            cache_get_value_name_int(i, "ProdStock1", BizData[bizid][bizProdStock][1]);
            cache_get_value_name_int(i, "ProdStock2", BizData[bizid][bizProdStock][2]);
            cache_get_value_name_int(i, "ProdStock3", BizData[bizid][bizProdStock][3]);
            cache_get_value_name_int(i, "ProdStock4", BizData[bizid][bizProdStock][4]);
            cache_get_value_name_int(i, "ProdStock5", BizData[bizid][bizProdStock][5]);
            cache_get_value_name_int(i, "ProdStock6", BizData[bizid][bizProdStock][6]);
            cache_get_value_name_int(i, "ProdStock7", BizData[bizid][bizProdStock][7]);
            cache_get_value_name_int(i, "ProdStock8", BizData[bizid][bizProdStock][8]);
            cache_get_value_name_int(i, "ProdStock9", BizData[bizid][bizProdStock][9]);
            cache_get_value_name_int(i, "ProdStock10", BizData[bizid][bizProdStock][10]);
            cache_get_value_name_int(i, "ProdPrice0", BizData[bizid][bizProdPrice][0]);
            cache_get_value_name_int(i, "ProdPrice1", BizData[bizid][bizProdPrice][1]);
            cache_get_value_name_int(i, "ProdPrice2", BizData[bizid][bizProdPrice][2]);
            cache_get_value_name_int(i, "ProdPrice3", BizData[bizid][bizProdPrice][3]);
            cache_get_value_name_int(i, "ProdPrice4", BizData[bizid][bizProdPrice][4]);
            cache_get_value_name_int(i, "ProdPrice5", BizData[bizid][bizProdPrice][5]);
            cache_get_value_name_int(i, "ProdPrice6", BizData[bizid][bizProdPrice][6]);
            cache_get_value_name_int(i, "ProdPrice7", BizData[bizid][bizProdPrice][7]);
            cache_get_value_name_int(i, "ProdPrice8", BizData[bizid][bizProdPrice][8]);
            cache_get_value_name_int(i, "ProdPrice9", BizData[bizid][bizProdPrice][9]);
            cache_get_value_name_int(i, "ProdPrice10", BizData[bizid][bizProdPrice][10]);
            cache_get_value_name_float(i, "SignX", BizData[bizid][bizSignPos][0]);
            cache_get_value_name_float(i, "SignY", BizData[bizid][bizSignPos][1]);
            cache_get_value_name_float(i, "SignZ", BizData[bizid][bizSignPos][2]);
            cache_get_value_name_float(i, "SignRX", BizData[bizid][bizSignPos][3]);
            cache_get_value_name_float(i, "SignRY", BizData[bizid][bizSignPos][4]);
            cache_get_value_name_float(i, "SignRZ", BizData[bizid][bizSignPos][5]);
            cache_get_value_name_int(i, "SignVw", BizData[bizid][bizSignVw]);
            cache_get_value_name_int(i, "SignInt", BizData[bizid][bizSignInt]);
            cache_get_value_name_int(i, "EmployeeID0", BizEmployeeID[bizid][0]);
            cache_get_value_name(i, "EmployeeName0", BizEmployeeName[bizid][0]);
            cache_get_value_name_int(i, "EmployeeID1", BizEmployeeID[bizid][1]);
            cache_get_value_name(i, "EmployeeName1", BizEmployeeName[bizid][1]);
            cache_get_value_name_int(i, "EmployeeID2", BizEmployeeID[bizid][2]);
            cache_get_value_name(i, "EmployeeName2", BizEmployeeName[bizid][2]);
            cache_get_value_name_int(i, "EmployeeID3", BizEmployeeID[bizid][3]);
            cache_get_value_name(i, "EmployeeName3", BizEmployeeName[bizid][3]);
            
            BizHighestBid[bizid] = 0;
            BizHighestBidder[bizid][0] = EOS;
            BizAuctionFinalizing[bizid] = false;
			Biz_Rebuild(bizid);
			Iter_Add(Bizes, bizid);
            if(BizData[bizid][bizBid])
            {
                Biz_LoadHighestBid(bizid);
            }
        }
        printf("[Dynamic Biz] Total number of loaded Biz: %d.", rows);
	}
    return 1;
}

forward OnBizCreated(playerid, bizid);
public OnBizCreated(playerid, bizid)
{
    Biz_Save(bizid);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s create Biz with ID: %d.", AccountData[playerid][pAdminname], bizid);
    if(IsPlayerConnected(playerid) && IsValidDynamicObject(BizData[bizid][bizSign]))
    {
        EditingBizID[playerid] = bizid;
        EditDynamicObject(playerid, BizData[bizid][bizSign]);
        ShowTDN(playerid, NOTIFICATION_INFO, "Silakan atur posisi sign bisnis. Sign text akan mengikuti otomatis.");
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    EditingBizID[playerid] = -1;
    PlayerShopBizID[playerid] = -1;
    PlayerBidBizID[playerid] = -1;
    PlayerEditBidBizID[playerid] = -1;
    PlayerEditBidDateMode[playerid] = 0;
    PlayerInBizAuctionOOC[playerid] = false;
    DeletePVar(playerid, "BizBidID");
    DeletePVar(playerid, "BizBidAmount");
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    EditingBizID[playerid] = -1;
    PlayerShopBizID[playerid] = -1;
    PlayerBidBizID[playerid] = -1;
    PlayerEditBidBizID[playerid] = -1;
    PlayerEditBidDateMode[playerid] = 0;
    PlayerInBizAuctionOOC[playerid] = false;
    DeletePVar(playerid, "BizBidID");
    DeletePVar(playerid, "BizBidAmount");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if((newkeys & KEY_YES) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !AccountData[playerid][pKnockdown])
    {
        new bizid = Biz_GetAuctionNearest(playerid, BIZ_AUCTION_KEY_RADIUS);
        if(bizid != -1)
        {
            return Biz_ShowBidMain(playerid, bizid);
        }
    }
    return 1;
}

ptask BizAuctionOOCCheck[1000](playerid)
{
    if(!AccountData[playerid][pSpawned]) return 1;

    new bool:inZone = (Biz_GetAuctionNearest(playerid, BIZ_AUCTION_CMD_RADIUS) != -1);
    if(inZone && !PlayerInBizAuctionOOC[playerid])
    {
        PlayerInBizAuctionOOC[playerid] = true;
        SendClientMessage(playerid, X11_CYAN, "INFO: Kamu memasuki Zona OOC Bid Auction. Gunakan /showbid untuk melihat informasi bid.");
    }
    else if(!inZone && PlayerInBizAuctionOOC[playerid])
    {
        PlayerInBizAuctionOOC[playerid] = false;
        SendClientMessage(playerid, X11_CYAN, "OOC ZONE: Anda keluar dari area bid auction business.");
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(EditingBizID[playerid] != -1 && Iter_Contains(Bizes, EditingBizID[playerid]))
    {
        new bizid = EditingBizID[playerid];
        if(objectid != BizData[bizid][bizSign]) return 0;

        if(response == EDIT_RESPONSE_UPDATE)
        {
            Biz_SetSignTextTransform(bizid, x, y, z, rx, ry, rz);
        }
        else if(response == EDIT_RESPONSE_FINAL)
        {
            BizData[bizid][bizSignPos][0] = x;
            BizData[bizid][bizSignPos][1] = y;
            BizData[bizid][bizSignPos][2] = z;
            BizData[bizid][bizSignPos][3] = rx;
            BizData[bizid][bizSignPos][4] = ry;
            BizData[bizid][bizSignPos][5] = rz;

            Biz_Save(bizid);
            Biz_Refresh(bizid);
            EditingBizID[playerid] = -1;
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Posisi sign bisnis berhasil disimpan.");
        }
        else if(response == EDIT_RESPONSE_CANCEL)
        {
            Biz_SyncSignObjects(bizid);
            EditingBizID[playerid] = -1;
            ShowTDN(playerid, NOTIFICATION_INFO, "Edit sign bisnis dibatalkan.");
        }
    }
    return 0;
}

Dialog:BizBidMain(playerid, response, listitem, inputtext[])
{
    new bizid = PlayerBidBizID[playerid];
    if(!response)
    {
        PlayerBidBizID[playerid] = -1;
        return 1;
    }
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");
    if(!Biz_IsAuctionRunning(bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Auction bisnis ini tidak sedang berjalan!");

    switch(listitem)
    {
        case 0: return Biz_ShowBidInfo(playerid, bizid);
        case 1: return Biz_ShowBidLeaderboard(playerid, bizid);
    }
    return 1;
}

Dialog:BizBidInfo(playerid, response, listitem, inputtext[])
{
    new bizid = PlayerBidBizID[playerid];
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    if(!response)
    {
        return Biz_ShowBidMain(playerid, bizid);
    }

    new amount;
    if(sscanf(inputtext, "d", amount))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan jumlah bid yang valid!");
        return Biz_ShowBidInfo(playerid, bizid);
    }
    if(!Biz_IsAuctionRunning(bizid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Auction bisnis ini tidak sedang berjalan!");
        return Biz_ShowBidInfo(playerid, bizid);
    }
    if(amount < Biz_GetMinimumNextBid(bizid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Bid minimal harus 100 Gold lebih tinggi dari highest bid saat ini.");
        return Biz_ShowBidInfo(playerid, bizid);
    }

    SetPVarInt(playerid, "BizBidID", bizid);
    SetPVarInt(playerid, "BizBidAmount", amount);

    new query[144];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `gold` FROM `player_ucp` WHERE `UCP`='%e' LIMIT 1", AccountData[playerid][pUCP]);
    mysql_pquery(g_SQL, query, "OnBizBidGoldChecked", "i", playerid);
    return 1;
}

Dialog:BizBidLeaderboard(playerid, response, listitem, inputtext[])
{
    new bizid = PlayerBidBizID[playerid];
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    if(!response)
    {
        return Biz_ShowBidMain(playerid, bizid);
    }

    if(listitem < 0 || listitem >= MAX_BIZ_BID_LEADERBOARD || PlayerBidListID[playerid][listitem] == 0)
    {
        return Biz_ShowBidLeaderboard(playerid, bizid);
    }

    new query[256];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `AccountName`, `CharacterName`, `BidAmount`, `BidTimestamp` FROM `biz_bids` WHERE `ID`=%d LIMIT 1", PlayerBidListID[playerid][listitem]);
    mysql_pquery(g_SQL, query, "OnBizBidDetailLoaded", "iii", playerid, bizid, PlayerBidListRank[playerid][listitem]);
    return 1;
}

Dialog:BizBidDetail(playerid, response, listitem, inputtext[])
{
    new bizid = PlayerBidBizID[playerid];
    if(response && Iter_Contains(Bizes, bizid))
    {
        return Biz_ShowBidLeaderboard(playerid, bizid);
    }
    PlayerBidBizID[playerid] = -1;
    return 1;
}

Dialog:BizAdminBidPanel(playerid, response, listitem, inputtext[])
{
    new bizid = PlayerEditBidBizID[playerid];
    if(!response)
    {
        PlayerEditBidBizID[playerid] = -1;
        return 1;
    }
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    switch(listitem)
    {
        case 0: return Biz_ShowAdminBidDateList(playerid, bizid, 1);
        case 1: return Biz_ShowAdminBidDateList(playerid, bizid, 2);
        case 2:
        {
            Dialog_Show(playerid, "BizAdminOpenBid", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Open Bid", "{FFFFFF}Masukkan open bid dalam Gold.\n\n{FFFF00}Starts In dan Ends In harus sudah diatur lebih dulu.", "Input", "Back");
        }
        case 3:
        {
            Biz_ClearAuction(bizid);
            Biz_Save(bizid);
            Biz_Refresh(bizid);
            SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menonaktifkan auction Business ID: %d.", AccountData[playerid][pAdminname], bizid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Auction bisnis berhasil dinonaktifkan.");
        }
    }
    return 1;
}

Dialog:BizAdminBidDate(playerid, response, listitem, inputtext[])
{
    new bizid = PlayerEditBidBizID[playerid], mode = PlayerEditBidDateMode[playerid];
    if(!response)
    {
        return Biz_ShowAdminBidPanel(playerid, bizid);
    }
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");
    if(listitem < 0 || listitem > 30) return Biz_ShowAdminBidPanel(playerid, bizid);

    if(mode == 1)
    {
        BizData[bizid][bizAuctionStart] = Biz_GetLocalDayStart(listitem);
        if(BizData[bizid][bizAuctionEnd] > 0 && BizData[bizid][bizAuctionEnd] <= BizData[bizid][bizAuctionStart])
        {
            BizData[bizid][bizAuctionEnd] = Biz_GetLocalDayEnd(listitem);
        }
        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Tanggal start auction berhasil diatur.");
    }
    else
    {
        BizData[bizid][bizAuctionEnd] = Biz_GetLocalDayEnd(listitem);
        if(BizData[bizid][bizAuctionStart] > 0 && BizData[bizid][bizAuctionEnd] <= BizData[bizid][bizAuctionStart])
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Ends In harus lebih besar dari Starts In!");
            return Biz_ShowAdminBidDateList(playerid, bizid, 2);
        }
        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Tanggal akhir auction berhasil diatur.");
    }

    Biz_Save(bizid);
    Biz_Refresh(bizid);
    Biz_SaveAuctionMain(bizid);
    return Biz_ShowAdminBidPanel(playerid, bizid);
}

Dialog:BizAdminOpenBid(playerid, response, listitem, inputtext[])
{
    new bizid = PlayerEditBidBizID[playerid];
    if(!response)
    {
        return Biz_ShowAdminBidPanel(playerid, bizid);
    }
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    new openBid;
    if(sscanf(inputtext, "d", openBid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan open bid yang valid!");
        return Biz_ShowAdminBidPanel(playerid, bizid);
    }
    if(openBid < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Open bid harus lebih dari 0 Gold!");
    if(BizData[bizid][bizAuctionStart] < 1 || BizData[bizid][bizAuctionEnd] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Atur Starts In dan Ends In lebih dulu!");
    if(BizData[bizid][bizAuctionEnd] <= BizData[bizid][bizAuctionStart]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ends In harus lebih besar dari Starts In!");
    if(!isnull(BizData[bizid][bizOwnerName])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis yang sudah dimiliki tidak bisa dilelang!");

    if(BizData[bizid][bizAuctionID] < 1 || Biz_GetAuctionStatus(bizid) == BIZ_AUCTION_NONE || Biz_GetAuctionStatus(bizid) == BIZ_AUCTION_ENDED)
    {
        BizData[bizid][bizAuctionID] = gettime();
        BizHighestBid[bizid] = 0;
        BizHighestBidder[bizid][0] = EOS;
        mysql_pquery(g_SQL, sprintf("UPDATE `biz_bids` SET `Status`=0 WHERE `BizID`=%d", bizid));
    }

    BizData[bizid][bizBid] = true;
    BizData[bizid][bizOpenBid] = openBid;
    BizData[bizid][bizAuctionStartedByID] = AccountData[playerid][pID];
    strcopy(BizData[bizid][bizAuctionStartedBy], AccountData[playerid][pAdminname]);
    if(BizHighestBid[bizid] > 0 && BizHighestBid[bizid] < openBid)
    {
        BizHighestBid[bizid] = 0;
        BizHighestBidder[bizid][0] = EOS;
        mysql_pquery(g_SQL, sprintf("UPDATE `biz_bids` SET `Status`=0 WHERE `BizID`=%d AND `AuctionID`=%d", bizid, BizData[bizid][bizAuctionID]));
    }

    Biz_Save(bizid);
    Biz_Refresh(bizid);
    Biz_SaveAuctionMain(bizid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuka auction Business ID: %d dengan open bid %d Gold.", AccountData[playerid][pAdminname], bizid, openBid);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Open bid auction berhasil disimpan.");
    return Biz_ShowAdminBidPanel(playerid, bizid);
}

Dialog:BizBuyProduct(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerShopBizID[playerid] = -1;
        return 1;
    }

    new bizid = AccountData[playerid][pInBiz], price;
    if(bizid == -1)
    {
        bizid = PlayerShopBizID[playerid];
    }
    if(bizid != -1)
    {
        static string[512];
        if(BizData[bizid][bizType] == 1)
        {
            if(listitem < 0 || listitem > 9) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih sesuatu!");
            if(BizData[bizid][bizProdStock][listitem] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Stock sudah habis!");
            price = BizData[bizid][bizProdPrice][listitem];

            switch(listitem)
            {
                case 0: //Udud
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                    static Float:countingtotalweight;
                    countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Udud"))/1000;
                    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Your inventory is full!");

                    TakePlayerMoneyEx(playerid, price);

                    BizData[bizid][bizProdStock][0]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);

                    Inventory_Add(playerid, "Udud", 19896, 12);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Udud", "Received 1x", 19896, 5);

                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
                }
                case 1: //Pancingan
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    static Float:countingtotalweight;
                    countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Pancingan"))/1000;
                    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Your inventory is full!");

                    TakePlayerMoneyEx(playerid, price);

                    BizData[bizid][bizProdStock][1]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);

                    Inventory_Add(playerid, "Pancingan", 18632);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Pancingan", "Received 1x", 18632, 5);

                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
                }
                case 2: //Baseball Bat
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                    TakePlayerMoneyEx(playerid, price);
                    GivePlayerWeaponEx(playerid, 5, 1, WEAPON_TYPE_PLAYER);
                    SendRPMeAboveHead(playerid, "Bought a Baseball Bat.");
                    BizData[bizid][bizProdStock][2]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Baseball Bat", "Received 1x", 336, 5);
                }
                case 3: //Pisau
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                    TakePlayerMoneyEx(playerid, price);
                    GivePlayerWeaponEx(playerid, 4, 1, WEAPON_TYPE_PLAYER);
                    BizData[bizid][bizProdStock][3]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Pisau", "Received 1x", 335, 5);
                }
                case 4: //Golf Stick
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                    TakePlayerMoneyEx(playerid, price);
                    GivePlayerWeaponEx(playerid, 2, 1, WEAPON_TYPE_PLAYER);
                    BizData[bizid][bizProdStock][4]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Golf Stick", "Received 1x", 333, 5);
                }
                case 5: //Pool Cue
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                    TakePlayerMoneyEx(playerid, price);
                    GivePlayerWeaponEx(playerid, 7, 1, WEAPON_TYPE_PLAYER);
                    BizData[bizid][bizProdStock][5]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Pool Cue", "Received 1x", 338, 5);
                }
                case 6: //Hunting Rifle
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                    TakePlayerMoneyEx(playerid, price);
                    AccountData[playerid][pHasHuntingRifle] = true;
                    BizData[bizid][bizProdStock][6]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Hunting Rifle", "Received 1x", 357, 5);
                }
                case 7: //Hunting Ammo
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                    TakePlayerMoneyEx(playerid, price);
                    Inventory_Add(playerid, "Hunt Ammo", 2358, 24);
                    BizData[bizid][bizProdStock][7]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);

                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Hunting Ammo", "Received 24x", 2358, 5);
                }
                case 8: //Obeng
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    static Float:countingtotalweight;
                    countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Obeng"))/1000;
                    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Your inventory is full!");

                    if(PlayerHasItem(playerid,"Obeng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Obeng!");
                    
                    TakePlayerMoneyEx(playerid, price);
                    BizData[bizid][bizProdStock][8]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);

                    Inventory_Add(playerid, "Obeng", 19627);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Obeng", "Received 1x", 19627, 5);

                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
                }
                case 9: //hoe
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    static Float:countingtotalweight;
                    countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Hoe"))/1000;
                    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

                    if(PlayerHasItem(playerid,"Hoe")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki hoe!");
                    
                    TakePlayerMoneyEx(playerid, price);
                    BizData[bizid][bizProdStock][8]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);

                    Inventory_Add(playerid, "Hoe", 2228);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Hoe", "Received 1x", 2228, 5);

                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
                }
            }
        }
        
        if(BizData[bizid][bizType] == 3)
        {
            if(listitem < 0 || listitem > 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih sesuatu!");
            if(BizData[bizid][bizProdStock][listitem] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Stock sudah habis!");
            price = BizData[bizid][bizProdPrice][listitem];
            
            switch(listitem)
            {
                case 0: //smartphone
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                    static Float:countingtotalweight;
                    countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Smartphone"))/1000;
                    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

                    TakePlayerMoneyEx(playerid, price);
                    BizData[bizid][bizProdStock][0]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);

                    mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
                    mysql_pquery(g_SQL, string, "OnPlayerBuySmartphone", "i", playerid);

                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Smartphone", "Received 1x", 19942, 5);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
                }
                case 1: //radio
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    BizData[bizid][bizProdStock][1]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);

                    TakePlayerMoneyEx(playerid, price);
                    PlayerVoiceData[playerid][pHasRadio] = true;

                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Radio", "Received 1x", 19942, 5);

                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
                }
                case 2: //earphone
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    BizData[bizid][bizProdStock][2]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);

                    TakePlayerMoneyEx(playerid, price);
                    AccountData[playerid][pEarphone] = true;

                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Earphone", "Received 1x", 19421, 5);

                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
                }
                case 3: //boombox
                {
                    if(AccountData[playerid][pVIP] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Donatur!");
                    
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    BizData[bizid][bizProdStock][3]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);
                    
                    TakePlayerMoneyEx(playerid, price);
                    AccountData[playerid][pBoombox] = true;

                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Boombox", "Received 1x", 2103, 5);

                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
                }
                case 4: //spraycan
                {
                    if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    static Float:countingtotalweight;
                    countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Pilox"))/1000;
                    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
                    
                    TakePlayerMoneyEx(playerid, price);
                    BizData[bizid][bizProdStock][6]--;
                    BizData[bizid][bizMoney] += price;
                    
                    Biz_Save(bizid);

                    Inventory_Add(playerid, "Pilox", 365);
                    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(price)), 1212, 4);
                    ShowItemBox(playerid, "Pilox", "Received 1x", 365, 5);

                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
                }
            }
        }
    }
    PlayerShopBizID[playerid] = -1;
    return 1;
}

Dialog:BizMenu(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    
    new bizid = AccountData[playerid][pInBiz];
    if(bizid != -1)
    {
        if(BizData[bizid][bizType] == 1)
        {
            if(listitem < 0 || listitem > 11) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih sesuatu!");

            switch(listitem)
            {
                case 0:
                {
                    Dialog_Show(playerid, "BizMenuName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Nama Biz", "Mohon masukkan nama untuk biz milikmu:", 
                    "Set", "Batal");
                }
                case 1:
                {
                    Dialog_Show(playerid, "BizMenuProfit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Profit Biz", "Mohon masukkan berapa jumlah yang ingin ditarik:", "Tarik", "Batal");
                }
                default:
                {
                    AccountData[playerid][pTempValue] = listitem - 2;
                    Dialog_Show(playerid, "BizMenuProduct", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Harga Produk", "Mohon masukkan berapa harga produk tersebut:", "Set", "Batal");
                }
            }
        }
        
        if(BizData[bizid][bizType] == 3)
        {
            if(listitem < 0 || listitem > 8) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih sesuatu!");

            switch(listitem)
            {
                case 0:
                {
                    Dialog_Show(playerid, "BizMenuName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Nama Biz", "Mohon masukkan nama untuk biz milikmu:", 
                    "Set", "Batal");
                }
                case 1:
                {
                    Dialog_Show(playerid, "BizMenuProfit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Profit Biz", "Mohon masukkan berapa jumlah yang ingin ditarik:", "Tarik", "Batal");
                }
                default:
                {
                    AccountData[playerid][pTempValue] = listitem - 2;
                    Dialog_Show(playerid, "BizMenuProduct", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Harga Produk", "Mohon masukkan berapa harga produk tersebut:", "Set", "Batal");
                }
            }
        }
    }
    return 1;
}

Dialog:BizMenuName(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new bizid = AccountData[playerid][pInBiz];
    if(bizid != -1)
    {
        if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dibiarkan kosong!");

        // Hitung panjang string tanpa kode warna {RRGGBB}
        new cleanlen, i, c, inbracket;
        while((c = inputtext[i++]) != EOS)
        {
            if(c == '{') { inbracket = 1; continue; }
            if(c == '}' && inbracket) { inbracket = 0; continue; }
            if(!inbracket) cleanlen++;
        }

        if(cleanlen < 3 || cleanlen > 32) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama biz (tanpa kode warna) antara 3 - 32 char!");
        if(strfind(inputtext, "%", true) != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menggunakan simbol persen!");
        
        strcopy(BizData[bizid][bizName], inputtext);
        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengganti nama biz!");

        Biz_Save(bizid);
        Biz_Refresh(bizid);
    }
    return 1;
}

Dialog:BizMenuProfit(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new bizid = AccountData[playerid][pInBiz];
    if(bizid != -1)
    {
        if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dibiarkan kosong!");
        if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi oleh angka!");
        if(strval(inputtext) < 1 || strval(inputtext) > BizData[bizid][bizMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

        BizData[bizid][bizMoney] -= strval(inputtext);
        GivePlayerMoneyEx(playerid, strval(inputtext));

        ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda mengambil $%s dari bisnis ini!", FormatMoney(strval(inputtext))));

        Biz_Save(bizid);
        Biz_Refresh(bizid);
    }
    return 1;
}

Dialog:BizMenuProduct(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new bizid = AccountData[playerid][pInBiz];
    if(bizid != -1)
    {
        if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dibiarkan kosong!");
        if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi oleh angka!");
        if(AccountData[playerid][pTempValue] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");

        if(strval(inputtext) < 20) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga minimal adalah $20!");
        if(strval(inputtext) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga maksimal adalah $50!");

        BizData[bizid][bizProdPrice][AccountData[playerid][pTempValue]] = strval(inputtext);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah harga produk tersebut!");

        Biz_Save(bizid);
        Biz_Refresh(bizid);
    }
    return 1;
}

Dialog:BizRestock(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new bizid = AccountData[playerid][pInBiz];
    if(bizid != -1)
    {
        if(BizData[bizid][bizType] == 1)
        {
            if(listitem < 0 || listitem > 9) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih sesuatu!");

            switch(listitem)
            {
                case 0:
                {
                    AccountData[playerid][pTempValue] = 0;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 1:
                {
                    AccountData[playerid][pTempValue] = 1;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 2:
                {
                    AccountData[playerid][pTempValue] = 2;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 3:
                {
                    AccountData[playerid][pTempValue] = 3;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 4:
                {
                    AccountData[playerid][pTempValue] = 4;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 5:
                {
                    AccountData[playerid][pTempValue] = 5;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 6:
                {
                    AccountData[playerid][pTempValue] = 6;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 7:
                {
                    AccountData[playerid][pTempValue] = 7;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 8:
                {
                    AccountData[playerid][pTempValue] = 8;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 9:
                {
                    AccountData[playerid][pTempValue] = 9;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
            }
        }
        if(BizData[bizid][bizType] == 3)
        {
            if(listitem < 0 || listitem > 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih sesuatu!");

            switch(listitem)
            {
                case 0:
                {
                    AccountData[playerid][pTempValue] = 0;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 1:
                {
                    AccountData[playerid][pTempValue] = 1;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 2:
                {
                    AccountData[playerid][pTempValue] = 2;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 3:
                {
                    AccountData[playerid][pTempValue] = 3;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
                case 4:
                {
                    AccountData[playerid][pTempValue] = 4;
                    Dialog_Show(playerid, "BizRestockConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Restock Product", ""WHITE"Please insert the ammount of stocks that you want to buy\nPrice: "SEAGREEN"$15.00/stock:", "Restock", "Batal");
                }
            }
        }
    }
    return 1;
}

Dialog:BizRestockConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new bizid = AccountData[playerid][pInBiz];
    if(bizid != -1)
    {
        if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dibiarkan kosong!");
        if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi oleh angka!");
        if(AccountData[playerid][pTempValue] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
        if(strval(inputtext) < 1 || strval(inputtext) > 1000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat restock antara 1 - 1000!");
        new totalling = BizData[bizid][bizProdStock][AccountData[playerid][pTempValue]] + strval(inputtext);
        if(totalling > 1000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Maksimal stok produk adalah 1000!");

        new pricing = strval(inputtext) * 1500;
        if(AccountData[playerid][pBankMoney] < RoundNegativeToPositive(pricing)) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo rekening anda tidak cukup!");

        AccountData[playerid][pBankMoney] -= pricing;
        BizData[bizid][bizProdStock][AccountData[playerid][pTempValue]] += strval(inputtext);
        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengisi ulang stock produk tersebut");

        Biz_Save(bizid);
        Biz_Refresh(bizid);
    }
    return 1;
}
