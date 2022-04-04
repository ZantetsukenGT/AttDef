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
	if (!IsNumeric(params))
		return SendErrorMessage(playerid, "You need to put a number for weather id.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/time [Hour]");

	new mytime = strval(params);
	if (mytime < 0 || mytime > TimeLimit)
		return SendErrorMessage(playerid, "Invalid time.");

	SetPlayerTime(playerid, mytime, 0);
	Player[playerid][Time] = mytime;

	new iString[128];
	format(iString, sizeof(iString), "UPDATE Players SET Time = %d WHERE Name = '%q'", mytime, Player[playerid][Name]);
	db_free_result(db_query(sqliteconnection, iString));

	format(iString, sizeof(iString), "{FFFFFF}Time changed to: %d", mytime);
	return SendClientMessage(playerid, -1, iString);
}
