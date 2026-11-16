#if defined _attdef_cmd_plcheck
	#endinput
#endif
#define _attdef_cmd_plcheck

YCMD: plcheck(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "toggle packet-loss status check on a specific player.");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/plcheck [Player Name/ID]");

	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player is not connected.");
	if (!Player[pID][NetCheck])
		return SendErrorMessage(playerid, "That player has netcheck disabled on him.");

	LogAdminCommand("plcheck", playerid, pID);

	Player[pID][PLCheck] = !Player[pID][PLCheck];
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has %s {FFFFFF}PL-Check " COL_PRIM "on: {FFFFFF}%s", Player[playerid][Name], Player[pID][PLCheck] ? "{66FF66}enabled" : "{FF6666}disabled",
		Player[pID][Name]);
}
