#if defined _attdef_cmd_fightstyle
	#endinput
#endif
#define _attdef_cmd_fightstyle

YCMD: fightstyle(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your fighting style.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/fightstyle [ 0 (Normal) | 1 (Boxing) | 2 (KungFu) | 3 (Knee-head) | 4 (Grab-kick) | 5 (Elbow-kick) ]");

	new fsID = strval(params);
	if (fsID < 0 || fsID > 5)
		return SendErrorMessage(playerid, "Invalid FightStyle ID (From 0 to 5 are valid)");

	Player[playerid][FightStyle] = FightStyleIDs[fsID];
	SetPlayerFightingStyle(playerid, Player[playerid][FightStyle]);

	new iString[128];
	format(iString, sizeof(iString), "UPDATE `Players` SET `FightStyle` = '%d' WHERE `Name` = '%q'", Player[playerid][FightStyle], Player[playerid][Name]);
	db_free_result(db_query(sqliteconnection, iString));

	return SendClientMessage(playerid, -1, va_return(COL_PRIM "FightStyle changed to: {FFFFFF}%s", FightStyleNames[fsID]));
}
