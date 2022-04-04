#if defined _attdef_cmd_remove
	#endinput
#endif
#define _attdef_cmd_remove

YCMD: remove(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "remove a specific player from the round.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/remove [Player ID]");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (!Player[pID][Playing])
		return SendErrorMessage(playerid, "That player is not playing.");

	new iString[160], HP[2];
	GetHP(pID, HP[0]);
	GetAP(pID, HP[1]);

	RemovePlayerFromRound(pID);

	LogAdminCommand("remove", playerid, pID);

	format(
		iString, sizeof(iString), "{FFFFFF}%s (%d) " COL_PRIM "removed {FFFFFF}%s (%d) " COL_PRIM "from round. {FFFFFF}(HP %d | AP %d)", Player[playerid][Name], playerid,
		Player[pID][Name], pID, HP[0], HP[1]);
	return SendClientMessageToAll(-1, iString);
}
