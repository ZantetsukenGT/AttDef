#if defined _attdef_cmd_mainspawn
	#endinput
#endif
#define _attdef_cmd_mainspawn

YCMD: mainspawn(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 4 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "change server main spawn position.");
	GetPlayerPos(playerid, MainSpawn[0], MainSpawn[1], MainSpawn[2]);
	GetPlayerFacingAngle(playerid, MainSpawn[3]);
	MainInterior = GetPlayerInterior(playerid);

	new iString[128], query[256];
	format(iString, sizeof(iString), "%.0f,%.0f,%.0f,%.0f,%d", MainSpawn[0], MainSpawn[1], MainSpawn[2], MainSpawn[3], MainInterior);
	format(query, sizeof(query), "UPDATE Configs SET Value = '%q' WHERE Option = 'Main Spawn'", iString);
	db_free_result(db_query(sqliteconnection, query));

	LogAdminCommand("mainspawn", playerid, INVALID_PLAYER_ID);

	format(iString, sizeof(iString), "%s " COL_PRIM "has changed the {FFFFFF}main spawn " COL_PRIM "location.", Player[playerid][Name]);
	return SendClientMessageToAll(-1, iString);
}
