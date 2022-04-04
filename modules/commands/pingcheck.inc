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
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/pingcheck [Player ID]");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player is not connected.");
	if (!Player[pID][NetCheck])
		return SendErrorMessage(playerid, "That player has netcheck disabled on him.");

	LogAdminCommand("pingcheck", playerid, pID);

	new iString[128];
	format(
		iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has %s Ping-Check on: {FFFFFF}%s", Player[playerid][Name], Player[pID][PingCheck] ? "disabled" : "enabled",
		Player[pID][Name]);
	Player[pID][PingCheck] = !Player[pID][PingCheck];
	return SendClientMessageToAll(-1, iString);
}
