#if defined _attdef_cmd_setlevel
	#endinput
#endif
#define _attdef_cmd_setlevel

YCMD: setlevel(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 5 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be level 5 or rcon admin.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "change the level of a player.");

	new GiveID, NewLevel;
	if (sscanf(params, "id", GiveID, NewLevel))
		return SendUsageMessage(playerid, "/setlevel [Player ID] [Level]");
	if (!IsPlayerConnected(GiveID))
		return SendErrorMessage(playerid, "That player is not connected.");
	if (!Player[GiveID][Logged])
		return SendErrorMessage(playerid, "That player is not logged in.");
	if (NewLevel < 0 || NewLevel >= MAX_ADMIN_LEVELS)
		return SendErrorMessage(playerid, "Invalid level.");
	if (Player[GiveID][Level] == NewLevel)
		return SendErrorMessage(playerid, "That player is already this level.");

	if (Player[GiveID][Level] == 0) // Previous level was 0. This means it's a new admin. Guide them.
		SendClientMessage(GiveID, -1, COL_PRIM "Looks like you're a new admin. Type {FFFFFF}/acmds " COL_PRIM " to see a list of admin commands!");

	new iString[128];
	format(iString, sizeof(iString), "UPDATE Players SET Level = %d WHERE Name = '%q'", NewLevel, Player[GiveID][Name]);
	db_free_result(db_query(sqliteconnection, iString));

	Player[GiveID][Level] = NewLevel;
	UpdatePlayerAdminGroup(GiveID);

	LogAdminCommand("setlevel", playerid, GiveID);

	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has set {FFFFFF}%s's " COL_PRIM "level to: {FFFFFF}%d", Player[playerid][Name], Player[GiveID][Name], NewLevel);
	return SendClientMessageToAll(-1, iString);
}
