#if defined _attdef_cmd_unlock
	#endinput
#endif
#define _attdef_cmd_unlock

YCMD: unlock(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "unlock the server.");
	if (!ServerLocked)
		return SendErrorMessage(playerid, "Server is not locked.");

	SendRconCommand("password 0");
	TextDrawSetString(LockServerTD, va_return("%sServer: ~r~Unlocked", MAIN_TEXT_COLOUR));

	ServerLocked = false;
	PermLocked	 = false;

	LogAdminCommand("unlock", playerid, INVALID_PLAYER_ID);

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has unlocked the server.", Player[playerid][Name]);
	return SendClientMessageToAll(-1, iString);
}
