#if defined _attdef_cmd_randomint
	#endinput
#endif
#define _attdef_cmd_randomint

YCMD: randomint(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "start a random round in an interior.");
	if (Current != -1)
		return SendErrorMessage(playerid, "A round is in progress, please wait for it to end.");
	if (!AllowStartBase)
		return SendErrorMessage(playerid, "Please wait.");

	if (isnull(params) || IsNumeric(params))
		return SendUsageMessage(playerid, "/randomint [base | arena]");

	switch (YHash(params, false))
	{
		case _I<base>:
		{
			AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
			new BaseID	   = DetermineRandomRound(1, false, BASE);
			if (BaseID == -1)
			{
				AllowStartBase = true;
				SendClientMessageToAll(-1, COL_PRIM "Couldn't start a {FFFFFF}base " COL_PRIM "because the current {FFFFFF}base set " COL_PRIM "doesn't have any.");
				return 1;
			}
			else if (BaseID == -2)
			{
				AllowStartBase = true;
				SendClientMessageToAll(-1, COL_PRIM "Couldn't start a {FFFFFF}base " COL_PRIM "with the defined criteria. {FFFFFF}(perhaps the current base set doesn't have interior bases)");
				return 1;
			}
			PreStartRoundTimer = SetTimerEx("OnBaseStart", 4000, false, "i", BaseID);

			GameType = BASE;

			new iString[144];
			format(iString, sizeof(iString), "%s " COL_PRIM "has randomly started interior Base: {FFFFFF}%s (ID: %d)", Player[playerid][Name], BName[BaseID], BaseID);
			SendClientMessageToAll(-1, iString);
		}
		case _I<arena>:
		{
			AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
			new ArenaID	   = DetermineRandomRound(1, false, ARENA);
			if (ArenaID == -1)
			{
				AllowStartBase = true;
				SendClientMessageToAll(-1, COL_PRIM "Couldn't start an {FFFFFF}arena " COL_PRIM "because the current {FFFFFF}arena set " COL_PRIM "doesn't have any.");
				return 1;
			}
			else if (ArenaID == -2)
			{
				AllowStartBase = true;
				SendClientMessageToAll(-1, COL_PRIM "Couldn't start an {FFFFFF}arena " COL_PRIM "with the defined criteria. {FFFFFF}(perhaps the current arena set doesn't have interior arenas)");
				return 1;
			}
			PreStartRoundTimer = SetTimerEx("OnArenaStart", 4000, false, "i", ArenaID);

			GameType = ARENA;

			new iString[144];
			format(iString, sizeof(iString), "%s " COL_PRIM "has randomly started interior Arena: {FFFFFF}%s (ID: %d)", Player[playerid][Name], AName[ArenaID], ArenaID);
			SendClientMessageToAll(-1, iString);
		}
		default: return SendUsageMessage(playerid, "/randomint [base | arena]");
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
