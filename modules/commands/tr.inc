#if defined _attdef_cmd_tr
	#endinput
#endif
#define _attdef_cmd_tr

YCMD: tr(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "set total rounds of the current match.");
	new Value;
	if (sscanf(params, "i", Value))
		return SendUsageMessage(playerid, "/tr [Total Rounds]");

	if (Value < CurrentRound || Value < 1 || Value > 100)
		return SendErrorMessage(playerid, "Invalid total rounds.");

	TotalRounds = Value;
	UpdateRoundsPlayedTextDraw();

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has changed the {FFFFFF}total rounds " COL_PRIM "to: {FFFFFF}%d", Player[playerid][Name], TotalRounds);
}
