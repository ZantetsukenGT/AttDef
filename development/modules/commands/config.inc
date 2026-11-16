#if defined _attdef_cmd_config
	#endinput
#endif
#define _attdef_cmd_config

YCMD: config(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 5 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be level 5 or rcon admin.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "display server configuration for you to modify.");

	LogAdminCommand("config", playerid, INVALID_PLAYER_ID);
	return ShowConfigDialog(playerid);
}
