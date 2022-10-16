#if defined _attdef_cmd_limit
	#endinput
#endif
#define _attdef_cmd_limit

YCMD: limit(playerid, params[], help)
{
	//if(Player[playerid][Level] < 3 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be level 5 or rcon admin.");
	if (help)
		return SendCommandHelpMessage(playerid, "set a limit for weather and time.");

	new Command[8], aLimit, CommandID, iString[144];
	if (sscanf(params, "s[8]d", Command, aLimit))
		return SendUsageMessage(playerid, "/limit [weather | time] [Limit]");

	switch (YHash(Command, false))
	{
		case _I<weather>: CommandID = 1;
		case _I<time>: CommandID = 2;
		default: return SendUsageMessage(playerid, "/limit [weather | time] [Limit]");
	}

	if (aLimit < 10 || aLimit > 9999)
		return SendErrorMessage(playerid, "Invalid limit.");

	switch (CommandID)
	{
		case 1:
		{
			WeatherLimit = aLimit;

			foreach (new i : Player)
			{
				if (Player[i][Weather] > WeatherLimit)
				{
					Player[i][Weather] = 0;
					SetPlayerWeather(i, Player[i][Weather]);

					format(iString, sizeof(iString), "UPDATE Players SET Weather = %d WHERE Name = '%q'", Player[i][Weather], Player[i][Name]);
					db_free_result(db_query(sqliteconnection, iString));
				}
			}

			format(iString, sizeof(iString), "%s " COL_PRIM "has changed {FFFFFF}weather limit " COL_PRIM "to: {FFFFFF}%d" COL_PRIM ".", Player[playerid][Name], WeatherLimit);
		}
		case 2:
		{
			TimeLimit = aLimit;

			foreach (new i : Player)
			{
				if (Player[i][Time] > TimeLimit)
				{
					Player[i][Time] = 12;
					SetPlayerTime(playerid, Player[i][Time], 12);

					format(iString, sizeof(iString), "UPDATE Players SET Time = %d WHERE Name = '%q'", Player[i][Time], Player[i][Name]);
					db_free_result(db_query(sqliteconnection, iString));
				}
			}

			format(iString, sizeof(iString), "%s " COL_PRIM "has changed {FFFFFF}time limit " COL_PRIM "to: {FFFFFF}%d" COL_PRIM ".", Player[playerid][Name], TimeLimit);
		}
	}
	LogAdminCommand("limit", playerid, INVALID_PLAYER_ID);
	return SendClientMessageToAll(-1, iString);
}
