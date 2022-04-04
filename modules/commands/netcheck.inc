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
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/netcheck [Player ID]");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player is not connected.");

	new iString[130], query[130];
	format(query, sizeof(query), "UPDATE Players SET NetCheck = %d WHERE Name = '%q'", !Player[pID][NetCheck], Player[pID][Name]);
	db_free_result(db_query(sqliteconnection, query));

	LogAdminCommand("netcheck", playerid, pID);

	format(
		iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has %s Net-Check on: {FFFFFF}%s", Player[playerid][Name], Player[pID][NetCheck] ? "disabled" : "enabled",
		Player[pID][Name]);
	Player[pID][NetCheck] = Player[pID][FPSCheck] = Player[pID][PingCheck] = Player[pID][PLCheck] = !Player[pID][NetCheck];
	return SendClientMessageToAll(-1, iString);
}
