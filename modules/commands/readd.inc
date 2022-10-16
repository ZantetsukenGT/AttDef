#if defined _attdef_cmd_readd
	#endinput
#endif
#define _attdef_cmd_readd

YCMD: readd(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "re-add a player to the round.");
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");

	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/readd [Player Name/ID]");

	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player is not connected.");
	if (Player[pID][Team] != ATTACKER && Player[pID][Team] != DEFENDER && Player[pID][Team] != REFEREE)
		return SendErrorMessage(playerid, "That player must be part of one of the following teams: Attacker, Defender or Referee.");

	if (Player[pID][Playing])
	{
		Player[pID][TotalKills]	 = Player[pID][TotalKills] - Player[pID][RoundKills];
		Player[pID][TotalDeaths] = Player[pID][TotalDeaths] - Player[pID][RoundDeaths];
		Player[pID][TotalDamage] = Player[pID][TotalDamage] - Player[pID][RoundDamage];
	}

	DeletePlayerTeamBar(pID);

	if (GameType == BASE)
		AddPlayerToBase(pID);
	else if (GameType == ARENA)
		AddPlayerToArena(pID);

	LogAdminCommand("readd", playerid, pID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has re-added {FFFFFF}%s " COL_PRIM "to the round.", Player[playerid][Name], Player[pID][Name]);
}
