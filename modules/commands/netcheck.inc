#if defined _attdef_cmd_netcheck
	#endinput
#endif
#define _attdef_cmd_netcheck

YCMD: netcheck(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "toggle net status check on a specific player.");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/netcheck [Player Name/ID]");

	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player is not connected.");

	db_free_result(db_query(sqliteconnection, va_return("UPDATE Players SET NetCheck = %d WHERE Name = '%q'", !Player[pID][NetCheck], Player[pID][Name])));

	LogAdminCommand("netcheck", playerid, pID);

	Player[pID][NetCheck] = Player[pID][FPSCheck] = Player[pID][PingCheck] = Player[pID][PLCheck] = !Player[pID][NetCheck];
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has %s {FFFFFF}Net-Check " COL_PRIM "on {FFFFFF}%s", Player[playerid][Name], Player[pID][NetCheck] ? "{66FF66}enabled" : "{FF6666}disabled",
		Player[pID][Name]);
}
