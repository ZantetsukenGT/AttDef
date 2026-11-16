#if defined _attdef_cmd_banip
	#endinput
#endif
#define _attdef_cmd_banip

YCMD: banip(playerid, params[], help)
{
	//if(Player[playerid][Level] < 4 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a level 4 admin to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "ban a specific IP (can be used for range-bans using *).");
	if (isnull(params))
		return SendUsageMessage(playerid, "/banip [IP or IP range to ban]");

	va_SendRconCommand("banip %s", params);
	SendRconCommand("reloadbans");

	LogAdminCommand("banip", playerid, INVALID_PLAYER_ID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has banned an {FFFFFF}IP address" COL_PRIM ".", Player[playerid][Name], playerid);
}
