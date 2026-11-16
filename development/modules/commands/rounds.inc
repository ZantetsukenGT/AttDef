#if defined _attdef_cmd_rounds
	#endinput
#endif
#define _attdef_cmd_rounds

YCMD: rounds(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display a record of rounds of a match.");
	new str1[1024];
	for (new id = 0; id < 101; id++)
	{
		if (MatchRoundsRecord[id][round__ID] != -1)
		{
			switch (MatchRoundsRecord[id][round__type])
			{
				case 0: //base
					format(
						str1, sizeof(str1), "%s\n{FFFFFF}%d.%s%s [ID:%d]", str1, id, (MatchRoundsRecord[id][round__completed]) ? ("") : ("{FAF62D}"),
						BName[MatchRoundsRecord[id][round__ID]], MatchRoundsRecord[id][round__ID]);
				case 1: //arena
					format(
						str1, sizeof(str1), "%s\n{B5B5B5}%d.%s%s [ID:%d]", str1, id, (MatchRoundsRecord[id][round__completed]) ? ("") : ("{FAF62D}"),
						AName[MatchRoundsRecord[id][round__ID]], MatchRoundsRecord[id][round__ID]);
				default: format(str1, sizeof(str1), "%s\nWadaffuq?", str1);
			}
		}
	}
	return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, "Rounds played in current/last match", str1, "Close", "");
}
