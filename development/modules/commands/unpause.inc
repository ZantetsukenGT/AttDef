#if defined _attdef_cmd_unpause
	#endinput
#endif
#define _attdef_cmd_unpause

YCMD: unpause(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "resume the currently active round.");
	if (RoundUnpausing)
		return SendErrorMessage(playerid, "Round is already unpausing.");
	if (!RoundPaused)
		return SendErrorMessage(playerid, "Round is not paused.");

	PauseCountdown = 4;
	UnpauseRound();

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has {FFFFFF}unpaused " COL_PRIM "the current round.", Player[playerid][Name]);
}
