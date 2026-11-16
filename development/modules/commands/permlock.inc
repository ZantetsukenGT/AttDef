#if defined _attdef_cmd_permlock
	#endinput
#endif
#define _attdef_cmd_permlock

YCMD: permlock(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 5 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "toggle server permanent lock status.");

	LogAdminCommand("permlock", playerid, INVALID_PLAYER_ID);
	if (!ServerLocked)
		return SendErrorMessage(playerid, "Server must be locked first. Use /lock !");

	PermLocked = !PermLocked;
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has %s " COL_PRIM "server's {FFFFFF}permanent lock" COL_PRIM ".", Player[playerid][Name], PermLocked ? "{66FF66}enabled" : "{FF6666}disabled");
}
