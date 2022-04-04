#if defined _attdef_cmd_roundtime
	#endinput
#endif
#define _attdef_cmd_roundtime

YCMD: roundtime(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "set the round time.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use the command while round is on.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/roundtime [Mints (1 - 30)]");

	new rTime = strval(params);
	if (rTime < 1 || rTime > 30)
		return SendErrorMessage(playerid, "Round time can't be lower than 1 or higher than 30 mints.");

	LogAdminCommand("roundtime", playerid, INVALID_PLAYER_ID);

	ConfigRoundTime = rTime;

	new iString[128];
	format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Round Time'", rTime);
	db_free_result(db_query(sqliteconnection, iString));

	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has changed the round time to: {FFFFFF}%d mints", Player[playerid][Name], rTime);
	return SendClientMessageToAll(-1, iString);
}
