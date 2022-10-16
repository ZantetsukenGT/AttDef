#if defined _attdef_cmd_muteall
	#endinput
#endif
#define _attdef_cmd_muteall

YCMD: muteall(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "mute everyone.");
	foreach (new i : Player)
		Player[i][Mute] = true;

	LogAdminCommand("muteall", playerid, INVALID_PLAYER_ID);

	new admName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, admName, sizeof(admName));
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has muted everyone! (Press {FFFFFF}Y " COL_PRIM "to ask for round pause)", admName);
}
