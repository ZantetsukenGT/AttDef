#if defined _attdef_cmd_weather
	#endinput
#endif
#define _attdef_cmd_weather

YCMD: weather(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your weather.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/weather [ID]");

	new myweather = strval(params);
	if (myweather < 0 || myweather > WeatherLimit)
		return SendErrorMessage(playerid, "Invalid weather ID.");

	SetPlayerWeather(playerid, myweather);
	Player[playerid][Weather] = myweather;

	new iString[128];
	format(iString, sizeof(iString), "UPDATE Players SET Weather = %d WHERE Name = '%q'", myweather, Player[playerid][Name]);
	db_free_result(db_query(sqliteconnection, iString));

	format(iString, sizeof(iString), "{FFFFFF}Weather changed to: %d", myweather);
	return SendClientMessage(playerid, -1, iString);
}
