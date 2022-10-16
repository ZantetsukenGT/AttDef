#if defined _attdef_cmd_setscore
	#endinput
#endif
#define _attdef_cmd_setscore

YCMD: setscore(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "set the score of a team.");
	if (!WarMode)
		return SendErrorMessage(playerid, "Warmode is not enabled.");

	new TeamID, Score;
	if (sscanf(params, "dd", TeamID, Score))
		return SendUsageMessage(playerid, "/setscore [Team ID (0 Att | 1 Def)] [Score]");

	if (TeamID < 0 || TeamID > 1)
		return SendErrorMessage(playerid, "Invalid team ID.");
	if (Score < 0 || Score > 100)
		return SendErrorMessage(playerid, "Score can only be between 0 and 100.");

	new iString[128];
	if (TeamID == 0)
	{
		if (Score + TeamScore[DEFENDER] >= TotalRounds)
			return SendErrorMessage(playerid, "Attacker plus defender score is bigger than or equal to the total rounds.");
		TeamScore[ATTACKER] = Score;
		format(iString, sizeof(iString), "%s " COL_PRIM "has set {FFFFFF}attacker team score " COL_PRIM "to: {FFFFFF}%d", Player[playerid][Name], TeamScore[ATTACKER]);
	}
	else
	{
		if (Score + TeamScore[ATTACKER] >= TotalRounds)
			return SendErrorMessage(playerid, "Attacker plus defender score is bigger than or equal to the total rounds.");
		TeamScore[DEFENDER] = Score;
		format(iString, sizeof(iString), "%s " COL_PRIM "has set {FFFFFF}defender team score " COL_PRIM "to: {FFFFFF}%d", Player[playerid][Name], TeamScore[DEFENDER]);
	}

	CurrentRound = TeamScore[ATTACKER] + TeamScore[DEFENDER];

	UpdateTeamScoreTextDraw();

	LogAdminCommand("setscore", playerid, INVALID_PLAYER_ID);

	return SendClientMessageToAll(-1, iString);
}
