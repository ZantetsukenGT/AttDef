#if defined _attdef_cmd_cc
	#endinput
#endif
#define _attdef_cmd_cc

YCMD: cc(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "clear the chat.");

	ClearChat();

	LogAdminCommand("cc", playerid, INVALID_PLAYER_ID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has cleared chat.", Player[playerid][Name]);
}
