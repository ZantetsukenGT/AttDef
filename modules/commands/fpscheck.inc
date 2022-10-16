#if defined _attdef_cmd_fpscheck
	#endinput
#endif
#define _attdef_cmd_fpscheck

YCMD: fpscheck(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "toggle FPS status check on a specific player.");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/fpscheck [Player Name/ID]");

	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player is not connected.");
	if (!Player[pID][NetCheck])
		return SendErrorMessage(playerid, "That player has netcheck disabled on him.");

	Player[pID][FPSCheck] = !Player[pID][FPSCheck];
	LogAdminCommand("fpscheck", playerid, pID);
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has %s {FFFFFF}FPS-Check " COL_PRIM "on: {FFFFFF}%s" COL_PRIM ".", Player[playerid][Name], Player[pID][FPSCheck] ? "{66FF66}enabled" : "{FF6666}disabled",
		Player[pID][Name]);
}
