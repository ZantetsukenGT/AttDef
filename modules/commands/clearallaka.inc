#if defined _attdef_cmd_clearallaka
	#endinput
#endif
#define _attdef_cmd_clearallaka

YCMD: clearallaka(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "clear all players aka logs from database");

	DB_FreeResultSet(DB_ExecuteQuery(sqliteconnection, "DELETE FROM `AKAs`"));
	return SendClientMessage(playerid, -1, "AKA logs have been successfully cleared!");
}
