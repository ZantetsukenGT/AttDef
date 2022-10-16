#if defined _attdef_cmd_add
	#endinput
#endif
#define _attdef_cmd_add

YCMD: add(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "add a specific player to the round.");

	new targetid;
	if (sscanf(params, "r", targetid))
		return SendUsageMessage(playerid, "/add [Player Name/ID]");

	PerformCommandAdd(playerid, targetid);
	return 1;
}

PerformCommandAdd(playerid, targetid)
{
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");

	if (targetid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player is not connected.");
	if (Player[targetid][Playing])
		return SendErrorMessage(playerid, "That player is already playing.");
	if (Player[targetid][InDuel])
		return SendErrorMessage(playerid, "That player is in a duel.");
	if (Player[targetid][Team] != ATTACKER && Player[targetid][Team] != DEFENDER && Player[targetid][Team] != REFEREE)
		return SendErrorMessage(playerid, "That player must be part of one of the following teams: Attacker, Defender or Referee.");

	if (Player[targetid][Spectating])
		StopSpectate(targetid); //no more need to ask players to do /specoff in order to add them
	if (GameType == BASE)
		AddPlayerToBase(targetid);
	else if (GameType == ARENA)
		AddPlayerToArena(targetid);

	LogAdminCommand("add", playerid, targetid);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has added {FFFFFF}%s " COL_PRIM "to the round.", Player[playerid][Name], Player[targetid][Name]);
}
