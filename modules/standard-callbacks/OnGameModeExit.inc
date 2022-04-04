#if defined _attdef_OnGMExit
	#endinput
#endif
#define _attdef_OnGMExit

public OnGameModeExit()
{
	db_close(sqliteconnection);
	return 1;
}
