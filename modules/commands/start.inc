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

	new Params[2][64];
	sscanf(params, "s[64]S( )[64]", Params[0], Params[1]);

	if (isnull(Params[0]) || IsNumeric(Params[0]))
		return SendUsageMessage(playerid, "/start [base | arena | rc | last] [ID]");

	new iString[144];

	switch (YHash(Params[0], false))
	{
		case _I<rc>:
		{
			AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
			PreStartRoundTimer = SetPreciseTimer("OnRCStart", 2000, false);

			format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has started RC Battlefield round (Interior: 72)", Player[playerid][Name]);
		}
		case _I<last>:
		{
			if (ServerLastPlayed == -1 && ServerLastPlayedType == -1)
				return SendErrorMessage(playerid, "No bases/arenas have been played lately!");

			if (ServerLastPlayedType == 1)
			{
				new BaseID = ServerLastPlayed;

				if (BaseID > MAX_BASES)
					return SendErrorMessage(playerid, "The last played base does not exist.");
				if (!BExist[BaseID])
					return SendErrorMessage(playerid, "The last played base does not exist.");

				GameType	   = BASE;

				AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
				PreStartRoundTimer = SetPreciseTimer("OnBaseStart", 2000, false, "i", BaseID);

				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has started the last played Base: {FFFFFF}%s (ID: %d)", Player[playerid][Name], BName[BaseID], BaseID);
			}
			else if (ServerLastPlayedType == 0)
			{
				new ArenaID = ServerLastPlayed;

				if (ArenaID > MAX_ARENAS)
					return SendErrorMessage(playerid, "The last played arena does not exist.");
				if (!AExist[ArenaID])
					return SendErrorMessage(playerid, "The last played arena does not exist.");

				GameType	   = ARENA;

				AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
				PreStartRoundTimer = SetPreciseTimer("OnArenaStart", 2000, false, "i", ArenaID);

				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has started the last played Arena: {FFFFFF}%s (ID: %d)", Player[playerid][Name], AName[ArenaID], ArenaID);
			}
		}
		case _I<base>:
		{
			if (!IsNumeric(Params[1]))
				return SendErrorMessage(playerid, "Base/Arena ID can only be numerical.");
			new BaseID = strval(Params[1]);

			if (BaseID > MAX_BASES)
				return SendErrorMessage(playerid, "That base does not exist.");
			if (!BExist[BaseID])
				return SendErrorMessage(playerid, "That base does not exist.");

			GameType	   = BASE;

			AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
			PreStartRoundTimer = SetPreciseTimer("OnBaseStart", 2000, false, "i", BaseID);

			format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has started Base: {FFFFFF}%s (ID: %d)", Player[playerid][Name], BName[BaseID], BaseID);
		}
		case _I<arena>:
		{
			if (!IsNumeric(Params[1]))
				return SendErrorMessage(playerid, "Base/Arena ID can only be numerical.");

			new ArenaID = strval(Params[1]);

			if (ArenaID > MAX_ARENAS)
				return SendErrorMessage(playerid, "That arena does not exist.");
			if (!AExist[ArenaID])
				return SendErrorMessage(playerid, "That arena does not exist.");

			GameType	   = ARENA;

			AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
			PreStartRoundTimer = SetPreciseTimer("OnArenaStart", 2000, false, "i", ArenaID);

			format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has started Arena: {FFFFFF}%s (ID: %d)", Player[playerid][Name], AName[ArenaID], ArenaID);
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
	return SendClientMessageToAll(-1, iString);
}
