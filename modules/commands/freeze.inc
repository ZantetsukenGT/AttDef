#if defined _attdef_cmd_freeze
	#endinput
#endif
#define _attdef_cmd_freeze

YCMD: freeze(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "freeze a player.");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/freeze [Player Name/ID]");
	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isnt connected.");

	TogglePlayerControllable(pID, 0);

	LogAdminCommand("freeze", playerid, pID);
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has frozen {FFFFFF}%s" COL_PRIM ".", Player[playerid][Name], Player[pID][Name]);
}

forward DelayedFreeze(pID);
public DelayedFreeze(pID)
{
	TogglePlayerControllable(pID, 0);
}
