#if defined _attdef_cmd_deathdiss
	#endinput
#endif
#define _attdef_cmd_deathdiss

YCMD: deathdiss(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "set a disrespect message to be shown for players whom you kill.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/deathdiss [Disrespect Message]");
	if (strlen(params) <= 3)
		return SendErrorMessage(playerid, "Too short!");
	if (strlen(params) >= 32)
		return SendErrorMessage(playerid, "Too long!");

	format(DeathMessageStr[playerid], 32, "%s", params);

	new iString[128];
	format(iString, sizeof(iString), "UPDATE `Players` SET `DeathMessage` = '%q' WHERE `Name` = '%q'", params, Player[playerid][Name]);
	DB_FreeResultSet(DB_ExecuteQuery(sqliteconnection, iString));
	Player[playerid][HasDeathQuote] = true;
	return SendClientMessage(playerid, -1, "Death diss message has been changed successfully!");
}
