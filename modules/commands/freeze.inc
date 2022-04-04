#if defined _attdef_cmd_freeze
	#endinput
#endif
#define _attdef_cmd_freeze

YCMD: freeze(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "freeze a player.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/freeze [Player ID]");

	new pID = strval(params);
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isnt connected.");

	TogglePlayerControllable(pID, 0);

	LogAdminCommand("freeze", playerid, pID);

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has frozen {FFFFFF}%s", Player[playerid][Name], Player[pID][Name]);
	return SendClientMessageToAll(-1, iString);
}

forward DelayedFreeze(pID);
public DelayedFreeze(pID)
{
	TogglePlayerControllable(pID, 0);
}
