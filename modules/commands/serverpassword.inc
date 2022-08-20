#if defined _attdef_cmd_serverpassword
	#endinput
#endif
#define _attdef_cmd_serverpassword

YCMD: serverpassword(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display server password for everyone connected.");
	if (!ServerLocked)
		return SendErrorMessage(playerid, "Server is not locked.");

	return va_SendClientMessageToAll(-1, COL_PRIM "Current Server Password: {FFFFFF}%s", ServerPass[9]);
}
