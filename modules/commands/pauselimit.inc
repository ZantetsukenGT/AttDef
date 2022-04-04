#if defined _attdef_cmd_pauselimit
	#endinput
#endif
#define _attdef_cmd_pauselimit

YCMD: pauselimit(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change pause limit and toggle auto unpause.");
	new maxpauses, pauseduration;
	if (sscanf(params, "ii", maxpauses, pauseduration))
		return SendUsageMessage(playerid, "/pauselimit [max pauses per round] [pause duration in minutes] []");
	// unimplemented since?
	return 1;
}
