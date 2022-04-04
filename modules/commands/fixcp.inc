#if defined _attdef_cmd_fixcp
	#endinput
#endif
#define _attdef_cmd_fixcp

YCMD: fixcp(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "re-load the checkpoint for you.");
	if (GameType == ARENA && !CPInArena)
		return SendErrorMessage(playerid, "Checkpoint in arenas option is disabled in this server");
	if (RCArena)
		return SendErrorMessage(playerid, "There are no checkpoints in RC arenas!");

	if (Player[playerid][Playing])
		SetPreciseTimer("SetCPForPlayer", 1000, false, "i", playerid);
	return 1;
}
