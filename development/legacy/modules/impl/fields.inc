#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_fields
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_fields
	#endinput
#endif
#define _attdef_impl_fields

/*
	Fields related: bases, arenas... etc
*/

LoadBases()
{
	new iString[64];
	new DBResult: res = DB_ExecuteQuery(sqliteconnection, va_return("SELECT * FROM `%q` ORDER BY ID ASC", CurrentBaseSet));

	Iter_Clear(CurrentBases);
	do {
		DB_GetFieldStringByName(res, "ID", iString, sizeof(iString));
		new i = strval(iString);
		Iter_Add(CurrentBases, i);

		DB_GetFieldStringByName(res, "Interior", iString, sizeof(iString));
		BInterior[i] = strval(iString);

		DB_GetFieldStringByName(res, "AttSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", BAttackerSpawn[i][0], BAttackerSpawn[i][1], BAttackerSpawn[i][2]);

		DB_GetFieldStringByName(res, "DefSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", BDefenderSpawn[i][0], BDefenderSpawn[i][1], BDefenderSpawn[i][2]);

		DB_GetFieldStringByName(res, "CPSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);

		DB_GetFieldStringByName(res, "Name", BName[i], MAX_MAP_FIELD_NAME);
	}
	while (DB_SelectNextRow(res));

	DB_FreeResultSet(res);

	ForgetPlayedBases();
	new totalBases = Iter_Count(CurrentBases);
	va_SendClientMessageToAll(-1, COL_PRIM "Bases Loaded: {FFFFFF}%d " COL_PRIM "| Current base set: {FFFFFF}%s", totalBases, CurrentBaseSet);
	printf("Bases Loaded: %d (from table: %s)", totalBases, CurrentBaseSet);
}

LoadArenas()
{
	new iString[64];
	new DBResult: res = DB_ExecuteQuery(sqliteconnection, va_return("SELECT * FROM `%q` ORDER BY ID ASC", CurrentArenaSet));

	Iter_Clear(CurrentArenas);
	do {
		DB_GetFieldStringByName(res, "ID", iString, sizeof(iString));
		new i = strval(iString);
		Iter_Add(CurrentArenas, i);

		DB_GetFieldStringByName(res, "Interior", iString, sizeof(iString));
		AInterior[i] = strval(iString);

		DB_GetFieldStringByName(res, "AttSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", AAttackerSpawn[i][0], AAttackerSpawn[i][1], AAttackerSpawn[i][2]);

		DB_GetFieldStringByName(res, "DefSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", ADefenderSpawn[i][0], ADefenderSpawn[i][1], ADefenderSpawn[i][2]);

		DB_GetFieldStringByName(res, "CPSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", ACPSpawn[i][0], ACPSpawn[i][1], ACPSpawn[i][2]);

		DB_GetFieldStringByName(res, "Max", iString, sizeof(iString));
		sscanf(iString, "p<,>ff", AMax[i][0], AMax[i][1]);

		DB_GetFieldStringByName(res, "Min", iString, sizeof(iString));
		sscanf(iString, "p<,>ff", AMin[i][0], AMin[i][1]);

		DB_GetFieldStringByName(res, "Name", AName[i], MAX_MAP_FIELD_NAME);
	}
	while (DB_SelectNextRow(res));

	DB_FreeResultSet(res);

	ForgetPlayedArenas();
	new totalArenas = Iter_Count(CurrentArenas);
	va_SendClientMessageToAll(-1, COL_PRIM "Arenas Loaded: {FFFFFF}%d " COL_PRIM "| Current arena set: {FFFFFF}%s", totalArenas, CurrentArenaSet);
	printf("Arenas Loaded: %d (from table: %s)", totalArenas, CurrentArenaSet);
}

LoadDMs()
{
	new iString[64];
	new DBResult: res = DB_ExecuteQuery(sqliteconnection, "SELECT * FROM DMs ORDER BY ID ASC");

	Iter_Clear(CurrentDMs);
	do {
		DB_GetFieldStringByName(res, "ID", iString, sizeof(iString));
		new i = strval(iString);
		Iter_Add(CurrentDMs, i);

		DB_GetFieldStringByName(res, "Interior", iString, sizeof(iString));
		DMInterior[i] = strval(iString);

		for (new j = 0; j < 3; ++j)
		{
			new fieldName[10], weapon[128];
			format(fieldName, sizeof(fieldName), "Wep%d", j + 1);
			DB_GetFieldStringByName(res, fieldName, weapon, sizeof(weapon));
			DMWeapons[i][j] = strval(weapon);
		}

		DB_GetFieldStringByName(res, "Spawn", iString, sizeof(iString));
		sscanf(iString, "p<,>ffff", DMSpawn[i][0], DMSpawn[i][1], DMSpawn[i][2], DMSpawn[i][3]);
	}
	while (DB_SelectNextRow(res));

	DB_FreeResultSet(res);

	new totalDMs = Iter_Count(CurrentDMs);
	printf("DMs Loaded: %d", totalDMs);
}
