#if defined _attdef_cmd_gamespeed
	#endinput
#endif
#define _attdef_cmd_gamespeed

YCMD: gamespeed(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change game speed (round timer and cp timer)");
	new speed;
	if (sscanf(params, "i", speed))
	{
		SendUsageMessage(playerid, va_return("/gamespeed [Time in milliseconds, " COL_PRIM "current: " COL_USAGE "%d{FFFFFF}]", GAME_SPEED));
		SendClientMessage(playerid, -1, "Note: this changes the speed (time per lap) of round timer and CP timer.");
		return SendClientMessage(playerid, -1, "Note: default value is 1000 milliseconds.");
	}
	if (speed < 500)
		return SendErrorMessage(playerid, "Speed can not be less than 500 milliseconds");

	new speedStr[12];
	if (speed == 1000)
		strcat(speedStr, "Default");
	else if (speed >= 500 && speed < 750)
		strcat(speedStr, "Very fast");
	else if (speed >= 750 && speed < 1000)
		strcat(speedStr, "Faster");
	else if (speed > 1000 && speed < 1100)
		strcat(speedStr, "Slower");
	else
		strcat(speedStr, "Very Slow");

	db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'GameSpeed'", speed)));

	GAME_SPEED = speed;
	RestartGameLoop();
	return va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has changed game speed to %d {FFFFFF}(%s)", Player[playerid][Name], speed, speedStr);
}
