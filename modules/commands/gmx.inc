#if defined _attdef_cmd_gmx
	#endinput
#endif
#define _attdef_cmd_gmx

YCMD: gmx(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 5 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a level 5 admin to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "restart your server.");

	va_SendClientMessageToAll(-1, "%s (%d) " COL_PRIM "has set the server to restart", Player[playerid][Name], playerid);

	db_close(sqliteconnection);
	LogAdminCommand("gmx", playerid, INVALID_PLAYER_ID);

	return SendRconCommand("gmx");
}
