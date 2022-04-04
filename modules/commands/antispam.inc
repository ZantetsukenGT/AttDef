#if defined _attdef_cmd_antispam
	#endinput
#endif
#define _attdef_cmd_antispam

YCMD: antispam(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "toggle the server anti-spam of commands and chat.");
	return ToggleAntiSpam(playerid);
}

ToggleAntiSpam(playerid)
{
	AntiSpam = !AntiSpam;
	LogAdminCommand("antispam", playerid, INVALID_PLAYER_ID);
	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has %s " COL_PRIM "anti-spam.", Player[playerid][Name], AntiSpam ? "{66FF66}enabled" : "{FF6666}disabled"));
}
