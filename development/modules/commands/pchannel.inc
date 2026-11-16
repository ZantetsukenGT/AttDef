#if defined _attdef_cmd_pchannel
	#endinput
#endif
#define _attdef_cmd_pchannel

YCMD: pchannel(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display players in a channel.");
	if (Player[playerid][ChatChannel] == -1)
		return SendErrorMessage(playerid, "You are not in any channel. To join one, use /cchannel");

	new iString[1300];
	new bool: firstIteration = true;
	new numberOfPlayers;
	foreach (new i : Player)
	{
		if (Player[i][ChatChannel] == Player[playerid][ChatChannel])
		{
			++numberOfPlayers;
			if (firstIteration)
			{
				firstIteration = false;
				strcat(iString, va_return("  {666666}- {FFFFFF}%s ({FF3333}%d{FFFFFF})", Player[i][Name], i));
			}
			else
				strcat(iString, va_return("\n  {666666}- {FFFFFF}%s ({FF3333}%d{FFFFFF})", Player[i][Name], i));
		}
	}

	if (!numberOfPlayers)
		return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, COL_PRIM "Current chat channel", "There are no players in this channel", "Close", "");
	return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, COL_PRIM "Current chat channel", iString, "Close", "");
}
