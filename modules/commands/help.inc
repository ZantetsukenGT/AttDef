#if defined _attdef_cmd_help
	#endinput
#endif
#define _attdef_cmd_help

YCMD: help(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display some guidelines");

	new str[440];
	strcat(str, COL_PRIM "Project on GitHub (v1.21, outdated): {FFFFFF}https://github.com/beijind/SAMPAttackDefend/");
	strcat(str, "\n" COL_PRIM "Project on GitHub (latest): {FFFFFF}https://github.com/ZantetsukenGT/AttDef/");
	strcat(str, "\n\n\n{FFFFFF}To see server settings: {888888}/settings");
	strcat(str, "\n{FFFFFF}For admin commands: {888888}/acmds");
	strcat(str, "\n{FFFFFF}For public commands: {888888}/cmds");
	strcat(str, "\n{FFFFFF}If you need help with a specific command: {888888}/cmdhelp");
	strcat(str, "\n{FFFFFF}Match help: {888888}/matchtips");
	strcat(str, "\n{FFFFFF}To stay updated always: {888888}/updates and /checkversion");
	return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, va_return("%s gamemode " COL_PRIM "help+tips", GM_NAME), str, "OK", "");
}
