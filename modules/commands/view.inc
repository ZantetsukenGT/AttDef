#if defined _attdef_cmd_view
	#endinput
#endif
#define _attdef_cmd_view

YCMD: view(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "put you in base/arena spectator mode.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use while round is on.");

	new mapType[6], Round;
	if (sscanf(params, "s[*]I(-1)", sizeof(mapType), mapType, Round) || Round < 0)
		return SendUsageMessage(playerid, "/view [base | arena] [Round ID]");

	new CommandID;
	switch (YHash(mapType, false))
	{
		case _I<base>: CommandID = 1;
		case _I<arena>: CommandID = 2;
		default: return SendUsageMessage(playerid, "/view [base | arena] [Round ID]");
	}
	switch (CommandID)
	{
		case 1: //base
		{
			if (!Iter_Contains(CurrentBases, Round))
				return SendErrorMessage(playerid, "That base does not exist.");
		}
		case 2: // Arena
		{
			if (!Iter_Contains(CurrentArenas, Round))
				return SendErrorMessage(playerid, "That arena does not exist.");
		}
	}
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel. Use /rq instead.");

	if (Player[playerid][InDM])
	{
		Player[playerid][InDM]	  = false;
		Player[playerid][DMReadd] = 0;
	}

	if (Player[playerid][Spectating])
		StopSpectate(playerid);

	Player[playerid][SpectatingRound] = Round;
	switch (CommandID)
	{
		case 1: //base
		{
			SetPlayerInterior(playerid, BInterior[Round]);
			SetPlayerCameraLookAt(playerid, BCPSpawn[Round][0], BCPSpawn[Round][1], BCPSpawn[Round][2]);
			SetPlayerCameraPos(playerid, BCPSpawn[Round][0] + 100, BCPSpawn[Round][1], BCPSpawn[Round][2] + 80);
			SetPlayerPos(playerid, BCPSpawn[Round][0], BCPSpawn[Round][1], BCPSpawn[Round][2]);

			Player[playerid][SpectatingType] = BASE;
			va_PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], "%sBase ~n~%s%s (ID: ~r~~h~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, BName[Round], Round, MAIN_TEXT_COLOUR);

			va_SendClientMessageToAll(-1, "%s " COL_PRIM "is spectating {FFFFFF}base" COL_PRIM ": {FFFFFF}%s (ID: %d)", Player[playerid][Name], BName[Round], Round);
		}
		case 2: // Arena
		{
			SetPlayerCameraLookAt(playerid, ACPSpawn[Round][0], ACPSpawn[Round][1], ACPSpawn[Round][2]);
			SetPlayerCameraPos(playerid, ACPSpawn[Round][0] + 100, ACPSpawn[Round][1], ACPSpawn[Round][2] + 80);
			SetPlayerPos(playerid, ACPSpawn[Round][0], ACPSpawn[Round][1], ACPSpawn[Round][2]);
			SetPlayerInterior(playerid, AInterior[Round]);

			Player[playerid][SpectatingType] = ARENA;
			va_PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], "%sArena ~n~%s%s (ID: ~r~~h~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, AName[Round], Round, MAIN_TEXT_COLOUR);

			va_SendClientMessageToAll(-1, "%s " COL_PRIM "is spectating {FFFFFF}arena" COL_PRIM ": {FFFFFF}%s (ID: %d)", Player[playerid][Name], AName[Round], Round);
		}
	}
	SendClientMessage(playerid, -1, "Cycle through maps with ~k~~PED_FIREWEAPON~ & ~k~~PED_LOCK_TARGET~. Quit this with /specoff. Press the ~k~~PED_JUMPING~ key to spawn in CP.");
	Player[playerid][Spectating] = true;

	return 1;
}
