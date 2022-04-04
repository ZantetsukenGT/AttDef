#if defined _attdef_cmd_match
	#endinput
#endif
#define _attdef_cmd_match

YCMD: match(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You Need To Be An Admin.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "toggle match mode.");
	return EnableMatchInterface(playerid);
}
