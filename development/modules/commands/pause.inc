#if defined _attdef_cmd_pause
	#endinput
#endif
#define _attdef_cmd_pause

YCMD: pause(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "pause the currently active round.");
	return ToggleRoundPause(playerid);
}

ToggleRoundPause(playerid)
{
	if (Current == -1)
		return SendErrorMessage(playerid, "There is no active round.");
	if (RoundUnpausing)
		return SendErrorMessage(playerid, "Round is unpausing, please wait.");

	new iString[144];
	if (RoundPaused)
	{
		if (GetTickCount() - PausePressed < 1700)
			return SendErrorMessage(playerid, "Please Wait.");

		PauseCountdown = 4;
		UnpauseRound();

		format(iString, sizeof(iString), "%s " COL_PRIM "has {FFFFFF}unpaused " COL_PRIM "the current round.", Player[playerid][Name]);
		return SendClientMessageToAll(-1, iString);
	}

	PausePressed = GetTickCount();
	PauseRound();

	format(iString, sizeof(iString), "%s " COL_PRIM "has {FFFFFF}paused " COL_PRIM "the current round.", Player[playerid][Name]);
	return SendClientMessageToAll(-1, iString);
}
