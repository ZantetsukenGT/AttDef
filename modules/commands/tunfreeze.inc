#if defined _attdef_cmd_tunfreeze
	#endinput
#endif
#define _attdef_cmd_tunfreeze

YCMD: tunfreeze(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "unfreeze a player for 500ms.");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/tunfreeze [Player Name/ID]");

	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isnt connected.");

	TogglePlayerControllable(pID, 1);
    SetTimerEx("DelayedFreeze", 500, false, "i", pID);

	LogAdminCommand("tunfreeze", playerid, pID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has unfrozen {FFFFFF}%s" COL_PRIM " for 500ms.", Player[playerid][Name], Player[pID][Name]);
}
