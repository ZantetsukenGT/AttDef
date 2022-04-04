#if defined _attdef_cmd_cr
	#endinput
#endif
#define _attdef_cmd_cr

YCMD: cr(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "set the current round of the current match.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/cr [Current Round]");

	new Value = strval(params);
	if (Value > TotalRounds || Value < 0)
		return SendErrorMessage(playerid, "Invalid current round.");

	CurrentRound = Value;

	UpdateRoundsPlayedTextDraw();

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has changed the current round to: {FFFFFF}%d", Player[playerid][Name], CurrentRound);
	return SendClientMessageToAll(-1, iString);
}
