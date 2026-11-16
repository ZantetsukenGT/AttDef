#if defined _attdef_cmd_cmdhelp
	#endinput
#endif
#define _attdef_cmd_cmdhelp

YCMD: cmdhelp(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display help about commands");
	if (isnull(params))
		return SendUsageMessage(playerid, "/cmdhelp [Command name]");

	Command_ReProcess(playerid, params, true);
	return 1;
}
