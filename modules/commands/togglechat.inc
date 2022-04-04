#if defined _attdef_cmd_togglechat
	#endinput
#endif
#define _attdef_cmd_togglechat

YCMD: togglechat(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "enable or disable main chat.");

	LogAdminCommand("togglechat", playerid, INVALID_PLAYER_ID);

	new message[128];
	format(
		message, sizeof(message), "{FFFFFF}%s " COL_PRIM "has %s", Player[playerid][Name],
		ChatDisabled ? "enabled main chat!" : "disabled main chat! (Press {FFFFFF}Y " COL_PRIM "to ask for round pause)");
	ChatDisabled = !ChatDisabled;
	return SendClientMessageToAll(-1, message);
}
