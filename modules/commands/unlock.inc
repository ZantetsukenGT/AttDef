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
	va_TextDrawSetString(LockServerTD, "%sServer: ~r~Unlocked", MAIN_TEXT_COLOUR);

	ServerLocked = false;
	PermLocked	 = false;

	LogAdminCommand("unlock", playerid, INVALID_PLAYER_ID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has {FFFFFF}unlocked " COL_PRIM "the server.", Player[playerid][Name]);
}
