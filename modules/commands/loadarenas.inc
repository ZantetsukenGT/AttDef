#if defined _attdef_cmd_loadarenas
	#endinput
#endif
#define _attdef_cmd_loadarenas

/*YCMD: loadarenas(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "load another set of arena from the database.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use this command while round is active.");
	new arenaset = 0;
	if (sscanf(params, "d", arenaset))
	{
		SendUsageMessage(playerid, "/loadarenas [arena set id]");
		SendClientMessage(playerid, -1, "Available arena set IDs:");
		SendClientMessage(playerid, -1, "0 = attdef arenas");
		return SendClientMessage(playerid, -1, "1 = underground-multiplayer arenas");
	}
	if (arenaset < 0 || arenaset > 1)
	{
		SendErrorMessage(playerid, "Invalid arena set ID.");
		SendUsageMessage(playerid, "/loadarenas [arena set id]");
		SendClientMessage(playerid, -1, "Available arena set IDs:");
		SendClientMessage(playerid, -1, "0 = attdef arenas");
		return SendClientMessage(playerid, -1, "1 = underground-multiplayer arenas");
	}
	CurrentArenaSet[0] = EOS;
	switch (arenaset)
	{
		case 0: strcat(CurrentArenaSet, "Arenas");
		case 1: strcat(CurrentArenaSet, "UGMPArenas");
	}
	DB_FreeResultSet(DB_ExecuteQuery(sqliteconnection, va_return("UPDATE `Configs` SET `Value`='%q' WHERE `Option`='CurrentArenaSet'", CurrentArenaSet)));
	LoadArenas();
	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has loaded arena set ID: {FFFFFF}%d | %s", Player[playerid][Name], arenaset, CurrentArenaSet));
}*/
