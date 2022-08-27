#if defined _attdef_cmd_lastplayed
	#endinput
#endif
#define _attdef_cmd_lastplayed

YCMD: lastplayed(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display the ID of the last played round.");
	if (Current < 0)
		return SendErrorMessage(playerid, "Invalid round ID.");
	return va_SendClientMessageToAll(
		-1, COL_PRIM "Last Played: {FFFFFF}%d " COL_PRIM "| Type {FFFFFF}/start last " COL_PRIM "to start it!", ServerLastPlayed);
}
