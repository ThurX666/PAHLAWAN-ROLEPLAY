YCMD:pdbcdj(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_PUTRIDELI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Putri Deli Beach Club!");

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 639.6934,-1873.5658,10.5920))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di alat DJ Putri Deli");
    
    new link[144];
    if(sscanf(params, "s[144]", link)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/pdbcdj [link mp3]~n~'off' untuk matikan");
    
    if(!strcmp(link, "off", true))
    {
        GM[PDBCDJLink] = EOS;
        foreach(new i : Player) if(IsPlayerInDynamicArea(i, PDCMusicZone))
        {
            StopAudioStreamForPlayer(i);
        }
        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil matikan musik DJ!");
    }
    else
    {
        strcopy(GM[PDBCDJLink], link);
        foreach(new i : Player) if(IsPlayerInDynamicArea(i, PDCMusicZone))
        {
            PlayAudioStreamForPlayer(i, link);
        }
        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memainkan musik!");
    }
    return 1;
}