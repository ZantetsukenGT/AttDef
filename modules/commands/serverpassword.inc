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

	new str[128];
	format(str, sizeof(str), COL_PRIM "Current Server Password: {FFFFFF}%s", ServerPass[9]);
	return SendClientMessageToAll(-1, str);
}
