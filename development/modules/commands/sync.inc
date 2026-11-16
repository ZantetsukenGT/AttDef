#if defined _attdef_cmd_sync
	#endinput
#endif
#define _attdef_cmd_sync

YCMD: sync(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "re-sync you (restore stamina and other stuff).");
	return SyncPlayer(playerid);
}
