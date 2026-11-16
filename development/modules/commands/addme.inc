#if defined _attdef_cmd_addme
	#endinput
#endif
#define _attdef_cmd_addme

YCMD: addme(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "add yourself to the round.");
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");
	if (Player[playerid][Team] != ATTACKER && Player[playerid][Team] != DEFENDER)
		return SendErrorMessage(playerid, "You must be either in attacker or defender team");
	if (WarMode)
		return SendErrorMessage(playerid, "Cannot do this when match mode is enabled.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "You're already playing.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "You cannot use this command while in a duel.");
	if (ElapsedTime > 30)
		return SendErrorMessage(playerid, "It's late. You cannot add yourself now.");

	Player[playerid][Team] = GetTeamWithLessPlayers();
	SwitchTeamFix(playerid, false, false);

	if (Player[playerid][Spectating])
		StopSpectate(playerid);
	if (GameType == BASE)
		AddPlayerToBase(playerid);
	else if (GameType == ARENA)
		AddPlayerToArena(playerid);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has added himself to the round {FFFFFF}(/addme)" COL_PRIM ".", Player[playerid][Name]);
}
