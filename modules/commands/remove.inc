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
	new pID;
	if (sscanf(params, "i", pID))
		return SendUsageMessage(playerid, "/remove [Player ID]");
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (!Player[pID][Playing])
		return SendErrorMessage(playerid, "That player is not playing.");

	new Float: pHP	   = GetPlayerHealth(pID);
	new Float: pArmour = GetPlayerArmour(pID);

	RemovePlayerFromRound(pID);

	LogAdminCommand("remove", playerid, pID);

	va_SendClientMessageToAll(
		-1, "{FFFFFF}%s " COL_PRIM "removed {FFFFFF}%s " COL_PRIM "from round. {FFFFFF}(HP %.1f | AP %.1f)", Player[playerid][Name], Player[pID][Name], pHP, pArmour);
	return 1;
}
