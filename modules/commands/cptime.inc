#if defined _attdef_cmd_cptime
	#endinput
#endif
#define _attdef_cmd_cptime

YCMD: cptime(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "set the time needed to capture a checkpoint.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/cptime [Seconds (1 - 60)]");

	new cpTime = strval(params);
	if (cpTime < 1 || cpTime > 60)
		return SendErrorMessage(playerid, "CP time can't be lower than 1 or higher than 60 seconds.");

	ConfigCPTime  = cpTime;
	CurrentCPTime = ConfigCPTime + 1;

	new iString[144];
	format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'CP Time'", cpTime);
	db_free_result(db_query(sqliteconnection, iString));

	LogAdminCommand("cptime", playerid, INVALID_PLAYER_ID);

	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has changed the CP time to: {FFFFFF}%d seconds", Player[playerid][Name], cpTime);
	return SendClientMessageToAll(-1, iString);
}
