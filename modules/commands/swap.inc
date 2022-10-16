#if defined _attdef_cmd_swap
	#endinput
#endif
#define _attdef_cmd_swap

YCMD: swap(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "swap the teams.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't swap while round is active.");

	SwapTeams();

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has {FFFFFF}swapped the teams" COL_PRIM ".", Player[playerid][Name]);
}
