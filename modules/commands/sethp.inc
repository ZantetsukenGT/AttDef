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
	if (!WC_IsPlayerSpawned(playerid) || IsPlayerDying(playerid))
		return SendErrorMessage(playerid, "That player isn't spawned.");

	Amount = clamp(Amount, 0, 100);
	SetHP(pID, float(Amount));

	LogAdminCommand("sethp", playerid, pID);

	return va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has set {FFFFFF}%s's " COL_PRIM "HP to: {FFFFFF}%d", Player[playerid][Name], Player[pID][Name], Amount);
}
