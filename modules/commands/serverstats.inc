#if defined _attdef_cmd_serverstats
	#endinput
#endif
#define _attdef_cmd_serverstats

YCMD: serverstats(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "fetch server network statistics.");
	new stats[450];
	GetNetworkStats(stats, sizeof(stats)); // get the servers networkstats
	return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, "Server Network Stats", stats, "Close", "");
}
