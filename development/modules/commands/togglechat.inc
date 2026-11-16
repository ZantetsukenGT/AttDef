#if defined _attdef_cmd_togglechat
	#endinput
#endif
#define _attdef_cmd_togglechat

YCMD: togglechat(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "enable or disable main chat.");

	LogAdminCommand("togglechat", playerid, INVALID_PLAYER_ID);

	ChatDisabled = !ChatDisabled;
	return va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has %s", Player[playerid][Name],
		ChatDisabled ? "disabled main chat! (Press {FFFFFF}Y " COL_PRIM "to ask for round pause)" : "enabled main chat!");
}
