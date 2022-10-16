#if defined _attdef_cmd_lobbyguns
	#endinput
#endif
#define _attdef_cmd_lobbyguns

YCMD: lobbyguns(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "toggle guns in lobby");
	return ToggleLobbyGuns(playerid);
}

ToggleLobbyGuns(playerid)
{
	LobbyGuns = !LobbyGuns;
	LogAdminCommand("lobbyguns", playerid, INVALID_PLAYER_ID);
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has %s {FFFFFF}guns in lobby" COL_PRIM ".", Player[playerid][Name], LobbyGuns ? "{66FF66}enabled" : "{FF6666}disabled");
}
