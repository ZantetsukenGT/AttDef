#if defined _attdef_cmd_fightstyle
	#endinput
#endif
#define _attdef_cmd_fightstyle

YCMD: fightstyle(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your fighting style.");
	new fsID;
	if (sscanf(params, "i", fsID))
		return SendUsageMessage(playerid, "/fightstyle [ 0 (Normal) | 1 (Boxing) | 2 (KungFu) | 3 (Knee-head) | 4 (Grab-kick) | 5 (Elbow-kick) ]");
	if (fsID < 0 || fsID > 5)
		return SendErrorMessage(playerid, "Invalid FightStyle ID (From 0 to 5 are valid)");

	Player[playerid][FightStyle] = FightStyleIDs[fsID];
	SetPlayerFightingStyle(playerid, Player[playerid][FightStyle]);

	new iString[144];
	format(iString, sizeof(iString), "UPDATE `Players` SET `FightStyle` = '%d' WHERE `Name` = '%q'", Player[playerid][FightStyle], Player[playerid][Name]);
	db_free_result(db_query(sqliteconnection, iString));

	return va_SendClientMessage(playerid, -1, COL_PRIM "FightStyle changed to: {FFFFFF}%s", FightStyleNames[fsID]);
}
