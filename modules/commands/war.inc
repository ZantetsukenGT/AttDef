#if defined _attdef_cmd_war
	#endinput
#endif
#define _attdef_cmd_war

YCMD: war(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "start a match quickly.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use this command while round is on.");
	if (WarModeEnding)
		return SendErrorMessage(playerid, "Please wait.");

	new TeamAName[7], TeamBName[7];
	if (sscanf(params, "s[7]S( )[7]", TeamAName, TeamBName))
		return SendUsageMessage(playerid, "/war ([Team A] [Team B]) (end)");
	if (strcmp(TeamAName, "end", true) == 0 && isnull(TeamBName) && WarMode)
	{
		WarModeEnding = true;
		SetTimer("WarEnded", 5000, false);
		va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set the match to end!", Player[playerid][Name]);
		SendClientMessageToAll(-1, COL_PRIM "Preparing End Match Results..");
		return SendClientMessageToAll(-1, COL_PRIM "If you missed the results, type {FFFFFF}/showagain");
	}

	if (WarMode)
		return SendErrorMessage(playerid, "War-mode is already on.");
	if (isnull(TeamBName))
		return SendUsageMessage(playerid, "/war ([Team A] [Team B]) (end)");
	if (strlen(TeamAName) > 6 || strlen(TeamBName) > 6)
		return SendErrorMessage(playerid, "Team name is too long.");
	if (strfind(TeamAName, "~") != -1 || strfind(TeamBName, "~") != -1)
		return SendErrorMessage(playerid, "~ not allowed.");

	format(TeamName[ATTACKER], sizeof(TeamAName), TeamAName);
	format(TeamName[ATTACKER_SUB], 24, "%s Sub", TeamName[ATTACKER]);
	format(TeamName[DEFENDER], sizeof(TeamBName), TeamBName);
	format(TeamName[DEFENDER_SUB], 24, "%s Sub", TeamName[DEFENDER]);
	UpdateTeamScoreTextDraw();
	UpdateRoundsPlayedTextDraw();
	UpdateTeamNameTextDraw();
	UpdateTeamNamesTextdraw();

	MatchRoundsStarted = 0;
	WarMode			   = true;
	RoundPaused		   = false;
	for (new i = 0; i < 101; i++)
	{
		MatchRoundsRecord[i][round__ID]		   = -1;
		MatchRoundsRecord[i][round__type]	   = -1;
		MatchRoundsRecord[i][round__completed] = false;
	}

	TextDrawSetString(WarModeText, va_return("%sWar Mode: ~r~ON", MAIN_TEXT_COLOUR));

	new toTeam = ATTACKER, oppositeTeam = DEFENDER;
	new Seat, MyVehicle					= -1;

	foreach (new i : Player)
	{
		Player[i][TotalKills]		 = 0;
		Player[i][TotalDeaths]		 = 0;
		Player[i][TotalDamage]		 = 0.0;
		Player[i][RoundPlayed]		 = 0;
		Player[i][TotalBulletsFired] = 0;
		Player[i][TotalshotsHit]	 = 0;

		if (Player[i][InDuel] || Player[i][IsAFK] || !Player[i][Spawned])
			continue;

		MyVehicle = -1;
		switch (strfind(Player[i][Name], TeamName[ATTACKER], true))
		{
			case -1: // tag not found
			{
				if (Player[i][Team] != oppositeTeam)
				{
					if (IsPlayerInAnyVehicle(i))
					{
						MyVehicle = GetPlayerVehicleID(i);
						Seat	  = GetPlayerVehicleSeat(i);
					}
					Player[i][Team] = oppositeTeam;
					SwitchTeamFix(i, false, false);
					if (MyVehicle != -1)
						PutPlayerInVehicle(i, MyVehicle, Seat);
				}
			}
			default: // found tag
			{
				if (Player[i][Team] != toTeam)
				{
					if (IsPlayerInAnyVehicle(i))
					{
						MyVehicle = GetPlayerVehicleID(i);
						Seat	  = GetPlayerVehicleSeat(i);
					}
					Player[i][Team] = toTeam;
					SwitchTeamFix(i, false, false);
					if (MyVehicle != -1)
						PutPlayerInVehicle(i, MyVehicle, Seat);
				}
			}
		}
	}
	ShowMatchScoreBoard();
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has enabled the Match-Mode.", Player[playerid][Name]);
}
