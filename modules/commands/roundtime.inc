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
	new rTime;
	if (sscanf(params, "i", rTime))
		return SendUsageMessage(playerid, va_return("/roundtime [1..30 (minutes), " COL_PRIM "current: " COL_USAGE "%d{FFFFFF}]", ConfigRoundTime));

	if (rTime < 1 || rTime > 30)
		return SendErrorMessage(playerid, "Round time can't be lower than 1 or higher than 30 minutes.");

	LogAdminCommand("roundtime", playerid, INVALID_PLAYER_ID);

	new oldValue = ConfigRoundTime;
	ConfigRoundTime = rTime;

	db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'Round Time'", rTime)));
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has changed {FFFFFF}the round time " COL_PRIM "to: {FFFFFF}%d minutes" COL_PRIM ", previous setting: {FFFFFF}%d minutes" COL_PRIM ".", Player[playerid][Name], rTime, oldValue);
}
