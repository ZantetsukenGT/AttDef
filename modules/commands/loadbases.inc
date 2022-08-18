#if defined _attdef_cmd_loadbases
	#endinput
#endif
#define _attdef_cmd_loadbases

YCMD: loadbases(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "load another set of bases from the database.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use this command while round is active.");
	new baseset = 0;
	if (sscanf(params, "d", baseset))
	{
		SendUsageMessage(playerid, "/loadbases [base set id]");
		SendClientMessage(playerid, -1, "Available base set IDs:");
		SendClientMessage(playerid, -1, "0 = new bulletproof bases (includes cYs Bases)");
		SendClientMessage(playerid, -1, "1 = old bulletproof bases (includes some oldschool bases)");
		SendClientMessage(playerid, -1, "2 = attdef bases (mainly TeK bases)");
		SendClientMessage(playerid, -1, "3 = Wargrounds bases (uL server)");
		SendClientMessage(playerid, -1, "4 = ESL bases");
		return SendClientMessage(playerid, -1, "5 = BattleGrounds bases");
	}
	if (baseset < 0 || baseset > 5)
	{
		SendErrorMessage(playerid, "Invalid base set ID.");
		SendClientMessage(playerid, -1, "Available base set IDs:");
		SendClientMessage(playerid, -1, "0 = new bulletproof bases (includes cYs Bases)");
		SendClientMessage(playerid, -1, "1 = old bulletproof bases (includes some oldschool bases)");
		SendClientMessage(playerid, -1, "2 = attdef bases (mainly TeK bases)");
		SendClientMessage(playerid, -1, "3 = Wargrounds bases (uL server)");
		SendClientMessage(playerid, -1, "4 = ESL bases");
		return SendClientMessage(playerid, -1, "5 = BattleGrounds bases");
	}
	CurrentBaseSet[0] = EOS;
	switch (baseset)
	{
		case 0: strcat(CurrentBaseSet, "NewBulletproofBases");
		case 1: strcat(CurrentBaseSet, "OldBulletproofBases");
		case 2: strcat(CurrentBaseSet, "AttdefBases");
		case 3: strcat(CurrentBaseSet, "Wargrounds");
		case 4: strcat(CurrentBaseSet, "ESL");
		case 5: strcat(CurrentBaseSet, "BattleGrounds");
	}
	db_free_result(db_query(sqliteconnection, va_return("UPDATE `Configs` SET `Value`='%q' WHERE `Option`='CurrentBaseSet'", CurrentBaseSet)));
	LoadBases();
	if (!strcmp(CurrentBaseSet, "NewBulletproofBases"))
		return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has loaded base set ID: {FFFFFF}%d | New Bulletproof + cYs Bases", Player[playerid][Name], baseset));
	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has loaded base set ID: {FFFFFF}%d | %s", Player[playerid][Name], baseset, CurrentBaseSet));
}
