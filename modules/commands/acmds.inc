#if defined _attdef_cmd_acmds
	#endinput
#endif
#define _attdef_cmd_acmds

YCMD: acmds(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display admin commands");

	new dialog_message[4095];
	strcat(dialog_message, COL_PRIM "Use {FF3333}@ " COL_PRIM "for admin chat\nIf you need help with a command, use " COL_SEC "/cmdhelp");
	new pLevel = Player[playerid][Level];
	for (new currentLevel = MAX_ADMIN_LEVELS - 1; currentLevel > 0; --currentLevel)
	{
		new commandsInLine = 1;
		if (pLevel >= currentLevel)
		{
			strcat(dialog_message, va_return(COL_PRIM "\n\nLevel {FF3333}%d" COL_PRIM ":", currentLevel));
			foreach (new i : Command())
			{
				if (GetCommandLevel(i) == currentLevel)
				{
					strcat(dialog_message, commandsInLine % 6 == 1 ? "\n" : "  ");
					strcat(dialog_message, va_return(COL_PRIM "/" COL_SEC "%s", Command_GetName(i)));
					++commandsInLine;
				}
			}
		}
	}
	return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, COL_SEC "Admin Commands", dialog_message, "OK", "");
}
