#if defined _attdef_cmd_rb
	#endinput
#endif
#define _attdef_cmd_rb

YCMD: rb(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a random base.");
	if (Current != -1)
		return SendErrorMessage(playerid, "A round is in progress, please wait for it to end.");
	if (!AllowStartBase)
		return SendErrorMessage(playerid, "Please wait.");

	DoRandomBase(playerid);
	return 1;
}

DoRandomBase(playerid)
{
	AllowStartBase = false; // Make sure other player or you yourself is not able to start base on top of another base.
	new BaseID	   = DetermineRandomRound(2, false, BASE);
	if (BaseID == -1)
	{
		AllowStartBase = true;
		SendClientMessageToAll(-1, COL_PRIM "Couldn't start a {FFFFFF}base " COL_PRIM "because the current {FFFFFF}base set " COL_PRIM "doesn't have any.");
		return;
	}
	else if (BaseID == -2)
	{
		AllowStartBase = true;
		SendClientMessageToAll(-1, COL_PRIM "Couldn't start a {FFFFFF}base " COL_PRIM "with the defined criteria. {FFFFFF}(perhaps the current base set doesn't have exterior bases)");
		return;
	}
	PreStartRoundTimer = SetTimerEx("OnBaseStart", 4000, false, "i", BaseID);

	new iString[144];
	format(iString, sizeof(iString), "%s " COL_PRIM "has randomly started Base: {FFFFFF}%s (ID: %d)", Player[playerid][Name], BName[BaseID], BaseID);
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
