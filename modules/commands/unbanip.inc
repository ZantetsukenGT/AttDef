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

	SendRconCommand(va_return("unbanip %s", params));
	SendRconCommand("reloadbans");

	LogAdminCommand("unbanip", playerid, INVALID_PLAYER_ID);

	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has unbanned an IP address.", Player[playerid][Name]));
}
