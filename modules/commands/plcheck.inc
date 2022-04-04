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
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/plcheck [Player ID]");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player is not connected.");
	if (!Player[pID][NetCheck])
		return SendErrorMessage(playerid, "That player has netcheck disabled on him.");

	LogAdminCommand("plcheck", playerid, pID);

	new iString[128];
	format(
		iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has disabled PL-Check on: {FFFFFF}%s", Player[playerid][Name], Player[pID][PLCheck] ? "disabled" : "enabled",
		Player[pID][Name]);
	Player[pID][PLCheck] = !Player[pID][PLCheck];
	return SendClientMessageToAll(-1, iString);
}
