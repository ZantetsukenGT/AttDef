#if defined _attdef_cmd_alladmins
	#endinput
#endif
#define _attdef_cmd_alladmins

YCMD: alladmins(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display a list of all server admins (offline and online).");
	inline const dialog_response(pid, response, item_value, string: inputtext[])
	{
		#pragma unused pid, response, item_value, inputtext
		return 1;
	}

	new DBResult: res = DB_ExecuteQuery(sqliteconnection, "SELECT * FROM Players WHERE LEVEL < " #MAX_ADMIN_LEVELS " AND LEVEL > 0 ORDER BY Level DESC");
	if (DB_GetRowCount(res) == 0)
		return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, "All Server Admins", "No admins found...", "Ok", "");

	DynDialog_AddItem(playerid, -1, "Nickname\tAdmin level\tLast seen (dd/MM/yyyy)");
	do {
		new oneAdmin[MAX_PLAYER_NAME];
		DB_GetFieldStringByName(res, "Name", oneAdmin);
		new oneAdminLevel = DB_GetFieldIntByName(res, "Level");
		new oneAdminDay = DB_GetFieldIntByName(res, "LastSeen_Day");
		new oneAdminMonth = DB_GetFieldIntByName(res, "LastSeen_Month");
		new oneAdminYear = DB_GetFieldIntByName(res, "LastSeen_Year");
		new day, month, year;
		getdate(year, month, day);
		if (day == oneAdminDay && month == oneAdminMonth && year == oneAdminYear)
			DynDialog_AddItem(playerid, -1, "{FFFFFF}%s\t{FF3333}%d\t{FFFFFF}today", oneAdmin, oneAdminLevel);
		else
			DynDialog_AddItem(playerid, -1, "{FFFFFF}%s\t{FF3333}%d\t{FFFFFF}%02d/%02d/%d", oneAdmin, oneAdminLevel, oneAdminDay, oneAdminMonth, oneAdminYear);
	}
	while (DB_SelectNextRow(res));
	DB_FreeResultSet(res);
	DynDialog_Show(playerid, using inline dialog_response, DIALOG_STYLE_TABLIST_HEADERS, "All Server Admins", "Ok", .items_per_page = 15);
	return 1;
}


