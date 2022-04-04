#if defined _attdef_cmd_connstats
	#endinput
#endif
#define _attdef_cmd_connstats

YCMD: connstats(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 3 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher level admin to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "fetch connection statistics of a player.");

	new pID = INVALID_PLAYER_ID;
	if (sscanf(params, "d", pID))
		return SendUsageMessage(playerid, "/connStats <playerid>");
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "** Invalid PlayerID! ");

	new szString[80];
	format(szString, sizeof(szString), "(%d)%s's current connection status: %i.", pID, Player[pID][Name], NetStats_ConnectionStatus(pID));
	return SendClientMessage(playerid, -1, szString);
}
