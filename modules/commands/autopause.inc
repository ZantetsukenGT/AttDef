#if defined _attdef_cmd_autopause
	#endinput
#endif
#define _attdef_cmd_autopause

YCMD: autopause(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "toggle automatic pausing on player disconnection in war mode");
	return ToggleAutoPause(playerid);
}

ToggleAutoPause(playerid)
{
	AutoPause = !AutoPause;
	LogAdminCommand("autopause", playerid, INVALID_PLAYER_ID);
	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has %s " COL_PRIM "Auto-Pause on player disconnect in war mode.", Player[playerid][Name],
		AutoPause ? "{66FF66}enabled" : "{FF6666}disabled"));
}
