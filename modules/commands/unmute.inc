#if defined _attdef_cmd_unmute
	#endinput
#endif
#define _attdef_cmd_unmute

YCMD: unmute(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "unmute a specific player.");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isnt connected.");
	if (!Player[pID][Mute])
		return SendErrorMessage(playerid, "That player is not muted.");

	Player[pID][Mute] = false;

	LogAdminCommand("unmute", playerid, pID);

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has unmuted {FFFFFF}%s", Player[playerid][Name], Player[pID][Name]);
	return SendClientMessageToAll(-1, iString);
}
