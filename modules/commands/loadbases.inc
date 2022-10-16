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
	if (sscanf(params, "d", baseset) || baseset < 0 || baseset > 7)
	{
		SendUsageMessage(playerid, "/loadbases [base set id]");
		SendClientMessage(playerid, -1, "Available base set IDs:");
		SendClientMessage(playerid, -1, "0 = AttDef Bases (original complete set)");
		SendClientMessage(playerid, -1, "1 = AttDef Bases For Tournaments (Volk Edition - No Garage Bases)");
		SendClientMessage(playerid, -1, "2 = BattleGrounds Bases");
		SendClientMessage(playerid, -1, "3 = cYs clan's New Bulletproof Bases");
		SendClientMessage(playerid, -1, "4 = ESL Bases");
		SendClientMessage(playerid, -1, "5 = New Bulletproof Bases (original complete set)");
		SendClientMessage(playerid, -1, "6 = Old Bulletproof Bases (original complete set)");
		return SendClientMessage(playerid, -1, "7 = Wargrounds bases (uL server)");
	}
	CurrentBaseSet[0] = EOS;
	switch (baseset)
	{
		case 0: strcat(CurrentBaseSet, "AttdefBases");
		case 1: strcat(CurrentBaseSet, "AttdefBasesForTournaments");
		case 2: strcat(CurrentBaseSet, "BattleGrounds");
		case 3: strcat(CurrentBaseSet, "cYsBulletproofBases");
		case 4: strcat(CurrentBaseSet, "ESL");
		case 5: strcat(CurrentBaseSet, "NewBulletproofBases");
		case 6: strcat(CurrentBaseSet, "OldBulletproofBases");
		case 7: strcat(CurrentBaseSet, "Wargrounds");
	}
	db_free_result(db_query(sqliteconnection, va_return("UPDATE `Configs` SET `Value`='%q' WHERE `Option`='CurrentBaseSet'", CurrentBaseSet)));
	LoadBases();
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has loaded base set ID: {FFFFFF}%d | %s", Player[playerid][Name], baseset, CurrentBaseSet);
}
