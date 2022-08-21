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

/*FindFreeArenaSlot()
{
	for (new i = 1; i < MAX_ARENAS; i++)
		if (!AExist[i])
			return i;

	return TotalArenas + 1;
}*/

FindFreeBaseSlot()
{
	for (new i = 1; i < MAX_BASES; i++)
		if (!BExist[i])
			return i;

	return TotalBases + 1;
}

LoadBases()
{
	TotalBases = 0;
	new iString[64];

	new DBResult: res = db_query(sqliteconnection, va_return("SELECT * FROM `%q` ORDER BY ID ASC", CurrentBaseSet));

	for (new i = 0; i < MAX_BASES; i++) BExist[i] = false;
	do {
		db_get_field_assoc(res, "ID", iString, sizeof(iString));
		new i = strval(iString);

		db_get_field_assoc(res, "Interior", iString, sizeof(iString));
		BInterior[i] = strval(iString);

		db_get_field_assoc(res, "AttSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", BAttackerSpawn[i][0], BAttackerSpawn[i][1], BAttackerSpawn[i][2]);

		db_get_field_assoc(res, "DefSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", BDefenderSpawn[i][0], BDefenderSpawn[i][1], BDefenderSpawn[i][2]);

		db_get_field_assoc(res, "CPSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);

		db_get_field_assoc(res, "Name", BName[i], MAX_MAP_FIELD_NAME);

		TotalBases++;
		BExist[i] = true;
	}
	while (db_next_row(res));

	db_free_result(res);

	SendClientMessageToAll(-1, va_return(COL_PRIM "Bases Loaded: {FFFFFF}%d " COL_PRIM "| Current base set: {FFFFFF}%s", TotalBases, CurrentBaseSet));
	printf("Bases Loaded: %d (from table: %s)", TotalBases, CurrentBaseSet);
}

LoadArenas()
{
	TotalArenas = 0;
	new iString[64];

	new DBResult: res = db_query(sqliteconnection, va_return("SELECT * FROM `%q` ORDER BY ID ASC", CurrentArenaSet));

	for (new i = 0; i < MAX_ARENAS; i++) AExist[i] = false;
	do {
		db_get_field_assoc(res, "ID", iString, sizeof(iString));
		new i = strval(iString);

		db_get_field_assoc(res, "Interior", iString, sizeof(iString));
		AInterior[i] = strval(iString);

		db_get_field_assoc(res, "AttSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", AAttackerSpawn[i][0], AAttackerSpawn[i][1], AAttackerSpawn[i][2]);

		db_get_field_assoc(res, "DefSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", ADefenderSpawn[i][0], ADefenderSpawn[i][1], ADefenderSpawn[i][2]);

		db_get_field_assoc(res, "CPSpawn", iString, sizeof(iString));
		sscanf(iString, "p<,>fff", ACPSpawn[i][0], ACPSpawn[i][1], ACPSpawn[i][2]);

		db_get_field_assoc(res, "Max", iString, sizeof(iString));
		sscanf(iString, "p<,>ff", AMax[i][0], AMax[i][1]);

		db_get_field_assoc(res, "Min", iString, sizeof(iString));
		sscanf(iString, "p<,>ff", AMin[i][0], AMin[i][1]);

		db_get_field_assoc(res, "Name", AName[i], MAX_MAP_FIELD_NAME);

		AExist[i] = true;
		TotalArenas++;
	}
	while (db_next_row(res));

	db_free_result(res);

	SendClientMessageToAll(-1, va_return(COL_PRIM "Arenas Loaded: {FFFFFF}%d " COL_PRIM "| Current arena set: {FFFFFF}%s", TotalArenas, CurrentArenaSet));
	printf("Arenas Loaded: %d (from table: %s)", TotalArenas, CurrentArenaSet);
}

LoadDMs()
{
	new iString[64], TotalDMs;

	new DBResult: res = db_query(sqliteconnection, "SELECT * FROM DMs ORDER BY ID ASC");

	for (new i = 0; i < MAX_DMS; i++) DMExist[i] = false;
	do {
		db_get_field_assoc(res, "ID", iString, sizeof(iString));
		new i = strval(iString);

		db_get_field_assoc(res, "Interior", iString, sizeof(iString));
		DMInterior[i] = strval(iString);

		for (new j = 0; j < 3; ++j)
		{
			new fieldName[10], weapon[128];
			format(fieldName, sizeof(fieldName), "Wep%d", j + 1);
			db_get_field_assoc(res, fieldName, weapon, 128);
			DMWeapons[i][j] = strval(weapon);
		}

		db_get_field_assoc(res, "Spawn", iString, sizeof(iString));
		sscanf(iString, "p<,>ffff", DMSpawn[i][0], DMSpawn[i][1], DMSpawn[i][2], DMSpawn[i][3]);
		DMExist[i] = true;

		//db_next_row(res);
		TotalDMs++;
	}
	while (db_next_row(res));

	db_free_result(res);

	printf("DMs Loaded: %d", TotalDMs);
}
