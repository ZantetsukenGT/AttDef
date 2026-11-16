#if defined _attdef_cmd_unmute
	#endinput
#endif
#define _attdef_cmd_unmute

YCMD: unmute(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "unmute a specific player.");

	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/unmute [Player Name/ID]");
	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isnt connected.");
	if (!Player[pID][Mute])
		return SendErrorMessage(playerid, "That player is not muted.");

	Player[pID][Mute] = false;

	LogAdminCommand("unmute", playerid, pID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has unmuted {FFFFFF}%s", Player[playerid][Name], Player[pID][Name]);
}
