#if defined _attdef_cmd_blockpm
	#endinput
#endif
#define _attdef_cmd_blockpm

YCMD: blockpm(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "block private messages from a specific player.");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/blockpm [Player Name/ID]");
	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");

	Player[playerid][blockedid] = pID;

	return va_SendClientMessage(playerid, -1, COL_PRIM "You have blocked PMs from {FFFFFF}%s", Player[pID][Name]);
}
