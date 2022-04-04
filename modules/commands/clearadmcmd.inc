#if defined _attdef_cmd_clearadmcmd
	#endinput
#endif
#define _attdef_cmd_clearadmcmd

YCMD: clearadmcmd(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "clear the admin command log file that is in scriptfiles folder");

	ClearAdminCommandLog();
	return SendClientMessage(playerid, -1, "Admin command log has been successfully cleared!");
}
