#if defined _attdef_cmd_setarmour
	#endinput
#endif
#define _attdef_cmd_setarmour

YCMD: setarmour(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "set a player armour to a specific value.");
	new pID, Amount;
	if (sscanf(params, "rd", pID, Amount))
		return SendUsageMessage(playerid, "/setarmour [Player Name/ID] [Amount]");
	if (Amount < 0 || Amount > 100)
		return SendErrorMessage(playerid, "Invalid amount.");
	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");

	SetAP(pID, Amount);

	LogAdminCommand("setarmour", playerid, pID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}%s's " COL_PRIM "armour to: {FFFFFF}%d", Player[playerid][Name], Player[pID][Name], Amount);
}
