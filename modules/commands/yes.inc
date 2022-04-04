#if defined _attdef_cmd_yes
	#endinput
#endif
#define _attdef_cmd_yes

YCMD: yes(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "accept a duel request.");

	new pID = Player[playerid][challengerid];
	if (Player[playerid][challengerid] == -1)
		return SendErrorMessage(playerid, "No one has invited you to a duel.");
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (Player[pID][Playing])
		return SendErrorMessage(playerid, "That player is in a round.");
	if (Player[pID][InDuel])
		return SendErrorMessage(playerid, "That player is already dueling someone else.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "You can't duel while being in a round.");

	StartDuel(
		pID, playerid, Player[playerid][duelweap1], Player[playerid][duelweap2], Player[playerid][Duel_X], Player[playerid][Duel_Y], Player[playerid][Duel_Size],
		Player[playerid][Duel_Interior]);

	new iString[128];
	format(
		iString, sizeof(iString), "%s%s {FFFFFF}accepted the duel challenge by %s%s", TextColor[Player[playerid][Team]], Player[playerid][Name], TextColor[Player[pID][Team]],
		Player[pID][Name]);
	return SendClientMessageToAll(-1, iString);
}
