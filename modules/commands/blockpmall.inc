#if defined _attdef_cmd_blockpmall
	#endinput
#endif
#define _attdef_cmd_blockpmall

YCMD: blockpmall(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "block private messages from everyone.");

	Player[playerid][blockedall] = !Player[playerid][blockedall];
	if (Player[playerid][blockedall])
		return SendClientMessage(playerid, -1, COL_PRIM "You have blocked PMs from everyone. To unblock type /blockpmall one more time!");
	return SendClientMessage(playerid, -1, COL_PRIM "PMs enabled!");
}
