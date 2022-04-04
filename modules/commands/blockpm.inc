#if defined _attdef_cmd_blockpm
	#endinput
#endif
#define _attdef_cmd_blockpm

YCMD: blockpm(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "block private messages from a specific player.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/blockpm [Player ID]");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isn't connected.");

	Player[playerid][blockedid] = pID;

	new String[128];
	format(String, sizeof(String), COL_PRIM "You have blocked PMs from {FFFFFF}%s", Player[pID][Name]);
	return SendClientMessage(playerid, -1, String);
}
