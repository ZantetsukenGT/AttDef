#if defined _attdef_cmd_cptime
	#endinput
#endif
#define _attdef_cmd_cptime

YCMD: cptime(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "set the time needed to capture a checkpoint.");
	new cpTime;
	if (sscanf(params, "i", cpTime))
		return SendUsageMessage(playerid, "/cptime [Seconds (20 - 40)]");

	cpTime = clamp(cpTime, 20, 40);

	ConfigCPTime  = cpTime;
	CurrentCPTime = ConfigCPTime + 1;

	new iString[144];
	format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'CP Time'", cpTime);
	db_free_result(db_query(sqliteconnection, iString));

	LogAdminCommand("cptime", playerid, INVALID_PLAYER_ID);

	format(iString, sizeof(iString), "%s " COL_PRIM "has changed the {FFFFFF}CP time " COL_PRIM "to: {FFFFFF}%d seconds", Player[playerid][Name], cpTime);
	return SendClientMessageToAll(-1, iString);
}
