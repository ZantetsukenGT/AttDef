#if defined _attdef_cmd_rq
	#endinput
#endif
#define _attdef_cmd_rq

YCMD: rq(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "get you out of a duel.");
	if (!Player[playerid][InDuel])
		return SendErrorMessage(playerid, "You are not in a duel");

	PlayerDuelQuit(playerid);
	return 1;
}
