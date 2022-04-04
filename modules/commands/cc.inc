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

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has cleared chat.", Player[playerid][Name]);
	return SendClientMessageToAll(-1, iString);
}
