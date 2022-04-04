#if defined _attdef_cmd_setcmdlevel
	#endinput
#endif
#define _attdef_cmd_setcmdlevel

YCMD: setcmdlevel(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "set the level of a command");

	new cmd[MAX_COMMAND_NAME], level;
	if (isnull(params) || sscanf(params, "s[32]d", cmd, level))
		return SendUsageMessage(playerid, "/setcmdlevel [Command name without /] [New level]");
	if (level < 0 || level >= MAX_ADMIN_LEVELS)
		return SendErrorMessage(playerid, "Invalid level!");
	if (SetCommandLevel(cmd, level, true) == 0)
		return SendErrorMessage(playerid, "Invalid command!");

	new message[180];
	if (level == 0)
		format(message, sizeof(message), "{FFFFFF}%s " COL_PRIM "has permitted command {FFFFFF}/%s " COL_PRIM "for everyone's use.", Player[playerid][Name], cmd);
	else
		format(
			message, sizeof(message), "{FFFFFF}%s " COL_PRIM "has permitted command {FFFFFF}/%s " COL_PRIM "for only level {FFFFFF}%d" COL_PRIM " and higher.",
			Player[playerid][Name], cmd, level);
	return SendClientMessageToAll(-1, message);
}
