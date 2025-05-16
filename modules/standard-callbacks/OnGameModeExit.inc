#if defined _attdef_OnGMExit
	#endinput
#endif
#define _attdef_OnGMExit

public OnGameModeExit()
{
	DB_Close(sqliteconnection);
	return 1;
}
