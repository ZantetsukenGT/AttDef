#if defined _attdef_cmd_asay
	#endinput
#endif
#define _attdef_cmd_asay

YCMD: asay(playerid, params[], help)
{
	//if(Player[playerid][Level] < 2 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a level 2 admin to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "send a public message as an administrator");
	if (isnull(params))
		return SendUsageMessage(playerid, "/asay [Text]");

	LogAdminCommand("asay", playerid, INVALID_PLAYER_ID);
	return va_SendClientMessageToAll(-1, "{6688FF}* Admin: %s", params);
}
