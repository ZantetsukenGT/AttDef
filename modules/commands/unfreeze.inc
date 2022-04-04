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
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/unfreeze [Player ID]");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isnt connected.");

	TogglePlayerControllable(pID, 1);

	LogAdminCommand("unfreeze", playerid, pID);

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has unfrozen {FFFFFF}%s", Player[playerid][Name], Player[pID][Name]);
	return SendClientMessageToAll(-1, iString);
}
