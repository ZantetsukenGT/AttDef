#if defined _attdef_cmd_lock
	#endinput
#endif
#define _attdef_cmd_lock

YCMD: lock(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "lock the server.");
	if (ServerLocked)
		return CallLocalFunction("OnPlayerCommandText", "ds", playerid, "/unlock");

	if (isnull(params))
		return SendUsageMessage(playerid, "/lock [Password]");
	if (strlen(params) > MAX_SERVER_PASS_LENGTH)
		return SendErrorMessage(playerid, "Server password is too long.");

	format(ServerPass, sizeof(ServerPass), "password %s", params);
	SendRconCommand(ServerPass);

	ServerLocked = true;
	PermLocked	 = false;

	new iString[144];
	format(iString, sizeof(iString), "%sServer Pass: ~r~%s", MAIN_TEXT_COLOUR, params);
	TextDrawSetString(LockServerTD, iString);

	LogAdminCommand("lock", playerid, INVALID_PLAYER_ID);

	format(iString, sizeof(iString), "%s " COL_PRIM "has {FFFFFF}locked " COL_PRIM "the server with password: {FFFFFF}%s", Player[playerid][Name], params);
	return SendClientMessageToAll(-1, iString);
}
