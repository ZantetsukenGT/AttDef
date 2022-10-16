#if defined _attdef_cmd_setacclevel
	#endinput
#endif
#define _attdef_cmd_setacclevel

YCMD: setacclevel(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 5)
		return SendErrorMessage(playerid, "You must be level 5 to use this command.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "change the level of an account in the database");

	new str[MAX_PLAYER_NAME], lev;
	if (isnull(params) || sscanf(params, "s[24]d", str, lev))
		return SendUsageMessage(playerid, "/setacclevel [Account Name] [Level]");
	if (lev < 0 || lev >= MAX_ADMIN_LEVELS)
		return SendErrorMessage(playerid, "Invalid level.");
	if (strlen(str) > MAX_PLAYER_NAME)
		return SendErrorMessage(playerid, "Maximum name length: 24 characters.");

	new iString[164];
	format(iString, sizeof(iString), "SELECT Level FROM Players WHERE Name = '%q'", str);
	new DBResult: result = db_query(sqliteconnection, iString);
	new db_rows			 = db_num_rows(result);
	db_free_result(result);

	if (db_rows == 0)
		return SendErrorMessage(playerid, va_return("%s" COL_PRIM "'s account wasn't found in the database.", str));
	if (db_rows > 1)
		return SendWarningMessage(
			playerid, va_return("%s" COL_PRIM "'s admin level was set, but the account was found {FF3333}%d" COL_PRIM " times in the database.", str, db_rows));

	format(iString, sizeof(iString), "UPDATE Players SET Level = %d WHERE Name = '%q'", lev, str);
	db_free_result(db_query(sqliteconnection, iString));

	return va_SendClientMessage(playerid, -1, "{008800}Success: {FFFFFF}%s" COL_PRIM "'s admin level was set to {FF3333}%d" COL_PRIM ".", str, lev);
}
