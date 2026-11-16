#if defined _attdef_cmd_style
	#endinput
#endif
#define _attdef_cmd_style

YCMD: style(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "an option to switch the style of round textdraws on your screen");
	return ShowPlayerDialog(playerid, DIALOG_ROUND_TD_STYLE, DIALOG_STYLE_LIST, "Select round textdraws style", "Modern\nBulletproof\nSimple (Good For FPS)", "Select", "Back");
}
