#if defined _attdef_cmd_unfreeze
	#endinput
#endif
#define _attdef_cmd_unfreeze

YCMD: unfreeze(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "unfreeze a player.");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/unfreeze [Player Name/ID]");
	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isnt connected.");

	TogglePlayerControllable(pID, 1);

	LogAdminCommand("unfreeze", playerid, pID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has unfrozen {FFFFFF}%s", Player[playerid][Name], Player[pID][Name]);
}
