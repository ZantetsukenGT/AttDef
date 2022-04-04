#if defined _attdef_cmd_jetpack
	#endinput
#endif
#define _attdef_cmd_jetpack

YCMD: jetpack(playerid, params[], help)
{
	if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "spawn a jetpack.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't use this command in round.");

	new pID = strval(params);
	if (isnull(params))
		pID = playerid;

	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isn't connected.");

	SetPlayerSpecialAction(pID, 2);

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "gave a jetpack to {FFFFFF}%s", Player[playerid][Name], Player[pID][Name]);
	return SendClientMessageToAll(-1, iString);
}
