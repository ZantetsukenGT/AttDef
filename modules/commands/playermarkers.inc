#if defined _attdef_cmd_playermarkers
	#endinput
#endif
#define _attdef_cmd_playermarkers

YCMD: playermarkers(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "an option to switch the color of the player markers on your radar");
	Player[playerid][PlayerMarkers] = !Player[playerid][PlayerMarkers];
	foreach (new i : Player)
	{
		CallLocalFunction("OnPlayerStreamIn", "ii", i, playerid);
	}
	db_free_result(db_query(sqliteconnection, va_return("UPDATE `Players` SET `PlayerMarkers` = '%d' WHERE `Name` = '%q'", Player[playerid][PlayerMarkers], Player[playerid][Name])));
	if (Player[playerid][PlayerMarkers])
		return SendClientMessage(playerid, -1, "Changed player markers setting: each player has a unique marker color on radar now.");
	return SendClientMessage(playerid, -1, "Changed player markers setting: you will now see marker color based on team color.");
}
