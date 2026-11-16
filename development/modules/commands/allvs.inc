#if defined _attdef_cmd_allvs
	#endinput
#endif
#define _attdef_cmd_allvs

YCMD: allvs(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "set everyone versus a specific team.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use while round is active.");

	new toTeam, TempTeamName[6];
	if (sscanf(params, "s[6]I(0)", TempTeamName, toTeam))
		return SendUsageMessage(playerid, "/allvs [Tag/Name] [Optional: Team ID (default 0)| 0 = Attacker, 1 = Defender]");
	if (toTeam < 0 || toTeam > 1)
		return SendErrorMessage(playerid, "Available teams: 0 for attacker and 1 for defender");

	switch (toTeam)
	{
		case 0: toTeam = ATTACKER;
		case 1: toTeam = DEFENDER;
	}

	new oppositeTeam;
	switch (toTeam)
	{
		case ATTACKER: oppositeTeam = DEFENDER;
		case DEFENDER: oppositeTeam = ATTACKER;
	}
	new playersSwitched[2], MyVehicle = -1, Seat;

	foreach (new i : Player)
	{
		if (Player[i][InDuel] || Player[i][IsAFK] || !Player[i][Spawned])
			continue;

		if (Player[i][Team] != ATTACKER && Player[i][Team] != DEFENDER)
			continue;

		MyVehicle = -1;
		switch (strfind(Player[i][Name], TempTeamName, true))
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
					playersSwitched[0]++;
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
					playersSwitched[1]++;
					if (MyVehicle != -1)
						PutPlayerInVehicle(i, MyVehicle, Seat);
				}
			}
		}
	}
	MessageBox(
		playerid, MSGBOX_TYPE_MIDDLE, "~b~~h~~h~all-vs result",
		va_return("%d players were swapped to the team you specified whilst %d were swapped to the opposite team", playersSwitched[1], playersSwitched[0]), 4000);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has changed the teams to {FFFFFF}\"%s\" vs all.", Player[playerid][Name], TempTeamName);
}
