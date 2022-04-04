#if defined _attdef_cmd_mute
	#endinput
#endif
#define _attdef_cmd_mute

YCMD: mute(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "mute a specific player.");
	new pID, Reason[128], iString[256];
	if (sscanf(params, "iS( )[128]", pID, Reason))
		return SendUsageMessage(playerid, "/mute [Player ID] [Reason]");
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isnt connected.");

	if (Player[pID][Mute])
		return SendErrorMessage(playerid, "That player is already muted.");
	/*if (Player[playerid][Level] <= Player[pID][Level] && playerid != pID)
		return SendErrorMessage(playerid, "That player is higher admin level than you.");*/

	Player[pID][Mute] = true;

	LogAdminCommand("mute", playerid, pID);

	if (strlen(Reason))
		format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has muted {FFFFFF}%s " COL_PRIM "| Reason: {FFFFFF}%s", Player[playerid][Name], Player[pID][Name], Reason);
	else
		format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has muted {FFFFFF}%s " COL_PRIM "| Reason: {FFFFFF}No reason given.", Player[playerid][Name], Player[pID][Name]);
	return SendClientMessageToAll(-1, iString);
}
