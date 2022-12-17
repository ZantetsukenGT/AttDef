#if defined _attdef_cmd_loadarenas
	#endinput
#endif
#define _attdef_cmd_loadarenas

YCMD: loadarenas(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "load another set of arenas from the database.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use this command while round is active.");
	new arenaset = 0;
	if (sscanf(params, "d", arenaset) || arenaset < 0 || arenaset > 1)
	{
		SendUsageMessage(playerid, "/loadarenas [arena set id]");
		SendClientMessage(playerid, -1, "Available arena set IDs:");
		SendClientMessage(playerid, -1, "0 = AttDef Arenas (original complete set)");
		return SendClientMessage(playerid, -1, "1 = UGMP Arenas");
	}
	CurrentArenaSet[0] = EOS;
	switch (arenaset)
	{
		case 0: strcat(CurrentArenaSet, "Arenas");
		case 1: strcat(CurrentArenaSet, "UGMPArenas");
	}
	db_free_result(db_query(sqliteconnection, va_return("UPDATE `Configs` SET `Value`='%q' WHERE `Option`='CurrentArenaSet'", CurrentArenaSet)));
	LoadArenas();
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has loaded arena set ID: {FFFFFF}%d | %s", Player[playerid][Name], arenaset, CurrentArenaSet);
}
