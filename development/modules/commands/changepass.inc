#if defined _attdef_cmd_changepass
	#endinput
#endif
#define _attdef_cmd_changepass

forward InlineChangePass(playerid, dialogid, response, listitem, string: inputtext[]);
forward OnChangePassHash(playerid);

YCMD: changepass(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your user account password.");
	if (!Player[playerid][Logged])
		return SendErrorMessage(playerid, "You must be logged in.");

	Dialog_ShowCallback(
		playerid, using public InlineChangePass<iiiis>, DIALOG_STYLE_PASSWORD, "{FFFFFF}Password Change Dialog", "{FFFFFF}Type your new password below:",
		"Modify", "Cancel");
	return 1;
}

public InlineChangePass(playerid, dialogid, response, listitem, string: inputtext[])
{
#pragma unused dialogid, listitem
	if (!response)
		return 1;
	if (isnull(inputtext))
	{
		Dialog_ShowCallback(
			playerid, using public InlineChangePass<iiiis>, DIALOG_STYLE_PASSWORD, "{FFFFFF}Password Change Dialog", "{FFFFFF}Type your new password below:",
			"Modify", "Cancel");
		return 1;
	}

	bcrypt_hash(playerid, "OnChangePassHash", inputtext, BCRYPT_COST);
	return 1;
}

public OnChangePassHash(playerid)
{
	new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);
	DB_FreeResultSet(DB_ExecuteQuery(sqliteconnection, va_return("UPDATE Players SET Password = '%q' WHERE Name = '%q'", dest, Player[playerid][Name])));
	SendClientMessage(playerid, -1, "Your password has been changed.");
	return 1;
}
