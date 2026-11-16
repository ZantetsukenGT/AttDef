#if defined _attdef_cmd_cr
	#endinput
#endif
#define _attdef_cmd_cr

YCMD: cr(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "set the current round of the current match.");
	new Value;
	if (sscanf(params, "i", Value))
		return SendUsageMessage(playerid, "/cr [Current Round]");

	if (Value > TotalRounds || Value < 0)
		return SendErrorMessage(playerid, "Invalid current round.");

	CurrentRound = Value;

	UpdateRoundsPlayedTextDraw();

	return va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has changed the current round to: {FFFFFF}%d", Player[playerid][Name], CurrentRound);
}
