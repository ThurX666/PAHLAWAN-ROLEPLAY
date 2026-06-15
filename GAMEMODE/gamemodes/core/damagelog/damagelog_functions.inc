#include <YSI_Coding\y_hooks>

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    if(issuerid != INVALID_PLAYER_ID)
    {
        if(!AccountData[issuerid][pInEvent] && !AccountData[playerid][pInEvent])
        {
            new sjhtr[512], weaponName[35];
            GetWeaponName(weaponid, weaponName, sizeof (weaponName));
            mysql_format(g_SQL, sjhtr, sizeof(sjhtr), "INSERT INTO `damagelogs` SET `OwnerID` = %d, `Date` = '%e', `Weapon` = '%e', `Damage` = '%.2f', `BodyPart` = '%e', `IssuerName` = '%e', `KorbanName` = '%e'", 
            AccountData[playerid][pID], GetSimpleTime(), weaponName, amount, GetBodyPartName(bodypart), AccountData[issuerid][pName], AccountData[playerid][pName]);
            mysql_pquery(g_SQL, sjhtr);
        }
    }
    else
    {
        if(!AccountData[playerid][pInEvent])
        {
            new sjhtr[512], weaponName[35];
            GetWeaponName(weaponid, weaponName, sizeof (weaponName));
            mysql_format(g_SQL, sjhtr, sizeof(sjhtr), "INSERT INTO `damagelogs` SET `OwnerID` = %d, `Date` = '%e', `Weapon` = '%e', `Damage` = '%.2f', `BodyPart` = '%e', `IssuerName` = 'Unknown', `KorbanName` = '%e'", 
            AccountData[playerid][pID], GetSimpleTime(), weaponName, amount, GetBodyPartName(bodypart), AccountData[playerid][pName]);
            mysql_pquery(g_SQL, sjhtr);
        }
    }
    return 1;
}