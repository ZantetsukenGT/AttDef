#if defined _attdef_cmd_start
	#endinput
#endif
#define _attdef_cmd_start

YCMD: start(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "start a round.");
	if (Current != -1)
		return SendErrorMessage(playerid, "A round is in progress, please wait for it to end.");
	if (!AllowStartBase)
		return SendErrorMessage(playerid, "Please wait.");

	new mapID, mapType[6];
	if (sscanf(params, "s[*]I(-1)", sizeof(mapType), mapType, mapID))
		return SendUsageMessage(playerid, "/start [base | arena | rc | last] [ID]");

	switch (YHash(mapType, false))
	{
		case _I<rc>:
		{
			AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
			PreStartRoundTimer = SetTimer("OnRCStart", 2000, false);

			va_SendClientMessageToAll(-1, "%s " COL_PRIM "has started {FFFFFF}RC Battlefield " COL_PRIM "round (Interior: 72)", Player[playerid][Name]);
		}
		case _I<last>:
		{
			if (ServerLastPlayed == -1 && ServerLastPlayedType == -1)
				return SendErrorMessage(playerid, "No bases/arenas have been played lately!");

			if (ServerLastPlayedType == 1)
			{
				new BaseID = ServerLastPlayed;

				if (!Iter_Contains(CurrentBases, BaseID))
					return SendErrorMessage(playerid, "The last played base does not exist.");

				GameType	   = BASE;

				AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
				PreStartRoundTimer = SetTimerEx("OnBaseStart", 2000, false, "i", BaseID);

				va_SendClientMessageToAll(-1, "%s " COL_PRIM "has started the {FFFFFF}last played base" COL_PRIM ": {FFFFFF}%s (ID: %d)", Player[playerid][Name], BName[BaseID], BaseID);
			}
			else if (ServerLastPlayedType == 0)
			{
				new ArenaID = ServerLastPlayed;

				if (!Iter_Contains(CurrentArenas, ArenaID))
					return SendErrorMessage(playerid, "The last played arena does not exist.");

				GameType	   = ARENA;

				AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
				PreStartRoundTimer = SetTimerEx("OnArenaStart", 2000, false, "i", ArenaID);

				va_SendClientMessageToAll(-1, "%s " COL_PRIM "has started the {FFFFFF}last played arena" COL_PRIM ": {FFFFFF}%s (ID: %d)", Player[playerid][Name], AName[ArenaID], ArenaID);
			}
		}
		case _I<base>:
		{
			if (mapID < 0)
				return SendUsageMessage(playerid, "/start base [ID]");
			if (!Iter_Contains(CurrentBases, mapID))
				return SendErrorMessage(playerid, "That base does not exist.");

			GameType	   = BASE;

			AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
			PreStartRoundTimer = SetTimerEx("OnBaseStart", 2000, false, "i", mapID);

			va_SendClientMessageToAll(-1, "%s " COL_PRIM "has started Base: {FFFFFF}%s (ID: %d)", Player[playerid][Name], BName[mapID], mapID);
		}
		case _I<arena>:
		{
			if (mapID < 0)
				return SendUsageMessage(playerid, "/start arena [ID]");
			if (!Iter_Contains(CurrentArenas, mapID))
				return SendErrorMessage(playerid, "That arena does not exist.");

			GameType	   = ARENA;

			AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
			PreStartRoundTimer = SetTimerEx("OnArenaStart", 2000, false, "i", mapID);

			va_SendClientMessageToAll(-1, "%s " COL_PRIM "has started Arena: {FFFFFF}%s (ID: %d)", Player[playerid][Name], AName[mapID], mapID);
		}
		default: return SendUsageMessage(playerid, "/start [base | arena | rc | last] [ID]");
	}

	foreach (new i : Player)
	{
		if (CanPlay(i))
		{
			TogglePlayerControllable(i, 0); // Pause all the players.
			Player[i][ToAddInRound] = true;
		}
	}
	return 1;
}
