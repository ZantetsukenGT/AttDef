#if defined _attdef_cmd_maxping
	#endinput
#endif
#define _attdef_cmd_maxping

YCMD: maxping(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "set maximum ping limit.");
	new iPacket;
	if (sscanf(params, "i", iPacket))
		return SendUsageMessage(playerid, "/maxping [Maximum Ping]");

	if (iPacket <= 0 || iPacket > 500)
		return SendErrorMessage(playerid, "Ping limit can be between 0 and 500 maximum.");

	Max_Ping = iPacket;

	new iString[144];
	format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Maximum Ping'", Max_Ping);
	db_free_result(db_query(sqliteconnection, iString));

	LogAdminCommand("maxping", playerid, INVALID_PLAYER_ID);

	format(iString, sizeof(iString), "%s " COL_PRIM "has changed {FFFFFF}maximum ping " COL_PRIM "limit to: {FFFFFF}%d", Player[playerid][Name], iPacket);
	return SendClientMessageToAll(-1, iString);
}
