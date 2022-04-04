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

	new str[128];
	format(str, sizeof(str), "banip %s", params);
	SendRconCommand(str);
	SendRconCommand("reloadbans");

	LogAdminCommand("banip", playerid, INVALID_PLAYER_ID);

	format(str, sizeof(str), "{FFFFFF}%s " COL_PRIM "has banned an IP address.", Player[playerid][Name], playerid);
	return SendClientMessageToAll(-1, str);
}
