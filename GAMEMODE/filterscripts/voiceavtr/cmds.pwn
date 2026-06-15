CMD:mumble(playerid, params[])
{
    if(vdLocalStream[playerid])
    {
        SvDeleteStream(vdLocalStream[playerid]);
        vdLocalStream[playerid] = SV_NULL;

        vdLocalStream[playerid] = SvCreateDLStreamAtPlayer(20.0, SV_INFINITY, playerid, 0xffff0000, "Lokal");

        SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"System voice telah dimuat ulang.");
    }
    return 1;
}