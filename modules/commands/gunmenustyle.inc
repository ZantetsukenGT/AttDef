#if defined _attdef_cmd_gunmenustyle
	#endinput
#endif
#define _attdef_cmd_gunmenustyle

YCMD: gunmenustyle(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your gunmenu style.");
	if (Player[playerid][OnGunmenu])
		return SendErrorMessage(playerid, "You cannot change style while selecting from gunmenu.");

	new styleStr[7];
	if (sscanf(params, "s[7]", styleStr))
		return SendUsageMessage(playerid, "/gunmenustyle [dialog / object]");

	new style;
	switch (YHash(styleStr, false))
	{
		case _I<dialog>: style = GUNMENU_STYLE_DIALOG;
		case _I<object>: style = GUNMENU_STYLE_OBJECT;
		default: return SendUsageMessage(playerid, "/gunmenustyle [dialog / object]");
	}

	Player[playerid][GunmenuStyle] = style;
	db_free_result(db_query(sqliteconnection, va_return("UPDATE Players SET GunmenuStyle = %d WHERE Name = '%q'", style, Player[playerid][Name])));
	return SendClientMessage(playerid, -1, va_return("Changed gunmenu style to: %s", styleStr));
}
