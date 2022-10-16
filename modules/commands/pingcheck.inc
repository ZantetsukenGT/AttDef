#if defined _attdef_cmd_pingcheck
	#endinput
#endif
#define _attdef_cmd_pingcheck

YCMD: pingcheck(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "toggle ping status check on a specific player.");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/pingcheck [Player Name/ID]");

	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player is not connected.");
	if (!Player[pID][NetCheck])
		return SendErrorMessage(playerid, "That player has netcheck disabled on him.");

	LogAdminCommand("pingcheck", playerid, pID);

	Player[pID][PingCheck] = !Player[pID][PingCheck];
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has %s {FFFFFF}Ping-Check " COL_PRIM "on: {FFFFFF}%s", Player[playerid][Name], Player[pID][PingCheck] ? "{66FF66}enabled" : "{FF6666}disabled",
		Player[pID][Name]);
}
