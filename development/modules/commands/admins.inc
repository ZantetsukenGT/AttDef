#if defined _attdef_cmd_admins
	#endinput
#endif
#define _attdef_cmd_admins

YCMD: admins(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display online admins.");

	new allAdmins[1200];
	new bool: isThereRCONAdmins;
	strcat(allAdmins, COL_PRIM "RCON Admins");
	foreach (new i : Player)
	{
		if (IsPlayerAdmin(i))
		{
			isThereRCONAdmins = true;
			strcat(allAdmins, va_return("\n  {666666}- {FFFFFF}%s", Player[i][Name]));
		}
	}

	strcat(allAdmins, isThereRCONAdmins ? "\n\n" : "\n  {666666}- No RCON admins logged in\n\n");

	new bool: isThereNormalAdmins;
	strcat(allAdmins, COL_PRIM "Admins");
	for (new currentLevel = MAX_ADMIN_LEVELS - 1; currentLevel > 0; --currentLevel)
	{
		foreach (new i : Player)
		{
			if (Player[i][Level] == currentLevel)
			{
				isThereNormalAdmins = true;
				strcat(allAdmins, va_return("\n  {666666}- {FFFFFF}%s ({FF3333}%d{FFFFFF})", Player[i][Name], Player[i][Level]));
			}
		}
	}

	strcat(allAdmins, isThereNormalAdmins ? "\n\n" : "\n  {666666}- No admins online\n\n");

	return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, "{FFFFFF}Admins Online", allAdmins, "Ok", "");
}
