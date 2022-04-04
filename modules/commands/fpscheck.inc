#if defined _attdef_cmd_fpscheck
	#endinput
#endif
#define _attdef_cmd_fpscheck

YCMD: fpscheck(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "toggle FPS status check on a specific player.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/fpscheck [Player ID]");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player is not connected.");
	if (!Player[pID][NetCheck])
		return SendErrorMessage(playerid, "That player has netcheck disabled on him.");

	new iString[128];
	format(
		iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has %s FPS-Check on: {FFFFFF}%s", Player[playerid][Name], Player[pID][FPSCheck] ? "disabled" : "enabled",
		Player[pID][Name]);
	Player[pID][FPSCheck] = !Player[pID][FPSCheck];

	LogAdminCommand("fpscheck", playerid, pID);

	return SendClientMessageToAll(-1, iString);
}
