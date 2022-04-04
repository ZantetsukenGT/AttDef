#if defined _attdef_cmd_themes
	#endinput
#endif
#define _attdef_cmd_themes

YCMD: themes(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 5 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be level 5 or rcon admin.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "change the theme color of your server.");
	new str[512];
	strcat(str, "White (Background) & Black (Text)\n");
	strcat(str, "Black (Background) & White (Text)\n");
	strcat(str, "White (Background) & Red (Text)\n");
	strcat(str, "Black (Background) & Red (Text)\n");
	strcat(str, "White (Background) & Blue (Text)\n");
	strcat(str, "Black (Background) & Blue (Text)\n");
	strcat(str, "White (Background) & Green (Text)\n");
	strcat(str, "Black (Background) & Green (Text)\n");
	strcat(str, "White (Background) & Purple (Text)\n");
	strcat(str, "Black (Background) & Purple (Text)");

	return ShowPlayerDialog(playerid, DIALOG_THEME_CHANGE1, DIALOG_STYLE_LIST, "{0044FF} Theme colour menu", str, "Select", "Cancel");
}
