#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_database
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_database
	#endinput
#endif
#define _attdef_impl_database

/*
	Database loading
*/

SetDatabaseToReload(playerid = INVALID_PLAYER_ID)
{
	if (playerid != INVALID_PLAYER_ID)
		va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has set the SQLite database to reload.", Player[playerid][Name]);

	db_close(sqliteconnection);
	sqliteconnection = db_open("AttDefDatabase.db");
	return SendClientMessageToAll(-1, COL_PRIM "SQLite database has been reloaded successfully.");
}

LoadDatabase()
{
	sqliteconnection = db_open("AttDefDatabase.db");
	if (!sqliteconnection)
	{
		printf("Warning: database is not loaded. Make sure 'AttDefDatabase.db' file is inside the '/scriptfiles' directory and restart. Visit %s for further help!", GM_WEBSITE);
		return 0;
	}
	// Vacuum SQL database
	db_free_result(db_query(sqliteconnection, "VACUUM"));

	LoadConfig();	 // Loads server configuration
	LoadTextDraws(); // Loads all global textdraws
	LoadBases();	 // Loads bases
	LoadArenas();	 // Loads arenas
	LoadDMs();		 // Loads DMs
	LoadCommands();	 // Load commands with level
	return 1;
}

OptimizeDatabase()
{
	// Vacuum SQL database
	db_free_result(db_query(sqliteconnection, "VACUUM"));
}
