#if defined _attdef_cmd_showagain
	#endinput
#endif
#define _attdef_cmd_showagain

YCMD: showagain(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display round or match results.");
	return ShowEndRoundTextDraw(playerid);
}
