#include <YSI_Coding\y_hooks>

#define MAX_SLOTS 48
 
new NotMoving[MAX_PLAYERS];
new acWeaponID[MAX_PLAYERS];
new CheckCrouch[MAX_PLAYERS];
new Ammo[MAX_PLAYERS][MAX_SLOTS];


hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if((newkeys & KEY_FIRE) && (oldkeys & KEY_CROUCH) && !((oldkeys & KEY_FIRE) || (newkeys & KEY_HANDBRAKE)) || (oldkeys & KEY_FIRE) && (newkeys & KEY_CROUCH) && !((newkeys & KEY_FIRE) || (newkeys & KEY_HANDBRAKE)) ) 
    {
        switch(GetPlayerWeapon(playerid)) 
        {
            case 23..25, 27, 29..34, 41: 
            {
                if(Ammo[playerid][GetPlayerWeapon(playerid)] > GetPlayerAmmo(playerid)) 
                {
                    OnPlayerCBug(playerid);
                }
                return 1;
            }
        }
    }
 
    if(CheckCrouch[playerid] == 1) 
    {
        switch(acWeaponID[playerid]) 
        {
            case 23..25, 27, 29..34, 41: 
            {
                if((newkeys & KEY_CROUCH) && !((newkeys & KEY_FIRE) || (newkeys & KEY_HANDBRAKE)) && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK ) 
                {
                    if(Ammo[playerid][GetPlayerWeapon(playerid)] > GetPlayerAmmo(playerid)) 
                    {
                        OnPlayerCBug(playerid);
                    }
                }
            }
        }
    }
 
    //if(newkeys & KEY_CROUCH || (oldkeys & KEY_CROUCH)) return 1;
 
    else if(((newkeys & KEY_FIRE) && (newkeys & KEY_HANDBRAKE) && !((newkeys & KEY_SPRINT) || (newkeys & KEY_JUMP))) ||
    (newkeys & KEY_FIRE) && !((newkeys & KEY_SPRINT) || (newkeys & KEY_JUMP)) ||
    (NotMoving[playerid] && (newkeys & KEY_FIRE) && (newkeys & KEY_HANDBRAKE)) ||
    (NotMoving[playerid] && (newkeys & KEY_FIRE)) ||
    (newkeys & KEY_FIRE) && (oldkeys & KEY_CROUCH) && !((oldkeys & KEY_FIRE) || (newkeys & KEY_HANDBRAKE)) ||
    (oldkeys & KEY_FIRE) && (newkeys & KEY_CROUCH) && !((newkeys & KEY_FIRE) || (newkeys & KEY_HANDBRAKE)) ) 
    {
        SetTimerEx("CrouchCheck", 3000, false, "i", playerid);
        CheckCrouch[playerid] = 1;
        acWeaponID[playerid] = GetPlayerWeapon(playerid);
        Ammo[playerid][GetPlayerWeapon(playerid)] = GetPlayerAmmo(playerid);
        return 1;
    }
    
    return 1;
}
 
ptask AntiCBugChecking[1000](playerid) 
{
    if(AccountData[playerid][pSpawned])
    {
        new Keys, ud, lr;
        GetPlayerKeys(playerid, Keys, ud, lr);
        if(CheckCrouch[playerid] == 1) 
        {
            switch(acWeaponID[playerid]) 
            {
                case 23..25, 27, 29..34, 41: 
                {
                    if((Keys & KEY_CROUCH) && !((Keys & KEY_FIRE) || (Keys & KEY_HANDBRAKE)) && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK) 
                    {
                        if(Ammo[playerid][GetPlayerWeapon(playerid)] > GetPlayerAmmo(playerid)) 
                        {
                            OnPlayerCBug(playerid);
                        }
                    }
                }
            }
        }
    
        if(!ud && !lr) 
        { 
            NotMoving[playerid] = 1;
        }
        else 
        { 
            NotMoving[playerid] = 0;
        }
    }
    return 1;
}
 
OnPlayerCBug(playerid) 
{
    static str2[144];
    format(str2, sizeof(str2), "[AntiCheat] Anda telah ditendang dari server karena C-Bug (%s)", ReturnWeaponName(acWeaponID[playerid]));
    SendClientMessage(playerid, X11_RED, str2);
    CheckCrouch[playerid] = 0;
    KickEx(playerid);
    return 1;
}

forward CrouchCheck(playerid);
public CrouchCheck(playerid) 
{
    CheckCrouch[playerid] = 0;
    return 1;
}