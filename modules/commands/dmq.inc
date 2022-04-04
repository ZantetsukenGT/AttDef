#if defined _attdef_cmd_dmq
	#endinput
#endif
#define _attdef_cmd_dmq

YCMD: dmq(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "get you out of a deathmatch arena.");
	return QuitDM(playerid);
}
