#if defined _attdef_cmd_time
	#endinput
#endif
#define _attdef_cmd_time

YCMD: time(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your day time.");
	if (!Player[playerid][Logged])
		return SendErrorMessage(playerid, "You need to log in.");
	new mytime;
	if (sscanf(params, "i", mytime))
		return SendUsageMessage(playerid, "/time [Hour]");

	mytime = clamp(mytime, 0, TimeLimit);

	SetPlayerTime(playerid, mytime, 0);
	Player[playerid][Time] = mytime;

	db_free_result(db_query(sqliteconnection, va_return("UPDATE Players SET Time = %d WHERE Name = '%q'", mytime, Player[playerid][Name])));

	return va_SendClientMessage(playerid, -1, "Time changed to: %d", mytime);
}
