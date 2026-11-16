#if defined _attdef_cmd_ra
	#endinput
#endif
#define _attdef_cmd_ra

YCMD: ra(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a random arena.");
	if (Current != -1)
		return SendErrorMessage(playerid, "A round is in progress, please wait for it to end.");
	if (!AllowStartBase)
		return SendErrorMessage(playerid, "Please wait.");

	DoRandomArena(playerid);
	return 1;
}

DoRandomArena(playerid)
{
	AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
	new ArenaID	   = DetermineRandomRound(2, false, ARENA);
	if (ArenaID == -1)
	{
		AllowStartBase = true;
		SendClientMessageToAll(-1, COL_PRIM "Couldn't start an {FFFFFF}arena " COL_PRIM "because the current {FFFFFF}arena set " COL_PRIM "doesn't have any.");
		return;
	}
	else if (ArenaID == -2)
	{
		AllowStartBase = true;
		SendClientMessageToAll(-1, COL_PRIM "Couldn't start an {FFFFFF}arena " COL_PRIM "with the defined criteria. {FFFFFF}(perhaps the current arena set doesn't have exterior arenas)");
		return;
	}
	
	PreStartRoundTimer = SetTimerEx("OnArenaStart", 4000, false, "i", ArenaID);

	new iString[144];
	format(iString, sizeof(iString), "%s " COL_PRIM "has randomly started Arena: {FFFFFF}%s (ID: %d)", Player[playerid][Name], AName[ArenaID], ArenaID);
	SendClientMessageToAll(-1, iString);

	foreach (new i : Player)
	{
		if (CanPlay(i))
		{
			TogglePlayerControllable(i, 0); // Pause all the players.
			Player[i][ToAddInRound] = true;
		}
	}
}
