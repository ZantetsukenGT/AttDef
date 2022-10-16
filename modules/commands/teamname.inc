#if defined _attdef_cmd_teamname
	#endinput
#endif
#define _attdef_cmd_teamname

YCMD: teamname(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "change the name of a team.");
	new TeamID, TeamNamee[24];
	if (sscanf(params, "ds[24]", TeamID, TeamNamee))
		return SendUsageMessage(playerid, "/teamname [Team ID] [Name] (0 = Attacker | 1 = Defender)");

	if (TeamID < 0 || TeamID > 1)
		return SendErrorMessage(playerid, "Invalid Team ID.");
	if (strlen(TeamNamee) > 6)
		return SendErrorMessage(playerid, "Team name is too long.");
	if (strfind(TeamNamee, "~") != -1)
		return SendErrorMessage(playerid, "~ not allowed.");

	switch (TeamID)
	{
		case 0:
		{
			format(TeamName[ATTACKER], 24, TeamNamee);
			format(TeamName[ATTACKER_SUB], 24, "%s Sub", TeamNamee);
			va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}attacker team name " COL_PRIM "to: {FFFFFF}%s", Player[playerid][Name], TeamName[ATTACKER]);
		}
		case 1:
		{
			format(TeamName[DEFENDER], 24, TeamNamee);
			format(TeamName[DEFENDER_SUB], 24, "%s Sub", TeamNamee);
			va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}defender team name " COL_PRIM "to: {FFFFFF}%s", Player[playerid][Name], TeamName[DEFENDER]);
		}
	}

	UpdateTeamNamesTextdraw();
	UpdateTeamNameTextDraw();
	return 1;
}
