#if defined _attdef_cmd_alladmins
	#endinput
#endif
#define _attdef_cmd_alladmins

YCMD: alladmins(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display a list of all server admins (offline and online).");

	new DBResult: res = db_query(sqliteconnection, "SELECT * FROM Players WHERE LEVEL < " #MAX_ADMIN_LEVELS " AND LEVEL > 0 ORDER BY Level DESC");
	if (db_num_rows(res) == 0)
		return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, "All Server Admins", "No admins found...", "Ok", "");

	AddDialogListitem(playerid, "Nickname\tAdmin level\tLast seen (dd/MM/yyyy)");
	do {
		new oneAdmin[MAX_PLAYER_NAME];
		db_get_field_assoc(res, "Name", oneAdmin);
		new oneAdminLevel = db_get_field_assoc_int(res, "Level");
		new oneAdminDay = db_get_field_assoc_int(res, "LastSeen_Day");
		new oneAdminMonth = db_get_field_assoc_int(res, "LastSeen_Month");
		new oneAdminYear = db_get_field_assoc_int(res, "LastSeen_Year");
		new day, month, year;
		getdate(year, month, day);
		if (day == oneAdminDay && month == oneAdminMonth && year == oneAdminYear)
			AddDialogListitem(playerid, "{FFFFFF}%s\t{FF3333}%d\t{FFFFFF}today", oneAdmin, oneAdminLevel);
		else
			AddDialogListitem(playerid, "{FFFFFF}%s\t{FF3333}%d\t{FFFFFF}%02d/%02d/%d", oneAdmin, oneAdminLevel, oneAdminDay, oneAdminMonth, oneAdminYear);
	}
	while (db_next_row(res));
	db_free_result(res);
	ShowPlayerDialogPages(playerid, #ShowNoResponseDialog, DIALOG_STYLE_TABLIST_HEADERS, "All Server Admins", "Ok", "", 15);
	return 1;
}


