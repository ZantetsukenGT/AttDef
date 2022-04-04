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

	new Params[64], Round, CommandID, iString[256];
	if (sscanf(params, "s[64]d", Params, Round))
		return SendUsageMessage(playerid, "/view [base | arena] [Round ID]");

	switch (YHash(Params, false))
	{
		case _I<base>: CommandID = 1;
		case _I<arena>: CommandID = 2;
		default: return SendUsageMessage(playerid, "/view [base | arena] [Round ID]");
	}

	if (Player[playerid][InDM])
	{
		Player[playerid][InDM]	  = false;
		Player[playerid][DMReadd] = 0;
	}
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel. Use /rq instead.");

	if (Player[playerid][Spectating])
		StopSpectate(playerid);

	Player[playerid][SpectatingRound] = Round;
	switch (CommandID)
	{
		case 1:
		{ //base
			if (Round > MAX_BASES)
				return SendErrorMessage(playerid, "That base does not exist.");
			if (!BExist[Round])
				return SendErrorMessage(playerid, "That base does not exist.");

			SetPlayerInterior(playerid, BInterior[Round]);
			SetPlayerCameraLookAt(playerid, BCPSpawn[Round][0], BCPSpawn[Round][1], BCPSpawn[Round][2]);
			SetPlayerCameraPos(playerid, BCPSpawn[Round][0] + 100, BCPSpawn[Round][1], BCPSpawn[Round][2] + 80);
			SetPlayerPos(playerid, BCPSpawn[Round][0], BCPSpawn[Round][1], BCPSpawn[Round][2]);

			Player[playerid][SpectatingType] = BASE;
			format(iString, sizeof(iString), "%sBase ~n~%s%s (ID: ~r~~h~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, BName[Round], Round, MAIN_TEXT_COLOUR);
			PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], iString);

			format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "is spectating Base: {FFFFFF}%s (ID: %d)", Player[playerid][Name], BName[Round], Round);
		}
		case 2:
		{ // Arena
			if (Round > MAX_ARENAS)
				return SendErrorMessage(playerid, "That arena does not exist.");
			if (!AExist[Round])
				return SendErrorMessage(playerid, "That arena does not exist.");

			SetPlayerCameraLookAt(playerid, ACPSpawn[Round][0], ACPSpawn[Round][1], ACPSpawn[Round][2]);
			SetPlayerCameraPos(playerid, ACPSpawn[Round][0] + 100, ACPSpawn[Round][1], ACPSpawn[Round][2] + 80);
			SetPlayerPos(playerid, ACPSpawn[Round][0], ACPSpawn[Round][1], ACPSpawn[Round][2]);
			SetPlayerInterior(playerid, AInterior[Round]);

			Player[playerid][SpectatingType] = ARENA;
			format(iString, sizeof(iString), "%sArena ~n~%s%s (ID: ~r~~h~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, AName[Round], Round, MAIN_TEXT_COLOUR);
			PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], iString);

			format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "is spectating Arena: {FFFFFF}%s (ID: %d)", Player[playerid][Name], AName[Round], Round);
		}
	}
	SendClientMessage(playerid, -1, "Switch between rounds using LMB & RMB. Go normal mode using /specoff. Press Jump key to spawn in CP.");
	Player[playerid][Spectating] = true;

	return SendClientMessageToAll(-1, iString);
}
