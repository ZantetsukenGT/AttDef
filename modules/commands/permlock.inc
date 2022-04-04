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

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has %s the server permanent lock!", Player[playerid][Name], PermLocked ? "disabled" : "enabled");
	PermLocked = !PermLocked;
	return SendClientMessageToAll(-1, iString);
}
