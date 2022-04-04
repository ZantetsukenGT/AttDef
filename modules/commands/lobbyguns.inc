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
	new iString[144];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has {FFFFFF}%s " COL_PRIM "guns in lobby.", Player[playerid][Name], LobbyGuns ? "disabled" : "enabled");
	LobbyGuns = !LobbyGuns;

	LogAdminCommand("lobbyguns", playerid, INVALID_PLAYER_ID);
	return SendClientMessageToAll(-1, iString);
}
