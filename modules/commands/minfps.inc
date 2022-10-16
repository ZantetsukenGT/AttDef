#if defined _attdef_cmd_minfps
	#endinput
#endif
#define _attdef_cmd_minfps

YCMD: minfps(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "set minimum FPS limit.");
	new iPacket;
	if (sscanf(params, "i", iPacket))
		return SendUsageMessage(playerid, "/minfps [Minimum FPS]");

	if (iPacket < 20 || iPacket > 90)
		return SendErrorMessage(playerid, "FPS limit can be between 20 and 90 maximum.");

	Min_FPS = iPacket;

	new iString[144];
	format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Minimum FPS'", Min_FPS);
	db_free_result(db_query(sqliteconnection, iString));

	LogAdminCommand("minfps", playerid, INVALID_PLAYER_ID);

	format(iString, sizeof(iString), "%s " COL_PRIM "has changed {FFFFFF}minimum FPS " COL_PRIM "limit to: {FFFFFF}%d", Player[playerid][Name], iPacket);
	return SendClientMessageToAll(-1, iString);
}
