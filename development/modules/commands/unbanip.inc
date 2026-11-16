#if defined _attdef_cmd_unbanip
	#endinput
#endif
#define _attdef_cmd_unbanip

YCMD: unbanip(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 3 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "unban a specific IP or a range.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/unbanip [IP]");

	va_SendRconCommand("unbanip %s", params);
	SendRconCommand("reloadbans");

	LogAdminCommand("unbanip", playerid, INVALID_PLAYER_ID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has unbanned an {FFFFFF}IP address" COL_PRIM ".", Player[playerid][Name]);
}
