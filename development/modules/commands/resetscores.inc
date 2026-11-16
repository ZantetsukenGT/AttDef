#if defined _attdef_cmd_resetscores
	#endinput
#endif
#define _attdef_cmd_resetscores

YCMD: resetscores(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "reset team scores.");

	TeamScore[ATTACKER] = 0;
	TeamScore[DEFENDER] = 0;
	CurrentRound		= 0;

	UpdateTeamScoreTextDraw();
	UpdateRoundsPlayedTextDraw();
	UpdateTeamNameTextDraw();

	ClearPlayerVariables();

	foreach (new i : Player)
	{
		Player[i][TotalKills]		 = 0;
		Player[i][TotalDeaths]		 = 0;
		Player[i][TotalDamage]		 = 0.0;
		Player[i][RoundPlayed]		 = 0;
		Player[i][TotalBulletsFired] = 0;
		Player[i][TotalshotsHit]	 = 0;
	}
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has reset the scores.", Player[playerid][Name]);
}
