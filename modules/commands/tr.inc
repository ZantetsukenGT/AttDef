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
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/tr [Total Rounds]");

	new Value = strval(params);
	if (Value < CurrentRound || Value < 1 || Value > 100)
		return SendErrorMessage(playerid, "Invalid total rounds.");

	TotalRounds = Value;
	UpdateRoundsPlayedTextDraw();

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has changed the total rounds to: {FFFFFF}%d", Player[playerid][Name], TotalRounds);
	return SendClientMessageToAll(-1, iString);
}
