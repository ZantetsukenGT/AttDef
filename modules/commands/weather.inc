#if defined _attdef_cmd_weather
	#endinput
#endif
#define _attdef_cmd_weather

YCMD: weather(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your weather.");
	new myweather;
	if (sscanf(params, "i", myweather))
		return SendUsageMessage(playerid, "/weather [ID]");

	if (myweather < 0 || myweather > WeatherLimit)
		return SendErrorMessage(playerid, "Invalid weather ID.");

	SetPlayerWeather(playerid, myweather);
	Player[playerid][Weather] = myweather;

	db_free_result(db_query(sqliteconnection, va_return("UPDATE Players SET Weather = %d WHERE Name = '%q'", myweather, Player[playerid][Name])));

	return va_SendClientMessage(playerid, -1, "Weather changed to: %d", myweather);
}
