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
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/remove [Player Name/ID]");
	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (!Player[pID][Playing])
		return SendErrorMessage(playerid, "That player is not playing.");

	new health = GetHP(pID);
	new armour = GetAP(pID);

	RemovePlayerFromRound(pID);

	LogAdminCommand("remove", playerid, pID);

	return va_SendClientMessageToAll(-1, "%s (%d) " COL_PRIM "removed {FFFFFF}%s (%d) " COL_PRIM "from round. {FFFFFF}(HP %d | AP %d)", Player[playerid][Name], playerid,
		Player[pID][Name], pID, health, armour);
}
