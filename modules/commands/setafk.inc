#if defined _attdef_cmd_setafk
	#endinput
#endif
#define _attdef_cmd_setafk

YCMD: setafk(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "force someone to go into AFK mode.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/setafk [Player ID]");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player is not connected.");
	if (Player[pID][Playing])
		return SendErrorMessage(playerid, "You cannot switch this player to AFK mode as he's playing");
	if (Player[pID][InDuel])
		return SendErrorMessage(playerid, "That player is in a duel");
	if (Player[pID][Spectating])
		StopSpectate(pID);
	if (Player[pID][InDM])
		QuitDM(pID);

	Player[pID][Team] = NON;
	SetPlayerColor(pID, 0xAAAAAAAA);
	TogglePlayerControllable(pID, 0);
	Player[pID][IsAFK] = true;

	LogAdminCommand("setafk", playerid, pID);

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has set {FFFFFF}%s " COL_PRIM "to AFK mode.", Player[playerid][Name], Player[pID][Name]);
	return SendClientMessageToAll(-1, iString);
}
