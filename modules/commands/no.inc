#if defined _attdef_cmd_no
	#endinput
#endif
#define _attdef_cmd_no

YCMD: no(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "deny a duel request.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "You are in a duel anyway");

	new pID = Player[playerid][challengerid];
	if (Player[playerid][challengerid] == -1)
		return SendErrorMessage(playerid, "No one has invited you to a duel.");
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isn't connected.");

	Player[playerid][challengerid] = -1;

	va_SendClientMessageToAll(-1, "%s%s {FFFFFF}denied the duel challenge by %s%s", TextColor[Player[playerid][Team]], Player[playerid][Name], TextColor[Player[pID][Team]],
		Player[pID][Name]);
	return 1;
}
