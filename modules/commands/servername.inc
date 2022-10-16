#if defined _attdef_cmd_servername
	#endinput
#endif
#define _attdef_cmd_servername

YCMD: servername(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "changes the server name used for the welcome message");
	new svname[52];
	if (sscanf(params, "s[52]", svname))
		return SendUsageMessage(playerid, "/servername [Server Name]");
	if (strlen(svname) > 50)
		return SendErrorMessage(playerid, "This server name exceeds the maximum character limit (50 characters).");

	ServerName[0] = EOS;
	strcat(ServerName, svname);
	db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = '%q' WHERE Option = 'Server Name'", ServerName)));

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has changed {FFFFFF}the server name " COL_PRIM "to {FFFFFF}%s", Player[playerid][Name], ServerName);
}
