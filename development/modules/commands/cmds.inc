#if defined _attdef_cmd_cmds
	#endinput
#endif
#define _attdef_cmd_cmds

YCMD: cmds(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display server commands");

	new dialog_message[4095];
	strcat(
		dialog_message, COL_PRIM "Use {FF3333}! " COL_PRIM "for team chat\nPress {FF3333}N " COL_PRIM "to request for backup in a round\nPress {FF3333}H " COL_PRIM "to lead your team\nIf you need help with a command, use " COL_SEC "/cmdhelp\n");
	new commandsInLine = 1;
	foreach (new i : Command())
	{
		if (GetCommandLevel(i) == 0)
		{
			strcat(dialog_message, commandsInLine % 6 == 1 ? "\n" : "  ");
			strcat(dialog_message, va_return(COL_PRIM "/" COL_SEC "%s", Command_GetName(i)));
			++commandsInLine;
		}
	}
	return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, COL_SEC "Player Commands", dialog_message, "OK", "");
}
