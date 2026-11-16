#if defined _attdef_cmd_setcmdlevel
	#endinput
#endif
#define _attdef_cmd_setcmdlevel

YCMD: setcmdlevel(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "set the level of a command");

	new cmd[MAX_COMMAND_LENGTH], level;
	if (sscanf(params, "s[*]d", sizeof(cmd), cmd, level))
		return SendUsageMessage(playerid, "/setcmdlevel [Command name without /] [New level]");
	if (level < 0 || level >= MAX_ADMIN_LEVELS)
		return SendErrorMessage(playerid, "Invalid level!");
	if (!SetCommandLevel(cmd, level, true))
		return SendErrorMessage(playerid, "Invalid command!");

	if (level == 0)
		va_SendClientMessageToAll(-1, "%s " COL_PRIM "has permitted command {FFFFFF}/%s " COL_PRIM "for everyone's use.", Player[playerid][Name], cmd);
	else
		va_SendClientMessageToAll(
			-1, "%s " COL_PRIM "has permitted command {FFFFFF}/%s " COL_PRIM "for only level {FFFFFF}%d" COL_PRIM " and higher.", Player[playerid][Name], cmd, level);
	return 1;
}
