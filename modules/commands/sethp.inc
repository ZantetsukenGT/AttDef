#if defined _attdef_cmd_sethp
	#endinput
#endif
#define _attdef_cmd_sethp

YCMD: sethp(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "set a player health to a specific value.");

	new pID, Amount;
	if (sscanf(params, "id", pID, Amount))
		return SendUsageMessage(playerid, "/sethp [Player ID] [Amount]");
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isn't connected.");

	if (Amount < 0)
		Amount = 0;
	if (Amount > 100)
		Amount = 100;

	SetHP(pID, Amount);

	LogAdminCommand("sethp", playerid, pID);

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has set {FFFFFF}%s's " COL_PRIM "HP to: {FFFFFF}%d", Player[playerid][Name], Player[pID][Name], Amount);
	return SendClientMessageToAll(-1, iString);
}
