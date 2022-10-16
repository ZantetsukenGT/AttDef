#if defined _attdef_cmd_defaultskins
	#endinput
#endif
#define _attdef_cmd_defaultskins

YCMD: defaultskins(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "reset team skins to default.");

	new iString[128];
	Skin[ATTACKER] = 170;
	format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Attacker Skin'", 170);
	db_free_result(db_query(sqliteconnection, iString));

	Skin[DEFENDER] = 177;
	format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Defender Skin'", 177);
	db_free_result(db_query(sqliteconnection, iString));

	Skin[REFEREE] = 51;
	format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Referee Skin'", 51);
	db_free_result(db_query(sqliteconnection, iString));

	foreach (new i : Player)
	{
		if (Player[i][Team] == ATTACKER)
			SetPlayerSkin(i, Skin[ATTACKER]);
		if (Player[i][Team] == DEFENDER)
			SetPlayerSkin(i, Skin[DEFENDER]);
		if (Player[i][Team] == REFEREE)
			SetPlayerSkin(i, Skin[REFEREE]);
	}

	LogAdminCommand("defaultskins", playerid, INVALID_PLAYER_ID);

	format(iString, sizeof(iString), "%s " COL_PRIM "has changed {FFFFFF}skins " COL_PRIM "to {FFFFFF}default" COL_PRIM ".", Player[playerid][Name]);
	return SendClientMessageToAll(-1, iString);
}
