#if defined _attdef_cmd_givemenu
	#endinput
#endif
#define _attdef_cmd_givemenu

YCMD: givemenu(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "show weapon menu to a specific player.");
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/givemenu [Player Name/ID]");

	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (!Player[pID][Playing])
		return SendErrorMessage(playerid, "That player isn't playing.");

	ShowPlayerGunmenu(pID, 0);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has showed {FFFFFF}%s " COL_PRIM "weapon menu.", Player[playerid][Name], Player[pID][Name]);
}
